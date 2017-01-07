#pragma once
#include <vector>

std::vector<unsigned char> getPerlinMap();
void addStartAndEnd(std::vector<unsigned char>& map);

class node {
public:
	node(int n=-1);
	int cellNum;

private:

};


bool verifyWinnable(std::vector<unsigned char> map);
bool recurse(std::vector<unsigned char>& map, int loc);

