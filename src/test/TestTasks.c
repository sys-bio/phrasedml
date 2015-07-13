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

START_TEST (task)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate steadystate\ntask1 = run sim1 on mod1", "task");
}
END_TEST

START_TEST (repeatedtask_uniform)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = repeat task1 for p1 in uniform(0,1,10)", "repeatedtask_uniform");
}
END_TEST

START_TEST (repeatedtask_uniform_stoch)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform_stochastic(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = repeat task1 for X in uniform(0,1,10)", "repeatedtask_uniform_stoch");
}
END_TEST

START_TEST (repeatedtask_uniform_plus_assignment)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform_stochastic(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = repeat task1 for X in uniform(0,1,10), mod1.p1 = 12", "repeatedtask_uniform_plus_assignment");
}
END_TEST

START_TEST (repeatedtask_two_uniform)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform_stochastic(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = repeat task1 for X in uniform(0,1,10), mod1.p1 in uniform(3,18,10)", "repeatedtask_two_uniform");
}
END_TEST

START_TEST (repeatedtask_vector)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = repeat task1 for p1 in [0,1,5,100]", "repeatedtask_vector");
}
END_TEST

START_TEST (repeatedtask_alltypes)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = repeat task1 for p1 in [0,1,5,100], S1 in uniform(0,10,100), S2 in logUniform(0,100,5), C1 = 2", "repeatedtask_alltypes");
}
END_TEST

START_TEST (repeatedtask_alltypes2)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = repeat task1 for p1 in [0,1,5,100], S1 in uniform(0,10,100), S2 in logUniform(0,100,5), C1 = S1+2", "repeatedtask_alltypes2");
}
END_TEST


Suite *
create_suite_Tasks (void)
{
  Suite *suite = suite_create("phraSED-ML Tasks");
  TCase *tcase = tcase_create("phraSED-ML Tasks");

  tcase_add_test( tcase, repeatedtask_alltypes2);

  tcase_add_test( tcase, task);
  tcase_add_test( tcase, repeatedtask_uniform);
  tcase_add_test( tcase, repeatedtask_uniform_stoch);
  tcase_add_test( tcase, repeatedtask_uniform_plus_assignment);
  tcase_add_test( tcase, repeatedtask_two_uniform);
  tcase_add_test( tcase, repeatedtask_vector);
  tcase_add_test( tcase, repeatedtask_alltypes);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


