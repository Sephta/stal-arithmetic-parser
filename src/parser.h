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
  Add      = 43, // 43 is the ASCII value of '+'
  Subtract = 45, // 43 is the ASCII value of '-'
  Multiply = 42, // 42 is the ASCII value of '*'
  Divide   = 47  // 47 is the ASCII value of '/'
};

/* Base Class AtomicValue
 * @brief Interface / Abstract Base Class for Foundational Data Classes. Everything in this parsing framework will have an evaluation resulting in some concrete value.
*/
class AtomicValue
{
  public:
    // CONSTRUCTOR

    AtomicValue();

    // DESTRUCTOR

    virtual ~AtomicValue();

    // PUBLIC METHODS

    /*
     * @brief Intended to eventually result in a concrete datatype represented as a double.
    */
    virtual double evaluate() = 0;

    /*
     * @brief Prints a string representation of this object to the provided output stream
    */
    virtual void print(std::ostream& output);
};

/* Child Class Expression
 * @brief Inherits from the AtomicValue interface. A number is a generic object wrapper to return a concrete numerable value as a double.
*/
class Number : AtomicValue
{
  protected:

    /*
     * @brief the concrete value of this AtomicValue, represented as a double.
    */
    double value;
  
  public:
    // CONSTRUCTORS

    // Will hold a default value of 0
    Number();

    /*
     * @param num Sets the value of this Number to the value stored in `num`.
    */
    Number(Number* num);

    /*
     * @param value Sets the value of this Number to the equivolent char value provided to the constructor
    */
    Number(char value);
    
    /*
     * @param value Sets the value of this Number to the equivolent int value provided to the constructor
    */
    Number(int value);
    
    /*
     * @param value Sets the value of this Number to the equivolent long value provided to the constructor
    */
    Number(long value);
    
    /*
     * @param value Sets the value of this Number to the equivolent double value provided to the constructor
    */
    Number(double value);

    // DESTRUCTOR

    virtual ~Number() override;

    // OVERRIDES

    /*
     * @brief Returns the numerable value of this AtomicValue represented as a double.
    */
    virtual double evaluate() override;
    
    /*
     * @brief Prints a string representation of this AtomicValue to the provided output stream.
    */
    virtual void print(std::ostream& output) override;

    // METHODS

    void setValue(char newValue);
};

/* Child Class Expression
 * @brief Inherits from the AtomicValue interface. An expression is of the form <Atomic> <Operator> <Atomic> and will evaluate based on the implication of its Operator. The Expression class is capable of evaluating for Addition, Subtraction, Division, and Multiplication.
*/
class Expression : AtomicValue
{
  protected:
  
    // The left hand side of this Expression. Left hand side is prioritized.
    AtomicValue* lhs;

    // The Operation to perfrom on the Left and Right hand side.
    Operator op;

    // The right hand side of this Expression. Left hand side is prioritized.
    AtomicValue* rhs;

  public:

    // CONSTRUCTOR

    // Will hold a default value that will evaluate to 0.
    Expression();

    /*
     * @param lhs The left hand side of the expression
     * @param op The operation to perform on this expression (lhs has priority). Can be expressed as a char ('+' , '-' , '/' , '*')
     * @param rhs The right hand side of the expression
    */
    Expression(AtomicValue* lhs, Operator op, AtomicValue* rhs);

    // DESTRUCTOR
    virtual ~Expression() override;

    /*
     * @brief Performs the provided operation on the Left and Right hand side of the Expression, returns the numerable result represented as a double.
    */
    virtual double evaluate() override;

    /*
     * @brief Prints a string representation of this AtomicValue to the provided output stream.
    */
    virtual void print(std::ostream& output) override;
};


/* Base Class Parser
 * @brief Each Parser object is provided a std::string to parse and evaluate. Each character in the string is treated as a token. It is standard to provide the Parser a string stripped of any whitespace, and in particular: spaces.
*/
class Parser
{

  public:
    // ATTRIBUTES

    /*
     * @brief publically accessible attribute continaing the expression to be parsed.
    */
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

    /* evaluate(void)
     * @brief Parses and evaluates the expression provided to the Parser object.
     * @returns the result of paring and evaluating as a double.
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

    /* isNumber(char)
     * @param token compares the ASCII char value of this to '0' through '9'.
     * @returns True if ASCII value between '0' and '9', False otherwise
    */
    bool isNumber(char token);

    /* isOperator(char)
     * @param token compares its ASCII value to '+' , '/' , '-' , and '*'
     * @returns True if ASCII value equals '+' or '/' or '-' or '*', False otherwise
    */
    bool isOperator(char token);
};
