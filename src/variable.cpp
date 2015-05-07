#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "variable.h"

#include "sedml\SedBase.h"

using namespace std;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp

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