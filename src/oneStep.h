#ifndef PHRASEDONESTEP_H
#define PHRASEDONESTEP_H

#include <string>
#include <vector>

#include "simulation.h"

class SedOneStep;

class PhrasedOneStep : public PhrasedSimulation
{
private:
  PhrasedOneStep(); //undefined

  double m_step;

public:

  PhrasedOneStep(std::string id, double step);
  PhrasedOneStep(SedOneStep* sedOneStep);
  ~PhrasedOneStep();

  virtual std::string getPhraSEDML() const;
  virtual void addSimulationToSEDML(SedDocument* sedml) const;

  virtual bool finalize();

private:

};


#endif //PHRASEDONESTEP_H
