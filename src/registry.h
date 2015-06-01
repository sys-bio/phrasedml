#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include <string>
#include <sstream>
#include <set>

#include "sedml\SedTypes.h"

//#include <ctype.h>
//#include <fstream>
//#include <iostream>
//#include <math.h>
//#include <set>
//#include <stdio.h>
//#include <string>
//#include <sstream>

//#include "dnastrand.h"
//#include "module.h"
//#include "reactantlist.h"
//#include "reaction.h"
//#include "enums.h"

class PhrasedModel;
class PhrasedSimulation;
class PhrasedTask;
class ModelChange;

class Registry
{
private:
  std::set<std::string>    m_variablenames;
  std::string              m_error;
  int                      m_errorLine;
  std::vector<std::string> m_warnings;

  SedDocument*             m_sedml;
  std::string              m_workingDirectory;

  //The actual SEDML bits:
  std::vector<PhrasedModel> m_models;
  std::vector<PhrasedSimulation*> m_simulations;
  std::vector<PhrasedTask> m_tasks;

public:
  Registry();
  ~Registry();

  std::istream* input;

  char* convertFile(const std::string& filename);
  char* convertString(std::string model);

  void setError(std::string error, int line) {m_error = error; m_errorLine=line;};
  void addErrorPrefix(std::string error) {m_error = error + m_error;};
  void addWarning(std::string warning) {m_warnings.push_back(warning);};
  void clearWarnings() {m_warnings.clear();};

  char* getPhraSEDML() const;
  char* getSEDML() const;
  const PhrasedModel* getModel(std::string modid) const;
  PhrasedModel* getModel(std::string modid);
  const PhrasedSimulation* getSimulation(std::string simid) const;
  PhrasedSimulation* getSimulation(std::string simid);
  const PhrasedTask* getTask(std::string taskid) const;
  PhrasedTask* getTask(std::string taskid);

  std::string getError() {return m_error;};
  int getErrorLine() {return m_errorLine;};
  std::vector<std::string> getWarnings() {return m_warnings;};

  //phraSED-ML lines that are clearly model definitions:
  bool addModelDef(std::vector<const std::string*>* name, std::vector<const std::string*>* model, const std::string* modelloc);
  bool addModelDef(std::vector<const std::string*>* name, std::vector<const std::string*>* model, const std::string* modelloc, std::vector<const std::string*>* with, std::vector<ModelChange>* changelist);
  bool addModelDef(std::vector<const std::string*>* name, std::vector<const std::string*>* model, const std::string* modelloc, std::vector<const std::string*>* with, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2);
  bool addModelDef(std::vector<const std::string*>* name, std::vector<const std::string*>* model, const std::string* modelloc, std::vector<const std::string*>* with, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<ModelChange>* changelist);

  //phraSED-ML lines that could be almost anything:
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2);
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<ModelChange>* changelist);
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<const std::string*>* key4);
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<const std::string*>* key4, std::vector<const std::string*>* key5);
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<const std::string*>* key4, std::vector<const std::string*>* key5, std::vector<ModelChange>* changelist);
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<double>* numlist);


  //phraSED-ML lines that are clearly plots:
  bool addPlot(std::vector<const std::string*>* plot, std::vector<const std::string*>* name, std::vector<const std::string*>* vs,  std::vector<std::vector<const std::string*>*>* plotlist);

  
  //ChangeList addition
  bool addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2);
  bool addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* name, double val);
  bool addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* name, std::vector<std::string>* formula);
  bool addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* name, double val);
  bool addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<const std::string*>* name, double val);
  
  //Setting the 'name' attribute
  bool setName(std::vector<const std::string*>* id, std::vector<const std::string*>* is, const std::string* name);

  //Assistance functions
  std::string ftoa(double val);
  const std::string* addWord(std::string word);
  void setWorkingDirectory(const char* directory);
  std::string getWorkingFilename(const std::string& filename);

  //When we're done, make sure the whole thing is coherent.
  bool finalize();

  //Keeping track of malloc'd stuff so we can free it ourselves if need be.
  std::vector<char*>    m_charstars;
  //std::vector<char**>   m_charstarstars;
  //std::vector<char***>  m_charstarstarstars;
  //std::vector<double*>  m_doublestars;
  //std::vector<double**> m_doublestarstars;
  //std::vector<unsigned long*> m_ulongstars;
  //std::vector<rd_type*> m_rd_typestars;
  void freeAll();

private:
  bool parseInput();
  bool parseSEDML();

  bool checkId(std::vector<const std::string*>* name);
  bool isValidSId(std::vector<const std::string*>* name);
  void clearAll();
  void clearSEDML();

  void createSEDML();
  bool file_exists (const std::string& filename);

};

extern Registry g_registry;


#endif //REGISTRY_H
