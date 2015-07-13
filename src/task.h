#ifndef PHRASEDTASK_H
#define PHRASEDTASK_H

#include <string>
#include <vector>
#include <set>

#include "variable.h"

class SedTask;
class SedDocument;

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

  virtual std::set<PhrasedModel*> getModels() const;
  virtual bool isRecursive(std::set<PhrasedTask*>& tasks);
  virtual bool finalize();

private:

};


#endif //PHRASEDTASK_H
