/**
 * \file    TestBasic.c
 * \brief   Test phraSEDML's basic constructs.
 * \author  Lucian Smith
 * ---------------------------------------------------------------------- -->*/

#include "libutil.h"
#include "phrasedml_api.h"

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
  free(sedgen);
}

void compareStringTranslation(const string& phrasedml, const string& sedml)
{
  char* converted = convertString(phrasedml.c_str());
  if (converted==NULL) {
    cout << getLastError() << endl << endl;
    fail_unless(false);
    return;
  }
  cout << converted;
  free(converted);
}

START_TEST (test_parameter)
{
  compareFileTranslation("model1");
}
END_TEST

START_TEST (test_parameter_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\"", "model1.xml");
}
END_TEST



Suite *
create_suite_Basic (void)
{
  Suite *suite = suite_create("Antimony Basic");
  TCase *tcase = tcase_create("Antimony Basic");

  tcase_add_test( tcase, test_parameter);
  tcase_add_test( tcase, test_parameter_txt);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


