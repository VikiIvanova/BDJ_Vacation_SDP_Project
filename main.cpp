#include <iostream>
#include <string>
#include <vector>
#include "skipList.h"

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

    

    //минавам по файла и създавам кутиите една по една само с label и сувенири
    // минавам втори път и гледам на например на кутия А със вложен цикъл къде е кутия B и я пушвам в кутия А
    //добавям си и празните кутии 
    //ако нямам сувенири и boxes и тях ги няма я премахвам
    // ако няма сувенири и има само една кутия сувенирите на тази стават на главната
    //кутия в която има една кутия

    return 0;
}