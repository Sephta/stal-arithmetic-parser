#include <iostream>
#include <vector>
#include "./parser.h"


#pragma region ATOMIC_VALUE
AtomicValue::AtomicValue()
{
  this->value = 0;
};

AtomicValue::AtomicValue(int value)
{
  this->value = value;
};

int AtomicValue::getValue() { return this->value; };
void AtomicValue::setValue(int newValue) { this->value = newValue; };
#pragma endregion


int main()
{
  AtomicValue* av_test = new AtomicValue(42);

  Operator newOp = Operator::Add;

  std::cout << "OP: " << newOp << " , Atomic Value: " << av_test->getValue() << std::endl;

  delete av_test;
}
