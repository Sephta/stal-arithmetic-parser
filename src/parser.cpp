/* Seth Tal
 * 07.29.2021
 * Rudimentary Arithmetic Parser
*/


#include "./parser.h"


#pragma region ATOMIC_VALUE
AtomicValue::AtomicValue() {};
AtomicValue::~AtomicValue() {};
#pragma endregion

#pragma region INT_NUMBER
IntNumber::IntNumber()
{
  this->value = 0;
}

IntNumber::IntNumber(int value)
{
  this->value = value;
};

IntNumber::IntNumber(char value)
{
  this->value = (int)(value - '0');
};

IntNumber::IntNumber(char* value)
{
  this->value = atoi((const char *) value);
};

IntNumber::IntNumber(const char* value)
{
  this->value = atoi(value);
};

IntNumber::IntNumber(IntNumber* iNum)
{
  this->value = iNum->evaluate();
};

IntNumber::~IntNumber() {};

long IntNumber::evaluate() { return (long) this->value; };
void IntNumber::setValue(int newValue) { this->value = newValue; };
#pragma endregion

LongNumber::LongNumber() {};
LongNumber::LongNumber(long value) : value(value) {};

long LongNumber::evaluate() { return this->value; };

#pragma region EXPRESSIONS

LongExpression::LongExpression(AtomicValue* lhs, Operator op, AtomicValue* rhs) : lhs(lhs), op(op), rhs(rhs) {};
LongExpression::~LongExpression() {};

long LongExpression::evaluate()
{
  if (this->lhs == nullptr || this->rhs == nullptr)
    return 0;

  int result = 0;

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

  return (long) result;
};

void LongExpression::print(std::ostream& output)
{
  output << "Expr: " << this->lhs->evaluate() << " " << (char) this->op << " " << this->rhs->evaluate() << std::endl;
};


IntExpression::IntExpression(IntNumber* lhs, Operator op, IntNumber* rhs) : lhs(lhs), op(op), rhs(rhs) {};

IntExpression::~IntExpression()
{
  if (lhs) delete lhs;
  if (rhs) delete rhs;
};

long IntExpression::evaluate()
{
  if (this->lhs == nullptr || this->rhs == nullptr)
    return 0;

  int result = 0;

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

void IntExpression::print(std::ostream& output)
{
  output << "Expr: " << this->lhs->evaluate() << " " << (char) this->op << " " << this->rhs->evaluate() << std::endl;
};
#pragma endregion

#pragma region PARSER
Parser::Parser() {};

Parser::Parser(std::string toParse) : expr(toParse), curr(0) {};

char Parser::currentToken() { return *(this->expr.begin()); };

char Parser::nextToken() { return *(++this->expr.begin()); };

char Parser::popExpression()
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

/* evaluate()
 * @brief Parses and evaluates the expression stored in the 'expr' attribute.
 * @returns the result of parsing and evaluating 'expr' as an int.
*/
long Parser::evaluate()
{
  AtomicValue* evaluation = nullptr;

  if (this->isNumber(this->currentToken()))
  {
    evaluation = (AtomicValue*) new IntNumber(this->popExpression());
  }
  else if (this->currentToken() == '(')
  {
    this->popExpression(); // Remove '('

    if (this->isOperator(this->nextToken()))
    {
      evaluation = (AtomicValue*) new IntExpression(new IntNumber(this->popExpression()),  // Left Hand Side
                                                    (Operator) this->popExpression(),      // Operator
                                                    new IntNumber(this->popExpression())); // Right Hand Side
    }
    else
    {
      std::cerr << "ERR: Expression enclosed in \'(\' and \')\' must be of the form: <Number> <Operator> <Number>" << std::endl;

      delete evaluation;
      delete this;

      exit(EXIT_FAILURE);
    }

    this->popExpression(); // Remove ')'
  }

  while (evaluation)
  {
    if (this->isOperator(this->currentToken()))
    {
      Operator newOp = (Operator) this->popExpression();

      if (this->isNumber(this->currentToken()))
      {
        int lhs = evaluation->evaluate();

        if (evaluation) delete evaluation;

        evaluation = (AtomicValue*) new IntExpression(new IntNumber(lhs), 
                                                      newOp,
                                                      new IntNumber(this->popExpression()));
      }
      else if (this->currentToken() == '(') 
      {
        this->popExpression(); // Remove '('

        AtomicValue* rhs;

        if (this->isOperator(this->nextToken()))
        {
          int lhs = evaluation->evaluate();

          if (evaluation) delete evaluation;

          rhs = (AtomicValue*) new IntExpression(new IntNumber(this->popExpression()), 
                                                 (Operator) this->popExpression(), 
                                                 new IntNumber(this->popExpression()));

          evaluation = (AtomicValue*) new IntExpression(new IntNumber(lhs),
                                                        newOp,
                                                        new IntNumber((int) rhs->evaluate()));
          if (rhs) delete rhs;
        }
        else
        {
          std::cerr << "ERR: Expression enclosed in \'(\' and \')\' must be of the form: <Number> <Operator> <Number>" << std::endl;

          delete evaluation;
          delete this;

          exit(EXIT_FAILURE);
        }

        this->popExpression(); // Remove ')'
      }
    }
    else
      break;
  }

  if (this->expr.size() > 0)
  {
    std::cerr << std::endl << "WARNING: there was likely a misplaced \'(\' or \')\' resulting in an incorrect evaluation." << std::endl;
  }

  auto result = evaluation->evaluate();
  
  if (evaluation) delete evaluation;
  
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