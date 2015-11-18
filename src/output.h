#ifndef PHRASEDOUTPUT_H
#define PHRASEDOUTPUT_H

#include <string>
#include <vector>
#include <map>

#include "variable.h"
#include "sbml/SBMLDocument.h"
#include "modelChange.h"

class SedPlot;
class SedReport;
class SedOutput;
class SedDocument;
class ASTNode;

class PhrasedOutput: public Variable
{
private:
  PhrasedOutput(); //undefined

  bool m_isPlot;
  std::vector<std::vector<ASTNode*> > m_outputVariables;
  std::map<std::string, std::vector<std::string> > m_variableMap;

public:

  PhrasedOutput(const std::vector<ASTNode*>& inputs);
  PhrasedOutput(const std::vector<std::vector<ASTNode*> >& curves);
  PhrasedOutput(SedOutput* sedout, SedDocument* seddoc);
  ~PhrasedOutput();

  bool isPlot() const {return m_isPlot;};

  std::string getPhraSEDML() const;
  std::string addDataGeneratorToSEDML(SedDocument* sedml, ASTNode* astnodes, int num1, int num2) const;
  void addOutputToSEDML(SedDocument* sedml) const;

  virtual bool finalize();
private:
  bool addVariableToMap(const std::string& var);
  std::string getMatchingDataGenerator(SedDocument* sedml, ASTNode* astnode) const;
  void replaceASTNamesAndAdd(ASTNode* astnode, SedDataGenerator* sdg) const;

};


#endif //PHRASEDOUTPUT_H
