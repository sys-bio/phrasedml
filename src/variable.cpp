#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>

#include "variable.h"

using namespace std;

#define DEFAULTCOMP "default_compartment" //Also defined in antimony_api.cpp

Variable::Variable(string id)
  : m_id(id)
  , m_name()
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