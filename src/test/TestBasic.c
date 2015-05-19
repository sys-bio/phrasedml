/**
 * \file    TestBasic.c
 * \brief   Test phraSEDML's basic constructs.
 * \author  Lucian Smith
 * ---------------------------------------------------------------------- -->*/

#include "libutil.h"
#include "phrasedml_api.h"
#include "registry.h"

#include <string>
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

START_TEST (test_model)
{
  compareFileTranslation("model1");
}
END_TEST

START_TEST (test_model_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\"", "model1.xml");
}
END_TEST


START_TEST (test_model_name)
{
  compareFileTranslation("model_name");
}
END_TEST

START_TEST (test_model_name_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_model is \"The SBML Model\"", "model_name.xml");
}
END_TEST

START_TEST (test_model2)
{
  compareFileTranslation("model2");
}
END_TEST

START_TEST (test_model2_txt)
{
  compareStringTranslation("sbml_model = model \"unknown_model.xml\"", "model2.xml");
}
END_TEST


START_TEST (test_model_attchange_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\" with S1=4", "model_attchange.xml");
}
END_TEST




Suite *
create_suite_Basic (void)
{
  Suite *suite = suite_create("Antimony Basic");
  TCase *tcase = tcase_create("Antimony Basic");

  tcase_add_test( tcase, test_model_attchange_txt);


  tcase_add_test( tcase, test_model);
  tcase_add_test( tcase, test_model_txt);
  tcase_add_test( tcase, test_model_name);
  tcase_add_test( tcase, test_model_name_txt);
  tcase_add_test( tcase, test_model2);
  tcase_add_test( tcase, test_model2_txt);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


