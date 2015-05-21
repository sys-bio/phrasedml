/**
 * \file    TestBasic.c
 * \brief   Test phraSEDML's basic constructs.
 * \author  Lucian Smith
 * ---------------------------------------------------------------------- -->*/

#include "libutil.h"
#include "phrasedml_api.h"
#include "registry.h"
#include "TestUtil.h"

#include <check.h>
#include <iostream>

using namespace std;

BEGIN_C_DECLS

extern char *TestDataDirectory;

void compareFileTranslation(const string& base)
{
  string dir(TestDataDirectory);
  string phrasedfile = dir + base + ".txt";
  string sedfile = dir + base + ".xml";
  char* sed_gen = convertFile(phrasedfile.c_str());
  if (sed_gen==NULL) {
    cout << getLastError() << endl << endl;
    fail_unless(false);
    return;
  }
  cout << "SED-ML generated from " << base << ".txt" << endl << sed_gen << endl;
  char* phrased_rt = getLastPhraSEDML();

  char* phrased_gen = convertFile(sedfile.c_str());
  if (phrased_gen==NULL) {
    cout << getLastError() << endl << endl;
    fail_unless(false);
    return;
  }
  cout << "phraSED-ML generated from " << base << ".xml" << endl << phrased_gen << endl;
  char* sed_rt = getLastSEDML();

  fail_unless((string)phrased_rt == (string)phrased_gen);
  fail_unless((string)sed_rt     == (string)sed_gen);

  free(sed_gen);
  free(sed_rt);
  free(phrased_gen);
  free(phrased_rt);
}

void compareStringTranslation(const string& phrasedml, const string& sedml)
{
  setWorkingDirectory(TestDataDirectory);
  char* sed_gen = convertString(phrasedml.c_str());
  if (sed_gen==NULL) {
    cout << getLastError() << endl << endl;
    fail_unless(false);
    return;
  }
  char* phrased_rt = getLastPhraSEDML();

  string dir(TestDataDirectory);
  string sedfile = dir + sedml;
  char* phrased_gen = convertFile(sedfile.c_str());
  if (phrased_gen==NULL) {
    cout << getLastError() << endl << endl;
    fail_unless(false);
    return;
  }
  char* sed_rt = getLastSEDML();

  fail_unless((string)phrased_rt == (string)phrased_gen);
  fail_unless((string)sed_rt     == (string)sed_gen);

  free(sed_gen);
  free(sed_rt);
  free(phrased_gen);
  free(phrased_rt);
}

END_C_DECLS
