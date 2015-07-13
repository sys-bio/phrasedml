#ifndef PHRASEDUNIFORM_H
#define PHRASEDUNIFORM_H

#include <string>
#include <vector>

#include "simulation.h"

class SedUniformTimeCourse;

class PhrasedUniform : public PhrasedSimulation
{
private:
  PhrasedUniform(); //undefined
  double m_start;
  double m_outstart;
  double m_end;
  long m_numpts;
  bool m_stochastic;

public:

  PhrasedUniform(std::string id, double start, double outstart, double end, long numpts, bool stochastic);
  PhrasedUniform(SedUniformTimeCourse* sedUniform);
  ~PhrasedUniform();

  virtual std::string getPhraSEDML() const;
  virtual void addSimulationToSEDML(SedDocument* sedml) const;

  virtual bool finalize();

private:

};


#endif //PHRASEDUNIFORMSIMULATION_H
