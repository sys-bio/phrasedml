#include <cassert>
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include <fstream>

#include "registry.h"
#include "stringx.h"

extern int phrased_yyparse();
extern int phrased_yylloc_last_line;


using namespace std;

Registry::Registry()
  : m_variablenames(),
    m_error(),
    m_warnings(),
    input(NULL)
{
}

Registry::~Registry()
{
}

string Registry::convertString(string model)
{
  //Try to read it as SED-ML first.
  //LS DEBUG:  TODO

  istringstream* inputstring = new istringstream(model + "\n");
  phrased_yylloc_last_line = 1;
  input = inputstring;
  return parseInput();
}

string Registry::convertFile(const string& filename)
{
  //Try to read it as SED-ML first
  //LS DEBUG:  TODO


  //If that failed, set up the 'input' member variable so we can parse it as Phrasedml.
  ifstream* inputfile = new ifstream();
  inputfile->open(filename.c_str(), ios::in);
  if (!inputfile->is_open() || !inputfile->good()) {
    string error = "Input file '";
    error += filename;
    error += "' cannot be read.  Check to see if the file exists and that the permissions are correct, and try again.  If this still does not work, contact us letting us know how you got this error.";
    setError(error);
    delete inputfile;
    return "";
  }
  input = inputfile;
  phrased_yylloc_last_line = 1;
  return parseInput();
}

bool Registry::addModelDef(vector<const string*>* name, vector<const string*>* model, const string* modelloc)
{
  string modkeyword = "model";
  string namestr = getStringFrom(name);
  string modelstr = getStringFrom(model);
  if (modelstr != modkeyword) {
    stringstream err;
    err << "Unable to parse line " << phrased_yylloc_last_line-1 << " ('" << namestr << " = " << modelstr << " \"" << *modelloc << "\"'): the only type of phraSED-ML content that fits the syntax '[ID] = [keyword] \"[string]\"' is model definitions, where 'keyword' is the word 'model' (i.e. 'mod1 = model \"file.xml\"').  ";
    setError(err.str());
    return true;
  }

  setError("Error in addModelDef v1.");
  return true;
}

bool Registry::addModelDef(vector<const string*>* name, vector<const string*>* model, const string* modelloc, vector<const string*>* with, ChangeList* changelist)
{

  setError("Error in addModelDef v2.");
  return true;
}


bool Registry::addModelDef(vector<const string*>* name, vector<const string*>* model, const string* modelloc, vector<const string*>* with, vector<const string*>* key1, vector<const string*>* key2, ChangeList* changelist)
{

  setError("Error in addModelDef v3.");
  return true;
}



//phraSED-ML lines that could be almost anything:
bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2)
{

  setError("Error in addEquals v1.");
  return true;
}


bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* key3, ChangeList* changelist)
{

  setError("Error in addEquals v2.");
  return true;
}


bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* key3, vector<const string*>* key4)
{

  setError("Error in addEquals v3.");
  return true;
}


bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* key3, vector<const string*>* key4, vector<const string*>* key5)
{

  setError("Error in addEquals v4.");
  return true;
}


bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* key3, vector<const string*>* key4, vector<const string*>* key5, ChangeList* changelist)
{

  setError("Error in addEquals v5.");
  return true;
}


bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2, vector<double>* numlist)
{

  setError("Error in addEquals v6.");
  return true;
}




//phraSED-ML lines that are clearly plots:
bool Registry::addPlot(vector<const string*>* plot, vector<const string*>* name, vector<const string*>* vs,  vector<vector<const string*>*>* plotlist)
{

  setError("Error in addPlot.");
  return true;
}




//ChangeList creation
ChangeList* Registry::createChangeList(vector<const string*>* name, double val)
{

  return NULL;
}


ChangeList* Registry::createChangeList(vector<const string*>* name, vector<const string*>* key, vector<string>* formula )
{

  return NULL;
}


ChangeList* Registry::createChangeList(vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* name, double val )
{

  return NULL;
}


ChangeList* Registry::createChangeList(vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* key3, vector<const string*>* name, double val )
{

  return NULL;
}



//ChangeList addition
bool Registry::addToChangeList(ChangeList* cl, vector<const string*>* key1, vector<const string*>* key2)
{

  return true;
}


bool Registry::addToChangeList(ChangeList* cl, vector<const string*>* name, double val)
{

  return true;
}


bool Registry::addToChangeList(ChangeList* cl, vector<const string*>* key1, vector<const string*>* name, vector<string>* formula)
{

  return true;
}


bool Registry::addToChangeList(ChangeList* cl, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* name, double val)
{

  return true;
}


bool Registry::addToChangeList(ChangeList* cl, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* key3, vector<const string*>* name, double val)
{

  return true;
}



//Assistance functions
string Registry::ftoa(double val)
{
  stringstream ret;
  ret << val;
  return ret.str();
}


const string* Registry::addWord(string word)
{
  pair<set<string>::iterator,bool> ret;

  ret = m_variablenames.insert(word);
  set<string>::iterator wordit = ret.first;
  return &(*wordit);
}

string Registry::getPhraSEDML() const
{
  string retval;


  return retval;
}

string Registry::getSEDML() const
{
  string retval;


  return retval;
}

/*
string Registry::getJarnac(string modulename) const
{
  const Module* jmod = getModule(modulename);
  if (jmod == NULL) return "";
  string jarnac = modulename + " = define model\n";
  jarnac += jmod->getJarnacReactions();
  jarnac += "\n";
  jarnac += jmod->getJarnacVarFormulas();
  jarnac += "\nend\n\n";
  jarnac += jmod->getJarnacConstFormulas(modulename);
  return jarnac;
}
*/

bool Registry::finalize()
{

  return false;
}

  void Registry::freeAll()
{
  for (size_t i=0; i<m_charstars.size(); i++) {
    free(m_charstars[i]);
  }
  m_charstars.clear();
  /*
  for (size_t i=0; i<m_charstarstars.size(); i++) {
    free(m_charstarstars[i]);
  }
  m_charstarstars.clear();
  for (size_t i=0; i<m_charstarstarstars.size(); i++) {
    free(m_charstarstarstars[i]);
  }
  m_charstarstarstars.clear();

  for (size_t i=0; i<m_doublestars.size(); i++) {
    free(m_doublestars[i]);
  }
  m_doublestars.clear();
  for (size_t i=0; i<m_doublestarstars.size(); i++) {
    free(m_doublestarstars[i]);
  }
  m_doublestarstars.clear();

  for (size_t i=0; i<m_ulongstars.size(); i++) {
    free(m_ulongstars[i]);
  }
  m_ulongstars.clear();
  for (size_t i=0; i<m_rd_typestars.size(); i++) {
    free(m_rd_typestars[i]);
  }
  m_rd_typestars.clear();
  */
}


string Registry::parseInput()
{
  m_error.clear();
  int success = phrased_yyparse();
  if (success != 0) {
    if (getError().size() == 0) {
      assert(false); //Need to fill in the reason why we failed explicitly, if possible.
      if (success == 1) {
        setError("Parsing failed because of invalid input.");
      }
      else if (success == 2) {
        setError("Parsing failed due to memory exhaution.");
      }
      else {
        setError("Unknown parsing error.");
      }
    }
  }
  return getSEDML();
}

string Registry::getSEDML()
{
  if (m_error.empty()) {
    return "Successfully parsed the phraSEDML file, but can't translate to SEDML yet.";
  }
  return "";
}

string Registry::getPhraSEDML()
{
  if (m_error.empty()) {
    return "Successfully parsed the SEDML file, but can't translate to phraSEDML yet.";
  }
  return "";
}

