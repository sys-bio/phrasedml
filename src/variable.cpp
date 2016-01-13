#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "variable.h"
#include "registry.h"

#include "sedml/SedBase.h"

using namespace std;

PHRASEDML_CPP_NAMESPACE_BEGIN
Variable::Variable(string id)
  : m_id(id)
  , m_name()
{
}

Variable::Variable(SedBase* sedbase)
  : m_id(sedbase->getId())
  , m_name(sedbase->getName())
{
}

Variable::~Variable()
{
}

void Variable::setId(string id)
{
  m_id = id;
}

void Variable::setName(string name)
{
  m_name = name;
}

string Variable::getId() const
{
  return m_id;
}

string Variable::getName() const
{
  return m_name;
}

bool Variable::finalize() const
{
  if (m_id.empty()) {
    g_registry.setError("Missing ID for element.", 0);
    return true;
  }
  return false;
}
PHRASEDML_CPP_NAMESPACE_END