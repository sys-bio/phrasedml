#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "registry.h"
#include "uniform.h"
#include "sedml/SedUniformTimeCourse.h"

extern int phrased_yylloc_last_line;
using namespace std;
using namespace libsedml;

PHRASEDML_CPP_NAMESPACE_BEGIN
PhrasedUniform::PhrasedUniform(std::string id, double start, double outstart, double end, long numpts, bool stochastic)
  : PhrasedSimulation(simtype_uniform, id)
  , m_start(start)
  , m_outstart(outstart)
  , m_end(end)
  , m_numpts(numpts)
  , m_stochastic(stochastic)
{
  if (stochastic) {
    m_kisao = 241;
  }
  else {
    m_kisao = 19;
  }
}

PhrasedUniform::PhrasedUniform(SedUniformTimeCourse* seduniform)
  : PhrasedSimulation(simtype_uniform, seduniform)
{
  m_start = seduniform->getInitialTime();
  m_outstart = seduniform->getOutputStartTime();
  m_end = seduniform->getOutputEndTime();
  m_numpts = seduniform->getNumberOfPoints();
  m_stochastic = false;
  if (seduniform->isSetAlgorithm()) {
    const SedAlgorithm* alg = seduniform->getAlgorithm();
    if (alg->isSetKisaoID() && kisaoIdIsStochastic(alg->getKisaoID())) {
      m_stochastic = true;
    }
  }
}

PhrasedUniform::~PhrasedUniform()
{
}

string PhrasedUniform::getPhraSEDML() const
{
  stringstream ret;
  ret << m_id << " = simulate uniform";
  if (m_stochastic) {
    ret << "_stochastic";
  }
  ret << "(" << m_start << ", ";
  if (m_start != m_outstart) {
    ret << m_outstart << ", ";
  }
  ret << m_end << ", ";
  ret << m_numpts << ")" << endl;
  writePhraSEDMLKisao(ret);
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
  SedAlgorithm* alg = uniform->createAlgorithm();
  if (m_stochastic) {
    alg->setKisaoID("KISAO:0000241"); //stochastic simulation
  }
  else {
    alg->setKisaoID("KISAO:0000019"); //non-stochastic simulation
  }
  addKisaoAndAlgorithmParametersToSEDML(uniform);
}

bool PhrasedUniform::setAlgorithmKisao(int kisao)
{
  m_kisao = kisao;
  if (kisaoIdIsStochastic(kisao)) {
    m_stochastic = true;
  }
  else if (kisaoIdIsSteadyState(kisao)) {
    stringstream err;
    err << "Error in line " << phrased_yylloc_last_line << ": unable to set the KiSAO ID of the simulation '" << m_id << "' to " << kisao << ", because this is a uniform time course simulation, but KiSAO ID " << kisao << " is steady state.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  else if (kisao<=0) {
    stringstream err;
    err << "Error in line " << phrased_yylloc_last_line << ": unable to set the KiSAO ID of the simulation '" << m_id << "' to " << kisao << ": all KiSAO IDs are 1 or greater.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  else {
    m_stochastic = false;
  }
  return false;
}

bool PhrasedUniform::kisaoIsDefault() const
{
  if (m_stochastic) {
    return m_kisao == 241;
  }
  else {
    return m_kisao == 19;
  }
}

bool PhrasedUniform::finalize()
{
  if (PhrasedSimulation::finalize()) {
    return true;
  }
  stringstream err;
  if (m_outstart < m_start) {
    err << "The output start time for a uniform time course simulation must be greater than or equal to the start time for the simulation.  The output start time for simulation '" << m_id << "' is '" << m_outstart << "', which is lower than '" << m_start << "', the simulation start.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  if (m_end < m_outstart) {
    err << "The end time for a uniform time course simulation must be greater than or equal to the start time (and output start time) for the simulation.  The end time for simulation '" << m_id << "' is '" << m_end << "', which is less than '" << m_outstart << "'.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  if (m_numpts <= 0) {
    err << "The number of points for a uniform time course simulation must be positive.  The number of points for simulation '" << m_id << "' is '" << m_numpts << "', which is negative.";
    g_registry.setError(err.str(), 0);
    return true;
  }
  return false;
}

PHRASEDML_CPP_NAMESPACE_END
