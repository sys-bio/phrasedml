#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>
#include <iomanip>

#include "registry.h"
#include "simulation.h"
#include "sedml/SedSimulation.h"
#include "stringx.h"

using namespace std;
extern int phrased_yylloc_last_line;

PHRASEDML_CPP_NAMESPACE_BEGIN
PhrasedSimulation::PhrasedSimulation(simtype type, std::string id)
  : Variable(id)
  , m_type(type)
  , m_kisao(0)
  , m_algparams()
{
}

PhrasedSimulation::PhrasedSimulation(simtype type, SedSimulation* sedsimulation)
  : Variable(sedsimulation)
  , m_type(type)
  , m_kisao(0)
  , m_algparams()
{
  if (sedsimulation->isSetAlgorithm()) {
    const SedAlgorithm* sedalg = sedsimulation->getAlgorithm();
    if (sedalg->isSetKisaoID()) {
      setAlgorithmKisao(getIntFromKisao(sedalg->getKisaoID()));
    }
    for (unsigned int ap=0; ap<sedalg->getNumAlgorithmParameters(); ap++) {
      const SedAlgorithmParameter* sap = sedalg->getAlgorithmParameter(ap);
      string kisao = "";
      string value = "";
      if (sap->isSetKisaoID()) {
        kisao = sap->getKisaoID();
      }
      if (sap->isSetValue()) {
        value = sap->getValue();
      }
      if (!kisao.empty() && !value.empty()) {
        addAlgorithmParameter(kisao, value);
      }
    }
  }
}

PhrasedSimulation::~PhrasedSimulation()
{
}

simtype PhrasedSimulation::getType() const
{
  return m_type;
}

bool PhrasedSimulation::setAlgorithmKisao(int kisao)
{
  m_kisao = kisao;
  return false;
}

bool PhrasedSimulation::setAlgorithmKisao(const std::vector<const std::string*>& kisao, stringstream& err)
{
  //Allowable values are either a single string that matches a known keyword (i.e. 'CVODE') or a particular kisao value (i.e. 'kisao.19')
  if (kisao.size() == 1) {
    int val = keywordToKisaoId(*kisao[0]);
    if (val==0) {
      err << "unknown algorithm type '" << *kisao[0] << "'.";
      g_registry.setError(err.str(), phrased_yylloc_last_line);
      return true;
    }
    setAlgorithmKisao(val);
    return false;
  }
  if (kisao.size() == 2) {
    //The first must be 'kisao' and the second must be a number
    if (!CaselessStrCmp(*kisao[0], "kisao")) {
      err << "when setting the type of a simulation algorithm, you must either use a single keyword (i.e. 'CVODE') or a kisao ID, written in the form 'kisao.19'.";
      g_registry.setError(err.str(), phrased_yylloc_last_line);
      return true;
    }
    if (!IsInt(*kisao[1])) {
      err << "when setting the kisao type of a simulation algorithm, kisao terms are written in the form 'kisao.19', where the value after 'kisao.' must be a positive integer.";
      g_registry.setError(err.str(), phrased_yylloc_last_line);
      return true;
    }
    if (setAlgorithmKisao(atoi((*kisao[1]).c_str()))) return true;
    return false;
  }
  err << "invalid algorithm type '" << getStringFrom(&kisao) << "'.  Types must be either a keyword ('CVODE') or of the form 'kisao.19'.";
  g_registry.setError(err.str(), phrased_yylloc_last_line);
  return true;
}

int PhrasedSimulation::keywordToKisaoId(const string& keyword) const
{
  if (CaselessStrCmp(keyword, "CVODE")) {
    return 19;
  }
  if (CaselessStrCmp(keyword, "gillespie")) {
    return 241;
  }
  if (CaselessStrCmp(keyword, "steadystate")) {
    return 407;
  }
  if (CaselessStrCmp(keyword, "rk4")) {
    return 32;
  }
  if (CaselessStrCmp(keyword, "rk45")) {
    return 435;
  }
  if (CaselessStrCmp(keyword, "stiff")) {
    return 288;
  }
  if (CaselessStrCmp(keyword, "non-stiff")) {
    return 280;
  }
  if (CaselessStrCmp(keyword, "nonstiff")) {
    return 280;
  }
  if (CaselessStrCmp(keyword, "bdf")) {
    return 288;
  }
  if (CaselessStrCmp(keyword, "adams")) {
    return 280;
  }
  if (CaselessStrCmp(keyword, "adams_moulton")) {
    return 280;
  }
  if (CaselessStrCmp(keyword, "lsoda")) {
    return 88;
  }


  return 0;
}

void PhrasedSimulation::addAlgorithmParameter(std::string kisao, std::string val)
{
  m_algparams.insert(make_pair(keywordToKisaoParamId(kisao), val));
}

