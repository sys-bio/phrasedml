#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "registry.h"
#include "task.h"
#include "sedml/SedTask.h"

using namespace std;

PHRASEDML_CPP_NAMESPACE_BEGIN
PhrasedTask::PhrasedTask(std::string id, std::string simulation, std::string model)
  : Variable(id)
  , m_simulation(simulation)
  , m_model(model)
{
}

PhrasedTask::PhrasedTask(SedTask* sedtask)
  : Variable(sedtask)
{
  m_simulation = sedtask->getSimulationReference();
  m_model = sedtask->getModelReference();
}

PhrasedTask::~PhrasedTask()
{
}

string PhrasedTask::getPhraSEDML() const
{
  return m_id + " = run " + m_simulation + " on " + m_model + "\n";
}

void PhrasedTask::addTaskToSEDML(SedDocument* sedml) const
{
  SedTask* sedtask = sedml->createTask();
  sedtask->setId(m_id);
  sedtask->setName(m_name);
  sedtask->setModelReference(m_model);
  sedtask->setSimulationReference(m_simulation);
}

bool PhrasedTask::isRepeated() const
{
  return false;
}

set<PhrasedModel*> PhrasedTask::getModels() const
{
  set<PhrasedModel*> ret;
  ret.insert(g_registry.getModel(m_model));
  return ret;
}

bool PhrasedTask::isRecursive(set<PhrasedTask*>& tasks)
{
  return false;
}

const ModelChange* PhrasedTask::getModelChangeFor(std::string varname) const
{
  return NULL;
}

bool PhrasedTask::finalize()
{
  if (Variable::finalize()) {
    return true;
  }
  if (g_registry.getModel(m_model) == NULL) {
    g_registry.setError("Error in task '" + m_id + "':  no such referenced model '" + m_model + "'.", 0);
    return true;
  }
  if (g_registry.getSimulation(m_simulation) == NULL) {
    g_registry.setError("Error in task '" + m_id + "':  no such referenced simulation '" + m_simulation + "'.", 0);
    return true;
  }

  return false;
}
PHRASEDML_CPP_NAMESPACE_END