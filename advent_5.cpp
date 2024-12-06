#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>

#include <algorithm>
#include <set>

int main()
{
    std::ifstream file("input5.txt");
    std::string line;
    std::string int_holder;
    std::vector<int> page_order;
    std::unordered_map<int, std::vector<int>> placement_key;
    std::regex rgx("^(\\d*)\\|(\\d*)");
    std::pair<int, int> page_holder = {0, 0};
    bool correct_pos = true;
    int answer_p1 = 0;
    int answer_p2 = 0;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::smatch m;
            if(std::regex_match(line, m, rgx)){
                page_holder.first = std::stoi(m[1]);
                page_holder.second = std::stoi(m[2]);
                if (placement_key.find(page_holder.first) != placement_key.end()) placement_key[page_holder.first].push_back(page_holder.second);
                else placement_key.insert({page_holder.first, {page_holder.second}});
            }
            if (line.empty()) break;
        }
        while (std::getline(file, line)) {
            std::vector<int> update_page;
            correct_pos = true;
            for (int i = 0; i < line.length(); i++){
                if (line[i] != ',') int_holder.push_back(line[i]);
                else {
                    update_page.push_back(std::stoi(int_holder));
                    int_holder.clear();
                }
            }
            update_page.push_back(std::stoi(int_holder));
            std::vector<int> update_page_p2 = update_page;
            int i = update_page.size() - 1;
            while (i > 1 && correct_pos == true) {
                for (int j = i - 1; j > 0; j--) {
                    if (std::find(placement_key[update_page[i]].begin(), placement_key[update_page[i]].end(), update_page[j]) != placement_key[update_page[i]].end()) {
                        correct_pos = false;
                    }
                }
                i--;
            }
            if (!correct_pos) {
                for (int i = update_page_p2.size() - 1; i > 1; i--) {
                    for (int j = i - 1; j > 0; j--) {
                        std::vector<int>::iterator ele = std::find(placement_key[update_page_p2[i]].begin(), placement_key[update_page_p2[i]].end(), update_page_p2[j]);
                        if (ele != placement_key[update_page_p2[i]].end()) {
                            correct_pos = false;
                            //std::cout << *ele << std::endl;
                        }
                    }
                }
                answer_p2 += update_page_p2[(update_page_p2.size()/2)];
            }
            if (correct_pos) answer_p1 += update_page[(update_page.size()/2)];
            int_holder.clear();
        }
        file.close();
    }
    std::cout << answer_p1 << std::endl;
    std::cout << answer_p2 << std::endl;
    return 0;
}