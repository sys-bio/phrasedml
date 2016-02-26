#ifndef PHRASEDSTEADYSTATE_H
#define PHRASEDSTEADYSTATE_H

#include <string>
#include <vector>

#include "simulation.h"
#include "phrasedml-namespace.h"

class SedSteadyState;

PHRASEDML_CPP_NAMESPACE_BEGIN
class PhrasedSteadyState: public PhrasedSimulation
{
private:
  PhrasedSteadyState(); //undefined


public:

  PhrasedSteadyState(std::string id);
  PhrasedSteadyState(SedSteadyState* sedSteadyState);
  ~PhrasedSteadyState();

  virtual std::string getPhraSEDML() const;
  virtual void addSimulationToSEDML(SedDocument* sedml) const;
  virtual bool setAlgorithmKisao(int kisao);
  bool kisaoIsDefault() const;

  virtual bool finalize();

private:

};
PHRASEDML_CPP_NAMESPACE_END


#endif //PHRASEDSTEADYSTATE_H
