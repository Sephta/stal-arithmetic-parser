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

int IntNumber::evaluate() { return this->value; };
void IntNumber::setValue(int newValue) { this->value = newValue; };
#pragma endregion

#pragma region EXPRESSIONS
// Expression::Expression() {};
// Expression::~Expression() {};

IntExpression::IntExpression(Operator op, IntNumber* lhs, IntNumber* rhs) : op(op), lhs(lhs), rhs(rhs) {};

IntExpression::~IntExpression() {};

int IntExpression::evaluate()
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

char Parser::currentToken()
{
  return this->expr[this->curr];
};

char Parser::nextToken()
{
  return this->expr[this->curr + 1];
};

int Parser::evaluate()
{
  // Parsing Algorithm outline...
  /*
  Expr* expr = new Expr();

  while (expression not parsed):
    curr_token = getToken();
    if (curr_token == '('):
      Parser.build_sub_expression();
    else if (curr_token == NUMBER):
      IntNumber* newNum = new IntNumber(curr_token);
      expr.appendAtomic(newNum);
    else if (curr_token == OPERATOR)
      Operator newOp = parser.getOperator(OPERATOR);
      expr.setOperator(newOp);
    
    curr_expression = getExpression();
    if (curr_expression.isValid()):
      evaluate the expression
  */

  auto currToken = this->currentToken();

  // AtomicValue* lhs;
  // Operator op;
  // AtomicValue* rhs;

  while (this->expr.begin() != this->expr.end())
  {
    // if (currToken == '(')
    // {
      
    // }
    std::cerr << "Expr: " << this->expr << std::endl;
    std::cerr << *(this->expr.begin()) << std::endl;

    // result.erase(remove_if(result.begin(), result.end(), isspace), result.end());
    this->expr.erase(this->expr.begin());
  }

  // return this->auxEvaluate(this->expr);
};

int Parser::auxEvaluate(std::string expression)
{
  // bool done = false;
  // while (!done)
  // {
  //   auto currentToken = this->currentToken();

  //   if (currentToken == '(')
  //   {
  //     // TODO
  //   }
  // }

  auto currToken = this->currentToken();

  if (this->isNumber(currToken))
  {
    return IntNumber(currToken).evaluate();
  }

  expression.erase(expression.begin());

  return auxEvaluate(expression);
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