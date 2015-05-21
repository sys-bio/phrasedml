#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "registry.h"
#include "steadystate.h"
#include "sedml\SedSteadyState.h"

using namespace std;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp

PhrasedSteadyState::PhrasedSteadyState(std::string id)
  : PhrasedSimulation(simtype_steadystate, id)
{
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
  return m_id + " = simulate steadyState\n";
}

void PhrasedSteadyState::addSimulationToSEDML(SedDocument* sedml) const
{
  SedSteadyState* steadyState = sedml->createSteadyState();
  steadyState->setId(m_id);
  steadyState->setName(m_name);
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
