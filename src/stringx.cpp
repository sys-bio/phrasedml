#include <sstream>
#include <assert.h>
#include <iostream>
#include "stringx.h"
#include "registry.h"
#include "sbml/SBMLDocument.h"
#include "model.h"

#ifdef PHRASEDML_ENABLE_XPATH_EVAL
  #include <libxml/parser.h>
  #include <libxml/xpath.h>
  #include <libxml/xpathInternals.h>
#endif

using namespace std;
using namespace libsbml;

extern bool CaselessStrCmp(const string& lhs, const string& rhs);

PHRASEDML_CPP_NAMESPACE_BEGIN

string stripExt(const string& path)
{
  // if it's a urn, leave it alone
  if (path.find("urn:") != std::string::npos) {
    return path;
  }
  std::size_t loc = path.rfind(".");
  if (loc != std::string::npos)
    return path.substr(0,loc);
  else
    return path;
}

string normalizeModelPath(const string& path)
{
  if (path.substr(0,2) == "./")
    return stripExt(path.substr(2));
  else
    return stripExt(path);
}

string SizeTToString(size_t number)
{
  ostringstream ostr;
  ostr << number;
  return ostr.str();
}

string DoubleToString(double number)
{
  ostringstream ostr;
  ostr << number;
  return ostr.str();
}

string getStringFrom(const vector<const string*>* name, string cc)
{
  string retval = "";
  for (size_t nn=0; nn<name->size(); nn++) {
    if (nn>0) {
      retval += cc;
    }
    retval += *(*name)[nn];
  }
  return retval;
}

string getStringFrom(const vector<string>* name, string cc)
{
  string retval = "";
  for (size_t nn=0; nn<name->size(); nn++) {
    if (nn>0) {
      retval += cc;
    }
    retval += (*name)[nn];
  }
  return retval;
}

string getStringFrom(const vector<double>& numbers)
{
  stringstream ret;
  for (size_t nn=0; nn<numbers.size(); nn++) {
    if (nn>0) {
      ret << ", ";
    }
    ret << numbers[nn];
  }
  return ret.str();
}

vector<string> getStringVecFromDelimitedString(const string& var, string delimiter)
{
  vector<string> ret;
  size_t begin = 0;
  size_t end = var.find(delimiter);
  while (end != string::npos) {
    string substr = var.substr(begin, end-begin);
    ret.push_back(substr);
    begin = end+5;
    end = var.find(delimiter, begin);
  }
  string substr = var.substr(begin, end);
  ret.push_back(substr);
  return ret;
}

string xpathToNode(const string& xpath) {
  {
    string selector = "/@value";
    if (xpath.rfind(selector) == xpath.size() - selector.size())
      return xpath.substr(0, xpath.size() - selector.size());
  }
  {
    string selector = "/@initialConcentration";
    if (xpath.rfind(selector) == xpath.size() - selector.size())
      return xpath.substr(0, xpath.size() - selector.size());
  }
  return xpath;
}

// does the xpath have "@value" on the end?
bool isValueSelector(const string& xpath) {
  string selector = "/@value";
  if (xpath.rfind(selector) == xpath.size() - selector.size())
    return true;
  else
    return false;
}

// does the xpath have "@initialConcentration" on the end?
bool isInitialConcentrationSelector(const string& xpath) {
  string selector = "/@initialConcentration";
  if (xpath.rfind(selector) == xpath.size() - selector.size())
    return true;
  else
    return false;
}

#ifdef PHRASEDML_ENABLE_XPATH_EVAL
vector<string> getIdFromXPathExtended(const string& xpath_, const string& source_doc, const std::string& sbml_ns)
{
  string xpath = xpathToNode(xpath_);
  vector<string> ret;
  xmlDocPtr doc;
  doc = xmlParseDoc((const xmlChar*)source_doc.c_str());
  if (doc == NULL ) {
    // error
    return ret;
  }

  xmlXPathContextPtr context;
  xmlXPathObjectPtr result;

  context = xmlXPathNewContext(doc);
  if (context == NULL) {
    return ret;
  }
  xmlXPathRegisterNs(context, (const xmlChar*)"sbml", (const xmlChar*)sbml_ns.c_str());

  result = xmlXPathEvalExpression((const xmlChar*)xpathToNode(xpath).c_str(), context);
  xmlXPathFreeContext(context);
  if (result == NULL) {
    return ret;
  }

  if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
    xmlXPathFreeObject(result);
    return ret;
  }

  xmlNodeSetPtr nodeset;
  nodeset = result->nodesetval;
  for (int i=0; i < nodeset->nodeNr; i++) {
    xmlNode* np = nodeset->nodeTab[i];
    xmlChar* id = xmlGetProp(np, (const xmlChar*)"id");
    if (!id) {
      np = np->parent;
      id = xmlGetProp(np, (const xmlChar*)"id");
      if (!id) {
        throw std::runtime_error("Cannot evaluate xpath " + xpath_);
      }
    }
    ret.push_back(string((char*)id));
  }
  xmlXPathFreeObject (result);
  xmlFreeDoc(doc);

  return ret;
}
#endif


