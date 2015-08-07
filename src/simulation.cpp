#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "registry.h"
#include "simulation.h"
#include "sedml/SedSimulation.h"

using namespace std;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp

PhrasedSimulation::PhrasedSimulation(simtype type, std::string id)
  : Variable(id)
  , m_type(type)
{
  setKisaoFromType();
}

PhrasedSimulation::PhrasedSimulation(simtype type, SedSimulation* sedsimulation)
  : Variable(sedsimulation)
  , m_type(type)
{
  setKisaoFromType();
}

PhrasedSimulation::~PhrasedSimulation()
{
}

simtype PhrasedSimulation::getType() const
{
  return m_type;
}

bool PhrasedSimulation::finalize()
{
  if (Variable::finalize()) {
    return true;
  }
  if (m_type == simtype_unknown) {
    g_registry.setError("Unknown simulation type for simulation '" + m_id + "'.", 0);
    return true;
  }
  return false;
}

void PhrasedSimulation::setKisaoFromType()
{
  switch(m_type) {
  case simtype_unknown:
    m_kisao = 0;
  case simtype_steadystate:
    m_kisao = 0;
    break;
  case simtype_onestep:
    m_kisao = 0;
    break;
  case simtype_uniform:
    m_kisao = 0;
    break;
  }
}

