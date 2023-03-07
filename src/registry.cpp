#include <cassert>
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include <fstream>

#include "registry.h"
#include "stringx.h"
#include "model.h"
#include "repeatedTask.h"
#include "steadyState.h"
#include "task.h"
#include "uniform.h"
#include "oneStep.h"
#include "output.h"
#include "sbmlx.h"

#include "sedml/SedDocument.h"

extern int phrased_yyparse();
extern int phrased_yylloc_last_line;

#ifdef _MSC_VER
#  define strdup _strdup
#endif

using namespace std;
using namespace libsbml;
using namespace libsedml;

PHRASEDML_CPP_NAMESPACE_BEGIN

Registry::Registry()
  : m_variablenames()
  , m_error()
  , m_errorLine(0)
  , m_warnings()
  , m_sedml(NULL)
  , m_workingDirectory()
  , m_separator("_____")
  , m_models()
  , m_simulations()
  , m_tasks()
  , m_repeatedTasks()
  , m_outputs()
  , m_referencedSBML()
  , m_l3ps()
  , input(NULL)
{
  m_l3ps.setParseCollapseMinus(true);
  m_l3ps.setParseLog(L3P_PARSE_LOG_AS_LOG10);
#if LIBSBML_VERSION >= 51201
  XMLOutputStream::setWriteTimestamp(false);
#endif
}

Registry::~Registry()
{
  clearAll();
  clearReferencedSBML();
  delete m_sedml;
}

