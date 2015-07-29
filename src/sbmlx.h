#ifndef SBMLX_H
#define SBMLX_H

#include <string>
#include <vector>
#include <set>

class ASTNode;

void getVariablesFromASTNode(ASTNode* astn, std::set<std::string>& variables);

#endif //SBMLX_h
