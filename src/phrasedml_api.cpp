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
#include "phrasedml-namespace.h"
#include <sbml/SBMLReader.h>
#include <sbml/SBMLTypes.h>


#ifdef _MSC_VER
#  define strdup _strdup
#endif

using namespace std;
extern int phrased_yylloc_last_line;
PHRASEDML_CPP_NAMESPACE_BEGIN

//Exported routines:

LIB_EXTERN char* convertFile(const char* filename)
{
  string oldlocale = setlocale(LC_ALL, NULL);
  setlocale(LC_ALL, "C");
  char* ret = g_registry.convertFile(filename);
  setlocale(LC_ALL, oldlocale.c_str());
  return ret;
}

LIB_EXTERN char* convertString(const char* model)
{
  string oldlocale = setlocale(LC_ALL, NULL);
  setlocale(LC_ALL, "C");
  char* ret = g_registry.convertString(model);
  setlocale(LC_ALL, oldlocale.c_str());
  return ret;
}


LIB_EXTERN char* getLastPhrasedError()
{
  return g_registry.getCharStar((g_registry.getError()).c_str());
}

LIB_EXTERN int getLastPhrasedErrorLine()
{
  return g_registry.getErrorLine();
}



LIB_EXTERN char* getLastPhraSEDML()
{
  return g_registry.getPhraSEDML();
}

LIB_EXTERN char* getLastSEDML()
{
  return g_registry.getSEDML();
}

LIB_EXTERN char* getPhrasedWarnings()
{
  string ret;
  vector<string> warnings = g_registry.getPhrasedWarnings();
  if (warnings.size() == 0) return NULL;
  for (size_t warn=0; warn<warnings.size(); warn++) {
    if (warn > 0) {
      ret += "\n";
    }
    ret += warnings[warn];
  }
  return g_registry.getCharStar(ret.c_str());
}

LIB_EXTERN void setWorkingDirectory(const char* directory)
{
  g_registry.setWorkingDirectory(directory);
}

LIB_EXTERN bool setReferencedSBML(const char* filename, const char* docstr)
{
  SBMLDocument* doc = readSBMLFromString(docstr);
  g_registry.setReferencedSBML(filename, doc);
  return (doc->getErrorLog()->getNumFailsWithSeverity(LIBSBML_SEV_ERROR) == 0);
}

LIB_EXTERN void clearReferencedSBML()
{
  g_registry.clearReferencedSBML();
}

LIB_EXTERN void addDotXMLToModelSources(bool force)
{
  g_registry.addDotXMLToModelSources(force);
}

LIB_EXTERN void freeAllPhrased()
{
  g_registry.freeAllPhrased();
}

LIB_EXTERN void setWriteSEDMLTimestamp(bool writeTimestamp)
{
  g_registry.SetWriteSEDMLTimestamp(writeTimestamp);
}

PHRASEDML_CPP_NAMESPACE_END
