/* Seth Tal
 * 07.31.2021
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
 * @brief Interface / Abstract Base Class for Foundational Data Classes. Everything in this parsing framework will have an evaluation resulting in some concrete value.
*/
class AtomicValue
{
  public:
    AtomicValue();
    virtual ~AtomicValue();
    virtual double evaluate() = 0;
    virtual void print(std::ostream& output);
};

class Number : AtomicValue
{
  protected:
    double value;
  
  public:
    // CONSTRUCTORS

    Number();
    Number(Number* num);
    Number(char value);
    Number(int value);
    Number(long value);
    Number(double value);

    // DESTRUCTOR

    virtual ~Number() override;

    // OVERRIDES

    virtual double evaluate() override;
    virtual void print(std::ostream& output) override;

    // METHODS

    void setValue(char newValue);
};

class Expression : AtomicValue
{
  protected:
    AtomicValue* lhs;
    Operator op;
    AtomicValue* rhs;

  public:
    Expression(AtomicValue* lhs, Operator op, AtomicValue* rhs);
    virtual ~Expression() override;

    virtual double evaluate() override;
    virtual void print(std::ostream& output) override;
};


class Parser
{

  public:
    // ATTRIBUTES

    std::string expr;
    
    // CONSTRUCTORS

    Parser();
    Parser(std::string toParse);
    
    // DESTRUCTOR

    ~Parser();

    // PUBLIC METHOD

    double evaluate();

  private:

    // PRIVATE METHODS

    char currentToken();
    char nextToken();
    char popToken();

    bool isNumber(char token);
    bool isOperator(char token);
};
