#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include "phrasedml-namespace.h"

#include "sedml/SedTypes.h"
#include "sbml/math/L3ParserSettings.h"
#include "sbml/SBMLDocument.h"

PHRASEDML_CPP_NAMESPACE_BEGIN
class PhrasedModel;
class PhrasedSimulation;
class PhrasedTask;
class PhrasedRepeatedTask;
class PhrasedOutput;
class ModelChange;

class Registry
{
private:
  std::set<std::string>    m_variablenames;
  std::string              m_error;
  int                      m_errorLine;
  std::vector<std::string> m_warnings;

  libsedml::SedDocument*   m_sedml;
  std::string              m_workingDirectory;
  std::string              m_separator;

  //The actual SEDML bits:
  std::vector<PhrasedModel>        m_models;
  std::vector<PhrasedSimulation*>  m_simulations;
  std::vector<PhrasedTask>         m_tasks;
  std::vector<PhrasedRepeatedTask> m_repeatedTasks;
  std::vector<PhrasedOutput>       m_outputs;

  //Any saved SBML documents the user has set:
  std::map<std::string, libsbml::SBMLDocument*> m_referencedSBML;

  L3ParserSettings         m_l3ps;

public:
  Registry();
  ~Registry();

  std::istream* input;

  char* convertFile(const std::string& filename);
  char* convertString(std::string model);

  L3ParserSettings* getL3ParserSettings() {return &m_l3ps;};

  void setError(std::string error, int line) {m_error = error; m_errorLine=line;};
  void addErrorPrefix(std::string error) {m_error = error + m_error;};
  void addWarning(std::string warning) {m_warnings.push_back(warning);};
  void clearWarnings() {m_warnings.clear();};

  std::string getSeparator() const {return m_separator;};

  char* getPhraSEDML() const;
  char* getSEDML() const;
  size_t getNumModels() const;
  const PhrasedModel* getModel(std::string modid) const;
  PhrasedModel* getModel(std::string modid);
  const PhrasedSimulation* getSimulation(std::string simid) const;
  PhrasedSimulation* getSimulation(std::string simid);
  size_t getNumTasks() const;
  const PhrasedTask* getTask(size_t num) const;
  const PhrasedTask* getTask(std::string taskid) const;
  PhrasedTask* getTask(std::string taskid);

  std::string getError() {return m_error;};
  int getErrorLine() {return m_errorLine;};
  std::vector<std::string> getPhrasedWarnings() {return m_warnings;};

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

  //phraSED-ML lines that define KiSAO terms:
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* value);
  bool addEquals(std::vector<const std::string*>* name, double value);

  //Repeated tasks, multiple tasks:
  bool addRepeatedTask(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<std::vector<const std::string*>*>*  key2, std::vector<const std::string*>* key3, std::vector<ModelChange>* changelist);


  //phraSED-ML lines that are clearly plots:
  bool addOutput(std::vector<const std::string*>* plot, std::vector<std::vector<std::string>*>* plotlist, const std::string* name = NULL);

  bool addMapToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* name, std::vector<const std::string*>* arg, std::vector<std::string>* formula);

  //ChangeList addition
  bool addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2);
  bool addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* name, std::vector<std::string>* formula);
  bool addToChangeListFromRange(std::vector<ModelChange>* cl, std::vector<const std::string*>* name, std::vector<const std::string*>* range, std::vector<std::string>* formula);
  bool addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* name, std::vector<std::string>* formula, bool usedEquals);
  bool addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* name, double val);
  bool addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<const std::string*>* name, double val);
  bool addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<double>* numlist);
  bool addToChangeList(std::vector<ModelChange>* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<double>* numlist);

  //Setting the 'name' attribute
  bool setName(std::vector<const std::string*>* id, std::vector<const std::string*>* is, const std::string* name);

  //Assistance functions
  std::string ftoa(double val);
  const std::string* addWord(std::string word);
  void setWorkingDirectory(const char* directory);
  std::string getWorkingFilename(const std::string& filename);

  libsbml::ASTNode* parseFormula(const std::string& formula);

  //When we're done, make sure the whole thing is coherent.
  bool finalize();

  //For parsing filenames that the user has given to us in memory instead:
  void setReferencedSBML(const char* filename, libsbml::SBMLDocument* doc);
  void clearReferencedSBML();
  libsbml::SBMLDocument* getSavedSBML(std::string filename);
  void addDotXMLToModelSources(bool force=false);

  //Some people might not want to write the Timestamp to SBML files.
  void SetWriteSEDMLTimestamp(bool set);
  bool GetWriteSEDMLTimestamp();

  //Keeping track of malloc'd stuff so we can free it ourselves if need be.
  std::vector<char*>    m_charstars;
  //std::vector<char**>   m_charstarstars;
  //std::vector<char***>  m_charstarstarstars;
  //std::vector<double*>  m_doublestars;
  //std::vector<double**> m_doublestarstars;
  //std::vector<unsigned long*> m_ulongstars;
  //std::vector<rd_type*> m_rd_typestars;
  void freeAllPhrased();

  char* getCharStar(const char* orig);

private:
  bool parseInput();
  bool parseSEDML();

  bool checkId(std::vector<const std::string*>* name);
  bool isValidSId(std::vector<const std::string*>* name);
  void clearAll();
  void clearSEDML();

  void createSEDML();
  bool file_exists (const std::string& filename);
  bool addASTToCurve(const std::vector<std::string>* x, std::vector<libsbml::ASTNode*>& curve, std::stringstream& err);
  bool addPlot(std::vector<std::vector<std::string>*>* plotlist, std::stringstream& err, const std::string* name);
  bool addReport(std::vector<std::vector<std::string>*>* plotlist, std::stringstream& err, const std::string* name);

  libsbml::ASTNode* fixTime(libsbml::ASTNode* astn);
};

PHRASEDML_CPP_NAMESPACE_END

extern PHRASEDML_CPP_NAMESPACE_QUALIFIER Registry g_registry;

#endif //REGISTRY_H