vector<string> getIdFromXPath(const string& xpath)
{
  vector<string> ret;
  size_t atid = xpath.find("[@id=");
  size_t idend = xpath.find("]", atid);
  while (atid != string::npos) {
    string name = xpath;
    name = name.substr(atid+6, idend-atid-7);
    ret.push_back(name);
    atid = xpath.find("[@id=", idend);
    idend = xpath.find("]", atid);
  }
  return ret;
}

string getValueXPathFromId(const vector<string>* id, const SBMLDocument* doc)
{
  if (id == NULL || id->size()==0) {
    g_registry.setError("The ID of the model element is missing entirely.", 0);
    return "";
  }
  string lastid = (*id)[id->size()-1];
  SBMLDocument* vdoc = const_cast<SBMLDocument*>(doc);
  const SBase* ref = vdoc->getElementBySId(lastid);
  if (ref==NULL) {
    g_registry.setError("No such id in SBML document: '" + getStringFrom(id, ".") + "'.", 0);
    return "";
  }
  const SBase* parent = ref;
  for (size_t n = id->size()-1; n != 0; n--) {
    string parentid = (*id)[n-1];
    bool foundparent = false;
    parent = ref->getParentSBMLObject();
    while (parent != NULL && parent->getTypeCode() != SBML_DOCUMENT) {
      if (parent->getId() == parentid) {
        foundparent = true;
        parent = NULL;
      }
      else {
        parent = parent->getParentSBMLObject();
      }
    }
    if (!foundparent) {
      g_registry.setError("No such id in SBML document: '" + getStringFrom(id, ".") + "'.", 0);
      return "";
    }
  }
  const Species* species;
  string ret = "/sbml:sbml/sbml:model/";
  switch(ref->getTypeCode()) {
  case SBML_SPECIES:
    ret += "sbml:listOfSpecies/sbml:species[@id='" + lastid + "']/@";
    species = static_cast<const Species*>(ref);
    if (species->isSetInitialAmount()) {
      ret += "initialAmount";
    }
    else if (species->isSetInitialConcentration()) {
      ret += "initialConcentration";
    }
    else {
      //Set a warning?  LS DEBUG
      ret += "initialConcentration";
    }
    break;
  case SBML_COMPARTMENT:
    ret += "sbml:listOfCompartments/sbml:compartment[@id='" + lastid + "']/@size";
    break;
  case SBML_PARAMETER:
    ret += "sbml:listOfParameters/sbml:parameter[@id='" + lastid + "']/@value";
    break;
  case SBML_LOCAL_PARAMETER:
    ret += "sbml:listOfReactions/sbml:reaction[@id='";
    ret += ref->getAncestorOfType(SBML_REACTION)->getId();
    ret += "']/sbml:kineticLaw/sbml:listOfLocalParameters/sbml:localParameter[@id='" + lastid + "']/@value";
  default:
    //Set a warning? LS DEBUG
    ret += "/descendant::*[@id='" + lastid + "']/@value";
    break;
  }
  return ret;

}

