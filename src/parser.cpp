/* Seth Tal
 * 07.31.2021
 * Rudimentary Arithmetic Parser

  I sort of developed my own 'algorithm', but its very derivative of "Recursive Descent" parsing, although HEAVILY simplified
  and lacks the recursion... which is like the whole point of recursive descent but I digress. My algorithm is simply itterative.

  Basically every character in the string stored in the Parser object is treated like a 'token' which gets 'popped' off the 
  front of the string. The algorithm goes through an itterative process of checking for specific types of tokens and performs
  specific behavior depending on the token it encounters.

  For the most part there is little to no memory leaking outside of specific program inputs I didnt account for.
  I made an effort to run my code using valgrind to catch any simple mistakes, but once again, I haven't accounted 
  for weird string inputs like "   \\ /", or "adfshfjkdhweoinvmn", and stuff like that.
*/


#include "./parser.h"


#pragma region ATOMIC_VALUE
AtomicValue::AtomicValue() {};
AtomicValue::~AtomicValue() {};

void AtomicValue::print(std::ostream& output) { output << this->evaluate() << std::endl; };
#pragma endregion


#pragma region NUMBER
Number::Number() : value(0) {};
Number::Number(Number* num) { this->value = num->evaluate(); };
Number::Number(char value) { this->value = (double)(value - '0'); };
Number::Number(int value) { this->value = (double) value; };
Number::Number(long value) { this->value = (double) value; };
Number::Number(double value) { this->value = value; };

Number::~Number() {}; // Does nothing

double Number::evaluate() { return this->value; };

void Number::print(std::ostream& output)
{
  output << "<Num: " << this->evaluate() << ">" << std::endl;
};

void Number::setValue(char newValue) { this->value = (double)(value - '0'); };
#pragma endregion


#pragma region EXPRESSION
Expression::Expression() : lhs(0), op(Operator::Add), rhs(0) {};

Expression::Expression(AtomicValue* lhs, Operator op, AtomicValue* rhs) : lhs(lhs), op(op), rhs(rhs) {};

Expression::~Expression()
{
  if (lhs) delete lhs;
  if (rhs) delete rhs;
};

double Expression::evaluate()
{
  if (this->lhs == nullptr || this->rhs == nullptr)
    return 0;

  double result = 0;

  switch (this->op)
  {
    case Operator::Add:
      result = lhs->evaluate() + rhs->evaluate();
      break;
    case Operator::Subtract:
      result = lhs->evaluate() - rhs->evaluate();
      break;
    case Operator::Multiply:
      result = lhs->evaluate() * rhs->evaluate();
      break;
    case Operator::Divide:
      result =  lhs->evaluate() / rhs->evaluate();
      break;
  }

  return result;
};

void Expression::print(std::ostream& output)
{
  output << "Expr: " << this->lhs->evaluate() << " " << (char) this->op << " " << this->rhs->evaluate() << std::endl;
};

#pragma endregion


#pragma region PARSER
Parser::Parser() : expr((std::string)"0+0") {};

Parser::Parser(std::string expression) : expr(expression) {};

Parser::~Parser() {}; // Does nothing tbh

