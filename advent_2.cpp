#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

static int maxDifference = 3;

bool p1(std::vector<int> int_comparer){
    bool isSafe = true;
    std::optional<bool> slopeIncreasing;
    for (size_t i = 1; i < int_comparer.size(); i++){
        int diff = int_comparer[i-1] - int_comparer[i];
        if (diff > 0 && diff <= maxDifference && (!slopeIncreasing.has_value() || slopeIncreasing == true)) slopeIncreasing = true;
        else if (diff < 0 && diff >= -maxDifference && (!slopeIncreasing.has_value() || slopeIncreasing == false)) slopeIncreasing = false;
        else {isSafe = false; return isSafe;}
    }
    return isSafe;
}

bool p2(std::vector<int> int_comparer){
    if (p1(int_comparer)) return true;
    for (size_t i = 0; i < int_comparer.size(); i++){
        std::vector<int> check_comparer = int_comparer;
        check_comparer.erase(check_comparer.begin()+i);
        if (p1(check_comparer)) return true;
    }
    return false;
}

int main()
{
    std::ifstream file("input2.txt");
    std::string line;
    int answer_p1 = 0;
    int answer_p2 = 0;
    std::string int_holder;
    std::vector<int> int_comparer;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            for (size_t i = 0; i < line.length(); i++){
                if (line[i] != ' ') int_holder.push_back(line[i]);
                else {
                    int_comparer.push_back(std::stoi(int_holder));
                    int_holder.clear();
                }
            }
            int_comparer.push_back(std::stoi(int_holder));
            int_holder.clear();
            if (p1(int_comparer)) answer_p1++;
            if (p2(int_comparer)) answer_p2++;
            int_comparer.clear();
        }
        file.close();
    }
    std::cout << static_cast<int>(answer_p1) << std::endl;
    std::cout << static_cast<int>(answer_p2) << std::endl;
}