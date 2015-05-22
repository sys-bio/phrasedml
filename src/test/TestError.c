/**
 * \file    TestErrors.c
 * \brief   Test parsing errors in phraSEDML's constructs.
 * \author  Lucian Smith
 * ---------------------------------------------------------------------- -->*/

#include "libutil.h"
#include "phrasedml_api.h"

#include <string>
#include <check.h>
#include <iostream>

using namespace std;

BEGIN_C_DECLS

extern char *TestDataDirectory;

void testError(const string& base, const string& err)
{
  char* sedgen = convertString(base.c_str());
  fail_unless(sedgen == NULL);
  char* errgen = getLastError();
  fail_unless(err == errgen);

  free(errgen);
}

START_TEST (test_model_err1)
{
  testError("sbml_model = mod \"sbml_model.xml\"", "Unable to parse line 1 ('sbml_model = mod \"sbml_model.xml\"'): the only type of phraSED-ML content that fits the syntax '[ID] = [keyword] \"[string]\"' is model definitions, where 'keyword' is the word 'model' (i.e. 'mod1 = model \"file.xml\"').");
}
END_TEST


START_TEST (test_model_err2)
{
  testError("sbml.model = model \"sbml_model.xml\"", "Unable to parse line 1: the phraSED-ML ID 'sbml.model' in this context may not be a sub-id of another variable.");
}
END_TEST


START_TEST (test_model_err3)
{
  testError("0sbml_model = model \"sbml_model.xml\"", "syntax error, unexpected number");
}
END_TEST


START_TEST (test_model_changeerr1)
{
  testError("sbml_model = model \"sbml_model.xml\" and S1=3", "Unable to parse line 1 ('sbml_model = model \"sbml_model.xml\" and [...]'): the only type of phraSED-ML content that fits the syntax '[ID] = [keyword] \"[string]\" [keyword] [...]' is model definitions, where 'keyword' is the word 'with' (i.e. 'mod1 = model \"file.xml\" with S1=3').");
}
END_TEST


START_TEST (test_model_changeerr2)
{
  testError("sbml_model = model \"sbml_model.xml\" with S1.S1=3", "No such id in SBML document: 'S1.S1'.");
}
END_TEST


START_TEST (test_model_noimp1)
{
  testError("sbml_model = model \"sbml_model.xml\" with remove S1", "Unable to parse line 1 at 'remove S1': changes to models of the form '[keyword] [id]' (such as 'remove S1') are not currently supported.  Future plans include incorporation of this functionality.");
}
END_TEST


START_TEST (test_model_noimp2)
{
  testError("sbml_model = model \"sbml_model.xml\" with add parameter S1=1", "Unable to parse line 0 at 'add parameterS1 = 1': changes to models of the form '[keyword] [keyword] [id] = [value]' (such as 'add parameter p1 = 3') are not currently supported.  Future plans include incorporation of this functionality.");
}
END_TEST


START_TEST (test_model_noimp3)
{
  testError("sbml_model = model \"sbml_model.xml\" with change S1 to S2=3", "Unable to parse line 0 at 'change S1toS2 = 3': changes to models of the form '[keyword] [id] [keyword] [id] = [value]' (such as 'change p1 to p3 = 5') are not currently supported.  Future plans include incorporation of this functionality.");
}
END_TEST


START_TEST (test_model_noimp4)
{
  testError("sbml_model = model \"sbml_model.xml\" with compute S1=k1/k2", "Unable to parse line 1 at 'compute S1 = k1 / k2': changes to models of the form '[keyword] [id] = [formula]' (such as 'compute S1 = k1/k2') are not currently supported.  Future plans include incorporation of this functionality.");
}
END_TEST


START_TEST (test_sim_uniform_noargs)
{
  testError("sim1 = simulate uniform", "Unable to parse line 1 ('sim1 = simulate uniform'): uniform and oneStep simulations must be defined with arguments to determine their properties, (i.e. 'sim1 = simulate uniform(0,10,100)' or 'sim2 = simulate oneStep(0.5)').");
}
END_TEST


START_TEST (test_sim_onestep_noargs)
{
  testError("sim1 = simulate onestep", "Unable to parse line 1 ('sim1 = simulate onestep'): uniform and oneStep simulations must be defined with arguments to determine their properties, (i.e. 'sim1 = simulate uniform(0,10,100)' or 'sim2 = simulate oneStep(0.5)').");
}
END_TEST


START_TEST (test_sim_onestep_negarg)
{
  testError("sim1 = simulate onestep(-3.2)", "The step size for a one-step simulation must be positive.  The step size for simulation 'sim1' is '-3.2', which is too small.");
}
END_TEST


START_TEST (test_sim_onestep_0args)
{
  testError("sim1 = simulate onestep()", "Unable to parse line 1 ('sim1 = simulate onestep()'): onestep simulations must take exactly one argument.");
}
END_TEST


START_TEST (test_sim_onestep_2args)
{
  testError("sim1 = simulate onestep(2, 8)", "Unable to parse line 1 ('sim1 = simulate onestep(2, 8)'): onestep simulations must take exactly one argument.");
}
END_TEST


START_TEST (test_sim_onestep_5args)
{
  testError("sim1 = simulate onestep(0, 5.5, 3e-10, 2, 0.00001)", "Unable to parse line 1 ('sim1 = simulate onestep(0, 5.5, 3e-010, 2, 1e-005)'): onestep simulations must take exactly one argument.");
}
END_TEST

