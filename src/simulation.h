#ifndef PHRASEDSIMULATION_H
#define PHRASEDSIMULATION_H

#include <string>
#include <vector>
#include <map>

#include "variable.h"
#include "phrasedml-namespace.h"

#include "sedml/SedSimulation.h"
#include "sedml/SedDocument.h"

PHRASEDML_CPP_NAMESPACE_BEGIN
enum simtype {
  simtype_unknown,
  simtype_steadystate, 
  simtype_onestep, 
  simtype_uniform,
  simtype_uniform_stochastic
};

class PhrasedSimulation : public Variable
{
private:
  PhrasedSimulation(); //undefined

protected:
  simtype m_type;
  int m_kisao;
  std::map<int, std::string> m_algparams;

public:

  PhrasedSimulation(simtype type, std::string id);
  PhrasedSimulation(simtype type, libsedml::SedSimulation* sedsimulation);
  virtual ~PhrasedSimulation();

  simtype getType() const;

  virtual std::string getPhraSEDML() const = 0;
  virtual void addSimulationToSEDML(libsedml::SedDocument* sedml) const = 0;

  virtual bool setAlgorithmKisao(int kisao);
  virtual bool setAlgorithmKisao(const std::vector<const std::string*>& kisao, std::stringstream& err);
  virtual int  keywordToKisaoId(const std::string& keyword) const;
  virtual void addAlgorithmParameter(std::string kisao, std::string val);
  virtual void addAlgorithmParameter(int kisao, double val);
  virtual void addAlgorithmParameter(int kisao, std::string val);
  virtual bool addAlgorithmParameter(const std::string* kisao, const std::string* val, std::stringstream& err);
  virtual bool addAlgorithmParameter(const std::string* kisao, double val, std::stringstream& err);
  virtual void addKisaoAndAlgorithmParametersToSEDML(libsedml::SedSimulation* sedsim) const;
  virtual int  keywordToKisaoParamId(const std::string& keyword) const;

  virtual void writePhraSEDMLKisao(std::stringstream& stream) const;
  virtual bool kisaoIsDefault() const = 0;

  virtual bool finalize();

  bool kisaoIdIsStochastic(const std::string& kisao) const;
  bool kisaoIdIsStochastic(int kisao) const;
  bool kisaoIdIsSteadyState(int kisao) const;
  bool kisaoIdIsDeterministic(int kisao) const;
  std::string getPhrasedVersionOf(int kisao) const;

protected:
  std::string getKisaoFromInt(int kisao) const;
  int getIntFromKisao(std::string kisao) const;

};
PHRASEDML_CPP_NAMESPACE_END


#endif //PHRASEDSIMULATION_H
