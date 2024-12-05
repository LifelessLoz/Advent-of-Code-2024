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
    int dir_y = 0;
    int dir_x = 0;
    for (int direction = 0; direction < 8; direction++){
        dir_y = directionMove[direction].first;
        dir_x = directionMove[direction].second;
        //Checking bounds
        if ((y + dir_y*3 >= 0 && y + dir_y*3 < puzzleMap.size()) && (x + dir_x*3 >= 0 && x + dir_x*3 < puzzleMap[0].size()))
            if (puzzleMap[y + dir_y*3][x + dir_x*3] == 'S' && puzzleMap[y + dir_y*2][x + dir_x*2] == 'A' && puzzleMap[y + dir_y][x + dir_x] == 'M') total+=1;
    }
    return total;
}
// Boo Hiss this way is ugly
/*
int check_puzzle_pt2(std::vector<std::string> puzzleMap, int y, int x){
    int total2 = 0;
    int dir_y2 = 0;
    int dir_x2 = 0;
    int dir_y_opp = 0;
    int dir_x_opp = 0;
    for (int direction = 0; direction < 4; direction += 2){
        dir_y2 = directionMove[direction].first;
        dir_x2 = directionMove[direction].second;
        dir_y_opp = directionMove[direction + 4].first;
        dir_x_opp = directionMove[direction + 4].second;
        if ((puzzleMap[y + dir_y2][x + dir_x2] == 'S' && puzzleMap[y + dir_y_opp][x + dir_x_opp] == 'M') || 
            (puzzleMap[y + dir_y2][x + dir_x2] == 'M' && puzzleMap[y + dir_y_opp][x + dir_x_opp] == 'S')) total2++;
        else break;
    }
    if (total2 == 2) return 1;
    return 0;
}
*/
// Prefer this way of doing it but left old one in
int check_puzzle_p2(std::vector<std::string> puzzleMap, int y, int x){
    std::string mas = "";
    for (int i = 0; i < 7; i += 2) {
        if (puzzleMap[y + directionMove[i].first][x + directionMove[i].second] == 'X' || puzzleMap[y + directionMove[i].first][x + directionMove[i].second] == 'A') return 0;
        mas += puzzleMap[y + directionMove[i].first][x + directionMove[i].second];
    }
    if (mas[0] != mas[2] && mas[1] != mas[3]) return 1;
    return 0;
}

int main()
{
    std::ifstream file("input4.txt");
    std::string line;
    std::vector<std::string> puzzleMap;
    int answer_p1 = 0;
    int answer_p2 = 0;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            puzzleMap.push_back(line);
        }
        file.close();
    }
    //Part 1
    for (int y = 0; y < puzzleMap.size(); y++){
        for (int x = 0; x < puzzleMap[0].size(); x++){
            if (puzzleMap[y][x] == 'X') answer_p1 += check_puzzle(puzzleMap, y, x);
        }
    }
    //Part 2
    for (int y = 1; y < puzzleMap.size()-1; y++){
        for (int x = 1; x < puzzleMap[0].size()-1; x++){
            if (puzzleMap[y][x] == 'A') answer_p2 += check_puzzle_p2(puzzleMap, y, x);
        }
    }
    std::cout << answer_p1 << std::endl;
    std::cout << answer_p2 << std::endl;
    return 0;
}