#include "./parser.h"


#pragma region ATOMIC_VALUE
// AtomicValue::AtomicValue()
// {
//   this->value = 0;
// };

// AtomicValue::AtomicValue(int value)
// {
//   this->value = value;
// };

AtomicValue::~AtomicValue() {};

// int AtomicValue::getValue() { return this->value; };
// void AtomicValue::setValue(int newValue) { this->value = newValue; };
#pragma endregion

#pragma region INT_NUMBER
IntNumber::IntNumber(int value)
{
  this->value = value;
};

IntNumber::~IntNumber() {};

int IntNumber::getValue() { return this->value; };
void IntNumber::setValue(int newValue) { this->value = newValue; };
#pragma endregion