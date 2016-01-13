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

using namespace std;

PHRASEDML_CPP_NAMESPACE_BEGIN
PhrasedUniform::PhrasedUniform(std::string id, double start, double outstart, double end, long numpts, bool stochastic)
  : PhrasedSimulation(simtype_uniform, id)
  , m_start(start)
  , m_outstart(outstart)
  , m_end(end)
  , m_numpts(numpts)
  , m_stochastic(stochastic)
{
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
    alg->setKisaoID("KISAO:0000029"); //stochastic simulation
  }
  else {
    alg->setKisaoID("KISAO:0000019"); //non-stochastic simulation
  }
}

bool PhrasedUniform::finalize()
{
  if (PhrasedSimulation::finalize()) {
    return true;
  }
  stringstream err;
  if (m_start < 0) {
    err << "The start time for a uniform time course simulation must be zero or greater.  The start time for simulation '" << m_id << "' is '" << m_start << "', which is negative.";
    g_registry.setError(err.str(), 0);
    return true;
  }
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

bool PhrasedUniform::kisaoIdIsStochastic(const string& kisao)
{
  if (kisao=="KISAO:0000029") return true; //our default
  if (kisao=="KISAO:0000319") return true;
  if (kisao=="KISAO:0000274") return true;
  if (kisao=="KISAO:0000241") return true;
  if (kisao=="KISAO:0000333") return true;
  if (kisao=="KISAO:0000329") return true;
  if (kisao=="KISAO:0000323") return true;
  if (kisao=="KISAO:0000331") return true;
  if (kisao=="KISAO:0000027") return true;
  if (kisao=="KISAO:0000082") return true;
  if (kisao=="KISAO:0000324") return true;
  if (kisao=="KISAO:0000350") return true;
  if (kisao=="KISAO:0000330") return true;
  if (kisao=="KISAO:0000028") return true;
  if (kisao=="KISAO:0000038") return true;
  if (kisao=="KISAO:0000039") return true;
  if (kisao=="KISAO:0000048") return true;
  if (kisao=="KISAO:0000074") return true;
  if (kisao=="KISAO:0000081") return true;
  if (kisao=="KISAO:0000045") return true;
  if (kisao=="KISAO:0000351") return true;
  if (kisao=="KISAO:0000084") return true;
  if (kisao=="KISAO:0000040") return true;
  if (kisao=="KISAO:0000046") return true;
  if (kisao=="KISAO:0000003") return true;
  if (kisao=="KISAO:0000051") return true;
  if (kisao=="KISAO:0000335") return true;
  if (kisao=="KISAO:0000336") return true;
  if (kisao=="KISAO:0000095") return true;
  if (kisao=="KISAO:0000022") return true;
  if (kisao=="KISAO:0000076") return true;
  //if (kisao=="KISAO:0000029") return true; //Where it appears in KiSAO, but we have it above.
  if (kisao=="KISAO:0000015") return true;
  if (kisao=="KISAO:0000075") return true;
  if (kisao=="KISAO:0000278") return true;

  return false;
}

PHRASEDML_CPP_NAMESPACE_END
