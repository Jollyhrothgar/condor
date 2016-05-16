#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

// returns a string ranomly generated from the characters in the
// first argument, with a length of the second argument.
std::string randomSet(const std::string& space, std::string& result, int length);

// Generates a random integer between a minimum and maximum value.
int randomNumber(int min, int max);

int main(int argc, char** argv)
{
  // make a map/vector with arguments - one for a string, one for a int, and one for a float
  // generate a 3 column text file from those arguments.
  // Use argv to determine how many to generate.
  if(argc != 4) 
  {
    std::cerr << " Usage is: " << std::endl << "  " << argv[0] 
        << " ARGUMENT_FILE_NAME NUMBER_OF_LINES OUTPUT_DIRECTORY" << std::endl;
    return -1;
  }
  std::string outFileName = argv[1];
  int nlines = atoi(argv[2]);
  std::string depositDirectory = argv[3];

  std::cout << "Generating list of " << argv[2] << " lines" << std::endl;
  std::cout << "  sending to file : " << argv[1] << std::endl;
  std::ofstream outFile(outFileName.c_str());

  std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::string numbers = "1234567890";
  for(int i = 0; i < nlines; i++)
  {
    // DEFINE ARGUMENTS HERE
    std::string string_arg = "";
    string_arg = randomSet(alphabet,string_arg,10);

    std::string int_arg = "";
    int_arg = randomSet(numbers,int_arg,5);

    std::string float_arg_1 = "";
    std::string float_arg_2 = "";
    float_arg_1 = randomSet(numbers,float_arg_1,3);
    float_arg_2 = randomSet(numbers,float_arg_2,3);

    std::string float_arg = float_arg_1 + "." + float_arg_2;

    // OUTPUT ARGUMENTS HERE
    outFile << "\"" << string_arg << "\"" 
        << "\t" << int_arg << "\t" 
        << float_arg << "\t" 
        << "\"" << depositDirectory << "/" << string_arg << "_" << int_arg << ".txt" << "\"" << std::endl;
  }
  outFile.close();
	return 0;
}

std::string randomSet(const std::string& space, std::string& result, int length)
{
  int max = space.size() - 1;
  int min = 0;
  if (max == 0) return "ERROR";
  int index = randomNumber(min,max);
  if(result.size() == 0 && space[index] == '0')
  {
    while(space[index] == '0')
    {
      index = randomNumber(min,max);
    }
  }
  if( result.size() == length )
  {
    return result;
  }
  else
  {
    result = result + space[index];
    return randomSet(space, result, length);
  }
}

int randomNumber(int min, int max)
{
  return (min + (rand() % (int)(max - min + 1)));
}
