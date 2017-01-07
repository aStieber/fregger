#include "mapgen.h"
#include "fregger.h"
#include "PerlinNoise.h"

std::vector<unsigned char> getPerlinMap() {
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
	return(outputMap);
}

void addStartAndEnd(std::vector<unsigned char>& map) {
	//finish
	for (size_t i = 0; i < BOARD_WIDTH; i++) { map[i] = FINISH; }

	map[map.size() - 1 - (BOARD_WIDTH / 2)] = START;
}