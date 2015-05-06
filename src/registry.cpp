#include <cassert>
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include <fstream>

#include "registry.h"
#include "stringx.h"
#include "model.h"

#include "sedml\SedDocument.h"

extern int phrased_yyparse();
extern int phrased_yylloc_last_line;


using namespace std;

Registry::Registry()
  : m_variablenames()
  , m_error()
  , m_warnings()
  , m_sedml(NULL)
  , m_models()
  , input(NULL)
{
}

Registry::~Registry()
{
  delete m_sedml;
}

char* Registry::convertString(string model)
{
  //Try to read it as SED-ML first.
  m_sedml = readSedMLFromString(model.c_str());
  if (m_sedml->getNumErrors(LIBSEDML_SEV_ERROR) == 0 && m_sedml->getNumErrors(LIBSEDML_SEV_FATAL) == 0) {
    parseSEDML();
    return getPhraSEDML();
  }
  istringstream* inputstring = new istringstream(model + "\n");
  phrased_yylloc_last_line = 1;
  input = inputstring;
  if (parseInput()) {
    return "";
  }
  createSEDML();
  return getSEDML();
}

char* Registry::convertFile(const string& filename)
{
  string file = filename;
  if (!file_exists(file)) {
    file = m_workingDirectory + file;
    if (!file_exists(file)) {
      string error = "Input file '";
      error += filename;
      error += "' cannot be found.  Check to see if the file exists and that the permissions are correct, and try again.  If this still does not work, contact us letting us know how you got this error.";
      setError(error);
      return NULL;
    }
  }
  string old_wd = m_workingDirectory;
  m_workingDirectory = file;
  size_t lastslash = m_workingDirectory.rfind('/');
  if (lastslash==string::npos) {
    lastslash = m_workingDirectory.rfind('\\');
  }
  if (lastslash!=string::npos) {
    m_workingDirectory.erase(lastslash+1, m_workingDirectory.size()-lastslash-1);
  }
  //Try to read it as SED-ML first
  m_sedml = readSedMLFromFile(file.c_str());
  if (m_sedml->getNumErrors(LIBSEDML_SEV_ERROR) == 0 && m_sedml->getNumErrors(LIBSEDML_SEV_FATAL) == 0) {
    parseSEDML();
    return getPhraSEDML();
  }

  //If that failed, set up the 'input' member variable so we can parse it as Phrasedml.
  clearSEDML();
  ifstream* inputfile = new ifstream();
  inputfile->open(file.c_str(), ios::in);
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
  if (parseInput()) {
    return "";
  }
  createSEDML();
  char* ret = getSEDML();
  m_workingDirectory = old_wd;
  return ret;
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
  if (checkId(name)) {
    return true;
  }
  PhrasedModel pm(namestr, *modelloc, true);
  m_models.push_back(pm);
  return false;
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

bool Registry::setName(vector<const string*>* id, vector<const string*>* is, const string* name)
{
  string iskeyword = "is";
  string idstr = getStringFrom(id);
  string isstr = getStringFrom(is);
  stringstream err;
  if (isstr != iskeyword) {
    err << "Unable to parse line " << phrased_yylloc_last_line-1 << " ('" << idstr << " " << isstr << " \"" << *name << "\"'): the only type of phraSED-ML content that fits the syntax '[ID] [keyword] \"[string]\"' is setting the names of elements, where 'keyword' is the word 'is' (i.e. 'mod1 is \"Biomodels file #322\"').  ";
    setError(err.str());
    return true;
  }
  if (checkId(id)) {
    return true;
  }
  for (size_t m=0; m<m_models.size(); m++) {
    if (m_models[m].getId() == idstr) {
      m_models[m].setName(*name);
      return false;
    }
  }

  err << "Error in line " << phrased_yylloc_last_line-1 << ": no such id '" << idstr << "' exists to set its name.";
  setError(err.str());
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

void Registry::setWorkingDirectory(const char* directory)
{
  m_workingDirectory = directory;
}

string Registry::getWorkingFilename(const string& filename)
{
  if (file_exists(filename)) return filename;
  string newfile = m_workingDirectory + filename;
  if (file_exists(newfile)) return newfile;
  return "";
}
  
char* Registry::getPhraSEDML() const
{
  string retval  = "//Created by libphrasedml ";
  retval += LIBPHRASEDML_VERSION_STRING;
  retval += "\n";
  string names = "";
  for (size_t m=0; m<m_models.size(); m++) {
    if (m==0) {
      retval += "// Models\n";
    }
    retval += m_models[m].getPhraSEDML();
    if (m==m_models.size()-1) {
      retval += "\n";
    }
    if (m_models[m].getName() != "") {
      names += m_models[m].getId() + " is \"" + m_models[m].getName() + "\"\n";
    }
  }


  if (names != "") {
    retval += "// Names\n" + names + "\n";
  }
  char* ret = strdup(retval.c_str());
  g_registry.m_charstars.push_back(ret);
  return ret;
}

char* Registry::getSEDML() const
{
  if (m_sedml==NULL) {
    return NULL;
  }
  char* ret = writeSedMLToString(m_sedml);
  g_registry.m_charstars.push_back(ret);
  return ret;
}

void Registry::createSEDML()
{
  delete m_sedml;
  m_sedml = new SedDocument();
  for (size_t m=0; m<m_models.size(); m++) {
    m_models[m].addModelToSEDML(m_sedml);
  }
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


bool Registry::parseInput()
{
  clearAll();
  clearSEDML();
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
    return true;
  }
  return false;
}

bool Registry::parseSEDML()
{
  clearAll();
  setError("Unable to parse SED-ML input at this time.");
  return true;
}

bool Registry::checkId(vector<const string*>* name)
{
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line-1 << ": ";
  if (name->size()==0) {
    assert(false); //This shouldn't be possible, and I want to see what happened to cause it if it happens.
    err << "a phraSED-ML top-level ID must exist, and this ID has corresponding string for it.";
    setError(err.str());
    return true;
  }
  else if (name->size() > 1) {
    err << "a phraSED-ML id may not be a sub-id of another variable:  '" << getStringFrom(name) << "' is not a legal ID for a phraSED-ML model.";
    setError(err.str());
    return true;
  }
  else if (!isValidSId(name)) {
    err << "a phraSED-ML id must adhere to the pattern '[A-Za-z_][A-Za-z_0-9]*', and '" << (*(*name)[0]) << " does not conform.";
    setError(err.str());
    return true;
  }
  return false;
}


bool Registry::isValidSId(vector<const string*>* name)
{
  if (name->size() != 1) return false;
  string corename = *(*name)[0];

  //Taken from libsbml's "SyntaxChecker::isValidInternalSId(string sid)"
  size_t size = (*name)[0]->size();
  if (size == 0)
  {
    return false;
  }

  size_t n = 0;

  char c = (*(*name)[0])[n];
  bool okay = (isalpha(c) || (c == '_'));
  n++;

  while (okay && n < size)
  {
    c = (*(*name)[0])[n];
    okay = (isalnum(c) || c == '_');
    n++;
  }

  return okay;
}

void Registry::clearAll()
{
  m_error.clear();
  m_warnings.clear();
  m_models.clear();
}

void Registry::clearSEDML()
{
  delete m_sedml;
  m_sedml = NULL;
}

bool Registry::file_exists (const string& filename)
{
#ifdef _MSC_VER
#  define stat _stat
#endif

  if (filename.empty()) return false;
  struct stat buf;
  return stat(filename.c_str(), &buf) == 0;
}

