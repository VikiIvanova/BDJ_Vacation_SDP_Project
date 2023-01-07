#ifndef __BOX_H
#define __BOX_H

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>

class Box
{
private:
    std::vector<std::string> souvenirs;
    std::vector<Box *> boxes;
    std::string label;

public:
    Box();
    Box(std::string label, std::vector<std::string> souvenirs, std::vector<Box *> boxes) : label(label), souvenirs(souvenirs), boxes(boxes) {}
    void printBox();
    friend void optimizeBoxes(std::vector<Box *> &boxes);
    friend bool optimizeBoxesHelper(Box* current, Box* parent, std::vector<Box *> &allBoxes);
    friend std::vector<Box> boxesListCreate(const std::string &boxesList);
};

Box::Box() {}

void Box::printBox()
{
    std::cout << label << std::endl;
    std::cout << "souvenirs: ";
    for (int i = 0; i < souvenirs.size(); i++)
    {
        std::cout << souvenirs[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "boxes: ";
    for (int i = 0; i < boxes.size(); i++)
    {
        std::cout << boxes[i]->label << " ";
    }
    std::cout << std::endl;
}

std::vector<Box> boxesListCreate(const std::string &boxesList)
{
    std::vector<Box> allBoxes;
    std::ifstream file(boxesList);
    if (!file.is_open())
    {
        return allBoxes;
    }

    int numBoxes;
    file >> numBoxes;
    for (int i = 0; i < numBoxes; i++)
    {
        std::string label;
        int souvenirCount, boxCount;
        file >> label >> souvenirCount;
        std::vector<std::string> souvenirs;
        for (int j = 0; j < souvenirCount; j++)
        {
            std::string souvenir;
            file >> souvenir;
            souvenirs.push_back(souvenir);
        }
        file >> boxCount;
        std::vector<Box *> internalBoxes;
        for (int k = 0; k < boxCount; k++)
        {
            std::string boxLabel; // тук четем само какъв е етикета за всяка вътрешна кутия и продължаваме, вътрешните прзни ли са?
            file >> boxLabel;
        }
        Box currentBox = Box(label, souvenirs, internalBoxes);
        allBoxes.push_back(currentBox);
    }
    file.close();

    std::ifstream file2(boxesList);
    if (!file2.is_open())
    {
        return allBoxes;
    }

    file2 >> numBoxes;
    for (int i = 0; i < numBoxes; i++)
    {
        std::string label;
        int souvenirCount, boxCount;
        file2 >> label >> souvenirCount;

        Box* currentBox; // указател е, за да не правим нов обект, на който референция е някъде другаде и след цикъла този обект не съществува
        for (int b = 0; b < allBoxes.size(); b++)
        {
            if (label == allBoxes[b].label)
            {
                currentBox = &allBoxes[b];
            }
        }
        for (int j = 0; j < souvenirCount; j++)
        {
            std::string souvenir;
            file2 >> souvenir;
        }
        file2 >> boxCount;
        for (int k = 0; k < boxCount; k++)
        {
            std::string boxLabel;
            file2 >> boxLabel;

            for (int m = 0; m < allBoxes.size(); m++) //за да можем да го вземем по референция
            {
                if (boxLabel == allBoxes[m].label)
                {       
                    currentBox->boxes.push_back(&allBoxes[m]);
                }
            }
        }
    }
    file2.close();

    return allBoxes;
}

bool optimizeBoxesHelper(Box* current, Box* parent, std::vector<Box *> &allBoxes)
{
    if(current->boxes.empty())
    {
        if(current->souvenirs.empty())
        {
            return true;
        }
        return false;
    }

    std::vector<Box *> toDeleteBoxes;
    for (int i = 0; i < current->boxes.size(); ++i)
    {
        bool toDelete = optimizeBoxesHelper(current->boxes[i], current, allBoxes);
        if (toDelete)
        {
            toDeleteBoxes.push_back(current->boxes[i]);
           
        }
    }
    //трием - махаме bags,...
    for(int j = 0; j < toDeleteBoxes.size(); ++j)
    {
        int index;
        for(int k = 0; k < current->boxes.size(); ++k)
        {
            if(toDeleteBoxes[j]->label == current->boxes[k]->label)
            {
                index = k;
            }
        }
        current->boxes.erase(current->boxes.begin() + index);

        for(int k = 0; k < allBoxes.size(); ++k)
        {
            if(toDeleteBoxes[j]->label == allBoxes[k]->label)
            {
                index = k;
            }
        }
        allBoxes.erase(allBoxes.begin() + index);
    }

    // да се освободят всички кутийки в deleteBoxes като памет

    //прехвърляме съдържанието на кутията в родителя, ако е само една и няма сувенири в нея
    if(current->souvenirs.empty() && current->boxes.size() == 1 && parent)
    {
         parent->boxes.push_back(current->boxes[0]);
         return true;
    }
    return false;
}

void optimizeBoxes(std::vector<Box*>& allBoxes)
{
    for(int i = 0; i < allBoxes.size(); ++i)
    {
        optimizeBoxesHelper(allBoxes[i], nullptr, allBoxes);
    }
}

#endif