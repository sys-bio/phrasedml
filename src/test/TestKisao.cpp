/**
 * \file    TestKisao.c
 * \brief   Test phraSEDML constructs.
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

START_TEST (test_steadystate_kisao_num)
{
  compareStringAndFileTranslation("sim1 = simulate steadystate\nsim1.algorithm = kisao.407", "steadystate_kisao407");
}
END_TEST

START_TEST (test_steadystate_kisao_val)
{
  compareStringAndFileTranslation("sim1 = simulate steadystate\nsim1.algorithm = steadystate", "steadystate_kisaotxt");
}
END_TEST

START_TEST (test_uniform_kisao_num)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm = kisao.435", "uniform_kisao435");
}
END_TEST

START_TEST (test_uniform_kisao_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm = rk45", "uniform_kisaotxt");
}
END_TEST

START_TEST (test_uniform_stochastic_kisao_num)
{
  compareStringAndFileTranslation("sim1 = simulate uniform_stochastic(0,10,100)\nsim1.algorithm = kisao.241", "uniform_stochastic_kisao241");
}
END_TEST

START_TEST (test_uniform_stochastic_kisao_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform_stochastic(0,10,100)\nsim1.algorithm = gillespie", "uniform_stochastic_kisaotxt");
}
END_TEST

START_TEST (test_onestep_kisao_num)
{
  compareStringAndFileTranslation("sim1 = simulate onestep(0.7)\nsim1.algorithm = kisao.241", "onestep_kisao241");
}
END_TEST

START_TEST (test_onestep_kisao_val)
{
  compareStringAndFileTranslation("sim1 = simulate onestep(0.7)\nsim1.algorithm = gillespie", "onestep_kisaotxt");
}
END_TEST

START_TEST (test_uniform_makestochastic)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm = gillespie", "uniform_makestochastic");
}
END_TEST

START_TEST (test_uniform_makedeterministic)
{
  compareStringAndFileTranslation("sim1 = simulate uniform_stochastic(0,10,100)\nsim1.algorithm = CVODE", "uniform_makedeterministic");
}
END_TEST

START_TEST (test_uniform_stiff)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm = stiff", "uniform_stiff");
}
END_TEST

START_TEST (test_uniform_nonstiff)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm = nonstiff", "uniform_nonstiff");
}
END_TEST

START_TEST (test_algparm_reltol_txt)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.relative_tolerance = 0.04", "algparm_reltol_txt");
}
END_TEST

START_TEST (test_algparm_reltol_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.209 = 0.04", "algparm_reltol_val");
}
END_TEST

START_TEST (test_algparm_abstol_txt)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.absolute_tolerance = 0.04", "algparm_abstol_txt");
}
END_TEST

START_TEST (test_algparm_abstol_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.211 = 0.04", "algparm_abstol_val");
}
END_TEST

START_TEST (test_algparm_max_numsteps_txt)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.maximum_num_steps = 40", "algparm_max_numsteps_txt");
}
END_TEST

START_TEST (test_algparm_max_numsteps_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.415 = 40", "algparm_max_numsteps_val");
}
END_TEST

START_TEST (test_algparm_max_timestep_txt)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.maximum_time_step = 3.3", "algparm_max_timestep_txt");
}
END_TEST

START_TEST (test_algparm_max_timestep_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.467 = 3.3", "algparm_max_timestep_val");
}
END_TEST

START_TEST (test_algparm_initial_timestep_txt)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.initial_time_step = 3.3", "algparm_initial_timestep_txt");
}
END_TEST

START_TEST (test_algparm_initial_timestep_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.332 = 3.3", "algparm_initial_timestep_val");
}
END_TEST

START_TEST (test_algparm_var_stepsize_txt)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.variable_step_size = true", "algparm_var_stepsize_txt");
}
END_TEST

START_TEST (test_algparm_var_stepsize_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.107 = true", "algparm_var_stepsize_val");
}
END_TEST

START_TEST (test_uniform_kisao_nokeyword)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm = kisao.379", "uniform_kisao_nokeyword");
}
END_TEST

START_TEST (test_algparm_kisao_nokeyword)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.479 = 99.201", "algparm_kisao_nokeyword");
}
END_TEST

START_TEST (test_algparm_max_adams_order_txt)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.maximum_adams_order = 8", "algparm_max_adams_order_txt");
}
END_TEST

START_TEST (test_algparm_max_adams_order_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.219 = 8", "algparm_max_adams_order_val");
}
END_TEST

START_TEST (test_algparm_max_bdf_order_txt)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.maximum_bdf_order = 8", "algparm_max_bdf_order_txt");
}
END_TEST

START_TEST (test_algparm_max_bdf_order_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.220 = 8", "algparm_max_bdf_order_val");
}
END_TEST

START_TEST (test_algparm_min_timestep_txt)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.minimum_time_step = 3.3", "algparm_min_timestep_txt");
}
END_TEST

START_TEST (test_algparm_min_timestep_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.485 = 3.3", "algparm_min_timestep_val");
}
END_TEST

START_TEST (test_algparm_max_iterations_txt)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.maximum_iterations = 800", "algparm_max_iterations_txt");
}
END_TEST

START_TEST (test_algparm_max_iterations_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.486 = 800", "algparm_max_iterations_val");
}
END_TEST

START_TEST (test_algparm_min_damping_txt)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.minimum_damping = 3.3", "algparm_min_damping_txt");
}
END_TEST

START_TEST (test_algparm_min_damping_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.487 = 3.3", "algparm_min_damping_val");
}
END_TEST

START_TEST (test_algparm_seed_txt)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.seed = 1001", "algparm_seed_txt");
}
END_TEST

START_TEST (test_algparm_seed_val)
{
  compareStringAndFileTranslation("sim1 = simulate uniform(0,10,100)\nsim1.algorithm.488 = 1001", "algparm_seed_val");
}
END_TEST



Suite *
create_suite_Kisao (void)
{
  Suite *suite = suite_create("phraSED-ML Kisao terms");
  TCase *tcase = tcase_create("phraSED-ML Kisao terms");

  tcase_add_test( tcase, test_algparm_min_damping_txt);

  tcase_add_test( tcase, test_steadystate_kisao_num);
  tcase_add_test( tcase, test_steadystate_kisao_val);
  tcase_add_test( tcase, test_uniform_kisao_num);
  tcase_add_test( tcase, test_uniform_kisao_val);
  tcase_add_test( tcase, test_uniform_stochastic_kisao_num);
  tcase_add_test( tcase, test_uniform_stochastic_kisao_val);
  tcase_add_test( tcase, test_onestep_kisao_num);
  tcase_add_test( tcase, test_onestep_kisao_val);
  tcase_add_test( tcase, test_uniform_makestochastic);
  tcase_add_test( tcase, test_uniform_makedeterministic);
  tcase_add_test( tcase, test_uniform_stiff);
  tcase_add_test( tcase, test_uniform_nonstiff);
  tcase_add_test( tcase, test_algparm_reltol_val);
  tcase_add_test( tcase, test_algparm_reltol_txt);
  tcase_add_test( tcase, test_algparm_abstol_val);
  tcase_add_test( tcase, test_algparm_abstol_txt);
  tcase_add_test( tcase, test_algparm_max_numsteps_val);
  tcase_add_test( tcase, test_algparm_max_numsteps_txt);
  tcase_add_test( tcase, test_algparm_max_timestep_val);
  tcase_add_test( tcase, test_algparm_max_timestep_txt);
  tcase_add_test( tcase, test_algparm_initial_timestep_val);
  tcase_add_test( tcase, test_algparm_initial_timestep_txt);
  tcase_add_test( tcase, test_algparm_var_stepsize_val);
  tcase_add_test( tcase, test_algparm_var_stepsize_txt);
  tcase_add_test( tcase, test_uniform_kisao_nokeyword);
  tcase_add_test( tcase, test_algparm_kisao_nokeyword);
  tcase_add_test( tcase, test_algparm_max_adams_order_txt);
  tcase_add_test( tcase, test_algparm_max_adams_order_val);
  tcase_add_test( tcase, test_algparm_max_bdf_order_txt);
  tcase_add_test( tcase, test_algparm_max_bdf_order_val);
  tcase_add_test( tcase, test_algparm_min_timestep_txt);
  tcase_add_test( tcase, test_algparm_min_timestep_val);
  tcase_add_test( tcase, test_algparm_max_iterations_txt);
  tcase_add_test( tcase, test_algparm_max_iterations_val);
  tcase_add_test( tcase, test_algparm_min_damping_txt);
  tcase_add_test( tcase, test_algparm_min_damping_val);
  tcase_add_test( tcase, test_algparm_seed_txt);
  tcase_add_test( tcase, test_algparm_seed_val);

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS


