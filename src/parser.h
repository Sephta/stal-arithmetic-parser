/* Seth Tal
 * 07.29.2021
 * Rudimentary Arithmetic Parser
*/
#include <string>

enum Operator {
  Add      = 43,
  Subtract = 45,
  Multiply = 42,
  Divide   = 47
};

class AtomicValue
{
protected:
  int value;

public:
  AtomicValue();
  AtomicValue(int value);

  int getValue();
  void setValue(int newValue);

};

class Parser
{
  public:
    std::string expr;

  public:
    Parser();

  char currentToken();
  char nextToken();
};
