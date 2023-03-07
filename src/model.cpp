#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>
#include <string>

#include "registry.h"
#include "model.h"
#include "modelChange.h"
#include "sbml/SBMLTypes.h"
#include "sbmlx.h"
#include "stringx.h"

using namespace std;
using namespace libsbml;
using namespace libsedml;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp

PHRASEDML_CPP_NAMESPACE_BEGIN
PhrasedModel::PhrasedModel(string id, string source, bool isFile)
  : Variable(id)
  , m_type(lang_XML)
  , m_source(source)
  , m_changes()
  , m_isFile(isFile)
  , m_sbml(3,1)
{
  processSource();
}

PhrasedModel::PhrasedModel(string id, string source, vector<ModelChange> changes, bool isFile)
  : Variable(id)
  , m_type(lang_XML)
  , m_source(source)
  , m_changes(changes)
  , m_isFile(isFile)
{
  processSource();
  for (size_t mc=0; mc<m_changes.size(); mc++) {
    m_changes[mc].setModel(id);
  }
}

PhrasedModel::PhrasedModel(SedModel* sedmodel, SedDocument* seddoc)
  : Variable(sedmodel)
  , m_type(lang_XML)
  , m_source(sedmodel->getSource())
  , m_changes()
  , m_isFile(true)
{
  m_type = getLanguageFromURI(sedmodel->getLanguage());
  SedModel* referenced = seddoc->getModel(m_source);
  if (referenced != NULL && referenced != sedmodel) {
    m_isFile = false;
  }
  else {
    processSource();
  }

  ostringstream stream;
  SBMLWriter sw;
  string sbml_source;
  if (getSBMLDocument()) {
    sw.writeSBML(getSBMLDocument(), stream);
    sbml_source = stream.str();

    for (unsigned int ch=0; ch<sedmodel->getNumChanges(); ch++) {
      SedChange* sc = sedmodel->getChange(ch);
      if (sc->getTarget().find("@id=''") != string::npos)
        continue;
      try {
        ModelChange mc(sc, seddoc, m_id, sbml_source, getSBMLDocument()->getNamespaces()->getURI(0));
        m_changes.push_back(mc);
        if (sc->getTypeCode() == SEDML_CHANGE_COMPUTECHANGE) {
          SedComputeChange* scc = static_cast<SedComputeChange*>(sc);
          for (unsigned int p=0; p<scc->getNumParameters(); p++) {
            ModelChange mc2(scc->getParameter(p));
            m_changes.push_back(mc2);
          }
        }
      } catch (const std::runtime_error& e) {
        g_registry.setError(std::string("Cannot make change for ") + sc->getTarget() + ": " + e.what(), 0);
      }
    }
  } else {
    if (sedmodel->getNumChanges() > 0)
      g_registry.setError("Cannot make changes without model source", 0);
  }
}

PhrasedModel::~PhrasedModel()
{
}

void PhrasedModel::setIsFile(bool quote)
{
  m_isFile = quote;
}

bool PhrasedModel::getIsFile() const
{
  return m_isFile;
}

language PhrasedModel::getType() const
{
  return m_type;
}

SBMLDocument* PhrasedModel::getSBMLDocument()
{
  if (!m_isFile && m_sbml.getModel()==NULL) {
    PhrasedModel* referencedModel = g_registry.getModel(m_source);
    if (referencedModel==NULL) {
      g_registry.setError("The model '" + m_id + "' references another SED-ML model '" + m_source + "', which does not exist.", 0);
      return NULL;
    }
    m_type = referencedModel->getType();
    SBMLDocument* doc = referencedModel->getSBMLDocument();
    if (doc==NULL) {
      return NULL;
    }
    m_sbml = *doc;
  }
  return &m_sbml;
}

string PhrasedModel::getPhraSEDML() const
{
  string ret = m_id;
  ret += " = model ";
  string source = m_source;
  if (m_isFile) {
    source = "\"" + source + "\"";
  }
  ret += source;
  for (size_t cl=0; cl<m_changes.size(); cl++) {
    if (cl==0) {
      ret += " with ";
    }
    else {
      ret += ", ";
    }
    ret += m_changes[cl].getPhraSEDML();
  }

  ret += "\n";
  return ret;
}

