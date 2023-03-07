#ifndef PHRASEDONESTEP_H
#define PHRASEDONESTEP_H

#include <string>
#include <vector>

#include "simulation.h"
#include "phrasedml-namespace.h"
#include "sedml/SedOneStep.h"

PHRASEDML_CPP_NAMESPACE_BEGIN

class PhrasedOneStep : public PhrasedSimulation
{
private:
  PhrasedOneStep(); //undefined

  double m_step;

public:

  PhrasedOneStep(std::string id, double step);
  PhrasedOneStep(libsedml::SedOneStep* sedOneStep);
  ~PhrasedOneStep();

  virtual std::string getPhraSEDML() const;
  virtual void addSimulationToSEDML(libsedml::SedDocument* sedml) const;
  virtual bool kisaoIsDefault() const;

  virtual bool finalize();

private:

};

PHRASEDML_CPP_NAMESPACE_END

#endif //PHRASEDONESTEP_H
