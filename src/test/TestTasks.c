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

START_TEST (task_txt)
{
  compareStringTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate steadystate\ntask1 = run sim1 on mod1", "task.xml");
}
END_TEST

START_TEST (task)
{
  compareFileTranslation("task");
}
END_TEST



Suite *
create_suite_Tasks (void)
{
  Suite *suite = suite_create("phraSED-ML Tasks");
  TCase *tcase = tcase_create("phraSED-ML Tasks");

  tcase_add_test( tcase, task_txt);
  tcase_add_test( tcase, task);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


