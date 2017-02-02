#include "mapgen.h"
#include "fregger.h"
#include "PerlinNoise.h"

std::vector<unsigned char> getPerlinMap() {
	while (true) {
		unsigned int seed = time(NULL) + (rand() % 999);
		PerlinNoise pn(seed);

		std::vector<double> doubleMap(BOARD_HEIGHT * BOARD_WIDTH, NULL);

		unsigned int kk = 0;
		double sum = 0;
		for (size_t i = 0; i < BOARD_HEIGHT; i++) {
			for (size_t j = 0; j < BOARD_WIDTH; j++) {
				double x = (double)j / (double)BOARD_WIDTH;
				double y = (double)i / (double)BOARD_HEIGHT;

				//tweaks
				double n = 15 * pn.noise(x, y, .6);

				n -= floor(n);
				doubleMap[kk] = n;

				//take average of all values, then compare
				sum += n;
				kk++;
			}
		}

		double Average = sum / (double)(kk);
		double LandModified = Average * 1.3;

		std::vector<unsigned char> outputMap(BOARD_HEIGHT * BOARD_WIDTH, NULL);
		for (size_t m = 0; m < kk; m++) { outputMap[m] = doubleMap[m] > LandModified; }

		//return(outputMap);
		addStartAndEnd(outputMap);
		if (verifyWinnable(outputMap)) {
			return(outputMap);
		}

	}

}

void addStartAndEnd(std::vector<unsigned char>& map) {
	//finish
	for (size_t i = 0; i < BOARD_WIDTH; i++) { map[i] = FINISH; }

	map[map.size() - 1 - (BOARD_WIDTH / 2)] = START;
}

bool verifyWinnable(std::vector<unsigned char> map) {
	int start = map.size() - 1 - (BOARD_WIDTH / 2);
	return (recurse(map, start));
}

bool recurse(std::vector<unsigned char>& map, int loc) {

	unsigned short liberties = 0; //go reference

	//if up is valid
	int var = loc - BOARD_WIDTH;
	liberties += recurseHelper(map, (loc >= BOARD_HEIGHT), var);
	//if left
	var = loc - 1;
	liberties += recurseHelper(map, (loc % BOARD_WIDTH), var);
	//if right
	var = loc + 1;
	liberties += recurseHelper(map, (var % BOARD_WIDTH), var);
	//if down
	var = loc + BOARD_WIDTH;
	liberties += recurseHelper(map, (loc < (BOARD_HEIGHT * (BOARD_WIDTH - 1))), var);

	return((bool)liberties);
}

bool recurseHelper(std::vector<unsigned char>& map, bool isValidLoc, int var) {
	if (isValidLoc) {
		if (map[var] == FINISH) { return(true); }

		if (map[var] != WATER && map[var] != VISITED) {
			map[var] = VISITED;
			return(recurse(map, var));
		}
	}
	return(false);
}