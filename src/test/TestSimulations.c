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

START_TEST (test_steadystate_0args_txt)
{
  compareStringTranslation("sim1 = simulate steadystate()", "steadystate.xml");
}
END_TEST

START_TEST (test_onestep_txt)
{
  compareStringTranslation("sim1 = simulate onestep(0.5)", "onestep.xml");
}
END_TEST

START_TEST (test_onestep)
{
  compareFileTranslation("onestep");
}
END_TEST


START_TEST (test_uniform_3args_txt)
{
  compareStringTranslation("sim1 = simulate uniform(0, 10, 1000)", "uniform_3args.xml");
}
END_TEST

START_TEST (test_uniform_3args)
{
  compareFileTranslation("uniform_3args");
}
END_TEST


START_TEST (test_uniform_4args_txt)
{
  compareStringTranslation("sim1 = simulate uniform(0, 5, 10, 500)", "uniform_4args.xml");
}
END_TEST

START_TEST (test_uniform_4args)
{
  compareFileTranslation("uniform_4args");
}
END_TEST



Suite *
create_suite_Simulations (void)
{
  Suite *suite = suite_create("phraSED-ML Simulations");
  TCase *tcase = tcase_create("phraSED-ML Simulations");

  tcase_add_test( tcase, test_uniform_4args_txt);
  tcase_add_test( tcase, test_uniform_4args);

  tcase_add_test( tcase, test_steadystate_txt);
  tcase_add_test( tcase, test_steadystate);
  tcase_add_test( tcase, test_steadystate_0args_txt);
  tcase_add_test( tcase, test_onestep_txt);
  tcase_add_test( tcase, test_onestep);
  tcase_add_test( tcase, test_uniform_3args_txt);
  tcase_add_test( tcase, test_uniform_3args);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


