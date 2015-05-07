#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

class SedBase;

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



private:

};


#endif //VARIABLE_H
