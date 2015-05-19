#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "registry.h"
#include "model.h"
#include "modelChange.h"
#include "sbml\SBMLTypes.h"

using namespace std;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp

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
  for (unsigned int ch=0; ch<sedmodel->getNumChanges(); ch++) {
    ModelChange mc(sedmodel->getChange(ch), seddoc, m_id);
    m_changes.push_back(mc);
  }
}

PhrasedModel::~PhrasedModel()
{
}

void PhrasedModel::setIsFile(bool quote)
{
  m_isFile = quote;
}

bool PhrasedModel::getIsFile()
{
  return m_isFile;
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
  model->setId(m_id);
  model->setName(m_name);
  model->setSource(m_source);
  model->setLanguage(getURIFromLanguage(m_type));
  for (size_t cl=0; cl<m_changes.size(); cl++) {
    m_changes[cl].addModelChangeToSEDML(model);
  }
}

void PhrasedModel::processSource()
{
  if (m_isFile) {
    string actualsource = g_registry.getWorkingFilename(m_source);
    if (actualsource.empty()) {
      //The file cannot be found, so we'll have to punt
      return;
    }
    SBMLDocument* doc = readSBMLFromFile(actualsource.c_str());
    if (doc->getNumErrors(LIBSBML_SEV_ERROR) == 0 && doc->getNumErrors(LIBSBML_SEV_FATAL) == 0) {
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

bool PhrasedModel::check() const
{
  if (Variable::check()) {
    return true;
  }
  if (m_sbml.getModel() == NULL) {
    g_registry.addWarning("Unable to find model '" + m_source + "'.  Some constructs may be incorrectly formed as a result.");
  }
  for (size_t c=0; c<m_changes.size(); c++) {
    if (m_changes[c].check()) {
      return true;
    }
  }
  return false;
}
