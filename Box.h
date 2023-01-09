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
    friend bool optimizeBoxesHelper(Box *current, Box *parent, std::vector<Box *> &allBoxes);
    friend std::vector<Box> boxesListCreate(const std::string &boxesList);
    friend std::vector<Box> boxesListCreateInternalBox(const std::string &boxesList);
};

Box::Box() {}

// Print function for box
void Box::printBox()
{
    std::cout << label << std::endl;
    std::cout << "Souvenirs: ";
    for (int i = 0; i < souvenirs.size(); i++)
    {
        std::cout << souvenirs[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Boxes: ";
    for (int i = 0; i < boxes.size(); i++)
    {
        std::cout << boxes[i]->label << " ";
    }
    std::cout << std::endl;
}

// Create list of boxes
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
        // create vector for internal boxes, but in this step only read label
        std::vector<Box *> internalBoxes;
        for (int k = 0; k < boxCount; k++)
        {
            std::string boxLabel;
            file >> boxLabel;
        }
        Box currentBox = Box(label, souvenirs, internalBoxes);
        allBoxes.push_back(currentBox);
    }
    file.close();

    return allBoxes;
}

// Function for create and add the inner boxes
std::vector<Box> boxesListCreateInternalBox(const std::string &boxesList)
{
    std::vector<Box> allBoxes = boxesListCreate(boxesList);
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

        Box *currentBox; // if it is an object after the loop it will not exist

        // Find the reference of the current box
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
            file >> souvenir;
        }
        file >> boxCount;
        for (int k = 0; k < boxCount; k++)
        {
            std::string boxLabel;
            file >> boxLabel;

            // In the vector of boxes of the current, add its inner boxes
            for (int m = 0; m < allBoxes.size(); m++)
            {
                if (boxLabel == allBoxes[m].label)
                {
                    currentBox->boxes.push_back(&allBoxes[m]);
                }
            }
        }
    }
    file.close();

    return allBoxes;
}

// Optimize specific box
bool optimizeBoxesHelper(Box *current, Box *parent, std::vector<Box *> &allBoxes)
{
    // if current box is empty and there are no souvenirs it should be removed, if there is we leave it
    if (current->boxes.empty())
    {
        if (current->souvenirs.empty())
        {
            return true;
        }
        return false;
    }

    std::vector<Box *> toDeleteBoxes;
    // Through the recursion we reach the inner box and if we find a box to be deleted we add it to the vector
    for (int i = 0; i < current->boxes.size(); ++i)
    {
        bool toDelete = optimizeBoxesHelper(current->boxes[i], current, allBoxes);
        if (toDelete)
        {
            toDeleteBoxes.push_back(current->boxes[i]);
        }
    }
    // delete unnecessary boxes from the vector containing the current boxes and vector with all boxes
    for (int j = 0; j < toDeleteBoxes.size(); ++j)
    {
        int index;
        for (int k = 0; k < current->boxes.size(); ++k)
        {
            if (toDeleteBoxes[j]->label == current->boxes[k]->label)
            {
                index = k;
            }
        }
        current->boxes.erase(current->boxes.begin() + index);

        for (int k = 0; k < allBoxes.size(); ++k)
        {
            if (toDeleteBoxes[j]->label == allBoxes[k]->label)
            {
                index = k;
            }
        }
        allBoxes.erase(allBoxes.begin() + index);
    }

    // Transfer the contents of the box to the parent if it is only one and has no souvenirs in it
    if (current->souvenirs.empty() && current->boxes.size() == 1 && parent)
    {
        parent->boxes.push_back(current->boxes[0]);
        return true;
    }
    return false;
}

// Optimize all boxes
void optimizeBoxes(std::vector<Box *> &allBoxes)
{
    for (int i = 0; i < allBoxes.size(); ++i)
    {
        optimizeBoxesHelper(allBoxes[i], nullptr, allBoxes);
    }
}

#endif