START_TEST (test_sim_uniform_0args)
{
  testError("sim1 = simulate uniform()", "Unable to parse line 1 ('sim1 = simulate uniform()'): uniform timecourse simulations must have either three arguments (start, stop, steps) or four (simulation_start, output_start, stop, steps).");
}
END_TEST


START_TEST (test_sim_uniform_2args)
{
  testError("sim1 = simulate uniform(2, -2)", "Unable to parse line 1 ('sim1 = simulate uniform(2, -2)'): uniform timecourse simulations must have either three arguments (start, stop, steps) or four (simulation_start, output_start, stop, steps).");
}
END_TEST


START_TEST (test_sim_uniform_6args)
{
  testError("sim1 = simulate uniform(-5, 8, 2.2, 9, 27.27, 82.0005)", "Unable to parse line 1 ('sim1 = simulate uniform(-5, 8, 2.2, 9, 27.27, 82.0005)'): uniform timecourse simulations must have either three arguments (start, stop, steps) or four (simulation_start, output_start, stop, steps).");
}
END_TEST


START_TEST (test_sim_uniform_negstart)
{
  testError("sim1 = simulate uniform(-5, 8, 20)", "The start time for a uniform time course simulation must be zero or greater.  The start time for simulation 'sim1' is '-5', which is negative.");
}
END_TEST


START_TEST (test_sim_uniform_lower_outstart)
{
  testError("sim1 = simulate uniform(5, 2, 10, 200)", "The output start time for a uniform time course simulation must be greater than or equal to the start time for the simulation.  The output start time for simulation 'sim1' is '2', which is lower than '5', the simulation start.");
}
END_TEST


START_TEST (test_sim_uniform_lower_outstart2)
{
  testError("sim1 = simulate uniform(0, -2, 10, 200)", "The output start time for a uniform time course simulation must be greater than or equal to the start time for the simulation.  The output start time for simulation 'sim1' is '-2', which is lower than '0', the simulation start.");
}
END_TEST


START_TEST (test_sim_uniform_lower_end)
{
  testError("sim1 = simulate uniform(5, 2, 200)", "The end time for a uniform time course simulation must be greater than or equal to the start time (and output start time) for the simulation.  The end time for simulation 'sim1' is '2', which is less than '5'.");
}
END_TEST


START_TEST (test_sim_uniform_lower_end2)
{
  testError("sim1 = simulate uniform(0, -2, 200)", "The end time for a uniform time course simulation must be greater than or equal to the start time (and output start time) for the simulation.  The end time for simulation 'sim1' is '-2', which is less than '0'.");
}
END_TEST


START_TEST (test_sim_uniform_lower_end3)
{
  testError("sim1 = simulate uniform(5, 10, 2, 200)", "The end time for a uniform time course simulation must be greater than or equal to the start time (and output start time) for the simulation.  The end time for simulation 'sim1' is '2', which is less than '10'.");
}
END_TEST


START_TEST (test_sim_uniform_lower_end4)
{
  testError("sim1 = simulate uniform(0, 3, 2, 200)", "The end time for a uniform time course simulation must be greater than or equal to the start time (and output start time) for the simulation.  The end time for simulation 'sim1' is '2', which is less than '3'.");
}
END_TEST


START_TEST (test_sim_uniform_negsteps)
{
  testError("sim1 = simulate uniform(5, 8, -200)", "The number of points for a uniform time course simulation must be positive.  The number of points for simulation 'sim1' is '-200', which is negative.");
}
END_TEST


START_TEST (test_sim_uniform_negsteps2)
{
  testError("sim1 = simulate uniform(5, 6, 8, -200)", "The number of points for a uniform time course simulation must be positive.  The number of points for simulation 'sim1' is '-200', which is negative.");
}
END_TEST



Suite *
create_suite_Errors (void)
{
  Suite *suite = suite_create("PhraSED-ML Errors");
  TCase *tcase = tcase_create("PhraSED-ML Errors");

  tcase_add_test( tcase, test_sim_uniform_negsteps);
  tcase_add_test( tcase, test_sim_uniform_negsteps2);

  tcase_add_test( tcase, test_model_err1);
  tcase_add_test( tcase, test_model_err2);
  tcase_add_test( tcase, test_model_err3);
  tcase_add_test( tcase, test_model_changeerr1);
  tcase_add_test( tcase, test_model_changeerr2);
  tcase_add_test( tcase, test_model_noimp1);
  tcase_add_test( tcase, test_model_noimp2);
  tcase_add_test( tcase, test_model_noimp3);
  tcase_add_test( tcase, test_model_noimp4);
  tcase_add_test( tcase, test_sim_uniform_noargs);
  tcase_add_test( tcase, test_sim_onestep_noargs);
  tcase_add_test( tcase, test_sim_onestep_negarg);
  tcase_add_test( tcase, test_sim_onestep_0args);
  tcase_add_test( tcase, test_sim_onestep_2args);
  tcase_add_test( tcase, test_sim_onestep_5args);
  tcase_add_test( tcase, test_sim_uniform_0args);
  tcase_add_test( tcase, test_sim_uniform_2args);
  tcase_add_test( tcase, test_sim_uniform_6args);
  tcase_add_test( tcase, test_sim_uniform_negstart);
  tcase_add_test( tcase, test_sim_uniform_lower_outstart);
  tcase_add_test( tcase, test_sim_uniform_lower_outstart2);
  tcase_add_test( tcase, test_sim_uniform_lower_end);
  tcase_add_test( tcase, test_sim_uniform_lower_end2);
  tcase_add_test( tcase, test_sim_uniform_lower_end3);
  tcase_add_test( tcase, test_sim_uniform_lower_end4);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


