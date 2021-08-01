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

    // @brief publically accessible attribute continaing the expression to be parsed.
    std::string expr;
    
    // CONSTRUCTORS

    Parser();

    /* Parser(std::string)
     * @param expression the string containing the expression to be parsed.
    */
    Parser(std::string expression);
    
    // DESTRUCTOR

    ~Parser();

    // PUBLIC METHOD

    /* evaluate()
     * @brief Parses and evaluates the expression provided to the Parser object.
     * @returns the result of paring and evaluating as a double int.
    */
    double evaluate();

  private:

    // PRIVATE METHODS

    /* currentToken(void)
     * @brief Intended to be used as a way of peeking at the current token to be parsed inside of `expr`
     * @returns a copy of the current token in the expression string
    */
    char currentToken();
    
    /* nextToken(void)
     * @brief intended to be used as a way of peeking at the next token to be parsed inside of `expr`
     * @returns a copy of the next token in the expression string (i.e. ++expr.begin())
    */
    char nextToken();
    
    /* popToken(void)
     * @brief removes and returns the front most token from the `expr` string.
     * @returns the current token at the front of `expr`
    */
    char popToken();

    /* isNumber(void)
     * @param token compares the ASCII char value of this to '0' through '9'.
     * @returns True if ASCII value between '0' and '9', False otherwise
    */
    bool isNumber(char token);

    /* isOperator(void)
     * @param token compares its ASCII value to '+' , '/' , '-' , and '*'
     * @returns True if ASCII value equals '+' or '/' or '-' or '*', False otherwise
    */
    bool isOperator(char token);
};
