#ifndef PHRASEDUNIFORM_H
#define PHRASEDUNIFORM_H

#include <string>
#include <vector>

#include "simulation.h"
#include "phrasedml-namespace.h"

#include "sedml/SedUniformTimeCourse.h"

PHRASEDML_CPP_NAMESPACE_BEGIN
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
  PhrasedUniform(libsedml::SedUniformTimeCourse* sedUniform);
  ~PhrasedUniform();

  virtual std::string getPhraSEDML() const;
  virtual void addSimulationToSEDML(libsedml::SedDocument* sedml) const;
  virtual bool setAlgorithmKisao(int kisao);
  virtual bool getStochastic() const {return m_stochastic;};
  virtual bool kisaoIsDefault() const;

  virtual bool finalize();

private:

};
PHRASEDML_CPP_NAMESPACE_END


#endif //PHRASEDUNIFORMSIMULATION_H
