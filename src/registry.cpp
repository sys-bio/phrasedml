#include <cassert>
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include <fstream>

#include "registry.h"
#include "stringx.h"
#include "model.h"
#include "steadyState.h"
#include "uniform.h"
#include "oneStep.h"

#include "sedml\SedDocument.h"
extern char* getCharStar(const char* orig);
extern int phrased_yyparse();
extern int phrased_yylloc_last_line;

#ifdef _MSC_VER
#  define strdup _strdup
#endif


using namespace std;

Registry::Registry()
  : m_variablenames()
  , m_error()
  , m_errorLine(0)
  , m_warnings()
  , m_sedml(NULL)
  , m_models()
  , input(NULL)
{
}

Registry::~Registry()
{
  clearAll();
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
    return NULL;
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
      setError(error, 0);
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
    char* ret = getPhraSEDML();
    m_workingDirectory = old_wd;
    return ret;
  }

  //If that failed, set up the 'input' member variable so we can parse it as Phrasedml.
  clearSEDML();
  ifstream* inputfile = new ifstream();
  inputfile->open(file.c_str(), ios::in);
  if (!inputfile->is_open() || !inputfile->good()) {
    string error = "Input file '";
    error += filename;
    error += "' cannot be read.  Check to see if the file exists and that the permissions are correct, and try again.  If this still does not work, contact us letting us know how you got this error.";
    setError(error, 0);
    delete inputfile;
    return NULL;
  }
  input = inputfile;
  phrased_yylloc_last_line = 1;
  if (parseInput()) {
    return NULL;
  }
  createSEDML();
  char* ret = getSEDML();
  m_workingDirectory = old_wd;
  return ret;
}

bool Registry::addModelDef(vector<const string*>* name, vector<const string*>* model, const string* modelloc)
{
  string namestr = getStringFrom(name);
  string modelstr = getStringFrom(model);
  if (!CaselessStrCmp(modelstr,"model")) {
    stringstream err;
    err << "Unable to parse line " << phrased_yylloc_last_line-1 << " ('" << namestr << " = " << modelstr << " \"" << *modelloc << "\"'): the only type of phraSED-ML content that fits the syntax '[ID] = [keyword] \"[string]\"' is model definitions, where 'keyword' is the word 'model' (i.e. 'mod1 = model \"file.xml\"').";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
  }
  if (checkId(name)) {
    return true;
  }
  PhrasedModel pm(namestr, *modelloc, true);
  m_models.push_back(pm);
  return false;
}

bool Registry::addModelDef(vector<const string*>* name, vector<const string*>* model, const string* modelloc, vector<const string*>* with, vector<ModelChange>* changelist)
{
  string namestr = getStringFrom(name);
  string modelstr = getStringFrom(model);
  string withstr = getStringFrom(with);
  if (!CaselessStrCmp(modelstr,"model")) {
    stringstream err;
    err << "Unable to parse line " << phrased_yylloc_last_line-1 << " ('" << namestr << " = " << modelstr << " \"" << *modelloc << "\" [...]'): the only type of phraSED-ML content that fits the syntax '[ID] = [keyword] \"[string]\" [...]' is model definitions, where 'keyword' is the word 'model' (i.e. 'mod1 = model \"file.xml\" with S1=3').";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
  }
  if (checkId(name)) {
    return true;
  }
  if (withstr != "with") {
    stringstream err;
    err << "Unable to parse line " << phrased_yylloc_last_line-1 << " ('" << namestr << " = " << modelstr << " \"" << *modelloc << "\" " << withstr << " [...]'): the only type of phraSED-ML content that fits the syntax '[ID] = [keyword] \"[string]\" [keyword] [...]' is model definitions, where 'keyword' is the word 'with' (i.e. 'mod1 = model \"file.xml\" with S1=3').";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
  }
  PhrasedModel pm(namestr, *modelloc, *changelist, true);
  m_models.push_back(pm);
  return false;
}


bool Registry::addModelDef(vector<const string*>* name, vector<const string*>* model, const string* modelloc, vector<const string*>* with, vector<const string*>* key1, vector<const string*>* key2)
{
  vector<ModelChange>* cl = new vector<ModelChange>;
  if (addToChangeList(cl, key1, key2)) {
    return true;
  }
  return addModelDef(name, model, modelloc, with, cl);
}


bool Registry::addModelDef(vector<const string*>* name, vector<const string*>* model, const string* modelloc, vector<const string*>* with, vector<const string*>* key1, vector<const string*>* key2, vector<ModelChange>* changelist)
{
  if (addToChangeList(changelist, key1, key2)) {
    return true;
  }
  return addModelDef(name, model, modelloc, with, changelist);
}



