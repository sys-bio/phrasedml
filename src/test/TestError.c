/**
 * \file    TestErrors.c
 * \brief   Test parsing errors in phraSEDML's constructs.
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

void testError(const string& base, const string& err)
{
  char* sedgen = convertString(base.c_str());
  fail_unless(sedgen == NULL);
  char* errgen = getLastError();
  fail_unless(err == errgen);

  free(errgen);
}

START_TEST (test_model_err1)
{
  testError("sbml_model = mod \"sbml_model.xml\"", "Unable to parse line 1 ('sbml_model = mod \"sbml_model.xml\"'): the only type of phraSED-ML content that fits the syntax '[ID] = [keyword] \"[string]\"' is model definitions, where 'keyword' is the word 'model' (i.e. 'mod1 = model \"file.xml\"').  ");
}
END_TEST



Suite *
create_suite_Errors (void)
{
  Suite *suite = suite_create("PhraSED-ML Errors");
  TCase *tcase = tcase_create("PhraSED-ML Errors");

  tcase_add_test( tcase, test_model_err1);
//  tcase_add_test( tcase, );

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


