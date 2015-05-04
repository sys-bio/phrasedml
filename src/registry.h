#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include <string>
#include <sstream>
#include <set>

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

class ChangeList;

class Registry
{
private:
  std::set<std::string>    m_variablenames;
  std::string              m_error;
  std::vector<std::string> m_warnings;

public:
  Registry();
  ~Registry();

  std::istream* input;

  std::string convertFile(const std::string& filename);
  std::string convertString(std::string model);

  void setError(std::string error) {m_error = error;};
  void addErrorPrefix(std::string error) {m_error = error + m_error;};
  void addWarning(std::string warning) {m_warnings.push_back(warning);};
  void clearWarnings() {m_warnings.clear();};

  std::string getPhraSEDML() const;
  std::string getSEDML() const;

  std::string getError() {return m_error;};
  std::vector<std::string> getWarnings() {return m_warnings;};

  //phraSED-ML lines that are clearly model definitions:
  bool addModelDef(std::vector<const std::string*>* name, std::vector<const std::string*>* model, const std::string* modelloc);
  bool addModelDef(std::vector<const std::string*>* name, std::vector<const std::string*>* model, const std::string* modelloc, std::vector<const std::string*>* with, ChangeList* changelist);
  bool addModelDef(std::vector<const std::string*>* name, std::vector<const std::string*>* model, const std::string* modelloc, std::vector<const std::string*>* with, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, ChangeList* changelist);

  //phraSED-ML lines that could be almost anything:
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2);
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, ChangeList* changelist);
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<const std::string*>* key4);
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<const std::string*>* key4, std::vector<const std::string*>* key5);
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<const std::string*>* key4, std::vector<const std::string*>* key5, ChangeList* changelist);
  bool addEquals(std::vector<const std::string*>* name, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<double>* numlist);


  //phraSED-ML lines that are clearly plots:
  bool addPlot(std::vector<const std::string*>* plot, std::vector<const std::string*>* name, std::vector<const std::string*>* vs,  std::vector<std::vector<const std::string*>*>* plotlist);

  
  //ChangeList creation
  ChangeList* createChangeList(std::vector<const std::string*>* name, double val);
  ChangeList* createChangeList(std::vector<const std::string*>* name, std::vector<const std::string*>* key, std::vector<std::string>* formula );
  ChangeList* createChangeList(std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* name, double val );
  ChangeList* createChangeList(std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<const std::string*>* name, double val );

  //ChangeList addition
  bool addToChangeList(ChangeList* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2);
  bool addToChangeList(ChangeList* cl, std::vector<const std::string*>* name, double val);
  bool addToChangeList(ChangeList* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* name, std::vector<std::string>* formula);
  bool addToChangeList(ChangeList* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* name, double val);
  bool addToChangeList(ChangeList* cl, std::vector<const std::string*>* key1, std::vector<const std::string*>* key2, std::vector<const std::string*>* key3, std::vector<const std::string*>* name, double val);
  
  //Assistance functions
  std::string ftoa(double val);
  const std::string* addWord(std::string word);

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
  std::string parseInput();
  std::string getSEDML();
  std::string getPhraSEDML();

};

extern Registry g_registry;


#endif //REGISTRY_H