void PhrasedSimulation::addAlgorithmParameter(int kisao, double val)
{
  stringstream valstr;
  valstr << val;
  addAlgorithmParameter(getKisaoFromInt(kisao), valstr.str());
}

void PhrasedSimulation::addAlgorithmParameter(int kisao, string val)
{
  addAlgorithmParameter(getKisaoFromInt(kisao), val);
}

bool PhrasedSimulation::addAlgorithmParameter(const std::string* kisao, const std::string* val, std::stringstream& err)
{
  int k_int = 0;
  if (IsInt(*kisao)) {
    k_int = atoi(kisao->c_str());
    if (k_int <= 0) {
      err << "KiSAO algorithm parameter IDs must be 1 or greater.";
      g_registry.setError(err.str(), phrased_yylloc_last_line);
      return true;
    }
  }
  else {
    k_int = keywordToKisaoParamId(*kisao);
    if (k_int == 0) {
      err << "unknown algorithm parameter keyword '" << *kisao << "'.";
      g_registry.setError(err.str(), phrased_yylloc_last_line);
      return true;
    }
  }
  //Might want to do some error checking on the value, but I'm not sure what the restrictions should be.
  addAlgorithmParameter(k_int, *val);
  return false;
}

bool PhrasedSimulation::addAlgorithmParameter(const std::string* kisao, double val, std::stringstream& err)
{
  int k_int = 0;
  if (IsInt(*kisao)) {
    k_int = atoi(kisao->c_str());
    if (k_int <= 0) {
      err << "KiSAO algorithm parameter IDs must be 1 or greater.";
      g_registry.setError(err.str(), phrased_yylloc_last_line);
      return true;
    }
  }
  else {
    k_int = keywordToKisaoParamId(*kisao);
    if (k_int == 0) {
      err << "unknown algorithm parameter keyword '" << *kisao << "'.";
      g_registry.setError(err.str(), phrased_yylloc_last_line);
      return true;
    }
  }
  addAlgorithmParameter(k_int, val);
  return false;
}

void PhrasedSimulation::addKisaoAndAlgorithmParametersToSEDML(SedSimulation* sedsim) const
{
  if (sedsim==NULL) {
    return;
  }
  if (m_kisao==0 && m_algparams.size()==0) {
    return;
  }
  SedAlgorithm* alg = const_cast<SedAlgorithm*>(sedsim->getAlgorithm());
  if (alg==NULL) {
    alg = sedsim->createAlgorithm();
  }
  if (m_kisao != 0) {
    alg->setKisaoID(getKisaoFromInt(m_kisao));
  }
  for (map<int, string>::const_iterator algparam = m_algparams.begin(); algparam != m_algparams.end(); algparam++) {
    SedAlgorithmParameter* sap = alg->createAlgorithmParameter();
    sap->setKisaoID(getKisaoFromInt(algparam->first));
    sap->setValue(algparam->second);
  }

}

int PhrasedSimulation::keywordToKisaoParamId(const string& keyword) const
{
  //CVODE params (rr)
  if (CaselessStrCmp(keyword, "relative_tolerance")) {
    return 209;
  }
  if (CaselessStrCmp(keyword, "RTOL")) {
    return 209;
  }
  if (CaselessStrCmp(keyword, "absolute_tolerance")) {
    return 211;
  }
  if (CaselessStrCmp(keyword, "ATOL")) {
    return 211;
  }
  if (CaselessStrCmp(keyword, "maximum_adams_order")) {
    return 219;
  }
  if (CaselessStrCmp(keyword, "maximum_bdf_order")) {
    return 220;
  }
  if (CaselessStrCmp(keyword, "maximum_num_steps")) {
    return 415;
  }
  if (CaselessStrCmp(keyword, "maximum_time_step")) {
    return 467;
  }
  if (CaselessStrCmp(keyword, "maximum_timestep")) {
    return 467;
  }
  if (CaselessStrCmp(keyword, "maximum_step_size")) {
    return 467;
  }
  if (CaselessStrCmp(keyword, "minimum_time_step")) {
    return 485;
  }
  if (CaselessStrCmp(keyword, "minimum_timestep")) {
    return 485;
  }
  if (CaselessStrCmp(keyword, "minimum_step_size")) {
    return 485;
  }
  if (CaselessStrCmp(keyword, "initial_time_step")) {
    return 559;
  }
  if (CaselessStrCmp(keyword, "variable_step_size")) {
    return 107;
  }
  //steady state params (rr)
  if (CaselessStrCmp(keyword, "maximum_iterations")) {
    return 486;
  }
  if (CaselessStrCmp(keyword, "minimum_damping")) {
    return 487;
  }
  //gillespie params (rr)
  if (CaselessStrCmp(keyword, "seed")) {
    return 488;
  }

  //Alternate 'max' and 'min' versions.
  if (CaselessStrCmp(keyword, "max_bdf_order")) {
    return 220;
  }
  if (CaselessStrCmp(keyword, "max_adams_order")) {
    return 219;
  }
  if (CaselessStrCmp(keyword, "max_num_steps")) {
    return 415;
  }
  if (CaselessStrCmp(keyword, "max_time_step")) {
    return 467;
  }
  if (CaselessStrCmp(keyword, "max_timestep")) {
    return 467;
  }
  if (CaselessStrCmp(keyword, "max_iterations")) {
    return 486;
  }
  if (CaselessStrCmp(keyword, "min_time_step")) {
    return 485;
  }
  if (CaselessStrCmp(keyword, "min_step_size")) {
    return 485;
  }
  if (CaselessStrCmp(keyword, "min_timestep")) {
    return 485;
  }
  if (CaselessStrCmp(keyword, "min_damping")) {
    return 487;
  }


  return getIntFromKisao(keyword);
}

