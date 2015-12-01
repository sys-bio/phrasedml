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

START_TEST (test_steadystate)
{
  compareStringAndFileTranslation("sim1 = simulate steadystate", "steadystate");
}
END_TEST

START_TEST (test_steadystate_0args)
{
  compareStringAndFileTranslation("sim1 = simulate steadystate()", "steadystate");
}
END_TEST

START_TEST (test_onestep)
{
  compareStringAndFileTranslation("sim1 = simulate onestep(0.5)", "onestep");
}
END_TEST

START_TEST (test_uniform_3args)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0, 10, 1000)", "uniform_3args");
}
END_TEST

START_TEST (test_uniform_4args)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0, 5, 10, 500)", "uniform_4args");
}
END_TEST


START_TEST (test_uniform_stochastic_3args)
{
  compareStringAndFileTranslation("sim1 = simulate uniform_stochastic(0, 10, 1000)", "uniform_stochastic_3args");
}
END_TEST

START_TEST (test_uniform_stochastic_4args)
{
  compareStringAndFileTranslation("sim1 = simulate uniform_stochastic(0, 5, 10, 500)", "uniform_stochastic_4args");
}
END_TEST 


START_TEST (test_sedml_webtools_gillespie_transcription)
{
  compareOriginalXMLTranslations("sedml_webtools_gillespie_transcription");
}
END_TEST 




Suite *
create_suite_Simulations (void)
{
  Suite *suite = suite_create("phraSED-ML Simulations");
  TCase *tcase = tcase_create("phraSED-ML Simulations");

  tcase_add_test( tcase, test_sedml_webtools_gillespie_transcription);

  tcase_add_test( tcase, test_steadystate);
  tcase_add_test( tcase, test_onestep);
  tcase_add_test( tcase, test_uniform_3args);
  tcase_add_test( tcase, test_uniform_4args);
  tcase_add_test( tcase, test_uniform_stochastic_3args);
  tcase_add_test( tcase, test_uniform_stochastic_4args);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