string getElementXPathFromId(const vector<string>* id, const SBMLDocument* doc)
{
  if (id == NULL || id->size()==0) {
    g_registry.setError("The ID of the model element is missing entirely.", 0);
    return "";
  }
  string lastid = (*id)[id->size()-1];
  SBMLDocument* vdoc = const_cast<SBMLDocument*>(doc);
  const SBase* ref = vdoc->getElementBySId(lastid);
  if (doc->getModel() != NULL) {
    //We can error check.  Otherwise, we assume the model has the relevant ID.
    if (ref==NULL) {
      g_registry.setError("No such id in SBML document: '" + getStringFrom(id, ".") + "'.", 0);
      return "";
    }
    const SBase* parent = ref;
    for (size_t n = id->size()-1; n != 0; n--) {
      string parentid = (*id)[n-1];
      bool foundparent = false;
      parent = ref->getParentSBMLObject();
      while (parent != NULL && parent->getTypeCode() != SBML_DOCUMENT) {
        if (parent->getId() == parentid) {
          foundparent = true;
          parent = NULL;
        }
        else {
          parent = parent->getParentSBMLObject();
        }
      }
      if (!foundparent) {
        g_registry.setError("No such id in SBML document: '" + getStringFrom(id, ".") + "'.", 0);
        return "";
      }
    }
    string ret = "/sbml:sbml/sbml:model/";
    switch(ref->getTypeCode()) {
    case SBML_SPECIES:
      ret += "sbml:listOfSpecies/sbml:species[@id='" + lastid + "']";
      break;
    case SBML_COMPARTMENT:
      ret += "sbml:listOfCompartments/sbml:compartment[@id='" + lastid + "']";
      break;
    case SBML_PARAMETER:
      ret += "sbml:listOfParameters/sbml:parameter[@id='" + lastid + "']";
      break;
    case SBML_LOCAL_PARAMETER:
      ret += "sbml:listOfReactions/sbml:reaction[@id='";
      ret += ref->getAncestorOfType(SBML_REACTION)->getId();
      ret += "']/sbml:kineticLaw/sbml:listOfLocalParameters/sbml:localParameter[@id='" + lastid + "']";
    default:
      //Set a warning? LS DEBUG
      ret += "/descendant::*[@id='" + lastid + "']";
      break;
    }
    return ret;
  }
  //Otherwise, make it generic:
  string ret = "/sbml:sbml/sbml:model/descendant::*[@id='" + (*id)[0] + "']";
  for (size_t n=1; n<id->size(); n++) {
    ret += "/descendant::*[@id='" + (*id)[n] + "']";
  }
  return ret;
}

void getElementXPathFromId(const string& id, set<PhrasedModel*> docs, string& xpath, string& modelref)
{
  vector<string> varid;
  varid.push_back(id);
  for (set<PhrasedModel*>::iterator d=docs.begin(); d != docs.end(); d++) {
    xpath = getElementXPathFromId(&varid, (*d)->getSBMLDocument());
    if (xpath != "") {
      modelref = (*d)->getId();
      return;
    }
  }
}


bool IsReal(const string& src)
{
  if (src.empty()) return false;

  long i;
  long end = src.size();
  bool pointfound = false;
  for (i = 0; i < end; ++i) {
    if (!isdigit(src[i])) {
      if (isspace(src[i])) continue; // whitespace is okay
      if (src[i] == '-') continue; // minus is okay
      if (src[i] == '+') continue; // plus is okay
      if (src[i] == 'e') continue; // e is okay
      if (src[i] != '.') return false;  // neither digit nor point
      if (pointfound) return false;   // a second decimal point?!
      pointfound = true;              // okay, first decimal point
    }
  }
  return true;
} /* IsReal */

bool IsInt(const string& src)
{
  if (src.empty()) return false;

  long i;
  long end = src.size();
  for (i = 0; i < end; ++i) {
    if (!isdigit(src[i])) {
      return false;   // Ints only have digits
    }
  }
  return true;
} /* IsInt */

string Trim(string in)
{
  string out = in;
  while (out.size() && out[0] == ' ') {
    out.erase(0,1);
  }
  while (out.size() && out[out.size()-1] == ' ') {
    out.erase(out.size()-1, 1);
  }
  size_t retpos;
  while ((retpos = out.find('\n')) != string::npos) {
    out.replace(retpos, 1, " ");
  }
  while ((retpos = out.find('\r')) != string::npos) {
    out.replace(retpos, 1, " ");
  }
  return out;
}

bool CaselessStrCmp(const string& lhs, const string& rhs)
{

  if (lhs.size() != rhs.size()) return false;

  for (size_t i = 0; i < lhs.size(); ++i) {
    if (toupper(lhs[i]) != toupper(rhs[i])) return false;
  }
  return true;

} /* CaselessStrCmp */
PHRASEDML_CPP_NAMESPACE_END
