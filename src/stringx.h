#ifndef STRINGX_H
#define STRINGX_H

#include <string>
#include <vector>
#include <set>
#include "phrasedml-namespace.h"

class SBMLDocument;
class PhrasedModel;

PHRASEDML_CPP_NAMESPACE_BEGIN
//String functions
std::string SizeTToString(size_t num);
std::string DoubleToString(double num);
std::string getStringFrom(const std::vector<const std::string*>* name, std::string cc=".");
std::string getStringFrom(const std::vector<std::string>* name, std::string cc=".");
std::string getStringFrom(const std::vector<double>& numbers);
std::vector<std::string> getStringVecFromDelimitedString(const std::string& var, std::string delimiter="_____");

//Xpath functions
std::vector<std::string> getIdFromXPath(const std::string& xpath);
std::string getValueXPathFromId(const std::vector<std::string>* id, const SBMLDocument* doc);
std::string getElementXPathFromId(const std::vector<std::string>* id, const SBMLDocument* doc);
void getElementXPathFromId(const std::string& id, std::set<PhrasedModel*> docs, std::string& xpath, std::string& modelref);

bool IsReal(const std::string& src);
bool IsInt(const std::string& src);

bool CaselessStrCmp(const std::string& lhs, const std::string& rhs);
PHRASEDML_CPP_NAMESPACE_END

#endif //STRINGX_h
