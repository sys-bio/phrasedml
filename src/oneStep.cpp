#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "registry.h"
#include "oneStep.h"
#include "sedml/SedOneStep.h"

using namespace std;
using namespace libsedml;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp

PHRASEDML_CPP_NAMESPACE_BEGIN

PhrasedOneStep::PhrasedOneStep(std::string id, double step)
  : PhrasedSimulation(simtype_onestep, id)
  , m_step(step)
{
  m_kisao = 19;
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
  writePhraSEDMLKisao(ret);
  return ret.str();
}

void PhrasedOneStep::addSimulationToSEDML(SedDocument* sedml) const
{
  SedOneStep* oneStep = sedml->createOneStep();
  oneStep->setId(m_id);
  oneStep->setName(m_name);
  oneStep->setStep(m_step);
  addKisaoAndAlgorithmParametersToSEDML(oneStep);
}

bool PhrasedOneStep::kisaoIsDefault() const
{
  return m_kisao == 19;
}

bool PhrasedOneStep::finalize()
{
  if (PhrasedSimulation::finalize()) {
    return true;
  }
  stringstream err;
  if (m_step <= 0) {
    err << "The step size for a one-step simulation must be positive.  The step size for simulation '" << m_id << "' is '" << m_step << "', which is too small.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  return false;
}
PHRASEDML_CPP_NAMESPACE_END