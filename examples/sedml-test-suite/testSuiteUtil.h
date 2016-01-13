/**
 * @file    testSuiteUtil.cpp
 * @brief   Functions used in both generateTestsFrom and checkTestCases.
 * @author  Lucian Smith
 * 
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 */

/*
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>


#include <sbml/SBMLTypes.h>
#include <sbml/packages/fbc/common/FbcExtensionTypes.h>
#include <sbml/packages/comp/common/CompExtensionTypes.h>

using namespace std;
LIBSBML_CPP_NAMESPACE_USE

bool variesIn(string id,  const map<string, vector<double> >& results);
vector<string> getStrings(string line) ;
void insertStrings(string linestr, map<string, vector<double> >& results, vector<string>& keys);

map<string, vector<double> > getResults(string filename) ;

bool hasActualErrors(SBMLDocument* document);
void printActualErrors(SBMLDocument* document);
bool variesIn(string id, ListOfSpeciesReferences* srs,  const map<string, vector<double> >& results);
bool variesIn(const ASTNode* math, Model* model,  const map<string, vector<double> >& results);
bool getConstant(string id, Model* model,  const map<string, vector<double> >& results);
bool variesIn(const ASTNode* math, Model* model,  const map<string, vector<double> >& results);
bool appearsIn(string id, const ASTNode* math);
bool variesBesides(string mayvar, const ASTNode* math, Model* model,  const map<string, vector<double> >& results);
bool variesIn(string id, Model* model,  const map<string, vector<double> >& results);
bool getInitialResultFor(string id, const map<string, vector<double> >& results, double& initialResult);
bool getSetValue(string id, Model* model, const set<string>& tests, double& setValue);
bool hasAssignmentOrAlgebraic(Model* model);
bool initialOverriddenIn(string id, Model* model, const map<string, vector<double> >& results, const set<string>& tests);
void checkRules(Model* model, set<string>& components, set<string>& tests);
void checkCompartments(Model* model, set<string>& components, set<string>& tests,  const map<string, vector<double> >& results);
void checkEvents(Model* model, set<string>& components, set<string>& tests);
void checkParameters(Model* model, set<string>& components, set<string>& tests,  const map<string, vector<double> >& results);
bool foundInMath(string id, const ASTNode* astn);
bool foundInMath(string id, Model* model);
void checkSpeciesRefs(Model* model, ListOfSpeciesReferences* losr, set<string>& components, set<string>& tests,  const map<string, vector<double> >& results);
void checkReactions(Model* model, set<string>& components, set<string>& tests,  const map<string, vector<double> >& results, bool fbc);
void checkSpecies(Model* model, set<string>& components, set<string>& tests,  const map<string, vector<double> >& results, bool fbc);
*/