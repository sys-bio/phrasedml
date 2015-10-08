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
#include <sbml/SBMLTypes.h>

using namespace std;

BEGIN_C_DECLS

extern char *TestDataDirectory;

START_TEST (test_saved_model_basic)
{
  SBMLDocument doc(3,1);
  Model* model = doc.createModel();
  Parameter* param = model->createParameter();
  param->setId("p1");
  param->setConstant(true);
  param->setValue(3);
  model->setId("memory_model");

  char* docstr = writeSBMLToString(&doc);
  setReferencedSBML("memory_model.xml", docstr);
  compareStringAndFileTranslation("sbml_model = model \"memory_model.xml\"", "saved_model_basic");
  free(docstr);
  
}
END_TEST

START_TEST (test_saved_model_complete)
{
  SBMLDocument doc(3,1);
  Model* model = doc.createModel();
  Parameter* param = model->createParameter();
  param->setId("p1");
  param->setConstant(true);
  param->setValue(3);
  model->setId("memory_model");

  char* docstr = writeSBMLToString(&doc);
  setReferencedSBML("memory_model.xml", docstr);
  compareStringAndFileTranslation("mod1 = model \"memory_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = repeat task1 for p1 in uniform(0,1,10)\nplot task2.time vs task2.p1", "saved_model_complete");
  free(docstr);
}
END_TEST


Suite *
create_suite_Saved_Models (void)
{
  Suite *suite = suite_create("phraSED-ML Models with saved SBML documents");
  TCase *tcase = tcase_create("phraSED-ML Models with saved SBML documents");

  tcase_add_test( tcase, test_saved_model_basic);
  tcase_add_test( tcase, test_saved_model_complete);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


