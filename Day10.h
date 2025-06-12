#pragma once

#include "advent.hpp"

namespace Day10 {

	// Enum for different pipe types
	enum class PipeType {
		VERTICAL,      // | - connects north and south
		HORIZONTAL,    // - - connects east and west
		NORTH_EAST,    // L - connects north and east
		NORTH_WEST,    // J - connects north and west
		SOUTH_WEST,    // 7 - connects south and west
		SOUTH_EAST,    // F - connects south and east
		GROUND,        // . - no pipe
		START          // S - starting position
	};

	class Day10 {
	public:
		Day10(string path) : adv(path) {
			parseGrid();
		};

		int p1() {
			// TODO: Implement part 1 solution
			return 0;
		}

		int64_t p2() {
			// TODO: Implement part 2 solution
			return 0;
		}

		// Helper method to print the grid for debugging
		void printGrid() const {
			for (int row = 0; row < height; ++row) {
				for (int col = 0; col < width; ++col) {
					cout << pipeToChar(grid[row][col]);
				}
				cout << endl;
			}
		}

		// Get pipe type at specific coordinates
		PipeType getPipeAt(int row, int col) const {
			if (row < 0 || row >= height || col < 0 || col >= width) {
				return PipeType::GROUND;
			}
			return grid[row][col];
		}

		// Get the starting position
		pair<int, int> getStartPosition() const {
			return startPos;
		}

		// Get grid dimensions
		pair<int, int> getDimensions() const {
			return make_pair(height, width);
		}

		// Check if a pipe connects in a given direction
		// Directions: 0=North, 1=East, 2=South, 3=West
		bool connectsInDirection(PipeType pipe, int direction) const {
			switch (pipe) {
			case PipeType::VERTICAL:
				return direction == 0 || direction == 2; // North or South
			case PipeType::HORIZONTAL:
				return direction == 1 || direction == 3; // East or West
			case PipeType::NORTH_EAST:
				return direction == 0 || direction == 1; // North or East
			case PipeType::NORTH_WEST:
				return direction == 0 || direction == 3; // North or West
			case PipeType::SOUTH_WEST:
				return direction == 2 || direction == 3; // South or West
			case PipeType::SOUTH_EAST:
				return direction == 2 || direction == 1; // South or East
			case PipeType::GROUND:
				return false;
			case PipeType::START:
				return true; // We'll need to determine this later
			default:
				return false;
			}
		}

	private:
		advent adv;
		vector<vector<PipeType>> grid;
		int width, height;
		pair<int, int> startPos; // row, col of start position

		// Convert character to PipeType
		PipeType charToPipe(char c) const {
			switch (c) {
			case '|': return PipeType::VERTICAL;
			case '-': return PipeType::HORIZONTAL;
			case 'L': return PipeType::NORTH_EAST;
			case 'J': return PipeType::NORTH_WEST;
			case '7': return PipeType::SOUTH_WEST;
			case 'F': return PipeType::SOUTH_EAST;
			case '.': return PipeType::GROUND;
			case 'S': return PipeType::START;
			default: return PipeType::GROUND;
			}
		}

		// Convert PipeType back to character for debugging
		char pipeToChar(PipeType p) const {
			switch (p) {
			case PipeType::VERTICAL: return '|';
			case PipeType::HORIZONTAL: return '-';
			case PipeType::NORTH_EAST: return 'L';
			case PipeType::NORTH_WEST: return 'J';
			case PipeType::SOUTH_WEST: return '7';
			case PipeType::SOUTH_EAST: return 'F';
			case PipeType::GROUND: return '.';
			case PipeType::START: return 'S';
			default: return '?';
			}
		}

		// Parse the input grid
		void parseGrid() {
			if (adv.raw_vec.empty()) {
				return;
			}

			height = adv.raw_vec.size();
			width = adv.raw_vec[0].size();
			grid.resize(height, vector<PipeType>(width));

			for (int row = 0; row < height; ++row) {
				const string& line = adv.raw_vec[row];
				for (int col = 0; col < width && col < line.size(); ++col) {
					grid[row][col] = charToPipe(line[col]);
					if (grid[row][col] == PipeType::START) {
						startPos = make_pair(row, col);
					}
				}
			}
		}
	};
}
