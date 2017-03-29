#include <sstream>
#include <assert.h>
#include <iostream>
#include "sbml/math/ASTNode.h"
#include "sbmlx.h"

using namespace std;

PHRASEDML_CPP_NAMESPACE_BEGIN
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

void replaceVariablesInASTNodeWith(ASTNode* astn, const map<string, string>& replacements)
{
  if (astn->getType() == AST_NAME) {
    map<string, string>::const_iterator rep = replacements.find(astn->getName());
    if (rep != replacements.end()) {
      astn->setName(rep->second.c_str());
    }
  }
  for (size_t c=0; c<astn->getNumChildren(); c++) {
    replaceVariablesInASTNodeWith(astn->getChild(c), replacements);
  }

}

string fixMinMaxSymbolsXMLStr(string input)
{
  string ret = input;
  // replace max
  string oldstr = "<max/>";
  string newstr = "<csymbol definitionURL=\"http://sed-ml.org/#max\" encoding=\"text\">max</csymbol>";
  size_t p = ret.find(oldstr);
  while(p != string::npos) {
    ret.replace(p, oldstr.size(), newstr);
    p = ret.find(oldstr);
  }

  // replace min
  oldstr = "<min/>";
  newstr = "<csymbol definitionURL=\"http://sed-ml.org/#min\" encoding=\"text\">min</csymbol>";
  p = ret.find(oldstr);
  while(p != string::npos) {
    ret.replace(p, oldstr.size(), newstr);
    p = ret.find(oldstr);
  }

  return ret;
}
PHRASEDML_CPP_NAMESPACE_END