void PhrasedSimulation::writePhraSEDMLKisao(std::stringstream& stream) const
{
  if (!kisaoIsDefault()) {
    stream << m_id << ".algorithm = " << getPhrasedVersionOf(m_kisao) << endl;
  }
  for (map<int, string>::const_iterator algparm = m_algparams.begin(); algparm != m_algparams.end(); algparm++) {
    stream << m_id << ".algorithm." << getPhrasedVersionOf(algparm->first) << " = " << algparm->second << endl;
  }
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

string PhrasedSimulation::getKisaoFromInt(int kisao) const
{
  stringstream ret;
  ret << "KISAO:";
  ret << setfill('0') << setw(7) << kisao;
  return ret.str();
}

int PhrasedSimulation::getIntFromKisao(string kisao) const
{
  if (kisao.find("KISAO:") != 0) {
    return 0;
  }
  kisao.replace(0,6,"");
  return atoi(kisao.c_str());
}

bool PhrasedSimulation::kisaoIdIsStochastic(const string& kisao) const
{
  return kisaoIdIsStochastic(getIntFromKisao(kisao));
}

bool PhrasedSimulation::kisaoIdIsStochastic(int kisao) const
{
  switch (kisao) {
  case 29:
  case 319:
  case 274:
  case 241: //our default
  case 333:
  case 329:
  case 323:
  case 331:
  case 27:
  case 82:
  case 324:
  case 350:
  case 330:
  case 28:
  case 38:
  case 39:
  case 48:
  case 74:
  case 81:
  case 45:
  case 351:
  case 84:
  case 40:
  case 46:
  case 3:
  case 51:
  case 335:
  case 336:
  case 95:
  case 22:
  case 76:
  case 15:
  case 75:
  case 278:
    return true;
  default:
    return false;
  }
  //can't fall through, but some compilers might complain:
  return false;
}

bool PhrasedSimulation::kisaoIdIsSteadyState(int kisao) const
{
  switch (kisao) {
  case 407:
  case 437:
  case 274:
  case 408:
  case 413:
  case 432:
  case 355:
  case 356:
  case 283:
  case 412:
  case 282:
  case 411:
  case 409:
  case 410:
    return true;
  default:
    return false;
  }
  return false;
}

bool PhrasedSimulation::kisaoIdIsDeterministic(int kisao) const
{
  if (kisaoIdIsSteadyState(kisao)) return false;
  if (kisaoIdIsStochastic(kisao)) return false;
  return true; //Ignores 
}

string PhrasedSimulation::getPhrasedVersionOf(int kisao) const
{
  switch (kisao) {
  case 19:
    return "CVODE";
  case 241:
    return "gillespie";
  case 407:
    return "steadystate";
  case 32:
    return "rk4";
  case 88:
    return "lsoda";
  case 435:
    return "rk45";
  case 288:
    return "bdf";
  case 280:
    return "adams_moulton";
  case 209:
    return "relative_tolerance";
  case 211:
    return "absolute_tolerance";
  case 219:
    return "maximum_adams_order";
  case 220:
    return "maximum_bdf_order";
  case 415:
    return "maximum_num_steps";
  case 467:
    return "maximum_time_step";
  case 485:
    return "minimum_time_step";
  case 332:
    return "initial_time_step";
  case 559:
    return "initial_time_step";
  case 107:
    return "variable_step_size";
  case 486:
    return "maximum_iterations";
  case 487:
    return "minimum_damping";
  case 488:
    return "seed";
  }
  stringstream ret;
  ret << "kisao." << kisao;
  return ret.str();
}

PHRASEDML_CPP_NAMESPACE_END
