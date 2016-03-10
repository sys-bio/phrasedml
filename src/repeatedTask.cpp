#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "registry.h"
#include "repeatedTask.h"
#include "stringx.h"
#include "sbmlx.h"
#include "sedml/SedRepeatedTask.h"

using namespace std;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp
PHRASEDML_CPP_NAMESPACE_BEGIN

PhrasedRepeatedTask::PhrasedRepeatedTask(std::string id, std::string task, vector<ModelChange>* changes)
  : PhrasedTask(id, "", "")
  , m_tasks()
  , m_changes(*changes)
  , m_resetModel(false)
{
  m_tasks.push_back(task);
}

PhrasedRepeatedTask::PhrasedRepeatedTask(SedRepeatedTask* sedRepeatedTask)
  : PhrasedTask(sedRepeatedTask)
  , m_tasks()
  , m_changes()
  , m_resetModel(false)
{
  if (sedRepeatedTask->isSetResetModel()) {
    m_resetModel = sedRepeatedTask->getResetModel();
  }
  for (unsigned long t=0; t<sedRepeatedTask->getNumSubTasks(); t++) {
    SedSubTask* sst = sedRepeatedTask->getSubTask(t);
    m_tasks.push_back(sst->getTask());
    if (sst->isSetOrder() && sst->getOrder() != t) {
      g_registry.addWarning("SED-ML repeated task '" + m_id + "' had a subtask '" + sst->getTask() + "', whose 'order' attribute did not match the order in the file.  The order in the file was used instead!");
    }
  }
  for (unsigned long r=0; r<sedRepeatedTask->getNumRanges(); r++) {
    SedRange* sr = sedRepeatedTask->getRange(r);
    ModelChange mc(sr);
    m_changes.push_back(mc);
    if (sr->getTypeCode() == SEDML_RANGE_FUNCTIONALRANGE) {
      SedFunctionalRange* sfr = static_cast<SedFunctionalRange*>(sr);
      for (unsigned long v=0; v<sfr->getNumVariables(); v++) {
        ModelChange mc_v(sfr);
        m_changes.push_back(mc_v);
      }
    }
  }
  for (unsigned long c=0; c<sedRepeatedTask->getNumTaskChanges(); c++) {
    SedSetValue* ssv = sedRepeatedTask->getTaskChange(c);
    ModelChange mc(ssv);
    m_changes.push_back(mc);
    for (unsigned long p=0; p<ssv->getNumParameters(); p++) {
      ModelChange mc_p(ssv->getParameter(p));
      m_changes.push_back(mc_p);
    }
  }
}

PhrasedRepeatedTask::~PhrasedRepeatedTask()
{
}

void PhrasedRepeatedTask::addTask(std::string task)
{
  m_tasks.push_back(task);
}

string PhrasedRepeatedTask::getPhraSEDML() const
{
  string ret = m_id + " = repeat " ;
  if (m_tasks.size() > 1) {
    ret += "[";
  }
  for (size_t t=0; t<m_tasks.size(); t++) {
    if (t>0) {
      ret += ", ";
    }
    ret += m_tasks[t];
  }
  if (m_tasks.size() > 1) {
    ret += "]";
  }
  ret += " for ";
  for (size_t c=0; c<m_changes.size(); c++) {
    if (c>0) {
      ret += ", ";
    }
    ret += m_changes[c].getPhraSEDML();
  }
  if (m_resetModel) {
    ret += ", reset=true";
  }
  ret += "\n";
  return ret;
}

void PhrasedRepeatedTask::addLocalVariablesToSetValue(SedSetValue* ssv, SedRepeatedTask* srt) const
{
  ASTNode* astn = const_cast<ASTNode*>(ssv->getMath());
  set<string> vars;
  getVariablesFromASTNode(astn, vars);
  for (set<string>::iterator v=vars.begin(); v != vars.end(); v++) {
    if (srt->getRange(*v) != NULL) {
      //Nothing we can do if there are two referenced ranges.
      ssv->setRange(*v);
    }
    else {
      set<PhrasedModel*> models = getModels();
      string xpath, modelref;
      getElementXPathFromId(*v, models, xpath, modelref);
      if (xpath.empty()) {
        //We need a local variable for it.  Check to see if one exists:
        bool found = false;
        for (size_t c=0; c<m_changes.size(); c++) {
          const ModelChange* mc = &m_changes[c];
          vector<string> varname = mc->getVariable();
          if (mc->getType() == ctype_val_assignment && varname.size()>1 && varname[0] == "local" && varname[1] == *v) {
            SedParameter* sp = ssv->createParameter();
            sp->setId(*v);
            sp->setValue(mc->getValues()[0]);
            found = true;
            continue;
          }
        }
        if (!found) {
          SedParameter* sp = ssv->createParameter();
          sp->setId(*v);
        }
      }
      else {
        SedVariable* sv = ssv->createVariable();
        sv->setModelReference(modelref);
        sv->setTarget(xpath);
        sv->setId(*v);
      }
    }
  }
}

