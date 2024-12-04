#include <iostream>
#include <fstream>
#include <string>
#include <regex>
int main()
{
    std::ifstream file("input3.txt");
    std::string line;
    std::string checkPrefix;
    std::regex rgx("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    std::regex rgx_dont("don't\\(\\)");
    std::regex rgx_doit("do\\(\\)");
    double answer_p1 = 0;
    double answer_p2 = 0;
    bool enabled = true;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::smatch m;
            std::smatch m_doit;
            std::smatch m_dont;
            while(std::regex_search(line, m, rgx)){
                checkPrefix = m.prefix().str();
                std::regex_search(checkPrefix, m_doit, rgx_doit);
                std::regex_search(checkPrefix, m_dont, rgx_dont);
                if (m_doit[0] == "" && m_dont[0] != "") enabled = false;
                else if (m_doit[0] != "" && m_dont[0] == "") enabled = true;
                else {
                    if (m_doit.suffix().str().size() > m_dont.suffix().str().size()) enabled = false;
                    else if (m_dont.suffix().str().size() > m_doit.prefix().str().size()) enabled = true;
                }
                if (enabled) answer_p2 += (std::stoi(m[1]) * std::stoi(m[2]));
                answer_p1 += (std::stoi(m[1]) * std::stoi(m[2]));
                line = m.suffix().str();
            }
        }
        file.close();
    }
    std::cout << static_cast<int>(answer_p1) << std::endl;
    std::cout << static_cast<int>(answer_p2) << std::endl;
    return 0;
}