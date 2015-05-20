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
  testError("sbml_model = mod \"sbml_model.xml\"", "Unable to parse line 1 ('sbml_model = mod \"sbml_model.xml\"'): the only type of phraSED-ML content that fits the syntax '[ID] = [keyword] \"[string]\"' is model definitions, where 'keyword' is the word 'model' (i.e. 'mod1 = model \"file.xml\"').");
}
END_TEST


START_TEST (test_model_err2)
{
  testError("sbml.model = model \"sbml_model.xml\"", "Unable to parse line 1: the phraSED-ML ID 'sbml.model' in this context may not be a sub-id of another variable.");
}
END_TEST


START_TEST (test_model_err3)
{
  testError("0sbml_model = model \"sbml_model.xml\"", "syntax error, unexpected number");
}
END_TEST


START_TEST (test_model_changeerr1)
{
  testError("sbml_model = model \"sbml_model.xml\" and S1=3", "Unable to parse line 1 ('sbml_model = model \"sbml_model.xml\" and [...]'): the only type of phraSED-ML content that fits the syntax '[ID] = [keyword] \"[string]\" [keyword] [...]' is model definitions, where 'keyword' is the word 'with' (i.e. 'mod1 = model \"file.xml\" with S1=3').");
}
END_TEST


START_TEST (test_model_changeerr2)
{
  testError("sbml_model = model \"sbml_model.xml\" with S1.S1=3", "No such id in SBML document: 'S1.S1'.");
}
END_TEST


START_TEST (test_model_noimp1)
{
  testError("sbml_model = model \"sbml_model.xml\" with remove S1", "Unable to parse line 1 at 'remove S1': changes to models of the form '[keyword] [id]' (such as 'remove S1') are not currently supported.  Future plans include incorporation of this functionality.");
}
END_TEST


START_TEST (test_model_noimp2)
{
  testError("sbml_model = model \"sbml_model.xml\" with add parameter S1=1", "Unable to parse line 0 at 'add parameterS1 = 1': changes to models of the form '[keyword] [keyword] [id] = [value]' (such as 'add parameter p1 = 3') are not currently supported.  Future plans include incorporation of this functionality.");
}
END_TEST


START_TEST (test_model_noimp3)
{
  testError("sbml_model = model \"sbml_model.xml\" with change S1 to S2=3", "Unable to parse line 0 at 'change S1toS2 = 3': changes to models of the form '[keyword] [id] [keyword] [id] = [value]' (such as 'change p1 to p3 = 5') are not currently supported.  Future plans include incorporation of this functionality.");
}
END_TEST


START_TEST (test_model_noimp4)
{
  testError("sbml_model = model \"sbml_model.xml\" with compute S1=k1/k2", "Unable to parse line 1 at 'compute S1 = k1 / k2': changes to models of the form '[keyword] [id] = [formula]' (such as 'compute S1 = k1/k2') are not currently supported.  Future plans include incorporation of this functionality.");
}
END_TEST


Suite *
create_suite_Errors (void)
{
  Suite *suite = suite_create("PhraSED-ML Errors");
  TCase *tcase = tcase_create("PhraSED-ML Errors");

  tcase_add_test( tcase, test_model_noimp1);
  tcase_add_test( tcase, test_model_noimp2);
  tcase_add_test( tcase, test_model_noimp3);
  tcase_add_test( tcase, test_model_noimp4);

  tcase_add_test( tcase, test_model_err1);
  tcase_add_test( tcase, test_model_err2);
  tcase_add_test( tcase, test_model_err3);
  tcase_add_test( tcase, test_model_changeerr1);
  tcase_add_test( tcase, test_model_changeerr2);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


