#include <sstream>
#include <assert.h>
#include <iostream>
#include "sbml/math/ASTNode.h"
#include "sbmlx.h"

using namespace std;

void getVariablesFromASTNode(ASTNode* astn, set<string>& variables)
{
  if (astn->getType() == AST_NAME) {
    variables.insert(astn->getName());
  }
  else if (astn->getType() == AST_NAME_TIME) {
    variables.insert("time");
    astn->setName("time");
    astn->setType(AST_NAME);
  }
  for (size_t c=0; c<astn->getNumChildren(); c++) {
    getVariablesFromASTNode(astn->getChild(c), variables);
  }
}

