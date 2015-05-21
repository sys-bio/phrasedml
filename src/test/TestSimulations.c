/**
 * \file    TestBasic.c
 * \brief   Test phraSEDML's basic constructs.
 * \author  Lucian Smith
 * ---------------------------------------------------------------------- -->*/

#include "libutil.h"
#include "phrasedml_api.h"
#include "registry.h"
#include "TestUtil.h"

#include <string>
#include <check.h>
#include <iostream>

using namespace std;

BEGIN_C_DECLS

extern char *TestDataDirectory;

START_TEST (test_steadystate_txt)
{
  compareStringTranslation("sim1 = simulate steadystate", "steadystate.xml");
}
END_TEST

START_TEST (test_steadystate)
{
  compareFileTranslation("steadystate");
}
END_TEST



Suite *
create_suite_Simulations (void)
{
  Suite *suite = suite_create("phraSED-ML Simulations");
  TCase *tcase = tcase_create("phraSED-ML Simulations");

  tcase_add_test( tcase, test_steadystate_txt);
  tcase_add_test( tcase, test_steadystate);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


