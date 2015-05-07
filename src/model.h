#ifndef PHRASEDMODEL_H
#define PHRASEDMODEL_H

#include <string>
#include <vector>

#include "variable.h"
#include "sbml\SBMLDocument.h"

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
  std::vector<ChangeList*> m_changes;

  bool m_isFile;
  SBMLDocument m_sbml;

public:

  PhrasedModel(std::string id, std::string source, bool isFile);
  PhrasedModel(std::string id, std::string source, std::vector<ChangeList*> changes, bool isFile);
  PhrasedModel(SedModel* sedmodel, SedDocument* seddoc);
  ~PhrasedModel();

  void setIsFile(bool isfile);
  bool getIsFile();

  std::string getPhraSEDML() const;
  void addModelToSEDML(SedDocument* sedml) const;

  void langTypeToURI(language type) const;
private:
  void processSource();
  language getLanguageFromURI(std::string uri) const;
  std::string getURIFromLanguage(language lang) const;

};


#endif //PHRASEDMODEL_H
