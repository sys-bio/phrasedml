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
PHRASEDML_CPP_NAMESPACE_USE

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


START_TEST (test_add_dot_xml)
{
  SBMLDocument doc(3,1);
  Model* model = doc.createModel();
  Parameter* param = model->createParameter();
  param->setId("p1");
  param->setConstant(true);
  param->setValue(3);
  model->setId("memory_model");

  char* docstr = writeSBMLToString(&doc);
  setReferencedSBML("memory_model", docstr);
  string phrasedml = "sbml_model = model \"memory_model\"";
  string sedml = "saved_model_basic.xml";
  setWorkingDirectory(TestDataDirectory);
  char* sed_gen = convertString(phrasedml.c_str());
  addDotXMLToModelSources();
  free(sed_gen);
  sed_gen = getLastSEDML();
  if (sed_gen==NULL) {
    cout << getLastPhrasedError() << endl << endl;
    fail_unless(false);
    return;
  }
  char* phrased_rt = getLastPhraSEDML();

  string dir(TestDataDirectory);
  string sedfile = dir + sedml;
  char* phrased_gen = convertFile(sedfile.c_str());
  if (phrased_gen==NULL) {
    cout << getLastPhrasedError() << endl << endl;
    fail_unless(false);
    return;
  }
  char* sed_rt = getLastSEDML();

  fail_unless((string)phrased_rt == (string)phrased_gen);
  fail_unless((string)sed_rt     == (string)sed_gen);
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
  tcase_add_test( tcase, test_add_dot_xml);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


