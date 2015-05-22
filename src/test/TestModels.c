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
  compareFileTranslation("model1");
}
END_TEST

START_TEST (test_model_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\"", "model1.xml");
}
END_TEST


START_TEST (test_model_name)
{
  compareFileTranslation("model_name");
}
END_TEST

START_TEST (test_model_name_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_model is \"The SBML Model\"", "model_name.xml");
}
END_TEST

START_TEST (test_model2)
{
  compareFileTranslation("model2");
}
END_TEST

START_TEST (test_model2_txt)
{
  compareStringTranslation("sbml_model = model \"unknown_model.xml\"", "model2.xml");
}
END_TEST


START_TEST (test_model_attchange_spec_conc_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\" with S1=4", "model_attchange_spec_conc.xml");
}
END_TEST


START_TEST (test_model_attchange_spec_conc)
{
  compareFileTranslation("model_attchange_spec_conc");
}
END_TEST


START_TEST (test_model_attchange_spec_amt_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\" with S2=4", "model_attchange_spec_amt.xml");
}
END_TEST


START_TEST (test_model_attchange_spec_amt)
{
  compareFileTranslation("model_attchange_spec_amt");
}
END_TEST


START_TEST (test_model_attchange_comp_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\" with C1=4", "model_attchange_comp.xml");
}
END_TEST


START_TEST (test_model_attchange_comp)
{
  compareFileTranslation("model_attchange_comp");
}
END_TEST


START_TEST (test_model_attchange_param_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\" with p1=4", "model_attchange_param.xml");
}
END_TEST


START_TEST (test_model_attchange_param)
{
  compareFileTranslation("model_attchange_param");
}
END_TEST


START_TEST (test_model_attchange_all_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\" with S1=4, S2=5.5, C1=0.0006, p1=-7", "model_attchange_all.xml");
}
END_TEST


START_TEST (test_model_attchange_all)
{
  compareFileTranslation("model_attchange_all");
}
END_TEST


START_TEST (test_twomodels1_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_mod2 = model sbml_model", "twomodels1.xml");
}
END_TEST


START_TEST (test_twomodels1)
{
  compareFileTranslation("twomodels1");
}
END_TEST


START_TEST (test_twomodels_attchange_spec_conc_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_mod2 = model sbml_model with S1=5", "twomodels_attchange_spec_conc.xml");
}
END_TEST


START_TEST (test_twomodels_attchange_spec_conc)
{
  compareFileTranslation("twomodels_attchange_spec_conc");
}
END_TEST


START_TEST (test_twomodels_attchange_spec_amt_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_mod2 = model sbml_model with S2=5", "twomodels_attchange_spec_amt.xml");
}
END_TEST


START_TEST (test_twomodels_attchange_spec_amt)
{
  compareFileTranslation("twomodels_attchange_spec_amt");
}
END_TEST


START_TEST (test_twomodels_attchange_comp_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_mod2 = model sbml_model with C1=5", "twomodels_attchange_comp.xml");
}
END_TEST


START_TEST (test_twomodels_attchange_comp)
{
  compareFileTranslation("twomodels_attchange_comp");
}
END_TEST


START_TEST (test_twomodels_attchange_param_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_mod2 = model sbml_model with p1=5", "twomodels_attchange_param.xml");
}
END_TEST


START_TEST (test_twomodels_attchange_param)
{
  compareFileTranslation("twomodels_attchange_param");
}
END_TEST


START_TEST (test_twomodels_attchange_all_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\"\nsbml_mod2 = model sbml_model with S1=4, S2=5, C1=6, p1=7", "twomodels_attchange_all.xml");
}
END_TEST


START_TEST (test_twomodels_attchange_all)
{
  compareFileTranslation("twomodels_attchange_all");
}
END_TEST


START_TEST (test_twomodels_attchange_mixed_txt)
{
  compareStringTranslation("sbml_model = model \"sbml_model.xml\" with S1=8, S2=-3\nsbml_mod2 = model sbml_model with C1=-6, p1=7", "twomodels_attchange_mixed.xml");
}
END_TEST


START_TEST (test_twomodels_attchange_mixed)
{
  compareFileTranslation("twomodels_attchange_mixed");
}
END_TEST




Suite *
create_suite_Models (void)
{
  Suite *suite = suite_create("phraSED-ML Models");
  TCase *tcase = tcase_create("phraSED-ML Models");

  tcase_add_test( tcase, test_twomodels_attchange_mixed);
  tcase_add_test( tcase, test_twomodels_attchange_mixed_txt);

  tcase_add_test( tcase, test_model);
  tcase_add_test( tcase, test_model_txt);
  tcase_add_test( tcase, test_model_name);
  tcase_add_test( tcase, test_model_name_txt);
  tcase_add_test( tcase, test_model2);
  tcase_add_test( tcase, test_model2_txt);
  tcase_add_test( tcase, test_model_attchange_spec_conc_txt);
  tcase_add_test( tcase, test_model_attchange_spec_conc_txt);
  tcase_add_test( tcase, test_model_attchange_spec_amt_txt);
  tcase_add_test( tcase, test_model_attchange_spec_amt_txt);
  tcase_add_test( tcase, test_model_attchange_comp_txt);
  tcase_add_test( tcase, test_model_attchange_comp_txt);
  tcase_add_test( tcase, test_model_attchange_param_txt);
  tcase_add_test( tcase, test_model_attchange_param_txt);
  tcase_add_test( tcase, test_model_attchange_all_txt);
  tcase_add_test( tcase, test_model_attchange_all);
  tcase_add_test( tcase, test_twomodels1);
  tcase_add_test( tcase, test_twomodels1_txt);
  tcase_add_test( tcase, test_twomodels_attchange_spec_conc);
  tcase_add_test( tcase, test_twomodels_attchange_spec_conc_txt);
  tcase_add_test( tcase, test_twomodels_attchange_spec_amt);
  tcase_add_test( tcase, test_twomodels_attchange_spec_amt_txt);
  tcase_add_test( tcase, test_twomodels_attchange_comp);
  tcase_add_test( tcase, test_twomodels_attchange_comp_txt);
  tcase_add_test( tcase, test_twomodels_attchange_param);
  tcase_add_test( tcase, test_twomodels_attchange_param_txt);
  tcase_add_test( tcase, test_twomodels_attchange_all);
  tcase_add_test( tcase, test_twomodels_attchange_all_txt);


  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