//phraSED-ML lines that could be almost anything:
bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2)
{
  if (checkId(name)) {
    return true;
  }
  string namestr = getStringFrom(name);
  string key1str = getStringFrom(key1);
  string key2str = getStringFrom(key2);
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line-1 << " ('" << namestr << " = " << key1str << " " << key2str << "'): ";
  if (CaselessStrCmp(key1str,"model")) {
    if (checkId(key2)) {
      return true;
    }
    PhrasedModel pm(namestr, key2str, false);
    m_models.push_back(pm);
    return false;
  }
  if (CaselessStrCmp(key1str,"simulate")) {
    if (CaselessStrCmp(key2str,"steadystate")) {
      PhrasedSteadyState* pss = new PhrasedSteadyState(namestr);
      m_simulations.push_back(pss);
      return false;
    }
    else if (CaselessStrCmp(key2str,"onestep") || CaselessStrCmp(key2str,"uniform")) {
      err << "uniform and oneStep simulations must be defined with arguments to determine their properties, (i.e. 'sim1 = simulate uniform(0,10,100)' or 'sim2 = simulate oneStep(0.5)').";
      setError(err.str(), phrased_yylloc_last_line-1);
      return true;
    }
    else {
      err << "the only type of phraSED-ML content that fits the syntax '[ID] = simulate [keyword]' (without anything following) is simulating the steady state, where 'keyword' is 'steadystate' (i.e. 'sim1 = simulate steadystate').";
      setError(err.str(), phrased_yylloc_last_line-1);
      return true;
    }
  }
  else {
    err << "unsupported keyword '" << key1str << "'.  Try 'model' or 'simulate' in this context.";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
  }
  return false;
}


bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* key3, vector<ModelChange>* changelist)
{
  if (checkId(name)) {
    return true;
  }
  string namestr = getStringFrom(name);
  string key1str = getStringFrom(key1);
  string key2str = getStringFrom(key2);
  string key3str = getStringFrom(key3);
  stringstream err;
  if (CaselessStrCmp(key1str,"model")) {
    if (checkId(key2)) {
      return true;
    }
    if (!CaselessStrCmp(key3str,"with")) {
      err << "Unable to parse line " << phrased_yylloc_last_line-1 << " ('" << namestr << " = " << key1str << " " << key2str << " " << key3str << " [...]'): the only type of phraSED-ML content that fits the syntax '[ID] = model [string] [keyword] [...]' is model definitions, where 'keyword' is the word 'with' (i.e. 'mod1 = model mod0 with S1=3').";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
    }
    PhrasedModel pm(namestr, key2str, *changelist, false);
    m_models.push_back(pm);
    return false;
  }
  else {
    setError("Error in addEquals v2:  unsupported keyword" + key1str, phrased_yylloc_last_line-1);
    return true;
  }
  return false;
}


bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* key3, vector<const string*>* key4)
{

  setError("Error in addEquals v3.", phrased_yylloc_last_line-1);
  return true;
}


bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* key3, vector<const string*>* key4, vector<const string*>* key5)
{

  setError("Error in addEquals v4.", phrased_yylloc_last_line-1);
  return true;
}


bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* key3, vector<const string*>* key4, vector<const string*>* key5, vector<ModelChange>* changelist)
{

  setError("Error in addEquals v5.", phrased_yylloc_last_line-1);
  return true;
}


bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2, vector<double>* numlist)
{
  if (checkId(name)) {
    return true;
  }
  string namestr = getStringFrom(name);
  string key1str = getStringFrom(key1);
  string key2str = getStringFrom(key2);
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line << " ('" << namestr << " = " << key1str << " " << key2str << "(";
  for (size_t n=0; n<numlist->size(); n++) {
    if (n!=0) {
      err << ", ";
    }
    err << (*numlist)[n];
  }
  err << ")'): ";
  if (CaselessStrCmp(key1str,"simulate")) {
    if (CaselessStrCmp(key2str,"steadystate")) {
      if (numlist->size() != 0) {
        err << "steady state simulations do not take any arguments.";
        setError(err.str(), phrased_yylloc_last_line);
        return true;
      }
      PhrasedSteadyState* pss = new PhrasedSteadyState(namestr);
      m_simulations.push_back(pss);
      return false;
    }
    else if (CaselessStrCmp(key2str,"onestep")) {
      if (numlist->size() != 1) {
        err << "onestep simulations must take exactly one argument.";
        setError(err.str(), phrased_yylloc_last_line);
        return true;
      }
      PhrasedOneStep* pone = new PhrasedOneStep(namestr, (*numlist)[0]);
      m_simulations.push_back(pone);
      return false;
    }
    else if (CaselessStrCmp(key2str,"uniform")) {
      if (numlist->size() == 3) {
        PhrasedUniform* puniform = new PhrasedUniform(namestr, (*numlist)[0], (*numlist)[0], (*numlist)[1], (long)(*numlist)[2]);
        m_simulations.push_back(puniform);
        return false;
      }
      else if (numlist->size() == 4) {
        PhrasedUniform* puniform = new PhrasedUniform(namestr, (*numlist)[0], (*numlist)[1], (*numlist)[2], (long)(*numlist)[3]);
        m_simulations.push_back(puniform);
        return false;
      }
      else {
        err << "uniform timecourse simulations must have either three arguments (start, stop, steps) or four (simulation_start, output_start, stop, steps).";
        setError(err.str(), phrased_yylloc_last_line);
        return true;
      }
    }
    else {
      err << "the only type of phraSED-ML content that fits the syntax '[ID] = [keyword] [keyword]([list of values])' is simulations (i.e. 'sim1 = simulate steadystate()' or 'sim2 = simulate uniform(0, 10, 100)').";
      setError(err.str(), phrased_yylloc_last_line);
      return true;
    }
  }
  else {
    err << "unsupported keyword '" << key1str << "'.  Try 'model' or 'simulate' in this context.";
    setError(err.str(), phrased_yylloc_last_line);
    return true;
  }
  return false;
}