void PhrasedModel::addModelToSEDML(SedDocument* sedml) const
{
  SedModel* model = sedml->createModel();
  libsbml::XMLNamespaces* sednames = sedml->getNamespaces();
  libsbml::XMLNamespaces* libsbmlnames = m_sbml.getNamespaces();
  for (int i = 0; i < libsbmlnames->getNumNamespaces(); i++)
  {
      string prefix = libsbmlnames->getPrefix(i);
      if (prefix.empty())
      {
          prefix = "sbml";
      }
      sednames->add(libsbmlnames->getURI(i), prefix);
  }

  model->setId(m_id);
  model->setName(m_name);
  model->setSource(m_source);
  model->setLanguage(getURIFromLanguage(m_type));
  for (size_t cl=0; cl<m_changes.size(); cl++) {
    m_changes[cl].addModelChangeToSEDMLModel(model);
  }
  //Now we need to create local variables for any ComputeChanges:
  for (unsigned int c=0; c<model->getNumChanges(); c++) {
    SedChange* sc = model->getChange(c);
    if (sc->getTypeCode() == SEDML_CHANGE_COMPUTECHANGE) {
      SedComputeChange* scc = static_cast<SedComputeChange*>(sc);
      addLocalVariablesToComputeChange(scc, model);
    }
  }
}

void PhrasedModel::addLocalVariablesToComputeChange(SedComputeChange* scc, SedModel* model) const
{
  ASTNode* astn = const_cast<ASTNode*>(scc->getMath());
  set<string> vars;
  getVariablesFromASTNode(astn, vars);
  for (set<string>::iterator v=vars.begin(); v != vars.end(); v++) {
    vector<string> idvec;
    idvec.push_back(*v);
    string xpath = getElementXPathFromId(&idvec, getSBMLDocument());
    if (xpath.empty()) {
      //We need a local variable for it.  Check to see if one exists:
      SedParameter* sp = scc->createParameter();
      sp->setId(*v);
      for (size_t c=0; c<m_changes.size(); c++) {
        const ModelChange* mc = &m_changes[c];
        vector<string> varname = mc->getVariable();
        if (mc->getType() == ctype_val_assignment && varname.size() && varname[0] == "local" && varname[1] == *v) {
          //It actually exists!
          sp->setValue(mc->getValues()[0]);
          continue;
        }
      }
    }
    else {
      SedVariable* sv = scc->createVariable();
      sv->setModelReference(m_id);
      sv->setTarget(xpath);
      sv->setId(*v);
    }
  }
}

void PhrasedModel::processSource()
{
  if (m_isFile) {
    SBMLDocument* doc = g_registry.getSavedSBML(m_source);
    if (doc == NULL) {
      string actualsource = g_registry.getWorkingFilename(m_source);
      if (actualsource.empty()) {
        //The file cannot be found, so we'll have to punt
        return;
      }
      doc = readSBMLFromFile(actualsource.c_str());
    }
    m_sbml = *doc;
    m_type = lang_SBML; //In case the levels/versions below don't work.
    switch(m_sbml.getLevel()) {
    case 1:
      switch(m_sbml.getVersion()) {
      case 1:
        m_type = lang_SBMLl1v1;
        break;
      case 2:
        m_type = lang_SBMLl1v2;
        break;
      }
      break;
    case 2:
      switch(m_sbml.getVersion()) {
      case 1:
        m_type = lang_SBMLl2v1;
        break;
      case 2:
        m_type = lang_SBMLl2v2;
        break;
      case 3:
        m_type = lang_SBMLl2v3;
        break;
      case 4:
        m_type = lang_SBMLl2v4;
        break;
      case 5:
        m_type = lang_SBMLl2v5;
        break;
      }
      break;
    case 3:
      switch(m_sbml.getVersion()) {
      case 1:
        m_type = lang_SBMLl3v1;
        break;
      case 2:
        m_type = lang_SBMLl3v2;
        break;
      }
      break;
    }
    if (doc->getNumErrors(LIBSBML_SEV_ERROR) != 0 || doc->getNumErrors(LIBSBML_SEV_FATAL) != 0) {
      g_registry.addWarning("The SBML model '" + m_source + "' has one or more validation errors, and may not be simulatable on all systems.");
    }
  }
  //If the referenced model is another SEDML construct, we'll have to process it later.
}

