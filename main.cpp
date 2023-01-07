#include <iostream>
#include <string>
#include <vector>
#include "skipList.h"
#include "Box.h"
#include "MaxLandmarks.h"

int main()
{

    //a)
    //приема положително естествено число n
    size_t n;
    std::cout << "Брой на градовете през които преминава пътническия влак: ";
    std::cin >> n;

    //списък от n низа, съставени от малки и главни латински букви,
    //и представляващи имената на последователните градове, през които пътническият влак минава
    skipList<std::string> list;
    std::cout << "Имената на градовете: ";
    size_t count = 0;
    while(count < n)
    {
        std::string temp;
        std::cin >> temp;
        list.pushElementInList(temp);
        count++;
    }

    std::cout << "Директни връзки: ";
    std::string currentTown, skipTown;
    std::string terminatedSymbol = ".";
    while(true)
    {
        std::cin >> currentTown;
        if(currentTown == terminatedSymbol)
         {
            break;
         }
        std::cin >> skipTown;
      list.addSkipRelation(currentTown, skipTown);
    }

    std::vector<std::string> listOfTownsPriority;
    std::cout << "Списък на градовете на Аня и Ванката: ";
    std::string currentInput;
    while(std::cin >> currentInput)
    {
        listOfTownsPriority.push_back(currentInput);
    }
    std::cout << "----------------------------------" << std::endl;

    std::stack<std::string> pathReverse = list.shortestPathWithPriorityTowns(listOfTownsPriority);
    std::stack<std::string> path;
    while(!pathReverse.empty())
    {
        path.push(pathReverse.top());
        pathReverse.pop();
    }
    while(!path.empty())
    {
        std::cout << path.top() << ' ';
        path.pop();
    }
    std::cout << std::endl;
    std::cout << "----------------------------------" << std::endl;

    // в)
    std::vector<Box> boxes = boxesListCreate("boxesList.txt");
    std::vector<Box *> boxesPointers;
    for (int i = 0; i < boxes.size(); i++)
    {
        boxesPointers.push_back(&boxes[i]);
    }
    optimizeBoxes(boxesPointers);
    for (int j = 0; j < boxesPointers.size(); ++j)
    {
        boxesPointers[j]->printBox();
        std::cout << std::endl;
    }
    std::cout << "----------------------------------" << std::endl;

    // б)

    // City city = readCity("landmarks.txt");

    // std::vector<std::string> route = findRoute(city);

    // for(int i = 0; i < route.size(); i++)
    // {
    //     std::cout << route[i] << ' ';
    // }
    //  std::cout << std::endl;
    // std::cout << "----------------------------------" << std::endl;

    return 0;
}