void PhrasedRepeatedTask::addRepeatedTaskToSEDML(SedDocument* sedml) const
{
  SedRepeatedTask* sedRepeatedTask = sedml->createRepeatedTask();
  sedRepeatedTask->setId(m_id);
  sedRepeatedTask->setName(m_name);
  sedRepeatedTask->setResetModel(m_resetModel);
  for (size_t t=0; t<m_tasks.size(); t++) {
    SedSubTask* subtask = sedRepeatedTask->createSubTask();
    subtask->setOrder(t);
    subtask->setTask(m_tasks[t]);
  }
  for (size_t c=0; c<m_changes.size(); c++) {
    m_changes[c].addModelChangeToSEDMLRepeatedTask(sedRepeatedTask, m_tasks);
  }
  //Now that all the changes have been added, we make sure that all the math variables can be found
  for (size_t sv=0; sv<sedRepeatedTask->getNumTaskChanges(); sv++) {
    SedSetValue* ssv = sedRepeatedTask->getTaskChange(sv);
    addLocalVariablesToSetValue(ssv, sedRepeatedTask);
  }
}

bool PhrasedRepeatedTask::isRepeated() const
{
  return true;
}

const ModelChange* PhrasedRepeatedTask::getModelChangeFor(std::string varname) const
{
  for (size_t mc=0; mc<m_changes.size(); mc++) {
    vector<string> variable = m_changes[mc].getVariable();
    if (variable.size() == 1 && varname == variable[0]) {
      return &(m_changes[mc]);
    }
  }
  return NULL;
}

bool PhrasedRepeatedTask::changeListIsInappropriate(stringstream& err)
{
  for (size_t c=0; c<m_changes.size(); c++) {
    switch (m_changes[c].getType()) {
    case ctype_val_assignment:
    case ctype_formula_assignment:
    case ctype_loop_uniformLinear:
    case ctype_loop_uniformLog:
    case ctype_loop_vector:
      break;
      //If we get additions, deletions, etc.; those go here.
//      err << "The model change '" << m_changes[c].getPhraSEDML() << "' is not the type of change that can be used in a repeated task.  These changes must be used in models directly, instead.";
//      return true;
    }
  }
  return false;
}

set<PhrasedModel*> PhrasedRepeatedTask::getModels() const
{
  set<PhrasedModel*> ret;
  for (size_t t=0; t<m_tasks.size(); t++) {
    PhrasedTask* task = g_registry.getTask(m_tasks[t]);
    if (task != NULL) {
      set<PhrasedModel*> newmods = task->getModels();
      ret.insert(newmods.begin(), newmods.end());
    }
  }
  return ret;
}

bool PhrasedRepeatedTask::isRecursive(set<PhrasedTask*>& tasks)
{
  for (size_t t=0; t<m_tasks.size(); t++) {
    PhrasedTask* task = g_registry.getTask(m_tasks[t]);
    if (tasks.find(task) != tasks.end()) {
      return true;
    }
    set<PhrasedTask*> subtasks = tasks;
    subtasks.insert(task);
    if (task->isRecursive(subtasks)) {
      return true;
    }
  }
  return false;
}

bool ASTNodeHasId(const ASTNode* astn, const string& id) 
{
  if (astn->getType() == AST_NAME) {
    if (id == astn->getName()) {
      return true;
    }
  }
  for (unsigned int child=0; child<astn->getNumChildren(); child++) {
    if (ASTNodeHasId(astn->getChild(child), id)) {
      return true;
    }
  }
  return false;
}

