#include <iostream>
#include <fstream>
#include <string>
#include <vector>

static std::vector<std::pair<int, int>> directionMove = {
    {-1,1},
    {0,1},
    {1,1},
    {1,0},
    {1,-1},
    {0,-1},
    {-1,-1},
    {-1,0},
};

int check_puzzle(std::vector<std::string> puzzleMap, int y, int x){
    int total = 0;
    for (int direction = 0; direction < 8; direction++){
        int dir_y = directionMove[direction].first;
        int dir_x = directionMove[direction].second;
        //Checking bounds
        if ((y + dir_y*3 >= 0 && y + dir_y*3 < puzzleMap.size()) && (x + dir_x*3 >= 0 && x + dir_x*3 < puzzleMap[0].size()))
            if (puzzleMap[y + dir_y*3][x + dir_x*3] == 'S' && puzzleMap[y + dir_y*2][x + dir_x*2] == 'A' && puzzleMap[y + dir_y][x + dir_x] == 'M') total+=1;
    }
    return total;
}

int main()
{
    std::ifstream file("input4.txt");
    std::string line;
    std::vector<std::string> puzzleMap;
    int answer_p1 = 0;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            puzzleMap.push_back(line);
        }
        file.close();
    }

    for (int y = 0; y < puzzleMap.size(); y++){
        for (int x = 0; x < puzzleMap[0].size(); x++){
            if (puzzleMap[y][x] == 'X') answer_p1 += check_puzzle(puzzleMap, y, x);
        }
    }
    std::cout << answer_p1 << std::endl;
    return 0;
}