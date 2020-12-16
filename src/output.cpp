#include "registry.h"
#include "output.h"
#include "sbmlx.h"
#include "stringx.h"
#include "task.h"
#include "model.h"

#include "sedml/SedPlot2D.h"
#include "sedml/SedPlot3D.h"
#include "sedml/SedDataGenerator.h"
#include "sedml/SedOutput.h"
#include "sedml/SedDocument.h"
#include "sedml/SedVariable.h"

using namespace std;
using namespace libsbml;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp

PHRASEDML_CPP_NAMESPACE_BEGIN
PhrasedOutput::PhrasedOutput(const vector<ASTNode*>& inputs)
  : Variable("_none")
  , m_isPlot(false)
  , m_outputVariables()
{
  m_outputVariables.push_back(inputs);
}

PhrasedOutput::PhrasedOutput(const std::vector<std::vector<ASTNode*> >& outputs)
  : Variable("_none")
  , m_isPlot(true)
  , m_outputVariables(outputs)
{
}

ASTNode* getASTNodeFrom(SedDataGenerator* datagen, SedDocument* seddoc, bool isLog)
{
  ASTNode* astn = datagen->getMath()->deepCopy();
  //Here is where we would make sure we could find things again!
  // LS DEBUG
  if (isLog) {
    ASTNode* newroot = new ASTNode(AST_FUNCTION_LOG);
    ASTNode ten(AST_INTEGER);
    ten.setValue(10);
    newroot->addChild(ten.deepCopy());
    newroot->addChild(astn);
    return newroot;
  }
  //And now we need to fix the IDs so that they match the actual thing they point to.
  map<string, string> dg2modvar;
  for (unsigned long v=0; v<datagen->getNumVariables(); v++) {
    SedVariable* var = datagen->getVariable(v);
    string id = var->getId();
    string task = var->getTaskReference();
    string model = var->getModelReference();
    vector<string> element;
    if (var->isSetTarget()) {
      element = getIdFromXPath(var->getTarget());
    }
    else if (var->isSetSymbol()) {
      if (var->getSymbol() == "urn:sedml:symbol:time") {
        element.push_back("time");
      }
      else {
        g_registry.addWarning("Unknown variable symbol '" + var->getSymbol() + "'.");
        element.push_back(id);
      }
    }
    else {
      g_registry.addWarning("Variable found without a symbol or a target: '" + id + "'.");
      element.push_back(id);
    }
    if (!model.empty()) {
      element.insert(element.begin(), model);
    }
    if (!task.empty()) {
      element.insert(element.begin(), task);
    }
    string newid = getStringFrom(&element, g_registry.getSeparator());
    dg2modvar.insert(make_pair(id, newid));
  }
  for (unsigned long p=0; p<datagen->getNumParameters(); p++) {
    SedParameter* param = datagen->getParameter(p);
    string id = param->getId();
    assert(false); 
  }
  replaceVariablesInASTNodeWith(astn, dg2modvar);
  return astn;
}

