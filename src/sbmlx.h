#ifndef SBMLX_H
#define SBMLX_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include "phrasedml-namespace.h"

class ASTNode;

PHRASEDML_CPP_NAMESPACE_BEGIN
void getVariablesFromASTNode(ASTNode* astn, std::set<std::string>& variables);
void replaceVariablesInASTNodeWith(ASTNode* astn, const std::map<std::string, std::string>& replacements);
PHRASEDML_CPP_NAMESPACE_END

#endif //SBMLX_h
