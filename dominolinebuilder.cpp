#include "dominolinebuilder.h"
#include <unordered_map>
std::unordered_map<std::string, Domino*> dominoMap;
Domino::Domino(std::string theBlueSymbol, std::string theRedSymbol)
{
   blueSymbol = theBlueSymbol;
   redSymbol = theRedSymbol;
}

DominoLineBuilder::DominoLineBuilder(unsigned long int totalNumberOfDominoes, std::istream& dominoInputData)
{
   for (unsigned long int i = 0; i < totalNumberOfDominoes; ++i)
   {
      std::string aBlueSymbol, aRedSymbol;
      std::getline(dominoInputData, aBlueSymbol, ':');
      std::getline(dominoInputData, aRedSymbol, '\n');

      Domino* newDomino = new Domino(aBlueSymbol, aRedSymbol);
      newDomino->previous = lastDisorderedDomino;
      lastDisorderedDomino = newDomino;

      // Populate the map for quick lookup
      dominoMap[aBlueSymbol] = newDomino;
   }
}




bool DominoLineBuilder::nextRight()
{
   if (orderedLine.empty())
   {
      if (lastDisorderedDomino == nullptr) {
         return false;
      }

      Domino* startingDomino = lastDisorderedDomino;
      orderedLine.push_back(*startingDomino);

      // Remove the starting domino from the map
      dominoMap.erase(startingDomino->blueSymbol);

      lastDisorderedDomino = lastDisorderedDomino->previous;
      delete startingDomino;
      return true;
   }

   std::string requiredBlueSymbol = orderedLine.back().redSymbol;

   // Check if a matching domino exists in the map
   auto it = dominoMap.find(requiredBlueSymbol);
   if (it != dominoMap.end())
   {
      Domino* matchingDomino = it->second;

      // Add the matching domino to the ordered line
      orderedLine.push_back(*matchingDomino);

      // Remove the matching domino from the map
      dominoMap.erase(it);

      // Adjust the linked list of disordered dominos
      if (matchingDomino == lastDisorderedDomino) {
         lastDisorderedDomino = matchingDomino->previous;
      } else {
         // Update the `previous` pointer of the domino before the matching one
         for (Domino* currentDomino = lastDisorderedDomino; currentDomino != nullptr; currentDomino = currentDomino->previous)
         {
            if (currentDomino->previous == matchingDomino)
            {
               currentDomino->previous = matchingDomino->previous;
               break;
            }
         }
      }

      delete matchingDomino;
      return true;
   }

   return false;
}
void DominoLineBuilder::displayLine(std::ostream& outputStream)
{
   for (Domino eachDomino : orderedLine)
   {
      outputStream << eachDomino.blueSymbol << ':' << eachDomino.redSymbol << ' ';
   }
}

DominoLineBuilder::~DominoLineBuilder()
{
   Domino* currentDomino = lastDisorderedDomino;
   while (currentDomino != nullptr)
   {
      Domino* dominoToDelete = currentDomino;
      currentDomino = currentDomino->previous;
      delete dominoToDelete;
   }
}
