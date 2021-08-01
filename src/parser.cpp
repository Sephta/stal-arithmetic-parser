/* Seth Tal
 * 07.31.2021
 * Rudimentary Arithmetic Parser
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
  AtomicValue* evaluation = nullptr;

  if (this->isNumber(this->currentToken()))
  {
    evaluation = (AtomicValue*) new Number(this->popToken());
  }
  else if (this->currentToken() == '(')
  {
    this->popToken(); // Remove '('

    if (this->isOperator(this->nextToken()))
    {
      evaluation = (AtomicValue*) new Expression((AtomicValue*) new Number(this->popToken()),  // Left Hand Side
                                                  (Operator) this->popToken(),      // Operator
                                                  (AtomicValue*) new Number(this->popToken())); // Right Hand Side
    }
    else
    {
      std::cerr << "ERR: Expression enclosed in \'(\' and \')\' must be of the form: <Number> <Operator> <Number>" << std::endl;

      delete evaluation;
      delete this;

      exit(EXIT_FAILURE);
    }

    this->popToken(); // Remove ')'
  }

  while (evaluation)
  {
    if (this->isOperator(this->currentToken()))
    {
      Operator newOp = (Operator) this->popToken();

      if (this->isNumber(this->currentToken()))
      {
        int lhs = evaluation->evaluate();

        if (evaluation) delete evaluation;

        evaluation = (AtomicValue*) new Expression((AtomicValue*) new Number(lhs), 
                                                    newOp,
                                                    (AtomicValue*) new Number(this->popToken()));
      }
      else if (this->currentToken() == '(') 
      {
        this->popToken(); // Remove '('

        AtomicValue* rhs;

        if (this->isOperator(this->nextToken()))
        {
          int lhs = evaluation->evaluate();

          if (evaluation) delete evaluation;

          rhs = (AtomicValue*) new Expression((AtomicValue*) new Number(this->popToken()), 
                                              (Operator) this->popToken(), 
                                              (AtomicValue*) new Number(this->popToken()));

          evaluation = (AtomicValue*) new Expression((AtomicValue*) new Number(lhs),
                                                     newOp,
                                                     (AtomicValue*) new Number((int) rhs->evaluate()));

          if (rhs) delete rhs;
        }
        else
        {
          std::cerr << "ERR: Expression enclosed in \'(\' and \')\' must be of the form: <Number> <Operator> <Number>" << std::endl;

          delete evaluation;
          delete this;

          exit(EXIT_FAILURE);
        }

        this->popToken(); // Remove ')'
      }
    }
    else
      break;
  }

  if (this->expr.size() > 0)
  {
    std::cerr << std::endl << "WARNING: there was likely a misplaced \'(\' or \')\' resulting in an incorrect evaluation." << std::endl;
  }

  double result = evaluation->evaluate();
  
  if (evaluation) delete evaluation;
  
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