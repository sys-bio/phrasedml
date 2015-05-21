#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "registry.h"
#include "oneStep.h"
#include "sedml\SedOneStep.h"

using namespace std;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp

PhrasedOneStep::PhrasedOneStep(std::string id, double step)
  : PhrasedSimulation(simtype_onestep, id)
  , m_step(step)
{
}

PhrasedOneStep::PhrasedOneStep(SedOneStep* sedOneStep)
  : PhrasedSimulation(simtype_onestep, sedOneStep)
{
  m_step = sedOneStep->getStep();
}

PhrasedOneStep::~PhrasedOneStep()
{
}

string PhrasedOneStep::getPhraSEDML() const
{
  stringstream ret;
  ret << m_id << " = simulate oneStep(" << m_step << ")" << endl;
  return ret.str();
}

void PhrasedOneStep::addSimulationToSEDML(SedDocument* sedml) const
{
  SedOneStep* oneStep = sedml->createOneStep();
  oneStep->setId(m_id);
  oneStep->setName(m_name);
  oneStep->setStep(m_step);
}

bool PhrasedOneStep::finalize()
{
  if (Variable::finalize()) {
    return true;
  }
  if (m_type == simtype_unknown) {
    g_registry.setError("Unknown oneStep type for oneStep '" + m_id + "'.", 0);
    return true;
  }
  return false;
}
