#pragma once
#include <vector>

std::vector<unsigned char> getPerlinMap();
void addStartAndEnd(std::vector<unsigned char>& map);

bool verifyWinnable(std::vector<unsigned char> map);
bool recurse(std::vector<unsigned char>& map, int loc);
bool recurseHelper(std::vector<unsigned char>& map, bool isValidLoc, int var);

