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
#include <fstream>

using namespace std;

BEGIN_C_DECLS

extern char *TestDataDirectory;
PHRASEDML_CPP_NAMESPACE_USE

#define FIX_STORED_FILES false

void compareFileTranslation(const string& base)
{
    string dir(TestDataDirectory);
    string phrasedfile = dir + base + ".txt";
    string sedfile = dir + base + ".xml";
    char* sed_gen = convertFile(phrasedfile.c_str());
    if (sed_gen == NULL) {
        cout << getLastPhrasedError() << endl << endl;
        fail_unless(false);
        return;
    }
    //cout << "SED-ML generated from " << base << ".txt" << endl << sed_gen << endl;
    char* phrased_rt = getLastPhraSEDML();

    char* phrased_gen = convertFile(sedfile.c_str());
    if (phrased_gen == NULL) {
        cout << getLastPhrasedError() << endl << endl;
        fail_unless(false);
        return;
    }
    //cout << "phraSED-ML generated from " << base << ".xml" << endl << phrased_gen << endl;
    char* sed_rt = getLastSEDML();

    if (FIX_STORED_FILES)
    {
        if ((string)sed_rt != (string)sed_gen) {
          ofstream outfile((dir + base + ".xml").c_str());
          outfile.write(sed_gen, ((string)sed_gen).size());
          outfile.close();
        }
    }
    else
    {
        fail_unless((string)sed_rt == (string)sed_gen);
    }
    fail_unless((string)phrased_rt == (string)phrased_gen);

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
    cout << getLastPhrasedError() << endl << endl;
    fail_unless(false);
    return;
  }
  char* phrased_rt = getLastPhraSEDML();

  string dir(TestDataDirectory);
  string sedfile = dir + sedml;
  char* phrased_gen = convertFile(sedfile.c_str());
  if (phrased_gen==NULL) {
    cout << getLastPhrasedError() << endl << endl;
    fail_unless(false);
    return;
  }
  char* sed_rt = getLastSEDML();

  if (FIX_STORED_FILES)
  {
      if ((string)sed_rt != (string)sed_gen) {
          ofstream outfile((dir + sedml).c_str());
          outfile.write(sed_gen, ((string)sed_gen).size());
          outfile.close();
      }
  }
  else
  {
      fail_unless((string)sed_rt == (string)sed_gen);
  }

  fail_unless((string)phrased_rt == (string)phrased_gen);
  if ((string)phrased_rt != (string)phrased_gen)
  {
      cout << "phraSED-ML has changed between:" << endl;
      cout << phrased_rt;
      cout << phrased_gen;
      cout << endl;
  }

  free(sed_gen);
  free(sed_rt);
  free(phrased_gen);
  free(phrased_rt);
}

void compareStringAndFileTranslation(const string& phrasedml, const string& base)
{
  compareStringTranslation(phrasedml, base+".xml");
  compareFileTranslation(base);
}

void compareOriginalXMLTranslations(const string& base)
{
  string dir(TestDataDirectory);
  string phrasedfile = dir + base + ".txt";
  string sedfile = dir + base + ".xml";
  string sedrtfile = dir + base + "_rt.xml";
  char* sed_gen = convertFile(phrasedfile.c_str());
  if (sed_gen==NULL) {
    cout << getLastPhrasedError() << endl << endl;
    fail_unless(false);
    return;
  }
  //cout << "SED-ML generated from " << base << ".txt" << endl << sed_gen << endl;
  char* phrased_rt = getLastPhraSEDML();

  char* phrased_gen = convertFile(sedfile.c_str());
  if (phrased_gen==NULL) {
    cout << getLastPhrasedError() << endl << endl;
    fail_unless(false);
    return;
  }
  //cout << "phraSED-ML generated from " << base << ".xml" << endl << phrased_gen << endl;


  char* phrased_rt_gen = convertFile(sedrtfile.c_str());
  char* sed_rt = getLastSEDML();

  if (FIX_STORED_FILES)
  {
      if ((string)sed_rt != (string)sed_gen) {
          ofstream outfile((dir + base + "_rt.xml").c_str());
          outfile.write(sed_gen, ((string)sed_gen).size());
          outfile.close();
      }
  }
  else
  {
      fail_unless((string)sed_rt == (string)sed_gen);
  }

  fail_unless((string)phrased_rt == (string)phrased_gen);
  fail_unless((string)phrased_rt == (string)phrased_rt_gen);

  if ((string)phrased_rt != (string)phrased_gen)
  {
      cout << "phraSED-ML has changed between:" << endl;
      cout << phrased_rt;
      cout << phrased_gen;
      cout << endl;
  }

  free(sed_gen);
  free(sed_rt);
  free(phrased_gen);
  free(phrased_rt);
  free(phrased_rt_gen);
}


END_C_DECLS
