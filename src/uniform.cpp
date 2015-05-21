#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "registry.h"
#include "uniform.h"
#include "sedml\SedUniformTimeCourse.h"

using namespace std;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp

PhrasedUniform::PhrasedUniform(std::string id, double start, double outstart, double end, long numpts)
  : PhrasedSimulation(simtype_uniform, id)
  , m_start(start)
  , m_outstart(outstart)
  , m_end(end)
  , m_numpts(numpts)
{
}

PhrasedUniform::PhrasedUniform(SedUniformTimeCourse* seduniform)
  : PhrasedSimulation(simtype_uniform, seduniform)
{
  m_start = seduniform->getInitialTime();
  m_outstart = seduniform->getOutputStartTime();
  m_end = seduniform->getOutputEndTime();
  m_numpts = seduniform->getNumberOfPoints();
}

PhrasedUniform::~PhrasedUniform()
{
}

string PhrasedUniform::getPhraSEDML() const
{
  stringstream ret;
  ret << m_id << " = simulate uniform (";
  ret << m_start << ", ";
  if (m_start != m_outstart) {
    ret << m_outstart << ", ";
  }
  ret << m_end << ", ";
  ret << m_numpts << ")" << endl;
  return ret.str();
}

void PhrasedUniform::addSimulationToSEDML(SedDocument* sedml) const
{
  SedUniformTimeCourse* uniform = sedml->createUniformTimeCourse();
  uniform->setId(m_id);
  uniform->setName(m_name);
  uniform->setInitialTime(m_start);
  uniform->setOutputStartTime(m_outstart);
  uniform->setOutputEndTime(m_end);
  uniform->setNumberOfPoints(m_numpts);
}

bool PhrasedUniform::finalize()
{
  if (PhrasedSimulation::finalize()) {
    return true;
  }
  stringstream err;
  if (m_start < 0) {
    err << "The start time for a uniform time course simulation must be zero or greater.  The start time for simulation " << m_id << "' is '" << m_start << "', which is negative.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  if (m_start > m_outstart) {
    err << "The output start time for a uniform time course simulation must be greater than or equal to the start time for the simulation.  The output start time for simulation " << m_id << "' is '" << m_outstart << "', which is greater than '" << m_start << "', the simulation start.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  if (m_end > m_outstart) {
    err << "The end time for a uniform time course simulation must be greater than or equal to the start time (and output start time) for the simulation.  The end time for simulation " << m_id << "' is '" << m_end << "', which is greater than '" << m_outstart << "'.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  if (m_numpts <= 0) {
    err << "The number of points for a uniform time course simulation must be positive.  The number of points for simulation " << m_id << "' is '" << m_numpts << "', which is too small.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  return false;
}
