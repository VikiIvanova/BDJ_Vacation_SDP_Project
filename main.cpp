#include <iostream>
#include <string>
#include <vector>

int main()
{
    //a)
    //приема положително естествено число n 
    size_t n;
    std::cout << "Брой на градовете през които преминава пътническия влак: ";
    std::cin >> n;

    //списък от n низа, съставени от малки и главни латински букви, 
    //и представляващи имената на последователните градове, през които пътническият влак минава
    std::vector<std::string> listOfTown;
    std::cout << "Имената на градовете: ";
    size_t count = 0;
    while(count < n)
    {
        std::string temp;
        std::cin >> temp;
        listOfTown.push_back(temp);
        count++;
    }

    //изпечатваме градовете от списъка
    for(std::string i : listOfTown)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;


    return 0;
}