//phraSED-ML lines that are clearly plots:
bool Registry::addPlot(vector<const string*>* plot, vector<const string*>* name, vector<const string*>* vs,  vector<vector<const string*>*>* plotlist)
{

  setError("Error in addPlot.", phrased_yylloc_last_line-1);
  return true;
}




//ChangeList addition
bool Registry::addToChangeList(vector<ModelChange>* cl, vector<const string*>* key1, vector<const string*>* key2)
{
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line -1 << " at '" << getStringFrom(key1) << " " << getStringFrom(key2) << "': changes to models of the form '[keyword] [id]' (such as 'remove S1') are not currently supported.  Future plans include incorporation of this functionality.";
  setError(err.str(), phrased_yylloc_last_line-1);
  return true;
}


bool Registry::addToChangeList(vector<ModelChange>* cl, vector<const string*>* name, double val)
{
  ModelChange mc(name, val);
  cl->push_back(mc);
  return false;
}


bool Registry::addToChangeList(vector<ModelChange>* cl, vector<const string*>* key1, vector<const string*>* name, vector<string>* formula)
{
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line -1 << " at '" << getStringFrom(key1) << " " << getStringFrom(name) << " = " << getStringFrom(formula) << "': changes to models of the form '[keyword] [id] = [formula]' (such as 'compute S1 = k1/k2') are not currently supported.  Future plans include incorporation of this functionality.";
  setError(err.str(), phrased_yylloc_last_line-1);
  return true;
}


bool Registry::addToChangeList(vector<ModelChange>* cl, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* name, double val)
{
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line -1 << " at '" << getStringFrom(key1) << " " << getStringFrom(key2) << getStringFrom(name) << " = " << val << "': changes to models of the form '[keyword] [keyword] [id] = [value]' (such as 'add parameter p1 = 3') are not currently supported.  Future plans include incorporation of this functionality.";
  setError(err.str(), phrased_yylloc_last_line-1);
  return true;
}


bool Registry::addToChangeList(vector<ModelChange>* cl, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* key3, vector<const string*>* name, double val)
{
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line -1 << " at '" << getStringFrom(key1) << " " << getStringFrom(key2) << getStringFrom(key3) << getStringFrom(name) << " = " << val << "': changes to models of the form '[keyword] [id] [keyword] [id] = [value]' (such as 'change p1 to p3 = 5') are not currently supported.  Future plans include incorporation of this functionality.";
  setError(err.str(), phrased_yylloc_last_line-1);
  return true;
}

