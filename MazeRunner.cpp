//============================================================================
// Name        : MazeRunner.cpp
// Author      : TateryBoi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream> // import txt

#include <direct.h> // getcwd
#include <string>

using namespace std;


int maze_display(char arr[][20], int len = 20) {
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			cout << arr[i][j];
		}
		cout << endl;
	}
	return 0;
}

//int maze_error_check(char arr[][], int len = 20) {
//	if (arr.length() != 20) {
//		cerr << "Error: maze does not contain 20 rows." << endl;
//		return 1;
//	}
//	for (int i = 0; i < len; ++i) { // check line lengths
//		if (arr[i].length() != 20) {
//			cerr << "Error: row " << i << " does not contain 20 characters." << endl;
//			return 1;
//		}
//	}
//
//}


int main() {
// get cwd
	const size_t size = 1024;
	char buffer[size];

	if (_getcwd(buffer, size) != 0) {
		clog << "Log: current working directory: " << buffer << endl;
	}
	else {
		cerr << "Error getting current working directory" << endl;
		return 1;
	}
// change cwd
	string mazeDir = string(buffer) + "\\mazes";

	if (_chdir(mazeDir.c_str()) != 0) {
		cerr << "Error: could not change directory to: " << mazeDir << endl;
		return 1;
	}

// get new wd
	if (_getcwd(buffer, size) != 0) {
		clog << "Log: new working directory: " << buffer << endl;
	}
	else {
		cerr << "Error: error getting new working directory." << endl;
		return 1;
	}


// import file
	ifstream maze_file("maze_1.txt");
// read file

	char maze_arr[20][20];
	string line;

	if (maze_file.is_open()) {
		for (int i = 0; i < 20; ++i) {
			if(getline(maze_file, line)) {
                for (int j = 0; j < 20; ++j) {
                    maze_arr[i][j] = line[j];
                }
			}
		}
		maze_file.close();
	}

	else {
		cerr << "Error: unable to open file." << endl;
		return 1;
	}


	maze_display(maze_arr);

	return 0;
}


