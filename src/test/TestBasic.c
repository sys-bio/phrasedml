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
  char* sedgen = convertFile(phrasedfile.c_str());
  if (sedgen==NULL) {
    cout << getLastError() << endl << endl;
    fail_unless(false);
    return;
  }
  cout << sedgen;
  char* phrased_rt = getLastPhraSEDML();
  cout << phrased_rt;
  free(sedgen);
  free(phrased_rt);
}

void compareStringTranslation(const string& phrasedml, const string& sedml)
{
  setWorkingDirectory(TestDataDirectory);
  char* sedgen = convertString(phrasedml.c_str());
  if (sedgen==NULL) {
    cout << getLastError() << endl << endl;
    fail_unless(false);
    return;
  }
  cout << sedgen;
  char* phrased_rt = getLastPhraSEDML();
  cout << phrased_rt;
  free(phrased_rt);
  free(sedgen);
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

START_TEST (test_model2_txt)
{
  compareStringTranslation("sbml_model = model \"unknown_model.xml\"", "model2.xml");
}
END_TEST




Suite *
create_suite_Basic (void)
{
  Suite *suite = suite_create("Antimony Basic");
  TCase *tcase = tcase_create("Antimony Basic");

  tcase_add_test( tcase, test_model);
  tcase_add_test( tcase, test_model_txt);
  tcase_add_test( tcase, test_model_name);
  tcase_add_test( tcase, test_model_name_txt);
  tcase_add_test( tcase, test_model2_txt);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


