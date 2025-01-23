#include <iostream>
#include <fstream>
#include <string>

#include "dominolinebuilder.h"

using std::chrono::steady_clock;
using std::chrono::milliseconds;
// using std::chrono::microseconds;
 using std::chrono::nanoseconds;
using std::chrono::duration_cast;

int main()
{


   const unsigned long int datasetSize = 60000;
   const std::string filepath = "dominoes-test_data/60000/60000-input.txt";

   std::ifstream theInputStream(filepath);
   if (! theInputStream.good()) throw std::invalid_argument("Cannot read from specified file.");

    steady_clock::time_point startTime = steady_clock::now();
   DominoLineBuilder theDominoLine(datasetSize,theInputStream);
 steady_clock::time_point finishTime = steady_clock::now();

 nanoseconds timeTaken = duration_cast<nanoseconds>(finishTime - startTime);




     // theDominoLine.nextRight();
     //
     //  theDominoLine.nextRight();

    //
    //  while (theDominoLine.nextRight());


   theDominoLine.displayLine(std::cout);



   std::cout <<"\nTime taken : " << timeTaken.count() << std::endl;
}
