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

START_TEST (test_model)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\"", "model1");
}
END_TEST


START_TEST (test_model_name)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_model is \"The SBML Model\"", "model_name");
}
END_TEST

START_TEST (test_model_attchange_spec_conc)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\" with S1=4", "model_attchange_spec_conc");
}
END_TEST


START_TEST (test_model_attchange_spec_amt)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\" with S2=4", "model_attchange_spec_amt");
}
END_TEST


START_TEST (test_model_attchange_comp)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\" with C1=4", "model_attchange_comp");
}
END_TEST


START_TEST (test_model_attchange_param)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\" with p1=4", "model_attchange_param");
}
END_TEST


START_TEST (test_model_attchange_all)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\" with S1=4, S2=5.5, C1=0.0006, p1=-7", "model_attchange_all");
}
END_TEST


START_TEST (test_twomodels1)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_mod2 = model sbml_model", "twomodels1");
}
END_TEST


START_TEST (test_twomodels_attchange_spec_conc)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_mod2 = model sbml_model with S1=5", "twomodels_attchange_spec_conc");
}
END_TEST


START_TEST (test_twomodels_attchange_spec_amt)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_mod2 = model sbml_model with S2=5", "twomodels_attchange_spec_amt");
}
END_TEST


START_TEST (test_twomodels_attchange_comp)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_mod2 = model sbml_model with C1=5", "twomodels_attchange_comp");
}
END_TEST


START_TEST (test_twomodels_attchange_param)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_mod2 = model sbml_model with p1=5", "twomodels_attchange_param");
}
END_TEST


START_TEST (test_twomodels_attchange_all)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_mod2 = model sbml_model with S1=4, S2=5, C1=6, p1=7", "twomodels_attchange_all");
}
END_TEST


START_TEST (test_twomodels_attchange_mixed)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\" with S1=8, S2=-3\nsbml_mod2 = model sbml_model with C1=-6, p1=7", "twomodels_attchange_mixed");
}
END_TEST


START_TEST (test_model_formchange)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\" with C1=4^2", "model_formchange");
}
END_TEST


START_TEST (test_model_formchange_var_assignment)
{
  compareStringAndFileTranslation("sbml_model = model \"sbml_model.xml\" with C1=4^x, x=2", "model_formchange_var_assignment");
}
END_TEST



Suite *
create_suite_Models (void)
{
  Suite *suite = suite_create("phraSED-ML Models");
  TCase *tcase = tcase_create("phraSED-ML Models");

  tcase_add_test( tcase, test_model_formchange_var_assignment);

  tcase_add_test( tcase, test_model);
  tcase_add_test( tcase, test_model_name);
  tcase_add_test( tcase, test_model_attchange_spec_conc);
  tcase_add_test( tcase, test_model_attchange_spec_amt);
  tcase_add_test( tcase, test_model_attchange_comp);
  tcase_add_test( tcase, test_model_attchange_param);
  tcase_add_test( tcase, test_model_attchange_all);
  tcase_add_test( tcase, test_twomodels1);
  tcase_add_test( tcase, test_twomodels_attchange_spec_conc);
  tcase_add_test( tcase, test_twomodels_attchange_spec_amt);
  tcase_add_test( tcase, test_twomodels_attchange_comp);
  tcase_add_test( tcase, test_twomodels_attchange_param);
  tcase_add_test( tcase, test_twomodels_attchange_all);
  tcase_add_test( tcase, test_twomodels_attchange_mixed);
  tcase_add_test( tcase, test_model_formchange);



  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


