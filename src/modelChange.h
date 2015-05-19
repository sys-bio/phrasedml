#ifndef MODELCHANGE_H
#define MODELCHANGE_H

#include <string>

class SedChange;
class SedDocument;
class SedModel;

class ModelChange
{
private:
  ModelChange(); //undefined

  std::string m_variable;
  double m_value;

  std::string m_parent;

public:

  ModelChange(std::vector<const std::string*>* name, double value);
  ModelChange(SedChange* sedchange, SedDocument* seddoc, std::string parent);
  ~ModelChange();

  void setIsFile(bool isfile);
  bool getIsFile();

  std::string getPhraSEDML() const;
  bool addModelChangeToSEDML(SedModel* sedmodel) const;

  void setParent(std::string parent);
  std::string getParent() const;

  bool check() const;
private:

};


#endif //MODELCHANGE_H
