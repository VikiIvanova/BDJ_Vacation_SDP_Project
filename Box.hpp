#ifndef __BOX_HPP
#define __BOX_HPP

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class Box
{
private:
    std::vector<std::string> souvenirs;
    std::vector<Box> boxes;
    std::string label;

public:
    Box(std::string label, std::vector<std::string> souvenirs, std::vector<Box> boxes) : label(label), souvenirs(souvenirs), boxes(boxes) {}

    std::vector<Box> boxesListCreate(const std::string &boxesList);
    std::vector<Box> optimizeBoxes(const std::vector<Box> &boxes);
};

std::vector<Box> Box::boxesListCreate(const std::string &boxesList)
{
    std::vector<Box> boxes;
    std::ifstream file(boxesList);
    if (!file.is_open())
    {
        return boxes;
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
        std::vector<Box> boxes;
        for (int k = 0; k < boxCount; k++)
        {
            std::string boxLabel;
            file >> boxLabel;
            boxes.push_back(Box(boxLabel, {}, {}));
        }
        boxes.push_back(Box(label, souvenirs, boxes));
    }
    file.close();
    return boxes;
}

std::vector<Box> Box::optimizeBoxes(const std::vector<Box> &boxes)
{
    std::vector<Box> nonEmptyBoxes;
    for (const Box &box : boxes)
    {
        if (!box.souvenirs.empty() || !box.boxes.empty())
        {
            Box optimizedBox = Box(box.label, box.souvenirs, optimizeBoxes(box.boxes));
            nonEmptyBoxes.push_back(optimizedBox);
        }
    }
    return nonEmptyBoxes;
}

#endif