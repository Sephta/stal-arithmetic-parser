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

/* Interface / Abstract Base Class for Foundational Data Classes */
class AtomicValue
{

public:
  virtual ~AtomicValue();
  virtual int getValue() = 0;
};

class IntNumber : AtomicValue 
{
protected:
  int value;

public:
  IntNumber();
  IntNumber(int value);
  ~IntNumber();

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
