#include <sstream>
#include <assert.h>
#include <iostream>
#include "stringx.h"
#include "registry.h"
#include "sbml/SBMLDocument.h"

using namespace std;
extern bool CaselessStrCmp(const string& lhs, const string& rhs);

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

string getStringFrom(const vector<string>* name)
{
  string retval = "";
  for (size_t nn=0; nn<name->size(); nn++) {
    if (nn>0) {
      retval += " ";
    }
    retval += (*name)[nn];
  }
  return retval;
}

string getIdFromXPath(const string& xpath)
{
  size_t atid = xpath.find("[@id=");
  size_t idend = xpath.find("]", atid);
  string ret = xpath;
  ret = ret.substr(atid+6, idend-atid-7);
  return ret;
}

string getValueXPathFromId(const string& id, SBMLDocument* doc)
{
  const SBase* ref = doc->getElementBySId(id);
  if (ref==NULL) {
    g_registry.setError("No such id in SBML document: '" + id + "'.", 0);
    return "";
  }
  const Species* species;
  string ret = "/sbml:sbml/sbml:model/";
  switch(ref->getTypeCode()) {
  case SBML_SPECIES:
    ret += "listOfSpecies/species[@id='" + id + "']/@";
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
    ret += "listOfCompartments/compartment[@id='" + id + "']/@size";
    break;
  case SBML_PARAMETER:
    ret += "listOfParameters/parameter[@id='" + id + "']/@value";
    break;
  case SBML_LOCAL_PARAMETER:
    ret += "listOfReactions/reaction[@id='";
    ret += ref->getAncestorOfType(SBML_REACTION)->getId();
    ret += "']/kineticLaw/listOfLocalParameters/localParameter[@id='" + id + "']/@value";
  default:
    //Set a warning? LS DEBUG
    ret += "/descendant::*[@id='" + id + "']/@value";
    break;
  }
  return ret;

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

