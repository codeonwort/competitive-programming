// https://www.acmicpc.net/problem/14500

#include <iostream>
#include <stdint.h>

struct Mask {
	int flags[4][4];
};

const Mask masks[] = {
	{{ // type 1
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 }
	}},
	{{ // type 2
		{ 1, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{ // type 3
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 1, 1, 1, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 1, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 0, 0, 1, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 1, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 1, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 1, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{ // type 4
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 1, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{ // type 5
		{ 1, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 0, 1, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	{{
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
};
const int numMasks = sizeof(masks) / sizeof(masks[0]);

#define MAX_ROWS 500
#define MAX_COLS 500

int table[MAX_ROWS][MAX_COLS];
int rows, cols;

int64_t evaluateMask(int y0, int x0, const Mask& mask) {
	int64_t sum = 0;

	for (int dy = 0; dy < 4; ++dy) {
		for (int dx = 0; dx < 4; ++dx) {
			int y = y0 + dy, x = x0 + dx;
			bool yOut = (y >= rows && mask.flags[dy][dx] != 0);
			bool xOut = (x >= cols && mask.flags[dy][dx] != 0);
			if (yOut || xOut) {
				// Invalid attempt
				sum = 0;
				break;
			}
			sum += table[y][x] * mask.flags[dy][dx];
		}
	}

	return sum;
}

int64_t findMax(int y0, int x0) {
	int64_t maxValue = 0;
	
	for (int maskIx = 0; maskIx < numMasks; ++maskIx) {
		int64_t val = evaluateMask(y0, x0, masks[maskIx]);
		if (maxValue < val) maxValue = val;
	}

	return maxValue;
}

int main() {
	// 1. Read input
	std::cin >> rows >> cols;
	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			std::cin >> table[y][x];
		}
	}

	// 2. Find max
	int64_t answer = 0;
	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			int64_t soln = findMax(y, x);
			if (answer < soln) answer = soln;
		}
	}

	// 3. Print
	std::cout << answer << std::endl;

	return 0;
}
