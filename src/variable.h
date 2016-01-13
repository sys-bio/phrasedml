#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "phrasedml-namespace.h"

class SedBase;

PHRASEDML_CPP_NAMESPACE_BEGIN
class Variable
{
private:
  Variable(); //undefined

protected:
  std::string m_id;
  std::string m_name;

public:

  Variable(std::string id);
  Variable(SedBase* sedbase);
  ~Variable();

  void setName(std::string name);
  std::string getName() const;

  void setId(std::string id);
  std::string getId() const;

  virtual bool finalize() const;

private:

};
PHRASEDML_CPP_NAMESPACE_END


#endif //VARIABLE_H
