/* Seth Tal
 * 07.29.2021
 * Rudimentary Arithmetic Parser
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include "./parser.h"


/* programUsage(int, char**)
 * @brief Checks to make sure program is being used correctly. i.e. Correct number of arguements, etc.
 * @param argc the number of arguements passed to the executable.
 * @param argv buffer which contains all program arguements passed to the executable.
 * @return 1 if tests passed, 0 otherwise.
*/
int programUsage(int argc, char** argv)
{
  if (argc != 2) return 0;
  else
  {
    return 1;
  }
}

/* programUsage(int, char**)
 * @brief Prints the program input to std::cerr for debug purposes.
 * @param argc the number of arguements passed to the executable.
 * @param argv buffer which contains all program arguements passed to the executable.
 * @return void
*/
void debugInput(int argc, char** argv)
{
  using namespace std;

  cerr << "ARGC: " << argc << endl;
  for (int i = 0; i < argc; i++)
    cerr << "ARGV[" << i << "]" << " = " << argv[i] << endl;
  
  cerr << endl;
}

/* getExpressionFromArgs(char**)
 * @brief Returns the expression the program will parse and calculate from the argv buffer. (ALSO: strips whitespace)
 * @param argv buffer which contains all program arguements passed to the executable.
 * @return std::string containing the expression to be parsed.
*/
std::string getExpressionFromArgs(char** argv)
{
  std::string result(argv[1]);

  // From <algorithm>...
  result.erase(remove_if(result.begin(), result.end(), isspace), result.end());

  // Returns expression to parse, and strips whitespace...
  return result;
}

/* main(int, char**)
 * @brief Main program execution loop.
 * @param argc the number of arguements passed to the executable.
 * @param argv buffer which contains all program arguements passed to the executable.
 * @return exit status as int.
*/
int main(int argc, char** argv)
{
  using namespace std;

  cout << "PROGRAM BEGIN..." << endl << endl;

  // debugInput(argc, argv);

  // Rudimentary check to make sure program is being used correctly...
  if (programUsage(argc, argv)) cout << "Program being used correctly..." << endl << endl;
  else
  {
    cout << "Program NOT being used correctly. Exiting program..." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Expression to be parsed: " << argv[1] << endl;

  std::string expression = getExpressionFromArgs(argv);

  cout << "After stripping whitespace: " << expression << endl;
  
  cout<< endl;

  Parser* parser = new Parser(expression);

  cerr << "Evaluating Parser: " << parser->evaluate() << endl;

  // PROGRAM CLEANUP
  cout << endl << "Cleaning program..." << endl;
  delete parser;
  // delete numTest;
  // delete exprTest;

  cout << endl << "PROGRAM END..." << endl;
}
