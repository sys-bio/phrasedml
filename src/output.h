#ifndef PHRASEDOUTPUT_H
#define PHRASEDOUTPUT_H

#include <string>
#include <vector>
#include <map>

#include "variable.h"
#include "sbml/SBMLDocument.h"
#include "sbml/math/ASTNode.h"
#include "modelChange.h"
#include "phrasedml-namespace.h"

#include "sedml/SedPlot.h"
#include "sedml/SedReport.h"
#include "sedml/SedOutput.h"
#include "sedml/SedDocument.h"

PHRASEDML_CPP_NAMESPACE_BEGIN

class PhrasedOutput: public Variable
{
private:
  PhrasedOutput(); //undefined

  bool m_isPlot;
  std::vector<std::vector<libsbml::ASTNode*> > m_outputVariables;
  std::map<std::string, std::vector<std::string> > m_variableMap;

public:

  PhrasedOutput(const std::vector<libsbml::ASTNode*>& inputs);
  PhrasedOutput(const std::vector<std::vector<libsbml::ASTNode*> >& curves);
  PhrasedOutput(libsedml::SedOutput* sedout, libsedml::SedDocument* seddoc);
  ~PhrasedOutput();

  bool isPlot() const {return m_isPlot;};

  std::string getPhraSEDML() const;
  std::string addDataGeneratorToSEDML(libsedml::SedDocument* sedml, libsbml::ASTNode* astnodes, int num1, int num2) const;
  void addOutputToSEDML(libsedml::SedDocument* sedml) const;

  virtual bool finalize();
private:
  bool addVariableToMap(const std::string& var);
  std::string getMatchingDataGenerator(libsedml::SedDocument* sedml, libsbml::ASTNode* astnode) const;
  void replaceASTNamesAndAdd(libsbml::ASTNode* astnode, libsedml::SedDataGenerator* sdg) const;
  std::string getSimpleString(std::string formula) const;

};
PHRASEDML_CPP_NAMESPACE_END


#endif //PHRASEDOUTPUT_H
