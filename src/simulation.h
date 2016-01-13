#ifndef PHRASEDSIMULATION_H
#define PHRASEDSIMULATION_H

#include <string>
#include <vector>

#include "variable.h"
#include "phrasedml-namespace.h"

class SedSimulation;
class SedDocument;

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

public:

  PhrasedSimulation(simtype type, std::string id);
  PhrasedSimulation(simtype type, SedSimulation* sedsimulation);
  ~PhrasedSimulation();

  simtype getType() const;

  virtual std::string getPhraSEDML() const = 0;
  virtual void addSimulationToSEDML(SedDocument* sedml) const = 0;

  virtual bool finalize();

private:
  void setKisaoFromType();

};
PHRASEDML_CPP_NAMESPACE_END


#endif //PHRASEDSIMULATION_H
