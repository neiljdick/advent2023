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
			return findFarthestDistance();
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

		// Debug method to show valid start directions
		void debugStartConnections() const {
			auto dirs = getValidStartDirections();
			cout << "Checking connections from start (" << startPos.first << ", " << startPos.second << "):" << endl;
			
			string dirNames[] = {"North", "East", "South", "West"};
			for (int dir = 0; dir < 4; ++dir) {
				auto nextPos = getNextPosition(startPos.first, startPos.second, dir);
				PipeType nextPipe = getPipeAt(nextPos.first, nextPos.second);
				int oppositeDir = getOppositeDirection(dir);
				bool connects = connectsInDirection(nextPipe, oppositeDir);
				
				cout << "  " << dirNames[dir] << " -> (" << nextPos.first << ", " << nextPos.second 
				     << ") has '" << pipeToChar(nextPipe) << "' connects back: " << connects << endl;
			}
			
			cout << "Valid start directions: ";
			for (int dir : dirs) {
				cout << dirNames[dir] << " ";
			}
			cout << endl;
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

		// Get the next position when moving in a direction
		pair<int, int> getNextPosition(int row, int col, int direction) const {
			switch (direction) {
			case 0: return make_pair(row - 1, col); // North
			case 1: return make_pair(row, col + 1); // East
			case 2: return make_pair(row + 1, col); // South
			case 3: return make_pair(row, col - 1); // West
			default: return make_pair(row, col);
			}
		}

		// Get the opposite direction
		int getOppositeDirection(int direction) const {
			return (direction + 2) % 4;
		}

		// Find valid directions from the starting position
		vector<int> getValidStartDirections() const {
			vector<int> validDirs;
			int startRow = startPos.first;
			int startCol = startPos.second;

			// Check each direction
			for (int dir = 0; dir < 4; ++dir) {
				auto nextPos = getNextPosition(startRow, startCol, dir);
				PipeType nextPipe = getPipeAt(nextPos.first, nextPos.second);
				
				// Check if the adjacent pipe connects back to us
				int oppositeDir = getOppositeDirection(dir);
				if (connectsInDirection(nextPipe, oppositeDir)) {
					validDirs.push_back(dir);
				}
			}
			return validDirs;
		}

		// Find the farthest distance in the loop
		int findFarthestDistance() const {
			vector<int> startDirs = getValidStartDirections();
			if (startDirs.size() != 2) {
				return 0; // Should have exactly 2 connections for a valid loop
			}

			// Follow the loop in one direction and count steps
			int currentRow = startPos.first;
			int currentCol = startPos.second;
			int currentDir = startDirs[0];
			int steps = 0;

			// Follow the loop until we return to start
			do {
				// Move to next position
				auto nextPos = getNextPosition(currentRow, currentCol, currentDir);
				currentRow = nextPos.first;
				currentCol = nextPos.second;
				steps++;

				// If we're back at start, we've completed the loop
				if (currentRow == startPos.first && currentCol == startPos.second) {
					break;
				}

				// Find the next direction (the pipe has two connections, go the opposite way from where we came)
				PipeType currentPipe = getPipeAt(currentRow, currentCol);
				int oppositeOfCurrent = getOppositeDirection(currentDir);
				
				// Find the other direction this pipe connects to
				for (int newDir = 0; newDir < 4; ++newDir) {
					if (newDir != oppositeOfCurrent && connectsInDirection(currentPipe, newDir)) {
						currentDir = newDir;
						break;
					}
				}

			} while (steps < 10000); // Safety limit

			// The farthest point is half the loop length
			return steps / 2;
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