char* Registry::convertString(string model)
{
  //Try to read it as SED-ML first.
  m_sedml = readSedMLFromString(model.c_str());
  if (m_sedml->getNumErrors(LIBSEDML_SEV_ERROR) == 0 && m_sedml->getNumErrors(LIBSEDML_SEV_FATAL) == 0) {
    parseSEDML();
    return getPhraSEDML();
  } else {
    // std::cerr << "Registry::convertString: errors reading SED-ML: " << m_sedml->getNumErrors(LIBSEDML_SEV_ERROR) << " errors, " << m_sedml->getNumErrors(LIBSEDML_SEV_FATAL) << " fatal errors\n";
    // if (m_sedml->getNumErrors(LIBSEDML_SEV_ERROR)) {
    //   for (int k=0; k<m_sedml->getNumErrors(LIBSEDML_SEV_ERROR); ++k) {
    //     std::cerr << m_sedml->getError(k)->getMessage() << "\n";
    //     // std::cerr << model << "\n";
    //   }
    // }
    istringstream* inputstring = new istringstream(model + "\n");
    phrased_yylloc_last_line = 1;
    input = inputstring;
    if (parseInput()) {
      return NULL;
    }
    createSEDML();
    return getSEDML();
  }
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
    else if (CaselessStrCmp(key2str,"onestep") || CaselessStrCmp(key2str,"uniform") || CaselessStrCmp(key2str, "uniform_stochastic")) {
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
  err << "Unable to parse line " << phrased_yylloc_last_line-1 << " ('" << namestr << " = " << key1str << " " << key2str << " " << key3str << " [...]'): ";
  if (CaselessStrCmp(key1str,"model")) {
    if (checkId(key2)) {
      return true;
    }
    if (!CaselessStrCmp(key3str,"with")) {
      err << "the only type of phraSED-ML content that fits the syntax '[ID] = model [string] [keyword] [...]' is model definitions, where 'keyword' is the word 'with' (i.e. 'mod1 = model mod0 with S1=3').";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
    }
    PhrasedModel pm(namestr, key2str, *changelist, false);
    if (pm.changeListIsInappropriate(err)) {
      return true;
    }
    m_models.push_back(pm);
    return false;
  }
  else if (CaselessStrCmp(key1str,"repeat")) {
    if (!CaselessStrCmp(key3str, "for")) {
      err << "the only type of phraSED-ML content that fits the syntax '[ID] = repeat [string] [keyword] [...]' is repeated tasks, where 'keyword' is the word 'for' (i.e. 'rt1 = repeat task1 for S1 in uniform(0,10,100)').";
      setError(err.str(), phrased_yylloc_last_line-1);
      return true;
    }
    if (checkId(key2)) {
      return true;
    }
    PhrasedRepeatedTask rt(namestr, key2str, changelist);
    if (rt.changeListIsInappropriate(err)) {
      return true;
    }
    m_repeatedTasks.push_back(rt);
  }
  else {
    err << "unsupported keyword '" << key1str << "'.  Try 'model' or 'repeat' in this context.";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
  }
  return false;
}


bool Registry::addEquals(vector<const string*>* name, vector<const string*>* key1, vector<const string*>* key2, vector<const string*>* key3, vector<const string*>* key4)
{
  if (checkId(name)) {
    return true;
  }
  string namestr = getStringFrom(name);
  string key1str = getStringFrom(key1);
  string key2str = getStringFrom(key2);
  string key3str = getStringFrom(key3);
  string key4str = getStringFrom(key4);
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line-1 << " ('" << namestr << " = " << key1str << " " << key2str << " " << key3str << " " << key4str << "'): ";
  if (CaselessStrCmp(key1str,"run")) {
    if (!CaselessStrCmp(key3str, "on")) {
      err << "the only type of phraSED-ML content that fits the syntax '[ID] = run [string] [keyword] [string]' is task definitions, where 'keyword' is the word 'on' (i.e. 'task1 = run sim1 on mod0').";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
    }
    PhrasedTask pt(namestr, key2str, key4str);
    m_tasks.push_back(pt);
    return false;
  }
  else {
    err << "unsupported keyword '" << key1str << "'.  Try 'run' in this context.";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
  }
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

bool Registry::addRepeatedTask(vector<const string*>* name, vector<const string*>* key1, vector<vector<const string*>*>*  key2, vector<const string*>* key3, vector<ModelChange>* changelist)
{
  if (key2==NULL) return true;
  if (key2->size()==0) return true;
  vector<const string*>* task = (*key2)[0];
  if (addEquals(name, key1, task, key3, changelist)) {
    return true;
  }
  for (size_t t=1; t<key2->size(); t++) {
    vector<const string*>* task = (*key2)[t];
    if (checkId(task)) {
      return true;
    }
    m_repeatedTasks[m_repeatedTasks.size()-1].addTask(getStringFrom(task));
  }
  return false;
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
    else if (CaselessStrCmp(key2str,"uniform") || CaselessStrCmp(key2str, "uniform_stochastic")) {
      bool stochastic=CaselessStrCmp(key2str, "uniform_stochastic");
      if (numlist->size() == 3) {
        PhrasedUniform* puniform = new PhrasedUniform(namestr, (*numlist)[0], (*numlist)[0], (*numlist)[1], (long)(*numlist)[2], stochastic);
        m_simulations.push_back(puniform);
        return false;
      }
      else if (numlist->size() == 4) {
        PhrasedUniform* puniform = new PhrasedUniform(namestr, (*numlist)[0], (*numlist)[1], (*numlist)[2], (long)(*numlist)[3], stochastic);
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

bool Registry::addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* value)
{
  string namestr = getStringFrom(name);
  string valstr  = getStringFrom(value);
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line-1 << " ('" << namestr << " = " << valstr << "'): ";
  if (name->size() <= 1) {
    err << "this formulation is only used to set the specifics of simulation algorithms.  Try lines like 'sim1.algorithm = CVODE' or 'sim1.algorithm.relative_tolerance = 2.2'.";
    setError(err.str(), phrased_yylloc_last_line);
    return true;
  }
  else if (name->size()==2 || name->size()==3) {
    PhrasedSimulation* phrasedsim = g_registry.getSimulation(*(*name)[0]);
    if (phrasedsim==NULL) {
      err << "this formulation can only be used for simulation algorithms, and '" << *(*name)[0] << "' is not a simulation.";
      setError(err.str(), phrased_yylloc_last_line);
      return true;
    }
    if (!CaselessStrCmp(*(*name)[1], "algorithm")) {
      err << "the specific type of an simulation's algorithm can only be set by using the keyword 'algorithm', i.e. '" << *(*name)[0] << ".algorithm'.";
      setError(err.str(), phrased_yylloc_last_line);
      return true;
    }
    if (name->size() == 2) {
      if (phrasedsim->setAlgorithmKisao(*value, err)) return true;
    }
    else {
      if (phrasedsim->addAlgorithmParameter((*name)[2], &valstr, err)) return true;
    }
  }
  else {
    err << "'" << namestr << "' has too many subvariables.  This formulation is only used to set the specifics of simulation algorithms.  Try lines like 'sim1.algorithm = CVODE' or 'sim1.algorithm.relative_tolerance = 2.2'.";
    setError(err.str(), phrased_yylloc_last_line);
    return true;
  }
  return false;
}

bool Registry::addEquals(std::vector<const std::string*>* name, double value)
{
  string namestr = getStringFrom(name);
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line << " ('" << namestr << " = " << value << "'): ";
  if (name->size() <= 2 || name->size() > 3) {
    err << "this formulation is only used to set the specifics of simulation algorithms.  Try lines like 'sim1.algorithm = kisao.19' or 'sim1.algorithm.relative_tolerance = 2.2'.";
    setError(err.str(), phrased_yylloc_last_line);
    return true;
  }
  PhrasedSimulation* phrasedsim = g_registry.getSimulation(*(*name)[0]);
  if (phrasedsim==NULL) {
    err << "this formulation can only be used for simulation algorithms, and '" << *(*name)[0] << "' is not a simulation.";
    setError(err.str(), phrased_yylloc_last_line);
    return true;
  }
  if (!CaselessStrCmp(*(*name)[1], "algorithm")) {
    err << "the specific type of an simulation's algorithm can only be set by using the keyword 'algorithm', i.e. '" << *(*name)[0] << ".algorithm'.";
    setError(err.str(), phrased_yylloc_last_line);
    return true;
  }
  if (phrasedsim->addAlgorithmParameter((*name)[2], value, err)) {
    return true;
  }
  return false;
}


//phraSED-ML lines that are clearly plots:
bool Registry::addOutput(vector<const string*>* plot,  vector<vector<string>*>* plotlist, const std::string* name)
{
  if (plotlist==NULL || plotlist->size()==0) {
    setError("Error in addOutput:  no plotlist given.", phrased_yylloc_last_line-1);
    return true;
  }
  string plotstr = getStringFrom(plot);
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line-1 << " ('" << plotstr << " ";
  for (size_t pl=0; pl<plotlist->size(); pl++) {
    if (pl>0) {
      err << ", ";
    }
    err << getStringFrom((*plotlist)[pl], " ");
  }
  err << "'): ";

  if (CaselessStrCmp(plotstr,"plot")) {
    if (addPlot(plotlist, err, name)) {
      return true;
    }
  }
  else if (CaselessStrCmp(plotstr,"report")) {
    if (addReport(plotlist, err, name)) {
      return true;
    }
  }
  else {
    err << "lines of this type are only valid if the first word is 'plot' or 'report', such as 'plot task1.time vs task1.S1' or 'report task1.time, task1.S1, task1.S2'.";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
  }
  return false;
}


//ChangeList addition
bool Registry::addToChangeList(vector<ModelChange>* cl, vector<const string*>* key1, vector<const string*>* key2)
{
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line -1 << " at '" << getStringFrom(key1) << " " << getStringFrom(key2) << "': changes to models of the form '[keyword] [id]' (such as 'remove S1') are not currently supported.  Future plans include incorporation of this functionality.";
  setError(err.str(), phrased_yylloc_last_line-1);
  return true;
}


bool Registry::addMapToChangeList(vector<ModelChange>* cl, vector<const string*>* name, vector<const string*>* arg, vector<string>* formula)
{
  std::string source;
  if (arg->size())
    source = *(*arg).at(0);
  ModelChange mc(name, source, formula, true);
  cl->push_back(mc);
  return false;
}


bool Registry::addToChangeList(vector<ModelChange>* cl, vector<const string*>* name, vector<string>* formula)
{
  ModelChange mc(name, formula);
  cl->push_back(mc);
  return false;
}


bool Registry::addToChangeListFromRange(vector<ModelChange>* cl, vector<const string*>* name, vector<const string*>* range, vector<string>* formula)
{
  std::string source_range;
  if (range->size() && range->at(0)) {
    source_range = *range->at(0);
  }
  ModelChange mc(name, source_range, formula, false);
  cl->push_back(mc);
  return false;
}


bool Registry::addToChangeList(vector<ModelChange>* cl, vector<const string*>* key1, vector<const string*>* name, vector<string>* formula, bool usedEquals)
{
  stringstream err;
  if (usedEquals) {
    err << "Unable to parse line " << phrased_yylloc_last_line -1 << " at '" << getStringFrom(key1) << " " << getStringFrom(name) << " = " << getStringFrom(formula, " ") << "': changes to models of the form '[keyword] [id] = [formula]' (such as 'compute S1 = k1/k2') are not currently supported.  Future plans include incorporation of this functionality.";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
  }
  err << "Unable to parse line " << phrased_yylloc_last_line -1 << " at '" << getStringFrom(key1) << " " << getStringFrom(name) << " (" << getStringFrom(formula, " ") << ")': changes to models of the form '[keyword] [keyword] ( [formula] )' (such as 'S1 in (uniform(0,10,100)+x)') are not currently supported.  Future plans include incorporation of this functionality.";
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

bool Registry::addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<double>* numlist)
{
  string key1str = getStringFrom(key1);
  string key2str = getStringFrom(key2);
  string key3str = getStringFrom(key3);
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line << " at '" << key1str << " " << key2str << " " << key3str << "(";
  for (size_t n=0; n<numlist->size(); n++) {
    if (n!=0) {
      err << ", ";
    }
    err << (*numlist)[n];
  }
  err << ")': ";

  if (key2str != "in") {
    err << "Changes of the form '[string] [keyword] [function()]' are only valid when [keyword] is 'in'.";
    setError(err.str(), phrased_yylloc_last_line);
    return true;
  }

  change_type type = ctype_loop_uniformLinear;
  if (CaselessStrCmp(key3str, "uniformLog") || CaselessStrCmp(key3str, "logUniform") ){
    type = ctype_loop_uniformLog;
  }
  else if (!CaselessStrCmp(key3str, "uniform") && !CaselessStrCmp(key3str, "uniformLinear") && !CaselessStrCmp(key3str, "linearUniform") ) {
    err << "Unrecognized function name '" << key3str << "'.  Known function names for changes in this format are 'uniform' and 'logUniform'.";
    setError(err.str(), phrased_yylloc_last_line);
    return true;
  }
  if (numlist->size() != 3) {
    err << "Incorrect number of arguments to '" << key3str << "' function; expected three (start, stop, numPoints).";
    setError(err.str(), phrased_yylloc_last_line);
    return true;
  }
  ModelChange mc(type, key1, numlist);
  cl->push_back(mc);
  return false;
}

bool Registry::addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<double>* numlist)
{
  string key1str = getStringFrom(key1);
  string key2str = getStringFrom(key2);
  stringstream err;
  err << "Unable to parse line " << phrased_yylloc_last_line << " at '" << key1str << " " << key2str << " [";
  for (size_t n=0; n<numlist->size(); n++) {
    if (n!=0) {
      err << ", ";
    }
    err << (*numlist)[n];
  }
  err << "]': ";

  if (key2str != "in") {
    err << "Changes of the form '[string] [keyword] [numlist]' are only valid when [keyword] is 'in'.";
    setError(err.str(), phrased_yylloc_last_line);
    return true;
  }

  ModelChange mc(ctype_loop_vector, key1, numlist);
  cl->push_back(mc);
  return false;
}

bool Registry::setName(vector<const string*>* id, vector<const string*>* is, const string* name)
{
  string idstr = getStringFrom(id);
  string isstr = getStringFrom(is);
  stringstream err;
  if (!CaselessStrCmp(isstr,"is")) {
    err << "Unable to parse line " << phrased_yylloc_last_line << " ('" << idstr << " " << isstr << " \"" << *name << "\"'): the only type of phraSED-ML content that fits the syntax '[ID] [keyword] \"[string]\"' is setting the names of elements, where 'keyword' is the word 'is' (i.e. 'mod1 is \"Biomodels file #322\"').";
    setError(err.str(), phrased_yylloc_last_line);
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
  for (size_t s=0; s<m_simulations.size(); s++) {
    if (m_simulations[s]->getId() == idstr) {
      m_simulations[s]->setName(*name);
      return false;
    }
  }
  for (size_t t=0; t<m_tasks.size(); t++) {
    if (m_tasks[t].getId() == idstr) {
      m_tasks[t].setName(*name);
      return false;
    }
  }
  for (size_t rt=0; rt<m_repeatedTasks.size(); rt++) {
    if (m_repeatedTasks[rt].getId() == idstr) {
      m_repeatedTasks[rt].setName(*name);
      return false;
    }
  }
  for (size_t o=0; o<m_outputs.size(); o++) {
    if (m_outputs[o].getId() == idstr) {
      m_outputs[o].setName(*name);
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
  string newfile = m_workingDirectory + "/" + filename;
  if (file_exists(newfile)) return newfile;
  return "";
}

char* Registry::getPhraSEDML() const
{
  string retval  = "// Created by libphrasedml ";
  retval += LIBPHRASEDML_VERSION_STRING;
  string names = "";
  for (size_t m=0; m<m_models.size(); m++) {
    if (m==0) {
      retval += "\n// Models\n";
    }
    retval += m_models[m].getPhraSEDML();
    if (m_models[m].getName() != "") {
      names += m_models[m].getId() + " is \"" + m_models[m].getName() + "\"\n";
    }
  }


  for (size_t s=0; s<m_simulations.size(); s++) {
    if (s==0) {
      retval += "\n// Simulations\n";
    }
    retval += m_simulations[s]->getPhraSEDML();
    if (m_simulations[s]->getName() != "") {
      names += m_simulations[s]->getId() + " is \"" + m_simulations[s]->getName() + "\"\n";
    }
  }


  for (size_t t=0; t<m_tasks.size(); t++) {
    if (t==0) {
      retval += "\n// Tasks\n";
    }
    retval += m_tasks[t].getPhraSEDML();
    if (m_tasks[t].getName() != "") {
      names += m_tasks[t].getId() + " is \"" + m_tasks[t].getName() + "\"\n";
    }
  }

  for (size_t t=0; t<m_repeatedTasks.size(); t++) {
    if (t==0) {
      retval += "\n// Repeated Tasks\n";
    }
    retval += m_repeatedTasks[t].getPhraSEDML();
    if (m_repeatedTasks[t].getName() != "") {
      names += m_repeatedTasks[t].getId() + " is \"" + m_repeatedTasks[t].getName() + "\"\n";
    }
  }

  for (size_t t=0; t<m_outputs.size(); t++) {
    if (t==0) {
      retval += "\n// Outputs\n";
    }
    retval += m_outputs[t].getPhraSEDML();
    //Outputs handle their own names.
  }

  if (names != "") {
    retval += "\n// Names\n" + names + "\n";
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
  if (m_sedml->getVersion() < 4) {
      m_sedml->setVersion(4);
  }
  ostringstream stream;
  SedWriter sw;
  sw.setProgramName("phraSED-ML");
  sw.setProgramVersion(LIBPHRASEDML_VERSION_STRING);
  sw.writeSedML(m_sedml, stream);
  string ret = stream.str();
  // fix single quotes
  size_t replace = ret.find("&apos;");
  while (replace != string::npos) {
    ret.replace(replace, 6, "'");
    replace = ret.find("&apos;");
  }
  // fix double quotes
  replace = ret.find("&quot;");
  while (replace != string::npos) {
    ret.replace(replace, 6, "\"");
    replace = ret.find("&quot;");
  }
  // fix min/max symbols
  ret = fixMinMaxSymbolsXMLStr(ret);
  return g_registry.getCharStar(ret.c_str());
}

size_t Registry::getNumModels() const
{
  return m_models.size();
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

const PhrasedSimulation* Registry::getSimulation(string simid) const
{
  for (size_t s=0; s<m_simulations.size(); s++) {
    if (m_simulations[s]->getId() == simid) {
      return m_simulations[s];
    }
  }
  return NULL;
}

PhrasedSimulation* Registry::getSimulation(string simid)
{
  for (size_t s=0; s<m_simulations.size(); s++) {
    if (m_simulations[s]->getId() == simid) {
      return m_simulations[s];
    }
  }
  return NULL;
}

const PhrasedTask* Registry::getTask(string taskid) const
{
  for (size_t s=0; s<m_tasks.size(); s++) {
    if (m_tasks[s].getId() == taskid) {
      return &m_tasks[s];
    }
  }
  for (size_t s=0; s<m_repeatedTasks.size(); s++) {
    if (m_repeatedTasks[s].getId() == taskid) {
      return &m_repeatedTasks[s];
    }
  }
  return NULL;
}

PhrasedTask* Registry::getTask(string taskid)
{
  for (size_t s=0; s<m_tasks.size(); s++) {
    if (m_tasks[s].getId() == taskid) {
      return &m_tasks[s];
    }
  }
  for (size_t s=0; s<m_repeatedTasks.size(); s++) {
    if (m_repeatedTasks[s].getId() == taskid) {
      return &m_repeatedTasks[s];
    }
  }
  return NULL;
}

size_t Registry::getNumTasks() const
{
  return m_tasks.size() + m_repeatedTasks.size();
}

const PhrasedTask* Registry::getTask(size_t num) const
{
  if (num >= m_tasks.size()) {
    num = num - m_tasks.size();
    if (num >= m_repeatedTasks.size()) {
      return NULL;
    }
    return &m_repeatedTasks[num];
  }
  return &m_tasks[num];
}

void Registry::createSEDML()
{
  delete m_sedml;
  m_sedml = new SedDocument(1, 4);
  for (size_t m=0; m<m_models.size(); m++) {
    m_models[m].addModelToSEDML(m_sedml);
  }
  for (size_t s=0; s<m_simulations.size(); s++) {
    m_simulations[s]->addSimulationToSEDML(m_sedml);
  }
  for (size_t t=0; t<m_tasks.size(); t++) {
    m_tasks[t].addTaskToSEDML(m_sedml);
  }
  for (size_t rt=0; rt<m_repeatedTasks.size(); rt++) {
    m_repeatedTasks[rt].addRepeatedTaskToSEDML(m_sedml);
  }
  for (size_t rt=0; rt<m_outputs.size(); rt++) {
    m_outputs[rt].addOutputToSEDML(m_sedml);
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
  for (size_t t=0; t<m_tasks.size(); t++) {
    if (m_tasks[t].finalize()) {
      return true;
    }
  }
  for (size_t t=0; t<m_repeatedTasks.size(); t++) {
    if (m_repeatedTasks[t].finalize()) {
      return true;
    }
  }
  for (size_t o=0; o<m_outputs.size(); o++) {
    if (m_outputs[o].finalize()) {
      return true;
    }
    stringstream id;
    if (m_outputs[o].isPlot()) {
      id << "plot";
    }
    else {
      id << "report";
    }
    id << "_" << o;
    m_outputs[o].setId(id.str());
  }

  return false;
}

void Registry::setReferencedSBML(const char* filename, SBMLDocument* doc)
{
  m_referencedSBML.insert(make_pair(filename, doc));
}

void Registry::clearReferencedSBML()
{
  for (map<string, SBMLDocument*>::iterator el = m_referencedSBML.begin(); el!= m_referencedSBML.end(); el++) {
    delete el->second;
  }
  m_referencedSBML.clear();
}

void Registry::addDotXMLToModelSources(bool force)
{
  for (size_t m=0; m<m_models.size(); m++) {
    if (m_models[m].getIsFile()) {
      string modelname = m_models[m].getSource();
      if (modelname.find(".xml") == string::npos && modelname.find(".sbml") == string::npos && modelname.find("urn:") == string::npos) {
        m_models[m].setSource(modelname + ".xml");
      }
    }
  }
  if (m_sedml != NULL) {
    for (unsigned long sm=0; sm<m_sedml->getNumModels(); sm++) {
      SedModel* sedmodel = m_sedml->getModel(sm);
      string modelstr = sedmodel->getSource();
      if ((m_sedml->getModel(modelstr) == NULL || m_sedml->getModel(modelstr) == sedmodel) && modelstr.find(".xml") == string::npos && modelstr.find(".sbml") == string::npos) {
        //It's a filename without ".xml"
        sedmodel->setSource(modelstr + ".xml");
      }
    }
  }
}

void Registry::SetWriteSEDMLTimestamp(bool set)
{
#if LIBSBML_VERSION >= 51201
  XMLOutputStream::setWriteTimestamp(set);
#endif
}

bool Registry::GetWriteSEDMLTimestamp()
{
#if LIBSBML_VERSION >= 51201
  return XMLOutputStream::getWriteTimestamp();
#endif
  return true;
}

SBMLDocument* Registry::getSavedSBML(std::string filename)
{
  map<string, SBMLDocument*>::iterator ret = m_referencedSBML.find(filename);
  if (ret != m_referencedSBML.end()) {
    return ret->second;
  }
  return NULL;
}


void Registry::freeAllPhrased()
{
  for (size_t i=0; i<m_charstars.size(); i++) {
    free(m_charstars[i]);
  }
  m_charstars.clear();
}


bool Registry::parseInput()
{
  clearAll();
  clearSEDML();
  int success = phrased_yyparse();
  if (success != 0) {
    if (getError().empty()) {
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
  for (unsigned int t=0; t<m_sedml->getNumTasks(); t++) {
    SedAbstractTask* sedtask = m_sedml->getTask(t);
    if (sedtask->getTypeCode() == SEDML_TASK) {
      PhrasedTask pt(static_cast<SedTask*>(sedtask));
      m_tasks.push_back(pt);
    }
    else if (sedtask->getTypeCode() == SEDML_TASK_REPEATEDTASK) {
      SedRepeatedTask* srt = static_cast<SedRepeatedTask*>(sedtask);
      PhrasedRepeatedTask rt(srt);
      m_repeatedTasks.push_back(rt);
    }
    else {
      setError("SED-ML task '" + sedtask->getId() + "' has unknown type.", 0);
      return true;
    }
  }
  for (unsigned int out=0; out<m_sedml->getNumOutputs(); out++) {
    SedOutput* output = m_sedml->getOutput(out);
    PhrasedOutput phrasedout(output, m_sedml);
    m_outputs.push_back(phrasedout);
  }
  return finalize();
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
  m_tasks.clear();
  m_repeatedTasks.clear();
  m_outputs.clear();
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

bool Registry::addASTToCurve(const vector<string>* x, vector<ASTNode*>& curve, stringstream& err)
{
  ASTNode* xAST = parseFormula(getStringFrom(x, " "));
  if (xAST==NULL) {
    err << "unable to parse the formula '" << getStringFrom(x, " ") << "' as a valid mathematical expression.";
    setError(err.str(), phrased_yylloc_last_line-1);
    return true;
  }
  curve.push_back(xAST);
  return false;
}

ASTNode* Registry::parseFormula(const string& formula)
{
  ASTNode* ret = SBML_parseL3FormulaWithSettings(formula.c_str(), &m_l3ps);
  //set<string> variables;
  //getVariablesFromASTNode(ret->deepCopy(), variables);
  return fixTime(ret);
}

ASTNode* Registry::fixTime(ASTNode* astn)
{
  if (astn==NULL) return NULL;
  if (astn->getType() == AST_NAME_TIME) {
    astn->setName("time");
    astn->setType(AST_NAME);
    astn->setDefinitionURL("");
  }
  for (unsigned int c=0; c<astn->getNumChildren(); c++) {
    fixTime(astn->getChild(c));
  }
  return astn;
}

bool Registry::addPlot( vector<vector<string>*>* plotlist, stringstream& err, const string* name)
{
  //Break up the plotlist vector if it has 'vs' in it
  vector<string> x;
  vector<string> y;
  vector<string> z;
  vector<ASTNode*> curve;
  vector<vector<ASTNode*> > curves;
  vector<string> thisoutput;
  int axis = 0;
  for (size_t pl=0; pl<plotlist->size(); pl++) {
    vector<string>* elements = (*plotlist)[pl];
    for (size_t e=0; e<elements->size(); e++) {
      string element = (*elements)[e];
      if (CaselessStrCmp(element, "vs")) {
        if (axis==0) {
          x = thisoutput;
          axis++;
        }
        else if (axis==1) {
          y = thisoutput;
          axis++;
        }
        else if (axis==2) {
          err << "can only create plots of two or three dimensions.  Use 'report' instead of 'plot' to output four-dimensional or higher data.";
          setError(err.str(), phrased_yylloc_last_line-1);
          return true;
        }
        thisoutput.clear();
      }
      else {
        thisoutput.push_back(element);
      }
    }
    if (x.empty()) {
      err << "can only create plots of two or three dimensions, not one.  Use 'report' instead of 'plot' to output one-dimensional data, or use 'vs' to distinguish axes in 2D or 3D data ('plot S1 vs S2').";
      setError(err.str(), phrased_yylloc_last_line-1);
      return true;
    }
    else if (y.empty()) {
      y = thisoutput;
    }
    else if (z.empty()) {
      z = thisoutput;
    }
    if (addASTToCurve(&x, curve, err)) {
      return true;
    }
    if (addASTToCurve(&y, curve, err)) {
      return true;
    }
    if (!z.empty()) {
      if (addASTToCurve(&z, curve, err)) {
        return true;
      }
    }
    curves.push_back(curve);
    axis = 0;
    y.clear();
    z.clear();
    thisoutput.clear();
    curve.clear();
  }
  size_t size = curves[0].size();
  for (size_t c=1; c<curves.size(); c++) {
    if (size != curves[c].size()) {
      err << "unable to create a single plot with both 2d and 3d data.  Create these plots separately, or adjust the dimensionality of the data.";
      setError(err.str(), phrased_yylloc_last_line-1);
      return true;
    }
  }
  PhrasedOutput pout(curves);
  if (name) {
    pout.setName(*name);
  }
  m_outputs.push_back(pout);
  return false;
}

bool Registry::addReport( vector<vector<string>*>* plotlist, stringstream& err, const string* name)
{
  //For reports, we treat 'vs' and commas as exactly the same thing:  everything simply gets listed.
  vector<vector<string> > outputs;
  vector<string> thisoutput;
  for (size_t pl=0; pl<plotlist->size(); pl++) {
    vector<string>* elements = (*plotlist)[pl];
    for (size_t e=0; e<elements->size(); e++) {
      string element = (*elements)[e];
      if (CaselessStrCmp(element, "vs")) {
        outputs.push_back(thisoutput);
        thisoutput.clear();
      }
      else {
        thisoutput.push_back(element);
      }
    }
    outputs.push_back(thisoutput);
    thisoutput.clear();
  }
  vector<ASTNode*> outputASTs;
  for (size_t i=0; i<outputs.size(); i++) {
    string wholeoutput = getStringFrom(&(outputs[i]), " ");
    ASTNode* astn = parseFormula(wholeoutput);
    if (astn == NULL) {
      err << "unable to parse the formula '" << wholeoutput << "' as a valid mathematical expression.";
      setError(err.str(), phrased_yylloc_last_line-1);
      return true;
    }
    outputASTs.push_back(astn);
  }
  PhrasedOutput pout(outputASTs);
  if (name) {
    pout.setName(*name);
  }
  m_outputs.push_back(pout);
  return false;
}

//Useful functions for later routines:
char* Registry::getCharStar(const char* orig)
{
  char* ret = strdup(orig);
  if (ret == NULL) {
    setError("Out of memory error.", phrased_yylloc_last_line-1);
    return NULL;
  }
  m_charstars.push_back(ret);
  return ret;
}

PHRASEDML_CPP_NAMESPACE_END