PhrasedOutput::PhrasedOutput(SedOutput* sedout, SedDocument* seddoc)
  : Variable("sedout")
  , m_isPlot(true)
  , m_outputVariables()
{
  if (sedout->isSetName()) {
    setName(sedout->getName());
  }
  if (sedout->isSetId()) {
    setId(sedout->getId());
  }
  switch(sedout->getTypeCode()) {
  case SEDML_OUTPUT_PLOT2D:
    {
      SedPlot2D* plot2d = static_cast<SedPlot2D*>(sedout);
      for (unsigned long p=0; p<plot2d->getNumCurves(); p++) {
        vector<ASTNode*> astns;
        SedAbstractCurve* abstractcurve = plot2d->getCurve(p);
        if (abstractcurve->getTypeCode() == SEDML_OUTPUT_CURVE) {
            SedCurve* curve = static_cast<SedCurve*>(abstractcurve);
            SedDataGenerator* datagen = seddoc->getDataGenerator(curve->getXDataReference());
            astns.push_back(getASTNodeFrom(datagen, seddoc, curve->getLogX()));
            datagen = seddoc->getDataGenerator(curve->getYDataReference());
            astns.push_back(getASTNodeFrom(datagen, seddoc, false));
            m_outputVariables.push_back(astns);
        }
        else {
            //It's a SedShadedArea, which we don't handle.
        }
      }
    }
    break;
  case SEDML_OUTPUT_PLOT3D:
    {
      SedPlot3D* plot3d = static_cast<SedPlot3D*>(sedout);
      for (unsigned long s=0; s<plot3d->getNumSurfaces(); s++) {
        vector<ASTNode*> astns;
        SedSurface* surface = plot3d->getSurface(s);
        SedDataGenerator* datagen = seddoc->getDataGenerator(surface->getXDataReference());
        astns.push_back(getASTNodeFrom(datagen, seddoc, surface->getLogX()));
        datagen = seddoc->getDataGenerator(surface->getYDataReference());
        astns.push_back(getASTNodeFrom(datagen, seddoc, surface->getLogY()));
        datagen = seddoc->getDataGenerator(surface->getZDataReference());
        astns.push_back(getASTNodeFrom(datagen, seddoc, surface->getLogZ()));
        m_outputVariables.push_back(astns);
      }
    }
    break;
  case SEDML_OUTPUT_REPORT:
    {
      m_isPlot = false;
      SedReport* report = static_cast<SedReport*>(sedout);
      for (unsigned long r=0; r<report->getNumDataSets(); r++) {
        SedDataSet* dataset = report->getDataSet(r);
        SedDataGenerator* datagen = seddoc->getDataGenerator(dataset->getDataReference());
        ASTNode* astn = getASTNodeFrom(datagen, seddoc, false);
        vector<ASTNode*> astns;
        astns.push_back(astn);
        m_outputVariables.push_back(astns);
      }
    }
    break;
  default:
    assert(false);
    break;
  }
}


PhrasedOutput::~PhrasedOutput()
{
}

string PhrasedOutput::getPhraSEDML() const
{
  string ret = "";
  if (m_isPlot) {
    ret += "plot ";
  }
  else {
    ret += "report ";
  }
  if (!m_name.empty()) {
    ret += "\"" + m_name + "\" ";
  }
  std::vector<std::vector<ASTNode*> > truncatedvars = m_outputVariables;
  if (m_isPlot) {
    char* firstx = SBML_formulaToL3String(truncatedvars[0][0]);
    for (size_t p=1; p<truncatedvars.size(); p++) {
      char* thisx = SBML_formulaToL3String(truncatedvars[p][0]);
      if ((string)firstx == (string)thisx) {\
        truncatedvars[p].erase(truncatedvars[p].begin());
      }
      free(thisx);
    }
    free(firstx);
  }
  for (size_t p=0; p<truncatedvars.size(); p++) {
    if (p>0) {
      ret += ", ";
    }
    for (size_t a=0; a<truncatedvars[p].size(); a++) {
      if (a>0) {
        if (m_isPlot) {
          ret += " vs ";
        }
        else {
          ret += ", ";
        }
      }
      ret += SBML_formulaToL3String(truncatedvars[p][a]);
    }
  }
  string sep = g_registry.getSeparator();
  size_t underscores = ret.find(sep);
  while (underscores != string::npos) {
    ret.replace(underscores, sep.size(), ".");
    underscores = ret.find(sep);
  }
  size_t t=0;
  const PhrasedTask* task = g_registry.getTask(t);
  set<PhrasedModel*> taskmodels;
  if (task) {
    taskmodels = task->getModels();
  }
  if (g_registry.getNumTasks() == 1) {
    //We can delete the 'task.' bit from everything.
    sep = task->getId() + ".";
    size_t lonetask = ret.find(sep);
    while (lonetask != string::npos) {
      ret.replace(lonetask, sep.size(), "");
      lonetask = ret.find(sep);
    }
  }
  if (g_registry.getNumModels() == 1 ||
      (g_registry.getNumTasks() == 1 && taskmodels.size()==1))
  {
    sep = (*taskmodels.begin())->getId() + ".";
    size_t lonemod = ret.find(sep);
    while (lonemod != string::npos) {
      ret.replace(lonemod, sep.size(), "");
      lonemod = ret.find(sep);
    }
  }
  return ret + "\n";
}

