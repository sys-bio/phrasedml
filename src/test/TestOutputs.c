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

#include "sbml/math/L3Parser.h"
#include "sedml\SedDataGenerator.h"
#include "sedml\SedDocument.h"
#include "output.h"

using namespace std;

BEGIN_C_DECLS

extern char *TestDataDirectory;

START_TEST (plot_basic)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nplot time vs S1", "plot_basic");
}
END_TEST

START_TEST (plot_formula)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nplot time vs S1/C1", "plot_formula");
}
END_TEST

START_TEST (report_basic)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nreport time vs S1", "report_basic");
}
END_TEST

START_TEST (report_formula)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nreport time vs S1/C1", "report_formula");
}
END_TEST

START_TEST (plot3d_basic)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nplot time vs S1 vs S2", "plot3d_basic");
}
END_TEST

START_TEST (plot3d_formula)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nplot time vs S1/C1 vs S2/C1", "plot3d_formula");
}
END_TEST

START_TEST (plot_log_formula)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nplot time vs log(S1/C1)", "plot_log_formula");
}
END_TEST

START_TEST (plot3d_log_formula)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nplot time vs log(S1/C1) vs log(S2)", "plot3d_log_formula");
}
END_TEST

START_TEST (report_log_formula)
{
  compareStringAndFileTranslation("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nreport time vs log(S1/C1) vs log(S2)", "report_log_formula");
}
END_TEST

START_TEST (sedml_bug)
{
  PhrasedOutput::testSedmlBug();
}
END_TEST

Suite *
create_suite_Outputs (void)
{
  Suite *suite = suite_create("phraSED-ML Outputs");
  TCase *tcase = tcase_create("phraSED-ML Outputs");

  //tcase_add_test( tcase, sedml_bug);


  //tcase_add_test( tcase, plot_log_formula);
  //tcase_add_test( tcase, plot3d_log_formula);
  //tcase_add_test( tcase, report_log_formula);

  tcase_add_test( tcase, plot_basic);
  tcase_add_test( tcase, plot_formula);
  tcase_add_test( tcase, report_basic);
  tcase_add_test( tcase, report_formula);
  tcase_add_test( tcase, plot3d_basic);
  tcase_add_test( tcase, plot3d_formula);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


