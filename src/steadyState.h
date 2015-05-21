#ifndef PHRASEDSTEADYSTATE_H
#define PHRASEDSTEADYSTATE_H

#include <string>
#include <vector>

#include "simulation.h"

class SedSteadyState;

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

  virtual bool finalize();

private:

};


#endif //PHRASEDSTEADYSTATE_H
