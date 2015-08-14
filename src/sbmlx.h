#ifndef SBMLX_H
#define SBMLX_H

#include <string>
#include <vector>
#include <set>
#include <map>

class ASTNode;

void getVariablesFromASTNode(ASTNode* astn, std::set<std::string>& variables);
void replaceVariablesInASTNodeWith(ASTNode* astn, const std::map<std::string, std::string>& replacements);

#endif //SBMLX_h
