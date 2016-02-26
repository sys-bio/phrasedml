#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "registry.h"
#include "steadyState.h"
#include "sedml/SedSteadyState.h"

extern int phrased_yylloc_last_line;
using namespace std;

PHRASEDML_CPP_NAMESPACE_BEGIN
PhrasedSteadyState::PhrasedSteadyState(std::string id)
  : PhrasedSimulation(simtype_steadystate, id)
{
  m_kisao = 407;
}

PhrasedSteadyState::PhrasedSteadyState(SedSteadyState* sedsteadyState)
  : PhrasedSimulation(simtype_steadystate, sedsteadyState)
{
}

PhrasedSteadyState::~PhrasedSteadyState()
{
}

string PhrasedSteadyState::getPhraSEDML() const
{
  stringstream ret;
  ret << m_id << " = simulate steadyState" << endl;
  writePhraSEDMLKisao(ret);
  return ret.str();
}

void PhrasedSteadyState::addSimulationToSEDML(SedDocument* sedml) const
{
  SedSteadyState* steadyState = sedml->createSteadyState();
  steadyState->setId(m_id);
  steadyState->setName(m_name);
  addKisaoAndAlgorithmParametersToSEDML(steadyState);
}

bool PhrasedSteadyState::setAlgorithmKisao(int kisao)
{
  if (!kisaoIdIsSteadyState(kisao)) {
    stringstream err;
    err << "Error in line " << phrased_yylloc_last_line-1 << ": unable to set the kisao ID of the simulation '" << m_id << "' to " << kisao << ", because that is not a steady state simulation KiSAO ID.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  m_kisao = kisao;
  return false;
}

bool PhrasedSteadyState::kisaoIsDefault() const
{
  return m_kisao == 407;
}

bool PhrasedSteadyState::finalize()
{
  if (Variable::finalize()) {
    return true;
  }
  if (m_type == simtype_unknown) {
    g_registry.setError("Unknown steadyState type for steadyState '" + m_id + "'.", 0);
    return true;
  }
  return false;
}
PHRASEDML_CPP_NAMESPACE_END