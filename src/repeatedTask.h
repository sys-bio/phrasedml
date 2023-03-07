#ifndef PHRASEDREPEATEDTASK_H
#define PHRASEDREPEATEDTASK_H

#include <string>
#include <vector>

#include "variable.h"
#include "modelChange.h"
#include "task.h"
#include "phrasedml-namespace.h"

#include "sedml/SedRepeatedTask.h"
#include "sedml/SedDocument.h"
#include "sedml/SedSetValue.h"
#include "sedml/SedRepeatedTask.h"

PHRASEDML_CPP_NAMESPACE_BEGIN

class PhrasedRepeatedTask : public PhrasedTask
{
private:
  PhrasedRepeatedTask(); //undefined

protected:
  std::vector<std::string> m_tasks;
  std::vector<ModelChange> m_changes;
  bool m_resetModel;

public:

  PhrasedRepeatedTask(std::string id, std::string task, std::vector<ModelChange>*);
  PhrasedRepeatedTask(libsedml::SedRepeatedTask* sedRepeatedTask);
  ~PhrasedRepeatedTask();

  virtual bool isRepeated() const;
  virtual void addTask(std::string task);
  virtual std::string getPhraSEDML() const;
  virtual void addRepeatedTaskToSEDML(libsedml::SedDocument* sedml) const;

  virtual const ModelChange* getModelChangeFor(std::string varname) const;

  virtual bool changeListIsInappropriate(std::stringstream& err);
  virtual std::set<PhrasedModel*> getModels() const;
  virtual bool isRecursive(std::set<PhrasedTask*>& tasks);
  virtual bool finalize();

private:
  void addLocalVariablesToSetValue(libsedml::SedSetValue* ssv, libsedml::SedRepeatedTask* srt) const;
  ModelChange* getModelChange(std::string id);

};

PHRASEDML_CPP_NAMESPACE_END

#endif //PHRASEDREPEATEDTASK_H
