#pragma once

#include "advent.hpp"
#include <stdexcept>

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
			return findEnclosedTiles();
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
			if (startDirs.size() == 0) {
				throw runtime_error("No valid connections found from starting position. Check input data.");
			}
			if (startDirs.size() == 1) {
				throw runtime_error("Only one connection found from starting position. A valid loop requires exactly 2 connections.");
			}
			if (startDirs.size() > 2) {
				throw runtime_error("More than 2 connections found from starting position. This creates an ambiguous path.");
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

			} while (steps < 1000000); // Safety limit for very large inputs

			// Check if we hit the safety limit without completing the loop
			if (steps >= 1000000) {
				ostringstream errorMsg;
				errorMsg << "Safety limit reached: loop traversal exceeded 1,000,000 steps. "
				         << "Current position: (" << currentRow << ", " << currentCol << "). "
				         << "This suggests an infinite loop or corrupted input data.";
				throw runtime_error(errorMsg.str());
			}

			// The farthest point is half the loop length
			return steps / 2;
		}

		// Get all tiles that are part of the main loop
		set<pair<int, int>> getLoopTiles() const {
			set<pair<int, int>> loopTiles;
			vector<int> startDirs = getValidStartDirections();
			if (startDirs.size() != 2) {
				return loopTiles; // Invalid loop
			}

			// Add start position
			loopTiles.insert(startPos);

			// Follow the loop and mark all tiles
			int currentRow = startPos.first;
			int currentCol = startPos.second;
			int currentDir = startDirs[0];
			int steps = 0;

			do {
				// Move to next position
				auto nextPos = getNextPosition(currentRow, currentCol, currentDir);
				currentRow = nextPos.first;
				currentCol = nextPos.second;
				steps++;

				// Add to loop tiles
				loopTiles.insert(make_pair(currentRow, currentCol));

				// If we're back at start, we've completed the loop
				if (currentRow == startPos.first && currentCol == startPos.second) {
					break;
				}

				// Find the next direction
				PipeType currentPipe = getPipeAt(currentRow, currentCol);
				int oppositeOfCurrent = getOppositeDirection(currentDir);
				
				for (int newDir = 0; newDir < 4; ++newDir) {
					if (newDir != oppositeOfCurrent && connectsInDirection(currentPipe, newDir)) {
						currentDir = newDir;
						break;
					}
				}

			} while (steps < 1000000);

			return loopTiles;
		}

		// Determine what type of pipe S actually represents
		PipeType determineStartPipeType() const {
			vector<int> startDirs = getValidStartDirections();
			if (startDirs.size() != 2) return PipeType::GROUND;

			// Sort directions to make comparison easier
			sort(startDirs.begin(), startDirs.end());

			// Check all combinations
			if (startDirs[0] == 0 && startDirs[1] == 1) return PipeType::NORTH_EAST; // North + East = L
			if (startDirs[0] == 0 && startDirs[1] == 2) return PipeType::VERTICAL;   // North + South = |
			if (startDirs[0] == 0 && startDirs[1] == 3) return PipeType::NORTH_WEST; // North + West = J
			if (startDirs[0] == 1 && startDirs[1] == 2) return PipeType::SOUTH_EAST; // East + South = F
			if (startDirs[0] == 1 && startDirs[1] == 3) return PipeType::HORIZONTAL; // East + West = -
			if (startDirs[0] == 2 && startDirs[1] == 3) return PipeType::SOUTH_WEST; // South + West = 7

			return PipeType::GROUND;
		}

		// Count enclosed tiles using ray casting
		int64_t findEnclosedTiles() const {
			set<pair<int, int>> loopTiles = getLoopTiles();
			PipeType startPipeType = determineStartPipeType();
			int64_t enclosedCount = 0;

			// For each tile in the grid
			for (int row = 0; row < height; ++row) {
				for (int col = 0; col < width; ++col) {
					pair<int, int> pos = make_pair(row, col);
					
					// Skip if this tile is part of the loop
					if (loopTiles.count(pos)) continue;

					// Cast ray to the right and count crossings
					int crossings = 0;
					bool onBoundary = false;
					char lastCorner = '\0';

					for (int checkCol = col + 1; checkCol < width; ++checkCol) {
						pair<int, int> checkPos = make_pair(row, checkCol);
						
						// Only count if it's part of the loop
						if (!loopTiles.count(checkPos)) continue;

						PipeType pipe = getPipeAt(row, checkCol);
						
						// Handle start position
						if (pipe == PipeType::START) {
							pipe = startPipeType;
						}

						char pipeChar = pipeToChar(pipe);

						// Count crossings based on pipe type
						if (pipeChar == '|') {
							crossings++;
						} else if (pipeChar == 'F' || pipeChar == 'L') {
							lastCorner = pipeChar;
						} else if (pipeChar == '7') {
							if (lastCorner == 'L') crossings++;
							lastCorner = '\0';
						} else if (pipeChar == 'J') {
							if (lastCorner == 'F') crossings++;
							lastCorner = '\0';
						}
						// '-' doesn't affect crossings in horizontal ray
					}

					// If odd number of crossings, point is inside
					if (crossings % 2 == 1) {
						enclosedCount++;
					}
				}
			}

			return enclosedCount;
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
