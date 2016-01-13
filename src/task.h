#ifndef PHRASEDTASK_H
#define PHRASEDTASK_H

#include <string>
#include <vector>
#include <set>

#include "variable.h"
#include "phrasedml-namespace.h"

class SedTask;
class SedDocument;

PHRASEDML_CPP_NAMESPACE_BEGIN
class PhrasedTask : public Variable
{
private:
  PhrasedTask(); //undefined

protected:
  std::string m_simulation;
  std::string m_model;

public:

  PhrasedTask(std::string id, std::string simulation, std::string model);
  PhrasedTask(SedTask* sedtask);
  ~PhrasedTask();

  virtual bool isRepeated() const;
  virtual std::string getPhraSEDML() const;
  virtual void addTaskToSEDML(SedDocument* sedml) const;

  virtual const ModelChange* getModelChangeFor(std::string varname) const;

  virtual std::set<PhrasedModel*> getModels() const;
  virtual bool isRecursive(std::set<PhrasedTask*>& tasks);
  virtual bool finalize();

private:

};
PHRASEDML_CPP_NAMESPACE_END


#endif //PHRASEDTASK_H
