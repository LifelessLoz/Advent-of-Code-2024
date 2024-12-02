#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

int main()
{
    std::ifstream file("input1.txt");
    std::string line;
    std::vector<long> left_list;
    std::vector<long> right_list;
    std::regex rgx("^(\\d*)\\s*(\\d*)");

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::smatch m;
            if(std::regex_match(line, m, rgx)){
                left_list.push_back(std::stoi(m[1]));
                right_list.push_back(std::stoi(m[2]));
            }
        }
        file.close();
    }

    std::sort(left_list.begin(), left_list.end());
    std::sort(right_list.begin(), right_list.end());

    long answer_p1 = 0;
    for (int i = 0; i < left_list.size(); i++)
    {
        answer_p1 += abs(left_list[i] - right_list[i]);
    }

    std::cout << answer_p1 << std::endl;

    long answer_p2 = 0;
    for (int i : left_list) {
        answer_p2 += i * std::count(right_list.begin(), right_list.end(), i);
    }

    std::cout << answer_p2 << std::endl;

    return 0;
}