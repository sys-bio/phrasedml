#ifndef PHRASEDMODEL_H
#define PHRASEDMODEL_H

#include <string>
#include <vector>

#include "variable.h"
#include "sbml/SBMLDocument.h"
#include "modelChange.h"
#include "phrasedml-namespace.h"

class SedComputeChange;
class SedModel;

PHRASEDML_CPP_NAMESPACE_BEGIN
enum language {
  lang_XML,
  lang_SBML,
  lang_CellML,
  lang_SBMLl1v1,
  lang_SBMLl1v2,
  lang_SBMLl2v1,
  lang_SBMLl2v2,
  lang_SBMLl2v3,
  lang_SBMLl2v4,
  lang_SBMLl2v5,
  lang_SBMLl3v1,
  lang_SBMLl3v2,
  lang_CellML1_0,
  lang_CellML1_1,
  lang_CellML1_2
};

class PhrasedModel : public Variable
{
private:
  PhrasedModel(); //undefined

  language m_type;
  std::string m_source;
  std::vector<ModelChange> m_changes;

  bool m_isFile;
  libsbml::SBMLDocument m_sbml;

public:

  PhrasedModel(std::string id, std::string source, bool isFile);
  PhrasedModel(std::string id, std::string source, std::vector<ModelChange> changes, bool isFile);
  PhrasedModel(SedModel* sedmodel, SedDocument* seddoc);
  ~PhrasedModel();

  void setIsFile(bool isfile);
  bool getIsFile() const;
  language getType() const;
  const libsbml::SBMLDocument* getSBMLDocument() const {return &m_sbml;} ;
  libsbml::SBMLDocument* getSBMLDocument();

  std::string getPhraSEDML() const;
  void addModelToSEDML(SedDocument* sedml) const;

  //void langTypeToURI(language type) const;

  std::string getSource() const {return m_source;};
  void setSource(std::string source) {m_source = source;};

  virtual bool changeListIsInappropriate(std::stringstream& err);
  virtual bool finalize();
private:
  void processSource();
  language getLanguageFromURI(std::string uri) const;
  std::string getURIFromLanguage(language lang) const;
  void addLocalVariablesToComputeChange(SedComputeChange* scc, SedModel* model) const;

};

PHRASEDML_CPP_NAMESPACE_END

#endif //PHRASEDMODEL_H