language PhrasedModel::getLanguageFromURI(string uri) const
{
  if (uri == "urn:sedml:language:xml") {
    return lang_XML;
  } else if (uri == "urn:sedml:language:sbml") {
    return lang_SBML;
  } else if (uri == "urn:sedml:language:cellml") {
    return lang_CellML;
  } else if (uri == "urn:sedml:language:sbml.level-1.version-1") {
    return lang_SBMLl1v1;
  } else if (uri == "urn:sedml:language:sbml.level-1.version-2") {
    return lang_SBMLl1v2;
  } else if (uri == "urn:sedml:language:sbml.level-2.version-1") {
    return lang_SBMLl2v1;
  } else if (uri == "urn:sedml:language:sbml.level-2.version-2") {
    return lang_SBMLl2v2;
  } else if (uri == "urn:sedml:language:sbml.level-2.version-3") {
    return lang_SBMLl2v3;
  } else if (uri == "urn:sedml:language:sbml.level-2.version-4") {
    return lang_SBMLl2v4;
  } else if (uri == "urn:sedml:language:sbml.level-2.version-5") {
    return lang_SBMLl2v5;
  } else if (uri == "urn:sedml:language:sbml.level-3.version-1") {
    return lang_SBMLl3v1;
  } else if (uri == "urn:sedml:language:sbml.level-3.version-2") {
    return lang_SBMLl3v2;
  } else if (uri == "urn:sedml:language:cellml_1.0") {
    return lang_CellML1_0;
  } else if (uri == "urn:sedml:language:cellml_1.1") {
    return lang_CellML1_1;
  } else if (uri == "urn:sedml:language:cellml_1.2") {
    return lang_CellML1_2;
  }
  return lang_XML;
}

std::string PhrasedModel::getURIFromLanguage(language lang) const
{
  switch(lang)
  {
  case lang_XML:
    return "urn:sedml:language:xml";
  case lang_SBML:
    return "urn:sedml:language:sbml";
  case lang_CellML:
    return "urn:sedml:language:cellml";
  case lang_SBMLl1v1:
    return "urn:sedml:language:sbml.level-1.version-1";
  case lang_SBMLl1v2:
    return "urn:sedml:language:sbml.level-1.version-2";
  case lang_SBMLl2v1:
    return "urn:sedml:language:sbml.level-2.version-1";
  case lang_SBMLl2v2:
    return "urn:sedml:language:sbml.level-2.version-2";
  case lang_SBMLl2v3:
    return "urn:sedml:language:sbml.level-2.version-3";
  case lang_SBMLl2v4:
    return "urn:sedml:language:sbml.level-2.version-4";
  case lang_SBMLl2v5:
    return "urn:sedml:language:sbml.level-2.version-5";
  case lang_SBMLl3v1:
    return "urn:sedml:language:sbml.level-3.version-1";
  case lang_SBMLl3v2:
    return "urn:sedml:language:sbml.level-3.version-2";
  case lang_CellML1_0:
    return "urn:sedml:language:cellml_1.0";
  case lang_CellML1_1:
    return "urn:sedml:language:cellml_1.0";
  case lang_CellML1_2:
    return "urn:sedml:language:cellml_1.2";
  }
  assert(false); //uncaught enum
  return "urn:sedml:language:xml";
}

bool PhrasedModel::changeListIsInappropriate(stringstream& err)
{
  for (size_t c=0; c<m_changes.size(); c++) {
    switch (m_changes[c].getType()) {
    case ctype_val_assignment:
    case ctype_formula_assignment:
      break;
    case ctype_loop_uniformLinear:
    case ctype_loop_uniformLog:
    case ctype_loop_vector:
    case ctype_loop_functional:
      err << "The model change '" << m_changes[c].getPhraSEDML() << "' is not the type of change that can be used on a single model.  These changes must be used in repeated tasks, instead.";
      return true;
    }
  }
  return false;
}

bool PhrasedModel::finalize()
{
  if (Variable::finalize()) {
    return true;
  }

  if (m_isFile) {
    if (m_sbml.getModel() == NULL) {
      g_registry.setError("Unable to find model '" + m_source + "', preventing phraSED-ML from creating accurate SED-ML constructs.  Try changing the working directory with 'setWorkingDirectory', or set the model directly with 'setReferencedSBML'.", 0);
      return true;
    }
  }
  else {
    SBMLDocument* docref = getSBMLDocument();
    if (docref==NULL) {
      //Error was already set.
      return true;
    }
  }
  for (size_t c=0; c<m_changes.size(); c++) {
    if (m_changes[c].finalize()) {
      return true;
    }
  }
  return false;
}

PHRASEDML_CPP_NAMESPACE_END