bool Registry::setName(vector<const string*>* id, vector<const string*>* is, const string* name)
{
  string idstr = getStringFrom(id);
  string isstr = getStringFrom(is);
  stringstream err;
  if (!CaselessStrCmp(isstr,"is")) {
    err << "Unable to parse line " << phrased_yylloc_last_line-1 << " ('" << idstr << " " << isstr << " \"" << *name << "\"'): the only type of phraSED-ML content that fits the syntax '[ID] [keyword] \"[string]\"' is setting the names of elements, where 'keyword' is the word 'is' (i.e. 'mod1 is \"Biomodels file #322\"').  ";
    setError(err.str(), phrased_yylloc_last_line-1);
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
  setError(err.str(), phrased_yylloc_last_line-1);
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


  for (size_t s=0; s<m_simulations.size(); s++) {
    if (s==0) {
      retval += "// Simulations\n";
    }
    retval += m_simulations[s]->getPhraSEDML();
    if (s==m_simulations.size()-1) {
      retval += "\n";
    }
    if (m_simulations[s]->getName() != "") {
      names += m_simulations[s]->getId() + " is \"" + m_simulations[s]->getName() + "\"\n";
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
  ostringstream stream;
  SedWriter sw;
  sw.writeSedML(m_sedml, stream);
  string ret = stream.str();
  size_t replace = ret.find("&apos;");
  while (replace != string::npos) {
    ret.replace(replace, 6, "'");
    replace = ret.find("&apos;");
  }
  replace = ret.find("&quot;");
  while (replace != string::npos) {
    ret.replace(replace, 6, "\"");
    replace = ret.find("&quot;");
  }
  return getCharStar(ret.c_str());
}

const PhrasedModel* Registry::getModel(string modid) const
{
  for (size_t m=0; m<m_models.size(); m++) {
    if (m_models[m].getId() == modid) {
      return &(m_models[m]);
    }
  }
  return NULL;
}

PhrasedModel* Registry::getModel(string modid)
{
  for (size_t m=0; m<m_models.size(); m++) {
    if (m_models[m].getId() == modid) {
      return &(m_models[m]);
    }
  }
  return NULL;
}

void Registry::createSEDML()
{
  delete m_sedml;
  m_sedml = new SedDocument();
  for (size_t m=0; m<m_models.size(); m++) {
    m_models[m].addModelToSEDML(m_sedml);
  }
  for (size_t s=0; s<m_simulations.size(); s++) {
    m_simulations[s]->addSimulationToSEDML(m_sedml);
  }
}

bool Registry::finalize()
{
  //Check the models
  for (size_t m=0; m<m_models.size(); m++) {
    if (m_models[m].finalize()) {
      return true;
    }
  }
  for (size_t s=0; s<m_simulations.size(); s++) {
    if (m_simulations[s]->finalize()) {
      return true;
    }
  }

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
        setError("Parsing failed because of invalid input.", phrased_yylloc_last_line);
      }
      else if (success == 2) {
        setError("Parsing failed due to memory exhaution.", phrased_yylloc_last_line-1);
      }
      else {
        setError("Unknown parsing error.", phrased_yylloc_last_line-1);
      }
    }
    return true;
  }
  return false;
}

bool Registry::parseSEDML()
{
  clearAll();
  for (unsigned long m=0; m<m_sedml->getNumModels(); m++) {
    PhrasedModel mod(m_sedml->getModel(m), m_sedml);
    m_models.push_back(mod);
  }
  for (unsigned long s=0; s<m_sedml->getNumSimulations(); s++) {
    SedSimulation* sedsim = m_sedml->getSimulation(s);
    int sedtype = sedsim->getTypeCode();
    if(sedtype==SEDML_SIMULATION_ONESTEP) {
      SedOneStep* sedonestep = static_cast<SedOneStep*>(sedsim);
      PhrasedOneStep* pone = new PhrasedOneStep(sedonestep);
      m_simulations.push_back(pone);
    }
    else if (sedtype==SEDML_SIMULATION_STEADYSTATE) {
      SedSteadyState* sedsteady = static_cast<SedSteadyState*>(sedsim);
      PhrasedSteadyState* psteady = new PhrasedSteadyState(sedsteady);
      m_simulations.push_back(psteady);
    }
    else if (sedtype==SEDML_SIMULATION_UNIFORMTIMECOURSE) {
      SedUniformTimeCourse* seduniform = static_cast<SedUniformTimeCourse*>(sedsim);
      PhrasedUniform* puniform = new PhrasedUniform(seduniform);
      m_simulations.push_back(puniform);
    }
    else {
      setError("SED-ML simulation '" + sedsim->getId() + "' has unknown type.", 0);
      return true;
    }
  }
  //setError("Unable to parse SED-ML input at this time.");
  return false;
}

bool Registry::checkId(vector<const string*>* name)
{
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line-1 << ": ";
  if (name->size()==0) {
    assert(false); //This shouldn't be possible, and I want to see what happened to cause it if it happens.
    err << "a phraSED-ML top-level ID must exist, and this construct has no corresponding ID.";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
  }
  else if (name->size() > 1) {
    err << "the phraSED-ML ID '" << getStringFrom(name) << "' in this context may not be a sub-id of another variable.";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
  }
  else if (!isValidSId(name)) {
    err << "a phraSED-ML id must adhere to the pattern '[A-Za-z_][A-Za-z_0-9]*', and '" << (*(*name)[0]) << " does not conform.";
    setError(err.str(), phrased_yylloc_last_line-1);
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
  m_errorLine = 0;
  m_warnings.clear();
  m_models.clear();
  for (size_t s=0; s<m_simulations.size(); s++) {
    delete m_simulations[s];
  }
  m_simulations.clear();
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

