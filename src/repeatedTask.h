#ifndef PHRASEDREPEATEDTASK_H
#define PHRASEDREPEATEDTASK_H

#include <string>
#include <vector>
#include <strstream>

#include "variable.h"
#include "modelChange.h"
#include "task.h"

class SedRepeatedTask;
class SedDocument;
class SedSetValue;
class SedRepeatedTask;

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
  PhrasedRepeatedTask(SedRepeatedTask* sedRepeatedTask);
  ~PhrasedRepeatedTask();

  virtual bool isRepeated() const;
  virtual void addTask(std::string task);
  virtual std::string getPhraSEDML() const;
  virtual void addRepeatedTaskToSEDML(SedDocument* sedml) const;

  virtual const ModelChange* getModelChangeFor(std::string varname) const;

  virtual bool changeListIsInappropriate(std::stringstream& err);
  virtual std::set<PhrasedModel*> getModels() const;
  virtual bool isRecursive(std::set<PhrasedTask*>& tasks);
  virtual bool finalize();

private:
  void addLocalVariablesToSetValue(SedSetValue* ssv, SedRepeatedTask* srt) const;
  ModelChange* getModelChange(std::string id);

};


#endif //PHRASEDREPEATEDTASK_H