string PhrasedOutput::getMatchingDataGenerator(SedDocument* sedml, ASTNode* astnode) const
{
  string ret = "";
  char* match_str = SBML_formulaToL3String(astnode);

  for (unsigned long dg=0; dg<sedml->getNumDataGenerators(); dg++) {
    SedDataGenerator* datagenerator = sedml->getDataGenerator(dg);
    const ASTNode* dg_astn = datagenerator->getMath();
    char* dg_str = SBML_formulaToL3String(dg_astn);
    if ((string)dg_str == (string) match_str) {
      free(dg_str);
      free(match_str);
      return datagenerator->getId();
    }
  }
  free(match_str);

  return ret;
}

string PhrasedOutput::addDataGeneratorToSEDML(SedDocument* sedml, ASTNode* astnode, int num1, int num2) const
{
  if (m_isPlot && astnode->isLog10()) {
    astnode = astnode->getChild(1);
  }
  string matching = getMatchingDataGenerator(sedml, astnode);
  if (!matching.empty()) return matching;
  stringstream id;
  id << m_id << "_" << num1 << "_" << num2;
  SedDataGenerator* sdg = sedml->createDataGenerator();
  sdg->setId(id.str());
  replaceASTNamesAndAdd(astnode, sdg);
  sdg->setMath(astnode);
  char* formula = SBML_formulaToL3String(astnode);
  sdg->setName(getSimpleString(formula));
  free(formula);
  return id.str();
}

void PhrasedOutput::addOutputToSEDML(SedDocument* sedml) const
{
  SedPlot3D* plot3d = NULL;
  SedPlot2D* plot2d = NULL;
  SedReport* report = NULL;
  if (m_isPlot) {
    if (m_outputVariables[0].size() == 2) {
      plot2d = sedml->createPlot2D();
      plot2d->setId(m_id);
      plot2d->setName(m_name);
    }
    else {
      plot3d = sedml->createPlot3D();
      plot3d->setId(m_id);
      plot3d->setName(m_name);
    }
  }
  else {
    report = sedml->createReport();
    report->setId(m_id);
    report->setName(m_name);
  }

  for (size_t ov=0; ov<m_outputVariables.size(); ov++) {
    vector<string> datagennames;
    vector<string> datagenlabels;
    const vector<ASTNode*>* vec = &(m_outputVariables[ov]);
    //Create Data Generators for each element.
    for (size_t an=0; an<vec->size(); an++) {
      datagennames.push_back(addDataGeneratorToSEDML(sedml, (*vec)[an], ov, an));
      char* cformula = SBML_formulaToL3String((*vec)[an]);
      datagenlabels.push_back(getSimpleString(cformula));
      free(cformula);
    }
    //Map those data generators to the plot/reports
    if (m_isPlot) {
      if (m_outputVariables[0].size() == 3) {
        SedSurface* surface = plot3d->createSurface();
        surface->setXDataReference(datagennames[0]);
        surface->setYDataReference(datagennames[1]);
        surface->setZDataReference(datagennames[2]);
        surface->setLogX((*vec)[0]->isLog10());
        surface->setLogY((*vec)[1]->isLog10());
        surface->setLogZ((*vec)[2]->isLog10());
        surface->setId(m_id + "__" + datagennames[0] + "__" + datagennames[1] + "__" + datagennames[2]);
      }
      else {
        SedCurve* curve = plot2d->createCurve();
        curve->setXDataReference(datagennames[0]);
        curve->setYDataReference(datagennames[1]);
        curve->setLogX((*vec)[0]->isLog10());
        curve->setLogY((*vec)[1]->isLog10());
        curve->setId(m_id + "__" + datagennames[0] + "__" + datagennames[1]);
      }
    }
    else {
      for (size_t d=0; d<datagennames.size(); d++) {
        SedDataSet* dataset = report->createDataSet();
        dataset->setDataReference(datagennames[d]);
        dataset->setLabel(datagenlabels[d]);
        dataset->setId(datagennames[d] + "_dataset");
      }
    }
  }
}
  

