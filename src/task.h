#ifndef PHRASEDTASK_H
#define PHRASEDTASK_H

#include <string>
#include <vector>

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

  PhrasedTask(std::string id, std::string simuilation, std::string model);
  PhrasedTask(SedTask* sedtask);
  ~PhrasedTask();

  virtual std::string getPhraSEDML() const;
  virtual void addTaskToSEDML(SedDocument* sedml) const;

  virtual bool finalize();

private:

};


#endif //PHRASEDTASK_H
