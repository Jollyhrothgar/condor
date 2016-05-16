#include <fstream>
#include <iostream>

void Test_Condor(std::string arg1, int arg2, double arg3, std::string outFileName)
{
  std::cout << "Processing arguments: " << arg1 << ", " << arg2 << ", " << arg3 << std::endl;
  std::cout << "Sending output to : " << outFileName << std::endl;
  std::ofstream outFile(outFileName.c_str());
  for(int i = 0; i < arg2; i++)
  {
    outFile << arg3 << " is a number that characterizes" << arg1 << std::endl;
  }
  outFile.close();
}