bool PhrasedRepeatedTask::finalize()
{
  if (Variable::finalize()) {
    return true;
  }
  string err = "Error in repeatedTask '" + m_id + "':  ";
  set<PhrasedTask*> tasks;
  for (size_t t=0; t<m_tasks.size(); t++) {
    PhrasedTask* task = g_registry.getTask(m_tasks[t]);
    if (task == NULL) {
      err += "no such referenced task '" + m_tasks[t] + "'.";
      g_registry.setError(err, 0);
      return true;
    }
    tasks.clear();
    tasks.insert(task);
    if (task->isRecursive(tasks)) {
      err += "this task, or a task it references, is recursive, which is not allowed.";
      g_registry.setError(err, 0);
      return true;
    }
  }

  set<PhrasedModel*> models = getModels();
  if (models.empty()) {
    err += "none of the referenced tasks pointed to any model.";
    g_registry.setError(err, 0);
    return true;
  }
  for (set<PhrasedModel*>::iterator pm=models.begin(); pm != models.end(); pm++) {
    if (*pm==NULL) {
      err += "a referenced task pointed to a model name that does not exist.";
      g_registry.setError(err, 0);
      return true;
    }
  }

  bool foundloop = false;
  for (size_t c=0; c<m_changes.size(); c++) {
    if (m_changes[c].finalize(models)) {
      return true;
    }
    if (isLoop(m_changes[c].getType())) {
      foundloop = true;
    }
  }

  if (!foundloop) {
    err += "no loop found.  Repeated tasks must be repeated over some loop, such as 'x in uniform(0,10,100)' or 'x in [0, 3, 4, 10]'.";
    g_registry.setError(err, 0);
    return true;
  }

  //Make sure all changes are to different things
  set<vector<string> > changetargets;
  for (size_t c=0; c<m_changes.size(); c++) {
    if (changetargets.insert(m_changes[c].getVariable()).second == false) {
      std::vector<std::string> v = m_changes[c].getVariable();
      err += "multiple changes to the variable '" + getStringFrom(&v, ".") + "' are defined.";
      g_registry.setError(err, 0);
      return true;
    }
  }

  //Check if one of the model changes is there to reset the model.
  for (vector<ModelChange>::iterator change=m_changes.begin(); change != m_changes.end(); ) {
    if (change->getType() == ctype_formula_assignment) {
      vector<string> var = change->getVariable();
      if (var.size()==1 && (CaselessStrCmp(var[0], "reset") || CaselessStrCmp(var[0], "resetModel"))) {
        const ASTNode* astn = change->getASTNode();
        if (astn && astn->getType() == AST_CONSTANT_TRUE) {
          m_resetModel = true;
          change = m_changes.erase(change);
          continue;
        }
        else if (astn->getType() == AST_CONSTANT_FALSE) {
          m_resetModel = false;
          change = m_changes.erase(change);
          continue;
        }
      }
    }
    change++;
  }

  //Collapse elements that are only there as placeholders:
  set<pair<vector<string>, string> > combinelist;
  for (size_t c=0; c<m_changes.size(); c++) {
    if (m_changes[c].getType() == ctype_formula_assignment) {
      const ASTNode* astn = m_changes[c].getASTNode();
      if (astn->getType() == AST_NAME) {
        string astid = astn->getName();
        ModelChange* reffed = getModelChange(astid);
        if (reffed != NULL && isLoop(reffed->getType())) {
          //We can add it to the combine list
          combinelist.insert(make_pair(m_changes[c].getVariable(), astid));
        }
      }
    }
  }
  //However, we need to take things back off the combine list if they're used in other formulas:
  for (size_t c=0; c<m_changes.size(); c++) {
    if (m_changes[c].getType() == ctype_formula_assignment) {
      const ASTNode* astn = m_changes[c].getASTNode();
      if (astn->getType() != AST_NAME) {
        for (set<pair<vector<string>, string> >::iterator comb = combinelist.begin(); comb != combinelist.end();) {
          string elided = comb->second;
          if (ASTNodeHasId(astn, elided)) {
            set<pair<vector<string>, string> >::iterator newcomb = comb;
            newcomb++;
            combinelist.erase(comb);
            comb = newcomb;
          }
          else {
            comb++;
          }
        }
      }
    }
  }
  for (set<pair<vector<string>, string> >::iterator comb = combinelist.begin(); comb != combinelist.end(); comb++) {
    vector<string> removeme = comb->first;
    for (vector<ModelChange>::iterator change = m_changes.begin(); change != m_changes.end(); change++) {
      if (change->getVariable() == removeme) {
        m_changes.erase(change);
        break;
      }
    }
  }
  for (set<pair<vector<string>, string> >::iterator comb = combinelist.begin(); comb != combinelist.end(); comb++) {
    string renameme = comb->second;
    ModelChange* mc = getModelChange(renameme);
    mc->setVariable(comb->first);
  }

  return false;
}

ModelChange* PhrasedRepeatedTask::getModelChange(std::string id)
{
  for (size_t c=0; c<m_changes.size(); c++) {
    vector<string> changeId = m_changes[c].getVariable();
    if (changeId[changeId.size()-1] == id) {
      return &m_changes[c];
    }
  }
  return NULL;
}
PHRASEDML_CPP_NAMESPACE_END