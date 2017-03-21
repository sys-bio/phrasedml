#ifndef MODELCHANGE_H
#define MODELCHANGE_H

#include <string>
#include "phrasedml-namespace.h"

class SedChange;
class SedChange;
class SedDocument;
class SedModel;
class SedParameter;
class SedRange;
class SedRepeatedTask;
class SedSetValue;
class ASTNode;

PHRASEDML_CPP_NAMESPACE_BEGIN
class PhrasedModel;

enum change_type {
    ctype_val_assignment
  , ctype_formula_assignment
  , ctype_loop_uniformLinear
  , ctype_loop_uniformLog
  , ctype_loop_vector
};

bool isLoop(change_type type);

class ModelChange
{
private:
  ModelChange(); //undefined

  change_type m_type;
  std::vector<std::string> m_variable;
  std::vector<double> m_values;
  std::string m_formula;
  ASTNode* m_astnode;

  std::string m_model;
  std::string sbml_source_;

public:

  ModelChange(std::vector<const std::string*>* name, std::vector<std::string>* formula);
  ModelChange(change_type type, std::vector<const std::string*>* name, const std::vector<double>* values);
  ModelChange(SedChange* sedchange, SedDocument* seddoc, std::string parent, std::string sbml_source, std::string sbml_ns);
  ModelChange(SedRange* sr);
  ModelChange(SedParameter* parameter);
  ModelChange(SedSetValue* ssv);
  ModelChange(const ModelChange& orig);
  ModelChange& operator=(const ModelChange& rhs);
  ~ModelChange();

  change_type getType() const;

  std::string getPhraSEDML() const;
  bool addModelChangeToSEDMLModel(SedModel* sedmodel) const;
  bool addModelChangeToSEDMLRepeatedTask(SedRepeatedTask* sedrtask, std::vector<std::string> tasks) const;

  bool setFormulaString(const std::string& formula);
  bool setASTNode(const ASTNode* astnode);

  void setModel(std::string model);
  void setVariable(std::vector<std::string> id);

  std::string getModel() const;
  std::vector<std::string> getVariable() const;
  std::vector<double> getValues() const;
  const ASTNode* getASTNode() const;

  virtual bool finalize() const;
  virtual bool finalize(std::set<PhrasedModel*> models);
private:

};

PHRASEDML_CPP_NAMESPACE_END

#endif //MODELCHANGE_H
