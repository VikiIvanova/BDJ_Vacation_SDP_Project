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
    std::cout << "Изпечатва всички градове: ";
    list.printSkipList();
    std::cout << std::endl;
    std::cout << "Изпечатва директните връзки: ";
    list.printSkipping();

    std::cout << "Изпечатва градовете, през които иска да преминат Аня и Ванката: ";
    for(std::string i : listOfTownsPriority)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    

    return 0;
}