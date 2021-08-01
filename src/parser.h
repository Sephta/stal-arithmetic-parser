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
    virtual long evaluate() = 0;
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

    virtual long evaluate() override;
    void setValue(int newValue);
};

class DoubleNumber : AtomicValue
{
  protected:
    double value;

  public:
    DoubleNumber();
    DoubleNumber(double value);

  virtual long evaluate();
};

class LongNumber : AtomicValue
{
  protected:
    long value;

  public:
    LongNumber();
    LongNumber(long value);

    virtual long evaluate();
};

class LongExpression : AtomicValue
{
  protected:
    AtomicValue* lhs;
    Operator op;
    AtomicValue* rhs;

  public:
    LongExpression(AtomicValue* lhs, Operator op, AtomicValue* rhs);
    virtual ~LongExpression();

    virtual long evaluate();
    void print(std::ostream& output);
};

class IntExpression : AtomicValue
{
  protected:
    IntNumber* lhs;
    Operator op;
    IntNumber* rhs;

  public:
    IntExpression(IntNumber* lhs, Operator op, IntNumber* rhs);
    virtual ~IntExpression();

    virtual long evaluate();
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

  long evaluate();

  private:
    char popExpression();
    bool isNumber(char token);
    bool isOperator(char token);
};
