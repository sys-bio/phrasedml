#ifndef STRINGX_H
#define STRINGX_H

#include <string>
#include <vector>

class SBMLDocument;

std::string SizeTToString(size_t num);
std::string DoubleToString(double num);
std::string getStringFrom(const std::vector<const std::string*>* name, std::string cc=".");
std::string getIdFromXPath(const std::string& xpath);
std::string getValueXPathFromId(const std::string& id, SBMLDocument* doc);

bool IsReal(const std::string& src);

bool CaselessStrCmp(const std::string& lhs, const std::string& rhs);

#endif //STRINGX_h
