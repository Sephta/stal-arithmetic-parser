/* Seth Tal
 * 07.31.2021
 * Rudimentary Arithmetic Parser
*/


#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include "./parser.h"


#define PROGRAM_FLAG 1
#define PROGRAM_EXPRESSION 2


/* getExpressionFromArgs(char**)
 * @brief Returns the expression the program will parse and calculate from the argv buffer. (ALSO: strips whitespace)
 * @param argv buffer which contains all program arguements passed to the executable.
 * @return std::string containing the expression to be parsed.
*/
std::string getExpressionFromArgs(char** argv)
{
  std::string result(argv[PROGRAM_EXPRESSION]);

  // From <algorithm>, removes all instances of spaces in the string.
  result.erase(remove_if(result.begin(), result.end(), isspace), result.end());

  // Returns expression to parse, and strips whitespace...
  return result;
}

/* getFlagFromArgs(char**)
 * @brief extracts the program flag from commandline argv[1].
 * @param argv buffer which contains all program arguements passed to the executable.
 * @returns char representing the program flag.
*/
char getFlagFromArgs(char** argv)
{
  std::string result(argv[PROGRAM_FLAG]);

  result.erase(remove(result.begin(), result.end(), '-'), result.end());

  return *(result.begin());
}

/* printUsageError()
 * @brief Simply displays program usage info to the provided output stream.
 * @param output The output stream to print to.
*/
void printUsageError(std::ostream& output)
{
  output << "ERROR: Program usage error." << std::endl;
  output << std::endl;
  output << "Usage: ./parser <flag> <input>" << std::endl;
  output << "Flag Options:" << std::endl;
  output << "\t-f \"File Mode\"\t\tTells program to run in file mode, must provide path to file in <input>." << std::endl;
  output << "\t-s \"Standard Mode\"\tTells the program to run in standard mode. Provide expression to parse in quotes.\n\n\t\ti.e. \"1 + 1\" or \"(1 + 2) * 3\"" << std::endl;
  output << std::endl;
  output << "For further usage explanation, please refer to the provided README.md document." << std::endl;
  output << std::endl;
};

/* programUsage(int, char**)
 * @brief Checks to make sure program is being used correctly. i.e. Correct number of arguements, etc.
 * @param argc the number of arguements passed to the executable.
 * @param argv buffer which contains all program arguements passed to the executable.
 * @return 1 if tests passed, 0 otherwise.
*/
int programUsage(int argc, char** argv)
{
  int result = 0;

  char flag = getFlagFromArgs(argv);

  switch (flag)
  {
    case 'f':
      if (argc == 3) result = 1;
      break;
    case 's':
      if (argc == 3) result = 1;
      break;
  }

  return result;
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

/*
 * @brief Creates a Parser object and provides it the expression arguement. The evaluation is printed to std::cout.
 * @param expression the expression to be parsed and evaluated.
*/
void parseExpression(std::string expression)
{
  using namespace std;

  cout << endl << "---" << endl;
  cout << endl;

  cout << "Expression to be parsed:\t\t" << expression << endl;

  // Strips spaces from the string.
  expression.erase(remove_if(expression.begin(), expression.end(), static_cast<int(&)(int)>(std::isspace)), expression.end());
  // cout << "After stripping whitespace: " << expression << endl;
  
  cout<< endl;

  if (expression == (std::string)"")
  {
    cerr << "ERROR: Program was provided empty expression to parse. Exiting..." << endl;
    exit(EXIT_FAILURE);
  }

  Parser* parser = new Parser(expression);

  cout.precision(17);
  cout << "Parser evaluated the expression to:\t" << parser->evaluate() << endl;

  cout << endl << "---" << endl;
  cout << endl;

  // PROGRAM CLEANUP
  delete parser;
}

/*
 * @brief Opens and reads the input file line by line passing each line to parseExpression().
*/
void FILEMODE(std::string pathToFile)
{
  std::fstream file;

  file.open(pathToFile, std::ios::in);

  if (file.is_open())
  {
    std::string line;
    while (getline(file, line))
    {
      parseExpression(line);
      // std::cerr << line << std::endl;
    }
    file.close();
  }
  else
  {
    std::cerr << "ERROR: there was an error opening file at: " << pathToFile << std::endl;
    exit(EXIT_FAILURE);
  }
}

/*
 * @brief Provides the string input to parseExpression().
*/
void STANDARDMODE(char** argv)
{
  std::string expr(argv[PROGRAM_EXPRESSION]);

  parseExpression(expr);
}

/* main(int, char**)
 * @brief This arithmetic parser program is a rudimentary cli which either reads the provided string input and evalutates it, or opens the provided file path and evaluates line by line.
 * @param argc the number of arguements passed to the executable.
 * @param argv buffer which contains all program arguements passed to the executable.
 * @return exit status as int.
*/
int main(int argc, char** argv)
{
  using namespace std;

  cout << endl << "PROGRAM BEGIN..." << endl << endl;

  // debugInput(argc, argv);

  // Rudimentary check to make sure program is being used correctly...
  if (!programUsage(argc, argv))
  {
    printUsageError(std::cerr);
    exit(EXIT_FAILURE);
  }

  char flag = getFlagFromArgs(argv);
  // std::cerr << "PROGRAM FLAG: " << flag << std::endl << std::endl;

  switch (flag)
  {
    case 'f':
      FILEMODE(argv[2]);
      break;
    case 's':
      STANDARDMODE(argv);
      break;
  }

  cout << endl << "PROGRAM END..." << endl << endl;
}
