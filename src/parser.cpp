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