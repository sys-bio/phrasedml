#include <cassert>
#include <clocale>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string.h>
#include <locale.h>

#include "phrasedml_api.h"
#include "registry.h"


using namespace std;
extern int phrasedml_yyparse();
extern int phrasedml_yylloc_first_line;

//Useful functions for later routines:
char* getCharStar(const char* orig)
{
  char* ret = strdup(orig);
  if (ret == NULL) {
    g_registry.setError("Out of memory error.");
    return NULL;
  }
  g_registry.m_charstars.push_back(ret);
  return ret;
}

//Exported routines:

LIB_EXTERN char* convertFile(const char* filename)
{
  string oldlocale = setlocale(LC_ALL, NULL);
  setlocale(LC_ALL, "C");
  string ret = g_registry.convertFile(filename);
  setlocale(LC_ALL, oldlocale.c_str());
  if(ret.empty()) return NULL;
  return getCharStar(ret.c_str());
}

LIB_EXTERN char* convertString(const char* model)
{
  string oldlocale = setlocale(LC_ALL, NULL);
  setlocale(LC_ALL, "C");
  string ret = g_registry.convertString(model);
  setlocale(LC_ALL, oldlocale.c_str());
  if(ret.empty()) return NULL;
  return getCharStar(ret.c_str());
}


LIB_EXTERN char* getLastError()
{
  return getCharStar((g_registry.getError()).c_str());
}

LIB_EXTERN char* getLastPhraSEDML()
{
  return getCharStar((g_registry.getPhraSEDML()).c_str());
}

LIB_EXTERN char* getLastSEDML()
{
  return getCharStar((g_registry.getSEDML()).c_str());
}

LIB_EXTERN char* getWarnings()
{
  string ret;
  vector<string> warnings = g_registry.getWarnings();
  if (warnings.size() == 0) return NULL;
  for (size_t warn=0; warn<warnings.size(); warn++) {
    if (warn > 0) {
      ret += "\n";
    }
    ret += warnings[warn];
  }
  return getCharStar(ret.c_str());
}

LIB_EXTERN void freeAll()
{
  g_registry.freeAll();
}