double Parser::evaluate()
{
  /* FROM ABOVE:
    I sort of developed my own 'algorithm', but its very derivative of "Recursive Descent" parsing, although HEAVILY simplified
    and lacks the recursion... which is like the whole point of recursive descent but I digress. My algorithm is simply itterative.

    Basically every character in the string stored in the Parser object is treated like a 'token' which gets 'popped' off the 
    front of the string. The algorithm goes through an itterative process of checking for specific types of tokens and performs
    specific behavior depending on the token it encounters.

    For the most part there is little to no memory leaking outside of specific program inputs I didnt account for.
    I made an effort to run my code using valgrind to catch any simple mistakes, but once again, I haven't accounted 
    for weird string inputs like "   \\ /", or "adfshfjkdhweoinvmn", and stuff like that.
  */


  AtomicValue* evaluation = nullptr;

  // This section is for the very first 'token' in the expression
  // If the token is a number then the while loop will break early and the Number will evaluate
  // Else its an expression, which is then built and 'evaluation' now points to an Expression.
  if (this->isNumber(this->currentToken()))
  {
    evaluation = (AtomicValue*) new Number(this->popToken()); // Here I just pop the current 'token' character off the `expr` string
  }
  else if (this->currentToken() == '(') // The open parenthesis signifies the start of an expression
  {
    // Expressions should be of the form: ( <Number> <Operator> <Number> )

    this->popToken(); // Removes the '(' from the head of the `expr` string

    // Here, this->currentToken() should be a number, and the next token after tha will be the operator
    if (this->isOperator(this->nextToken()))
    {
      evaluation = (AtomicValue*) new Expression((AtomicValue*) new Number(this->popToken()),   // Left Hand Side
                                                  (Operator) this->popToken(),                  // Operator
                                                  (AtomicValue*) new Number(this->popToken())); // Right Hand Side
    }
    else
    {
      std::cerr << "ERR: Expression enclosed in \'(\' and \')\' must be of the form: <Number> <Operator> <Number>" << std::endl;

      // Cleans up allocated objects as a form of garbage collection for when the program exits.
      delete evaluation;
      delete this;

      // Choosing to just hault program execution since Expression must have a strict form. 
      // The rest of the expression string cannot be evaluated correctly otherwise.
      exit(EXIT_FAILURE);
    }

    this->popToken(); // Removes the ')' from the head of the `expr` string
  }

  // Now the rest of the `expr` gets evaluated by constantly updating the evaluation pointer.
  while (evaluation)
  {
    // The next 'token' should garunteed be a valid Operator otherwise there is likely
    //  a syntax issue with the expression given to the Parser.
    if (this->isOperator(this->currentToken()))
    {
      // This step is unecessary and is here for readability
      Operator newOp = (Operator) this->popToken();

      // Similar to above, if its a number, update the value of 'evaluation'
      // Although this time we need a new Expression object to pass the operator
      // popped above.
      if (this->isNumber(this->currentToken()))
      {
        double lhs = evaluation->evaluate();

        if (evaluation) delete evaluation; // no memory leaking here  :) ... I think

        evaluation = (AtomicValue*) new Expression((AtomicValue*) new Number(lhs), 
                                                   newOp,
                                                   (AtomicValue*) new Number(this->popToken()));
      }
      else if (this->currentToken() == '(') 
      {
        this->popToken(); // Removes the '(' from the head of the `expr` string

        // This is used for readability, and is probably unecessary.
        AtomicValue* rhs;

        // Makes sure its going to encounter an operator...
        if (this->isOperator(this->nextToken()))
        {
          double lhs = evaluation->evaluate();

          if (evaluation) delete evaluation;

          rhs = (AtomicValue*) new Expression((AtomicValue*) new Number(this->popToken()), 
                                              (Operator) this->popToken(), 
                                              (AtomicValue*) new Number(this->popToken()));

          evaluation = (AtomicValue*) new Expression((AtomicValue*) new Number(lhs),
                                                     newOp,
                                                     (AtomicValue*) new Number(rhs->evaluate()));

          if (rhs) delete rhs; // no memory leaking here  :) ... hopefully
        }
        else
        {
          std::cerr << "ERR: Expression enclosed in \'(\' and \')\' must be of the form: <Number> <Operator> <Number>" << std::endl;

          // Cleaning and haulting program for similar reasons as seen earlier in the method.
          delete evaluation;
          delete this;

          exit(EXIT_FAILURE);
        }

        this->popToken(); // Removes the ')' from the head of the `expr` string
      }
    }
    else
      break;
  }

  // Idealy after parsing the expression string it should just be an empty-ish string. If thats not the case their may
  // have been some kind of syntactic error I didn't program a workaround for.
  if (this->expr.size() > 0)
  {
    std::cerr << std::endl << "WARNING: there was likely a misplaced \'(\' or \')\' resulting in an incorrect evaluation." << std::endl;
  }

  double result = evaluation->evaluate();
  
  if (evaluation) delete evaluation; // Garbage collecting....
  
  return result;
};

char Parser::currentToken() { return *(this->expr.begin()); };

char Parser::nextToken() { return *(++this->expr.begin()); };

char Parser::popToken()
{
  char result;

  if(result=*(this->expr.begin()));
  else
  {
    std::cerr << std::endl << "WARNING: missing enclosing parenthesis \')\'." << std::endl;
    return '\0';
  }

  this->expr.erase(this->expr.begin());

  return result;
};

bool Parser::isNumber(char token)
{
  if ('0' <= token && token <= '9')
    return true;

  return false;
};

bool Parser::isOperator(char token)
{
  bool result = false;

  switch (token)
  {
    case Operator::Add:
      result = true;
      break;
    case Operator::Subtract:
      result = true;
      break;
    case Operator::Multiply:
      result = true;
      break;
    case Operator::Divide:
    result = true;
      break;
  }

  return result;
}
#pragma endregion