string PhrasedOutput::getSimpleString(string formula) const
{
  size_t space = formula.find(" ");
  while (space != string::npos) {
    formula.replace(space, 1, "");
    space = formula.find(" ");
  }
  size_t separators = formula.find(g_registry.getSeparator());
  while (separators != string::npos) {
    formula.replace(separators, g_registry.getSeparator().size(), ".");
    separators = formula.find(g_registry.getSeparator());
  }
  return formula;
}

bool PhrasedOutput::finalize()
{
  if (Variable::finalize()) {
    return true;
  }
  set<string> variables;
  for (size_t c=0; c<m_outputVariables.size(); c++) {
    for (size_t a=0; a<m_outputVariables[c].size(); a++) {
      getVariablesFromASTNode(m_outputVariables[c][a], variables);
    }
  }
  for (set<string>::iterator var = variables.begin(); var != variables.end(); var++) {
    if (addVariableToMap(*var)) {
      return true;
    }
  }
  return false;
}

bool getTask(vector<string>& varname, vector<string>& mapname, const PhrasedTask*& task, const PhrasedModel*& model, stringstream& err) {
  task = g_registry.getTask(varname[0]);
  size_t tasknum = 0;
  if (varname.size()==1 || task==NULL) {
    //There must be exactly one task in the model
    if (g_registry.getNumTasks() != 1) {
      err << "without referencing a valid task it came from (i.e. 'task1." << getStringFrom(&varname, ".") << "').  This is only legal if there is exactly one defined task, but here, there are " << g_registry.getNumTasks() << ".";
      g_registry.setError(err.str(), 0);
      return true;
    }
    task = g_registry.getTask(tasknum);
    assert(task != NULL); //Shouldn't, since there's one task in the registry.
    mapname.push_back(task->getId());
    return false;
  }
  mapname.push_back(task->getId());
  varname.erase(varname.begin(), varname.begin()+1);
  return false;
}


