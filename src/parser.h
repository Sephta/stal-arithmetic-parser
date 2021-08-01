/* Seth Tal
 * 07.29.2021
 * Rudimentary Arithmetic Parser
*/


#include <iostream>
#include <string>

/* enum Operator
 * @brief Each enum value represents a verbose form of the ASCII character associated with each operator. 
          i.e. "Add" = ASCII value 43 which is equivolent to '+'.
*/
enum Operator {
  Add      = 43,
  Subtract = 45,
  Multiply = 42,
  Divide   = 47
};

/* Class AtomicValue
 * @brief Interface / Abstract Base Class for Foundational Data Classes 
*/
class AtomicValue
{
public:
  AtomicValue();
  virtual ~AtomicValue();
  virtual int evaluate() = 0;
};

/* Class IntNumber
 * @brief Inherits AtomicValue, represents a numerable type in Integer form.
*/
class IntNumber : AtomicValue 
{
protected:
  int value;

public:
  IntNumber();
  IntNumber(int value);
  IntNumber(char value);
  IntNumber(char* value);
  IntNumber(const char* value);
  IntNumber(IntNumber* iNum);
  ~IntNumber();

  virtual int evaluate();
  void setValue(int newValue); 
};

class IntExpression : AtomicValue
{
  protected:
    Operator op;
    IntNumber* lhs;
    IntNumber* rhs;

  public:
    IntExpression(IntNumber* lhs, Operator op, IntNumber* rhs);
    virtual ~IntExpression();

    virtual int evaluate();
    void print(std::ostream& output);
};

class Parser
{
  public:
    std::string expr;
    int curr;

  public:
    Parser();
    Parser(std::string toParse);

  char currentToken();
  char nextToken();

  int evaluate();

  private:
    char popExpression();
    bool isNumber(char token);
    bool isOperator(char token);
};
