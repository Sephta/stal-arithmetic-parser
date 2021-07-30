/* Seth Tal
 * 07.29.2021
 * Rudimentary Arithmetic Parser
*/

enum Operator {
  Add,
  Subtract,
  Multiply,
  Divide
}op;

class AtomicValue
{
protected:
  int value;

public:
  AtomicValue();
  AtomicValue(int value);

  int getValue();
  void setValue(int newValue);

};
