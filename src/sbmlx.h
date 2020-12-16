#ifndef SBMLX_H
#define SBMLX_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include "phrasedml-namespace.h"
#include "sbml/math/ASTNode.h"

PHRASEDML_CPP_NAMESPACE_BEGIN
void getVariablesFromASTNode(libsbml::ASTNode* astn, std::set<std::string>& variables);
void replaceVariablesInASTNodeWith(libsbml::ASTNode* astn, const std::map<std::string, std::string>& replacements);
std::string fixMinMaxSymbolsXMLStr(std::string input);
PHRASEDML_CPP_NAMESPACE_END

#endif //SBMLX_h
