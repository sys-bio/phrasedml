#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "model.h"
#include "modelChange.h"
#include "registry.h"
#include "stringx.h"

#include "sedml\SedChange.h"
#include "sedml\SedChangeAttribute.h"
#include "sedml\SedDocument.h"

using namespace std;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp

ModelChange::ModelChange(vector<const string*>* name, double value)
  : m_variable(getStringFrom(name, "."))
  , m_value(value)
  , m_parent()
{

}

ModelChange::ModelChange(SedChange* sedchange, SedDocument* seddoc, string parent)
  : m_parent(parent)
{
  string target = sedchange->getTarget();
  SedChangeAttribute* sedchangeatt = static_cast<SedChangeAttribute*>(sedchange);
  stringstream val(sedchangeatt->getNewValue());

  switch(sedchange->getTypeCode())
  {
  case SEDML_CHANGE_ATTRIBUTE:
    m_variable = getIdFromXPath(target);
    val >> m_value;
    break;
  default:
    //Warn that we don't handle these yet.
    break;
  }
}

ModelChange::~ModelChange()
{
}

string ModelChange::getPhraSEDML() const
{
  string ret = m_variable;
  ret += " = ";
  ret += DoubleToString(m_value);
  return ret;
}

bool ModelChange::addModelChangeToSEDML(SedModel* sedmodel) const
{
  SedChangeAttribute* sca = sedmodel->createChangeAttribute();
  PhrasedModel* mod = g_registry.getModel(m_parent);
  if (mod==NULL) return true;
  SBMLDocument* doc = mod->getSBMLDocument();
  sca->setTarget(getValueXPathFromId(m_variable, doc));
  sca->setNewValue(DoubleToString(m_value));
  return false;
}

void ModelChange::setParent(string parent)
{
  m_parent = parent;
}

string ModelChange::getParent() const 
{
  return m_parent;
}

bool ModelChange::check() const
{
  PhrasedModel* mod = g_registry.getModel(m_parent);
  SBMLDocument* doc = mod->getSBMLDocument();
  if (getValueXPathFromId(m_variable, doc).empty()) {
    return true;
  }
  return false;

}