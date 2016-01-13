/**
 * @file    generateTestsFrom.cpp
 * @brief   Takes a test case model and generates the translated versions of the model plus the .m file.
 * @author  Lucian Smith
 * 
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <sstream>

#include <sbml\SBMLTypes.h>
#include <sedml\SedDocument.h>
#include <sedml\SedReader.h>
#include <sedml\SedAlgorithm.h>
#include "antimony_api.h"
#include "phrasedml_api.h"
#include "uniform.h"
//#include "testSuiteUtil.h"

using namespace std;
LIBSBML_CPP_NAMESPACE_USE

template <class T>
inline std::string toString (const T& t)
{
  std::stringstream ss;
  ss << t;
  return ss.str();
}

string stringFromIndex(int index)
{
  string ret = "00000";
  string num = toString(index);
  ret.replace(5-num.size(), num.size(), num);

  return ret;
}

void fixFilenames(string& phrasedml, string num)
{
  string f0 = "\"" + num + "-sbml.xml\"";
  string f1 = "\"" + num + "-sbml1.xml\"";
  string f2 = "\"" + num + "-sbml2.xml\"";
  string f3 = "\"" + num + "-sbml3.xml\"";
  size_t fileindex = phrasedml.find("FILE0");
  while (fileindex != string::npos) {
    phrasedml.replace(fileindex, 5, f0);
    fileindex = phrasedml.find("FILE0");
  }
  fileindex = phrasedml.find("FILE1");
  while (fileindex != string::npos) {
    phrasedml.replace(fileindex, 5, f1);
    fileindex = phrasedml.find("FILE1");
  }
  fileindex = phrasedml.find("FILE2");
  while (fileindex != string::npos) {
    phrasedml.replace(fileindex, 5, f2);
    fileindex = phrasedml.find("FILE2");
  }
  fileindex = phrasedml.find("FILE3");
  while (fileindex != string::npos) {
    phrasedml.replace(fileindex, 5, f3);
    fileindex = phrasedml.find("FILE3");
  }
}

string toCellML(const string& sbml)
{
  string cellml = sbml;
  size_t index = cellml.find("-sbml");
  while (index != string::npos) {
    cellml.replace(index, 5, "-cellml");
    index = cellml.find("-sbml");
  }

  index = cellml.find(":language:sbml");
  while (index != string::npos) {
    cellml.replace(index+10, 22, "cellml");
    index = cellml.find(":language:sbml");
  }
  
  index = cellml.find("/sbml:sbml/sbml:model/");
  while (index != string::npos) {
    cellml.replace(index, 21, "/cellml:model/");
    index = cellml.find("/sbml:sbml/sbml:model/");
  }

  return cellml;
}

bool writeFile(string filename, const string& contents)
{
  string oldlocale = setlocale(LC_ALL, NULL);
  setlocale(LC_ALL, "C");
  ofstream ofile(filename);
  if (!ofile.good()) {
    cerr << "Unable to open file '" << filename << "' for writing.";
    return true;
  }
  ofile << contents;
  ofile.close();
  setlocale(LC_ALL, oldlocale.c_str());
  return false;
}

void getTagsAndType(string sed_sbml, set<string>& components, set<string>& tests, set<string>& types)
{
  SedDocument* seddoc = readSedMLFromString(sed_sbml.c_str());
  if (seddoc->getNumModels() > 0) {
    components.insert("Model");
  }
  if (seddoc->getNumDataDescriptions() > 0) {
    components.insert("DataDescription");
  }
  if (seddoc->getNumDataGenerators() > 0) {
    components.insert("DataGenerator");
  }
  for (size_t out=0; out<seddoc->getNumOutputs(); out++) {
    SedOutput* sedout = seddoc->getOutput(out);
    if (sedout->getTypeCode() == SEDML_OUTPUT_REPORT) {
      components.insert("Report");
    }
    else if (sedout->getTypeCode() == SEDML_OUTPUT_PLOT2D) {
      components.insert("Plot2D");
    }
    else if (sedout->getTypeCode() == SEDML_OUTPUT_PLOT3D) {
      components.insert("Plot3D");
    }
    else {
      components.insert("UNKNOWN_OUTPUT_TYPE");
    }
  }
  for (size_t sim=0; sim<seddoc->getNumSimulations(); sim++) {
    SedSimulation* sedsim = seddoc->getSimulation(sim);
    if (sedsim->getTypeCode() == SEDML_SIMULATION_UNIFORMTIMECOURSE) {
      components.insert("UniformTimeCourse");
      if (sedsim->isSetAlgorithm()) {
        const SedAlgorithm* alg = sedsim->getAlgorithm();
        string kisao = alg->getKisaoID();
        if (phrasedml::PhrasedUniform::kisaoIdIsStochastic(kisao)) {
          types.insert("StochasticTimeCourse");
        }
        else {
          types.insert("DeterministicTimeCourse");
        }
      }
    }
    else if (sedsim->getTypeCode() == SEDML_SIMULATION_STEADYSTATE) {
      components.insert("SteadyState");
      types.insert("SteadyState");
    }
    else if (sedsim->getTypeCode() == SEDML_SIMULATION_ONESTEP) {
      components.insert("OneStep");
      types.insert("OneStep");
    }
  }

  if (types.empty()) {
    types.insert("UNKNOWN_TEST_TYPE");
  }
  delete seddoc;
}

string createInfoFile(string blurb, string num, string description, const string& sed_sbml, const vector<string>& sbmlnames, const vector<string>& cellmlnames, vector<string>::iterator antimony, int nummods, const string& phrasedml)
{
  set<string> components, tests, types;
  getTagsAndType(sed_sbml, components, tests, types);
  stringstream info;
  info << "category:      Test" << endl 
       << "synopsis:      " << blurb << endl
       << "sbml:          " << num << "-sedml-sbml.xml" << endl
       << "cellml:        " << num << "-sedml-cellml.xml" << endl
       << "componentTags: ";
  for (set<string>::iterator comp = components.begin(); comp != components.end(); comp++) {
    if (comp != components.begin()) {
      info << ", ";
    }
    info << *comp;
  }
  info << endl << "testTags:      ";
  for (set<string>::iterator test = tests.begin(); test != tests.end(); test++) {
    if (test != tests.begin()) {
      info << ", ";
    }
    info << *test;
  }
  info << endl << "testTypes:     ";
  for (set<string>::iterator type = types.begin(); type != types.end(); type++) {
    if (type != types.begin()) {
      info << ", ";
    }
    info << *type;
  }
  info << endl
       << "description:" << endl << endl << description << endl
       << endl;

  if (types.find("StochasticTimeCourse") != types.end()) {
    info << "NOTE:  This is a stochastic test, so the expected results are not in the same format as the results generated from the 'report' construct:  instead, the expected mean and standard deviation of the results are included.  See cases/stochastic.txt for more detail." << endl << endl;
  }

  info << "Antimony version of the model:" << endl;
  for (int a=0; a<nummods; a++) {
    if (a>0) {
      info << endl;
    }
    info << *antimony;
    antimony++;
  }
  info << endl << endl;
  info << "phraSED-ML version of the SED-ML (for SBML):" << endl
       << phrasedml << endl;

  return info.str();
}

void createTest(int testIndex, vector<string>::iterator antbegin, int nummods, int sedIndex, const vector<string>& phrasedmls, vector<string>& blurbs, vector<string>& descriptions, string directory)
{
  vector<string> sbmlnames, cellmlnames;
  string phrasedml = phrasedmls[sedIndex];
  string blurb = blurbs[sedIndex];
  string description = descriptions[sedIndex];
  string num = stringFromIndex(testIndex);
  directory = directory + "\\" + num + "\\";
  system(("mkdir \"" + directory + "\"").c_str());

  fixFilenames(phrasedml, num);
  vector<string>::iterator antit = antbegin;
  for (int mod=0; mod<nummods; mod++) {
    string antimony = *antit;
    string sbmlfilename = num + "-sbml" + toString(mod+1) + ".xml";
    string cellmlfilename = num + "-cellml" + toString(mod+1) + ".xml";
    if (mod==0 && nummods==1) {
      sbmlfilename = directory + num + "-sbml.xml";
      cellmlfilename = directory + num + "-cellml.xml";
    }
    loadAntimonyString(antimony.c_str());
    writeSBMLFile(sbmlfilename.c_str(), NULL);
    writeCellMLFile(cellmlfilename.c_str(), NULL);

    sbmlnames.push_back(sbmlfilename);
    cellmlnames.push_back(cellmlfilename);

    antit++;
  }
  phrasedml::setWorkingDirectory(directory.c_str());
  char* sed_sbml = phrasedml::convertString(phrasedml.c_str());
  if (sed_sbml==NULL) {
    cerr << "Error converting:" << endl << phrasedml << endl << "Error: " << phrasedml::getLastPhrasedError() << endl;
    return;
  }
  writeFile(directory + num + "-sedml-sbml.xml", sed_sbml);
  string sed_cellml = toCellML(sed_sbml);
  writeFile(directory + num + "-sedml-cellml.xml", sed_cellml);

  string info = createInfoFile(blurb, num, description, sed_sbml, sbmlnames, cellmlnames, antbegin, nummods, phrasedml);
  writeFile(directory + num + "-info.txt", info);
}

void setupModels(vector<string>& models)
{
  models.push_back("  a=3");
  models.push_back("  a=3\n  a'=1");
  models.push_back("  J0: -> a; 1\n  a=3");

}

void setupSEDML(vector<string>& phrasedml, vector<string>& blurbs, vector<string>& descriptions)
{
  phrasedml.push_back("  mod1 = model FILE0\n  sim1 = simulate uniform(0,10,100)\n  task1 = run sim1 on mod1\n  report time vs a\n  plot time vs a");
  blurbs.push_back("Basic report");
  descriptions.push_back("This is as simple a SED-ML file as you can have and still produce output:  it points to a model, simulates it for ten seconds, and reports the output.  The model itself (both the SBML version and the CellML version) has a single variable, 'a', with a value of '3' that doesn't change.");

  phrasedml.push_back(phrasedml[0]);
  blurbs.push_back(blurbs[0]);
  descriptions.push_back("This is another very simple SED-ML file that points to a model, simulates it for ten seconds, and reports the output.  The model itself has a single variable ('a') that starts at 3 and increases at a rate of 1/second.");

  phrasedml.push_back(phrasedml[0]);
  blurbs.push_back(blurbs[0]);
  descriptions.push_back("This is another very simple SED-ML file that points to a model, simulates it for ten seconds, and reports the output.  The model itself has a single variable ('a') that starts at 3 and increases at a rate of 1/second due to a reaction.");

  phrasedml.push_back("  mod1 = model FILE0\n  sim1 = simulate uniform_stochastic(0,10,100)\n  task1 = run sim1 on mod1\n  report time vs a\n  plot time vs a");
  blurbs.push_back("Basic stochastic report");
  descriptions.push_back("This is technically a stochastic simulation of a simple model, but since the single variable ('a') never changes, the expected mean for that value is 3, and the expected standard deviation is 0.");

  phrasedml.push_back("  mod1 = model FILE0\n  sim1 = simulate uniform_stochastic(0,10,100)\n  task1 = run sim1 on mod1\n  report time vs a\n  plot time vs a");
  blurbs.push_back("Basic stochastic report");
  descriptions.push_back("This is a stochastic simulation of a simple model, where a single variable ('a') that starts at 3 and increases at a rate of 1/second due to a reaction.  The reaction should proceed stochastically.");

}


int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << endl << "Useage: create-test-suite [directory], where [directory] is the root directory of the SED-ML test suite." << endl << endl;
    return 1;
  }
  string directory = argv[1];

  vector<string> models, phrasedml, blurbs, descriptions;
  setupModels(models);
  setupSEDML(phrasedml, blurbs, descriptions);

  vector<string>::iterator modindex = models.begin();
  createTest(1, modindex+0, 1, 0, phrasedml, blurbs, descriptions, directory);
  createTest(2, modindex+1, 1, 1, phrasedml, blurbs, descriptions, directory);
  createTest(3, modindex+2, 1, 2, phrasedml, blurbs, descriptions, directory);
  createTest(4, modindex+0, 1, 3, phrasedml, blurbs, descriptions, directory);
  createTest(5, modindex+2, 1, 4, phrasedml, blurbs, descriptions, directory);


  return 0;
}