bool getModel(vector<string>& varname, vector<string>& mapname, const PhrasedTask*& task, const PhrasedModel*& model, stringstream& err) {
  if (varname.size() == 0) {
    err << "which couldn't be resolved.";
  }
  set<PhrasedModel*> models = task->getModels();
  for (set<PhrasedModel*>::iterator mod = models.begin(); mod != models.end(); mod++) {
    if (varname[0] == (*mod)->getId()) {
      model = *mod;
      break;
    }
  }
  if (varname.size()==1 || model==NULL) {
    const ModelChange* mc = task->getModelChangeFor(varname[0]);
    if (mc != NULL) {
      mapname.push_back("");
      return false;
    }
    if (models.size() == 1) {
      model = *(models.begin());
      mapname.push_back(model->getId());
      return false;
    }
    //Otherwise, it's an error:
    if (varname.size()==1) {
      err << "but there is no task subvariable named '" << varname[0] << "', either as a local variable for that task, or as a model variable that can be clearly mapped to a single model.  Variables in plot and report mathematics must be unambiguous, or defined clearly as 'task.model.varname'.";
      g_registry.setError(err.str(), 0);
      return true;
    }
    err << "but the task '" << task->getId() << "' has no corresponding model named '" << varname[0] << "', and has multiple models associated with it, with no single model that can be assumed to contain the variable.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  mapname.push_back(model->getId());
  varname.erase(varname.begin(), varname.begin()+1);
  return false;
}


bool getVariable(vector<string>& varname, vector<string>& mapname, const PhrasedTask*& task, const PhrasedModel*& model, stringstream& err) {
  if (varname.size() == 0) {
    err << "which couldn't be resolved.";
  }
  string fullvarname = getStringFrom(&varname, g_registry.getSeparator());
  if (varname[varname.size()-1] == "time") {
    mapname.push_back("time");
    return false;
  }
  if (model==NULL) {
    //It has to be a task model change variable or 'time'
    const ModelChange* mc = task->getModelChangeFor(varname[0]);
    if (varname.size() > 1 || mc == NULL) {
      err << "which is not a local variable for task '" << task->getId() << "'" ;
      if (varname.size() > 1) {
        err << ":  no local task variable has any subvariables.";
      }
      g_registry.setError(err.str(), 0);
      return true;
    }
    mapname.push_back(fullvarname);
    return false;
  }
  string xpath = getElementXPathFromId(&varname, model->getSBMLDocument());
  if (xpath.empty()) {
    err << "which cannot be found in task '" << task->getId() << "'s model '" << model->getId() << "'.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  mapname.push_back(fullvarname);
  return false;
}


bool PhrasedOutput::addVariableToMap(const string& var)
{
  stringstream err;
  vector<string> varname = getStringVecFromDelimitedString(var);
  err << "Error:  an output plot or report references variable '" << getStringFrom(&varname, ".") << "' ";
  if (varname.size()==0) {
    //Not sure how this would happen, but hey.
    err << "which has no name.  This should be impossible, but regardless, we cannot continue.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  vector<string> mapname;
  const PhrasedTask* task = NULL;
  const PhrasedModel* model = NULL;
  if (getTask(varname, mapname, task, model, err)) {
    return true;
  }
  if (getModel(varname, mapname, task, model, err)) {
    return true;
  }
  if (getVariable(varname, mapname, task, model, err)) {
    return true;
  }
  m_variableMap.insert(make_pair(var, mapname));
  return false;
}

void PhrasedOutput::replaceASTNamesAndAdd(ASTNode* astnode, SedDataGenerator* sdg) const
{
  if (astnode->getType() == AST_NAME) {
    string name = astnode->getName();
    vector<string> fullname = m_variableMap.find(astnode->getName())->second;
    assert(fullname.size()==3);
    if (sdg->getVariable(name)==NULL && sdg->getVariable(name)==NULL) {
      if (fullname[1].empty()) {
        //Need to create a local parameter.
        PhrasedTask* task = g_registry.getTask(fullname[0]);
        assert(task != NULL);
        const ModelChange* mc = task->getModelChangeFor(fullname[2]);
        assert(mc != NULL);
        SedParameter* param = sdg->createParameter();
        param->setId(name);
        param->setValue(mc->getValues()[0]);
      }
      else {
        //Create a new variable.
        SedVariable* var = sdg->createVariable();
        var->setId(astnode->getName());
        var->setTaskReference(fullname[0]);
        if (fullname[2] == "time") {
          var->setSymbol("urn:sedml:symbol:time");
          return;
        }
        var->setModelReference(fullname[1]);
        SBMLDocument* doc = g_registry.getModel(fullname[1])->getSBMLDocument();
        vector<string> idonly = getStringVecFromDelimitedString(fullname[2]);
        string xpath = getElementXPathFromId(&idonly, doc);
        var->setTarget(xpath);
      }
    }
  }
  else {
    for (unsigned int c=0; c<astnode->getNumChildren(); c++) {
      replaceASTNamesAndAdd(astnode->getChild(c), sdg);
    }
  }
}
PHRASEDML_CPP_NAMESPACE_END