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
  setWorkingDirectory(TestDataDirectory);
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
  testError("0sbml_model = model \"sbml_model.xml\"", "Error in line 1: syntax error, unexpected number");
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


START_TEST (test_sim_uniform_stochastic_noargs)
{
  testError("sim1 = simulate uniform_stochastic", "Unable to parse line 1 ('sim1 = simulate uniform_stochastic'): uniform and oneStep simulations must be defined with arguments to determine their properties, (i.e. 'sim1 = simulate uniform(0,10,100)' or 'sim2 = simulate oneStep(0.5)').");
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


START_TEST (test_sim_uniform_stochastic_0args)
{
  testError("sim1 = simulate uniform_stochastic()", "Unable to parse line 1 ('sim1 = simulate uniform_stochastic()'): uniform timecourse simulations must have either three arguments (start, stop, steps) or four (simulation_start, output_start, stop, steps).");
}
END_TEST


START_TEST (test_sim_uniform_stochastic_2args)
{
  testError("sim1 = simulate uniform_stochastic(2, -2)", "Unable to parse line 1 ('sim1 = simulate uniform_stochastic(2, -2)'): uniform timecourse simulations must have either three arguments (start, stop, steps) or four (simulation_start, output_start, stop, steps).");
}
END_TEST


START_TEST (test_sim_uniform_stochastic_6args)
{
  testError("sim1 = simulate uniform_stochastic(-5, 8, 2.2, 9, 27.27, 82.0005)", "Unable to parse line 1 ('sim1 = simulate uniform_stochastic(-5, 8, 2.2, 9, 27.27, 82.0005)'): uniform timecourse simulations must have either three arguments (start, stop, steps) or four (simulation_start, output_start, stop, steps).");
}
END_TEST


START_TEST (test_sim_uniform_stochastic_negstart)
{
  testError("sim1 = simulate uniform_stochastic(-5, 8, 20)", "The start time for a uniform time course simulation must be zero or greater.  The start time for simulation 'sim1' is '-5', which is negative.");
}
END_TEST


START_TEST (test_sim_uniform_stochastic_lower_outstart)
{
  testError("sim1 = simulate uniform_stochastic(5, 2, 10, 200)", "The output start time for a uniform time course simulation must be greater than or equal to the start time for the simulation.  The output start time for simulation 'sim1' is '2', which is lower than '5', the simulation start.");
}
END_TEST


START_TEST (test_sim_uniform_stochastic_lower_outstart2)
{
  testError("sim1 = simulate uniform_stochastic(0, -2, 10, 200)", "The output start time for a uniform time course simulation must be greater than or equal to the start time for the simulation.  The output start time for simulation 'sim1' is '-2', which is lower than '0', the simulation start.");
}
END_TEST


START_TEST (test_sim_uniform_stochastic_lower_end)
{
  testError("sim1 = simulate uniform_stochastic(5, 2, 200)", "The end time for a uniform time course simulation must be greater than or equal to the start time (and output start time) for the simulation.  The end time for simulation 'sim1' is '2', which is less than '5'.");
}
END_TEST


START_TEST (test_sim_uniform_stochastic_lower_end2)
{
  testError("sim1 = simulate uniform_stochastic(0, -2, 200)", "The end time for a uniform time course simulation must be greater than or equal to the start time (and output start time) for the simulation.  The end time for simulation 'sim1' is '-2', which is less than '0'.");
}
END_TEST


START_TEST (test_sim_uniform_stochastic_lower_end3)
{
  testError("sim1 = simulate uniform_stochastic(5, 10, 2, 200)", "The end time for a uniform time course simulation must be greater than or equal to the start time (and output start time) for the simulation.  The end time for simulation 'sim1' is '2', which is less than '10'.");
}
END_TEST


START_TEST (test_sim_uniform_stochastic_lower_end4)
{
  testError("sim1 = simulate uniform_stochastic(0, 3, 2, 200)", "The end time for a uniform time course simulation must be greater than or equal to the start time (and output start time) for the simulation.  The end time for simulation 'sim1' is '2', which is less than '3'.");
}
END_TEST


START_TEST (test_sim_uniform_stochastic_negsteps)
{
  testError("sim1 = simulate uniform_stochastic(5, 8, -200)", "The number of points for a uniform time course simulation must be positive.  The number of points for simulation 'sim1' is '-200', which is negative.");
}
END_TEST


START_TEST (test_sim_uniform_stochastic_negsteps2)
{
  testError("sim1 = simulate uniform_stochastic(5, 6, 8, -200)", "The number of points for a uniform time course simulation must be positive.  The number of points for simulation 'sim1' is '-200', which is negative.");
}
END_TEST


START_TEST (test_nameerr)
{
  testError("sim1 isnt \"The name of this sim\"", "Unable to parse line 1 ('sim1 isnt \"The name of this sim\"'): the only type of phraSED-ML content that fits the syntax '[ID] [keyword] \"[string]\"' is setting the names of elements, where 'keyword' is the word 'is' (i.e. 'mod1 is \"Biomodels file #322\"').");
}
END_TEST


START_TEST (test_task_no_on)
{
  testError("task1 = run foo bar baz", "Unable to parse line 1 ('task1 = run foo bar baz'): the only type of phraSED-ML content that fits the syntax '[ID] = run [string] [keyword] [string]' is task definitions, where 'keyword' is the word 'on' (i.e. 'task1 = run sim1 on mod0').");
}
END_TEST


START_TEST (test_repeated_task_no_repeat)
{
  testError("task1 = repeated task1 for J2 in uniform(0,1,10)", "Unable to parse line 1 ('task1 = repeated task1 for [...]'): unsupported keyword 'repeated'.  Try 'model' or 'repeat' in this context.");
}
END_TEST


START_TEST (test_repeated_task_no_for)
{
  testError("task1 = repeat task1 fore J2 in uniform(0,1,10)", "Unable to parse line 1 ('task1 = repeat task1 fore [...]'): the only type of phraSED-ML content that fits the syntax '[ID] = repeat [string] [keyword] [...]' is repeated tasks, where 'keyword' is the word 'for' (i.e. 'rt1 = repeat task1 for S1 in uniform(0,10,100)').");
}
END_TEST


START_TEST (test_repeated_task_no_in)
{
  testError("task1 = repeat task1 for J2 een uniform(0,1,10)", "Unable to parse line 1 at 'J2 een uniform(0, 1, 10)': Changes of the form '[string] [keyword] [function()]' are only valid when [keyword] is 'in'.");
}
END_TEST


START_TEST (test_repeated_task_unknown_function)
{
  testError("task1 = repeat task1 for J2 in funkyUniform(0,1,10)", "Unable to parse line 1 at 'J2 in funkyUniform(0, 1, 10)': Unrecognized function name 'funkyUniform'.  Known function names for changes in this format are 'uniform' and 'logUniform'.");
}
END_TEST


START_TEST (test_repeated_task_unknown_name)
{
  testError("task1 = repeat task1 for none.X in uniform(0,1,10)", "Unable to parse line 1 at 'none.X in uniform(0, 1, 10)': Unrecognized function name 'funkyUniform'.  Known function names for changes in this format are 'uniform' and 'logUniform'.");
}
END_TEST


START_TEST (test_repeated_task_no_loop)
{
  testError("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = repeat task1 for p1 = 12", "Error in repeatedTask 'task2':  no loop found.  Repeated tasks must be repeated over some loop, such as 'x in uniform(0,10,100)' or 'x in [0, 3, 4, 10]'.");
}
END_TEST


START_TEST (test_repeated_unknown_task)
{
  testError("task1 = repeat task2 for p1 in [3]", "Error in repeatedTask 'task1':  no such referenced task 'task2'.");
}
END_TEST


START_TEST (test_repeated_unknown_multitasks)
{
  testError("task1 = repeat [task2, task3] for p1 in [3]", "Error in repeatedTask 'task1':  no such referenced task 'task2'.");
}
END_TEST


START_TEST (test_repeated_unknown_multitasks2)
{
  testError("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = repeat [task1, task3] for p1 in [12]", "Error in repeatedTask 'task2':  no such referenced task 'task3'.");
}
END_TEST


START_TEST (test_repeated_task_recursive)
{
  testError("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = repeat task2 for p1 in [3]\ntask2 = repeat task1 for p1 in [12]", "Error in repeatedTask 'task1':  this task, or a task it references, is recursive, which is not allowed.");
}
END_TEST


START_TEST (test_repeated_task_recursive2)
{
  testError("task1 = repeat task1 for p1 in [3]", "Error in repeatedTask 'task1':  this task, or a task it references, is recursive, which is not allowed.");
}
END_TEST


START_TEST (test_repeated_task_recursive3)
{
  testError("task1 = repeat task2 for p1 in [3]\ntask2 = repeat task3 for p1 in [4]\ntask3 = repeat task3 for p1 in [5]\n", "Error in repeatedTask 'task1':  this task, or a task it references, is recursive, which is not allowed.");
}
END_TEST


START_TEST (test_repeated_task_duplicate_assignments)
{
  testError("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = repeat task1 for p1 in uniform(0,1,10), p1 = 12", "Error in repeatedTask 'task2':  the variable 'mod1.p1' is defined multiple times.");
}
END_TEST


START_TEST (test_repeated_task_duplicate_assignments2)
{
  testError("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = repeat task1 for p1 in uniform(0,1,10), mod1.p1 = 12", "Error in repeatedTask 'task2':  the variable 'mod1.p1' is defined multiple times.");
}
END_TEST


START_TEST (test_plot_wrongkey)
{
  testError("ploot S1 vs S2", "Unable to parse line 1 ('ploot S1 vs S2'): lines of this type are only valid if the first word is 'plot' or 'report', such as 'plot task1.time vs task1.S1' or 'report task1.time, task1.S1, task1.S2'.");
}
END_TEST


START_TEST (test_plot_plot4d)
{
  testError("plot S1 vs S2 vs S3 vs S4", "Unable to parse line 1 ('plot S1 vs S2 vs S3 vs S4'): can only create plots of two or three dimensions.  Use 'report' instead of 'plot' to output four-dimensional or higher data.");
}
END_TEST


START_TEST (test_plot_plot1d)
{
  testError("plot S1", "Unable to parse line 1 ('plot S1'): can only create plots of two or three dimensions, not one.  Use 'report' instead of 'plot' to output one-dimensional data, or use 'vs' to distinguish axes in 2D or 3D data ('plot S1 vs S2').");
}
END_TEST


START_TEST (test_plot_invalid_math)
{
  testError("plot S1++ vs S2", "Unable to parse line 1 ('plot S1 + + vs S2'): unable to parse the formula 'S1 + +' as a valid mathematical expression.");
}
END_TEST


START_TEST (test_plot_2d_and_3d)
{
  testError("plot S1 vs S2, S3 vs S4 vs S6", "Unable to parse line 1 ('plot S1 vs S2, S3 vs S4 vs S6'): unable to create a single plot with both 2d and 3d data.  Create these plots separately, or adjust the dimensionality of the data.");
}
END_TEST


START_TEST (test_report_invalid_math)
{
  testError("report S1++, S2", "Unable to parse line 1 ('report S1 + +, S2'): unable to parse the formula 'S1 + +' as a valid mathematical expression.");
}
END_TEST


START_TEST (test_plot_novar_1d)
{
  testError("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nplot p1 vs nothing", "Error:  an output plot or report references variable 'nothing' which cannot be found in task 'task1's model 'mod1'.");
}
END_TEST


START_TEST (test_plot_novar_2d)
{
  testError("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nplot p1 vs task1.nothing", "Error:  an output plot or report references variable 'task1.nothing' which cannot be found in task 'task1's model 'mod1'.");
}
END_TEST


START_TEST (test_plot_novar_2dv2)
{
  testError("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nplot p1 vs mod1.nothing", "Error:  an output plot or report references variable 'mod1.nothing' which cannot be found in task 'task1's model 'mod1'.");
}
END_TEST


START_TEST (test_plot_novar_3d)
{
  testError("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nplot p1 vs task1.mod1.nothing", "Error:  an output plot or report references variable 'task1.mod1.nothing' which cannot be found in task 'task1's model 'mod1'.");
}
END_TEST


START_TEST (test_plot_nomod_2d)
{
  testError("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nplot p1 vs mod2.nothing", "Error:  an output plot or report references variable 'mod2.nothing' which cannot be found in task 'task1's model 'mod1'.");
}
END_TEST


START_TEST (test_plot_nomod_3d)
{
  testError("mod1 = model \"sbml_model.xml\"\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\nplot p1 vs task1.mod2.nothing", "Error:  an output plot or report references variable 'task1.mod2.nothing' which cannot be found in task 'task1's model 'mod1'.");
}
END_TEST



START_TEST (test_plot_ambiguous_task)
{
  testError("mod1 = model \"sbml_model.xml\"\nmod2 = model mod1 with S1=3\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = run sim1 on mod2\ntask3 = repeat [task1, task2] for S3 in [0,3]\nplot p1 vs S1", "Error:  an output plot or report references variable 'S1' without referencing a valid task it came from (i.e. 'task1.S1').  This is only legal if there is exactly one defined task, but here, there are 3.");
}
END_TEST


START_TEST (test_plot_ambiguous_model)
{
  testError("mod1 = model \"sbml_model.xml\"\nmod2 = model mod1 with S1=3\nsim1 = simulate uniform(0,10,100)\ntask1 = run sim1 on mod1\ntask2 = run sim1 on mod2\ntask3 = repeat [task1, task2] for S3 in [0,3]\nplot task3.p1 vs task3.S1", "Error:  an output plot or report references variable 'task3.S1' but there is no task subvariable named 'S1', either as a local variable for that task, or as a model variable that can be clearly mapped to a single model.  Variables in plot and report mathematics must be unambiguous, or defined clearly as 'task.model.varname'.");
}
END_TEST


Suite *
create_suite_Errors (void)
{
  Suite *suite = suite_create("PhraSED-ML Errors");
  TCase *tcase = tcase_create("PhraSED-ML Errors");

  tcase_add_test( tcase, test_plot_ambiguous_task);
  tcase_add_test( tcase, test_plot_ambiguous_model);

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
  tcase_add_test( tcase, test_sim_uniform_negsteps);
  tcase_add_test( tcase, test_sim_uniform_stochastic_noargs);
  tcase_add_test( tcase, test_sim_onestep_noargs);
  tcase_add_test( tcase, test_sim_onestep_negarg);
  tcase_add_test( tcase, test_sim_onestep_0args);
  tcase_add_test( tcase, test_sim_onestep_2args);
  tcase_add_test( tcase, test_sim_onestep_5args);
  tcase_add_test( tcase, test_sim_uniform_stochastic_0args);
  tcase_add_test( tcase, test_sim_uniform_stochastic_2args);
  tcase_add_test( tcase, test_sim_uniform_stochastic_6args);
  tcase_add_test( tcase, test_sim_uniform_stochastic_negstart);
  tcase_add_test( tcase, test_sim_uniform_stochastic_lower_outstart);
  tcase_add_test( tcase, test_sim_uniform_stochastic_lower_outstart2);
  tcase_add_test( tcase, test_sim_uniform_stochastic_lower_end);
  tcase_add_test( tcase, test_sim_uniform_stochastic_lower_end2);
  tcase_add_test( tcase, test_sim_uniform_stochastic_lower_end3);
  tcase_add_test( tcase, test_sim_uniform_stochastic_lower_end4);
  tcase_add_test( tcase, test_sim_uniform_stochastic_negsteps);
  tcase_add_test( tcase, test_sim_uniform_stochastic_negsteps2);
  tcase_add_test( tcase, test_sim_uniform_stochastic_negsteps2);
  tcase_add_test( tcase, test_nameerr);
  tcase_add_test( tcase, test_task_no_on);
  tcase_add_test( tcase, test_repeated_task_no_repeat);
  tcase_add_test( tcase, test_repeated_task_no_for);
  tcase_add_test( tcase, test_repeated_task_no_in);
  tcase_add_test( tcase, test_repeated_task_unknown_function);
  tcase_add_test( tcase, test_repeated_task_no_loop);
  tcase_add_test( tcase, test_repeated_unknown_task);
  tcase_add_test( tcase, test_repeated_unknown_multitasks);
  tcase_add_test( tcase, test_repeated_unknown_multitasks2);
  tcase_add_test( tcase, test_repeated_task_recursive);
  tcase_add_test( tcase, test_repeated_task_recursive2);
  tcase_add_test( tcase, test_repeated_task_recursive3);
  tcase_add_test( tcase, test_repeated_task_duplicate_assignments);
  tcase_add_test( tcase, test_repeated_task_duplicate_assignments2);
  tcase_add_test( tcase, test_plot_wrongkey);
  tcase_add_test( tcase, test_plot_plot4d);
  tcase_add_test( tcase, test_plot_plot1d);
  tcase_add_test( tcase, test_plot_invalid_math);
  tcase_add_test( tcase, test_report_invalid_math);
  tcase_add_test( tcase, test_plot_2d_and_3d);
  tcase_add_test( tcase, test_plot_novar_1d);
  tcase_add_test( tcase, test_plot_novar_2d);
  tcase_add_test( tcase, test_plot_novar_2dv2);
  tcase_add_test( tcase, test_plot_novar_3d);
  tcase_add_test( tcase, test_plot_nomod_2d);
  tcase_add_test( tcase, test_plot_nomod_3d);


  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


