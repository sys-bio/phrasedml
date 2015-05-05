#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "registry.h"
#include "model.h"

#ifdef LIBSBML_HAS_PACKAGE_DISTRIB
#include "sbml/packages/distrib/common/DistribExtensionTypes.h"
#endif

extern Registry g_registry;
using namespace std;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp

PhrasedModel::PhrasedModel(string id, string source, bool quoteSource)
  : Variable(id)
  , m_type(lang_XML)
  , m_source(source)
  , m_changes()
  , m_quoteSource(quoteSource)
{
  processSource();
}

PhrasedModel::PhrasedModel(string id, string source, vector<ChangeList*> changes, bool quoteSource)
  : Variable(id)
  , m_type(lang_XML)
  , m_source(source)
  , m_changes(changes)
  , m_quoteSource(quoteSource)
{
  processSource();
}

PhrasedModel::~PhrasedModel()
{
}

void PhrasedModel::setQuoteSource(bool quote)
{
  m_quoteSource = quote;
}

bool PhrasedModel::getQuoteSource()
{
  return m_quoteSource;
}

string PhrasedModel::getPhraSEDML() const
{
  string ret = m_id;
  ret += " = model ";
  string source = m_source;
  if (m_quoteSource) {
    source = "\"" + source + "\"";
  }
  ret += source + "\n";
  return ret;
}

void PhrasedModel::processSource()
{
  //Probably have to use libsbml or whatever.
}

language PhrasedModel::getLanguageFromURI(string uri)
{
  if (uri == "urn:sedml:language:xml") {
    return lang_XML;
  } else if (uri == "urn:sedml:language:sbml") {
    return lang_SBML;
  } else if (uri == "urn:sedml:language:cellml") {
    return lang_CellML;
  } else if (uri == "urn:sedml:language:sbml.level-2.version-2") {
    return lang_SBMLl1v2;
  } else if (uri == "urn:sedml:language:sbml.level-2.version-1") {
    return lang_SBMLl2v1;
  } else if (uri == "urn:sedml:language:sbml.level-2.version-2") {
    return lang_SBMLl2v2;
  } else if (uri == "urn:sedml:language:sbml.level-2.version-3") {
    return lang_SBMLl2v3;
  } else if (uri == "urn:sedml:language:sbml.level-2.version-4") {
    return lang_SBMLl2v4;
  } else if (uri == "urn:sedml:language:sbml.level-2.version-5") {
    return lang_SBMLl2v5;
  } else if (uri == "urn:sedml:language:sbml.level-3.version-1") {
    return lang_SBMLl3v1;
  } else if (uri == "urn:sedml:language:sbml.level-3.version-2") {
    return lang_SBMLl3v2;
  } else if (uri == "urn:sedml:language:cellml_1.0") {
    return lang_CellML1_0;
  } else if (uri == "urn:sedml:language:cellml_1.1") {
    return lang_CellML1_1;
  } else if (uri == "urn:sedml:language:cellml_1.2") {
    return lang_CellML1_2;
  }
  return lang_XML;
}

std::string PhrasedModel::getURIFromLanguage(language lang)
{
  switch(lang)
  {
  case lang_XML: 
    return "urn:sedml:language:xml";
  case lang_SBML: 
    return "urn:sedml:language:sbml";
  case lang_CellML: 
    return "urn:sedml:language:cellml";
  case lang_SBMLl1v2: 
    return "urn:sedml:language:sbml.level-2.version-2";
  case lang_SBMLl2v1: 
    return "urn:sedml:language:sbml.level-2.version-1";
  case lang_SBMLl2v2: 
    return "urn:sedml:language:sbml.level-2.version-2";
  case lang_SBMLl2v3: 
    return "urn:sedml:language:sbml.level-2.version-3";
  case lang_SBMLl2v4: 
    return "urn:sedml:language:sbml.level-2.version-4";
  case lang_SBMLl2v5: 
    return "urn:sedml:language:sbml.level-2.version-5";
  case lang_SBMLl3v1: 
    return "urn:sedml:language:sbml.level-3.version-1";
  case lang_SBMLl3v2: 
    return "urn:sedml:language:sbml.level-3.version-2";
  case lang_CellML1_0: 
    return "urn:sedml:language:cellml_1.0";
  case lang_CellML1_1: 
    return "urn:sedml:language:cellml_1.0";
  case lang_CellML1_2:
    return "urn:sedml:language:cellml_1.2";
  }
  assert(false); //uncaught enum
  return "urn:sedml:language:xml";
}

