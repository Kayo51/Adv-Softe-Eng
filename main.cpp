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

 steady_clock::time_point startTime = steady_clock::now();
   const unsigned long int datasetSize = 10;
   const std::string filepath = "dominoes-test_data/10/10-input.txt";

   std::ifstream theInputStream(filepath);
   if (! theInputStream.good()) throw std::invalid_argument("Cannot read from specified file.");


   DominoLineBuilder theDominoLine(datasetSize,theInputStream);



    theDominoLine.nextRight();
    //
     theDominoLine.nextRight();
    //

     while (theDominoLine.nextRight());


   theDominoLine.displayLine(std::cout);
 steady_clock::time_point finishTime = steady_clock::now();

 nanoseconds timeTaken = duration_cast<nanoseconds>(finishTime - startTime);



   std::cout <<"\nTime taken : " << timeTaken.count() << std::endl;
}
