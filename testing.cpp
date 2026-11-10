//============================================================================
// Name        : testing.cpp
// Author      : TateryBoi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream> // import txt
#include <cctype> // lower char

#include <direct.h> // getcwd
#include <bits/stdc++.h> // enemy direction
#include <string>
#include <vector> // temp maze
#include <windows.h> // sleep
#include <cstdlib> // clear console

#include "entities.h" // import entities


using namespace std;


int change_cwd() {
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

	return 0;
}

int maze_error_check(vector<vector<char>> maze) {
	// check rows
	if (maze.size() != 20) {
	    cerr << "Error: maze contains " << maze.size() << " rows instead of 20." << endl;
	    return 1;
	}

	// check elements per row + border validity + character validity
	int P = 0;
	int T = 0;
	int E = 0;
	int X = 0;

	for (int i = 0; i < 20; ++i) {
		// check if each row has 20 characters
	    if (maze[i].size() != 20) {
	        cerr << "Error: row " << i + 1 << " contains " << maze[i].size() << " elements instead of 20." << endl;
	        return 1;
	    }

	    // check borders of row 2-19: first and last char must be "#"
	    if (maze[i][0] != '#' || maze[i][19] != '#') {
	        cerr << "Error: incorrect border generation." << endl;
	        return 1;
	    }

    	// check borders of first and last row: all chars must be "#"
	    for (int j = 0; j < 20; ++j) {
	        if (maze[0][j] != '#' || maze[19][j] != '#') {
	            cerr << "Error: incorrect border generation." << endl;
	            return 1;
	        }
	    }

	    // check character validity
	    for (int j = 1; j < 19; ++j) { // minimise complexity: don't need to check first and last rows anymore
	    	char cur = maze[i][j];

	    	if (cur == '.' || cur == '#') {
	    	    continue;
	    	}
	    	else if (cur == 'P') {
	    	    P++;
	    	}
	    	else if (cur == 'E') {
	    	    E++;
	    	}
	    	else if (cur == 'T') {
	    	    T++;
	    	}
	    	else if (cur == 'X') {
	    	    X++;
	    	}
	    	else {
	    	    cerr << "Error: invalid character '" << cur << "' in maze on line " << i + 1 << "." << endl;
	    	    return 1;
	    	}
	    }
	}

	if (P != 1) {
		cerr << "Error: maze must contain 1x P." << endl;
		return 1;
	}
	if (T != 5) {
		cerr << "Error: maze must contain 5x T." << endl;
		return 1;
	}
	if (E != 3) {
		cerr << "Error: maze must contain 3x E." << endl;
		return 1;
	}
	if (X != 1) {
		cerr << "Error: maze must contain 1x X." << endl;
		return 1;
	}

	return 0;
}

int maze_display(Player& player, char arr[20][20]) {
	cout << endl << endl;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			cout << arr[i][j];
		}
		cout << endl;
	}
	cout << "Lives: " << player.get_lives() << endl;
	cout << "Score: " << player.get_score() << endl;
	cout << endl << endl;
	return 0;
}

bool move_player(Player& player, char maze[20][20], int safezone_x, int safezone_y) {
	// input move 
	cout << "Please enter your move: ";
	char move;
	cin >> move;
	move = tolower(move);

	if (move == 'q') {
		clog << "Quitting game..." << endl;
		return false;
	}

	int x = player.get_x();
	int y = player.get_y();

	// UP
	if (move == 'w') {
		char new_pos = maze[y - 1][x];
		if (new_pos != '#') {
			if (new_pos == 'T') {
				player.add_score();
			}
			if (new_pos == 'E') {
				player.sub_lives();
				maze[y][x] = '.'; // remove P from current position
				maze[safezone_y][safezone_x] = 'P'; // move P to starter position
				player.set_y(safezone_y); // update player position
				player.set_x(safezone_x);
			}
			else {
				maze[y][x] = '.'; // remove P from current position
				maze[y - 1][x] = 'P'; // move P to new position
				player.set_y(y - 1); // update player position
			}
		} 
	}

	// LEFT
	else if (move == 'a') {
		char new_pos = maze[y][x - 1];
		if (new_pos != '#') {
			if (new_pos == 'T') {
				player.add_score();
			}
			if (new_pos == 'E') {
				player.sub_lives();
				maze[y][x] = '.'; // remove P from current position
				maze[safezone_y][safezone_x] = 'P'; // move P to starter position
				player.set_y(safezone_y); // update player position
				player.set_x(safezone_x);
			}
			else { 
				maze[y][x] = '.'; // remove P from current position
				maze[y][x - 1] = 'P'; // move P to new position
				player.set_x(x - 1); // update player position
			} 
		}
	}
	// DOWN
	else if (move == 's') {
		char new_pos = maze[y + 1][x];
		if (new_pos != '#') {
			if (new_pos == 'T') {
				player.add_score();
			}
			if (new_pos == 'E') {
				player.sub_lives();
				maze[y][x] = '.'; // remove P from current position
				maze[safezone_y][safezone_x] = 'P'; // move P to starter position
				player.set_y(safezone_y); // update player position
				player.set_x(safezone_x);
			}
			else {
				maze[y][x] = '.'; // remove P from current position
				maze[y + 1][x] = 'P'; // move P to new position
				player.set_y(y + 1); // update player position
			}
		}
	} 
	// RIGHT
	else if (move == 'd') {
		char new_pos = maze[y][x + 1];
		if (new_pos != '#'){
			if (new_pos == 'T') {
				player.add_score();
			}
			if (new_pos == 'E') {
				player.sub_lives();
				maze[y][x] = '.'; // remove P from current position
				maze[safezone_y][safezone_x] = 'P'; // move P to starter position
				player.set_y(safezone_y); // update player position
				player.set_x(safezone_x);
			}
			else {
				maze[y][x] = '.'; // remove P from current position
				maze[y][x + 1] = 'P'; // move P to new position
				player.set_x(x + 1); // update player position
			} 
		}
	}

	else {
		cerr << "Error: please input a valid move. W (up), A (left), S (down) or D (right). Or Q to quit." << endl;
	}
return true;
};


int main() {
	
	if (change_cwd() != 0) {
	    return 1;
	}

	string filename = "maze_random_spaces.txt";

	if (filename.substr(filename.find_last_of(".") + 1) != "txt") { // check if file is .txt
	    cerr << "Error: file must be a .txt file." << endl;
	    return 1;
	}

	ifstream maze_file(filename);

	// read file
	vector<vector<char>> vect_maze;
	string line;

	if (maze_file.is_open()) {
		while(getline(maze_file, line)) { // read a line
			vector<char> temp_row; // create temp row and put it in per char
	        for (char c : line) {
	        	if (c != ' ') { // handle possible unseen spaces at end of row
	        		temp_row.push_back(c);
	        	}
	        }
	        if (!temp_row.empty()) { // handle possible unseen spaces on 21st row
	        	vect_maze.push_back(temp_row); // add temp row to temp maze
	        }
	    }
		maze_file.close();
	}
	else {
		cerr << "Error: unable to open file." << endl;
		return 1;
	}

	if (maze_error_check(vect_maze) != 0) {
	    return 1;
	}

	// create array maze and copy vector over
	char maze_arr[20][20];

	for (int i = 0; i < 20; ++i) {
	    for (int j = 0; j < 20; ++j) {
	        maze_arr[i][j] = vect_maze[i][j];
	    }
	}


	// title screen
	// cout << "----------------------------------    Welcome to    ----------------------------------\n\n";
	// cout << "███    ███  █████  ███████ ███████ ██████  ██    ██ ███    ██ ███    ██ ███████ ██████\n"
	// 		"████  ████ ██   ██    ███  ██      ██   ██ ██    ██ ████   ██ ████   ██ ██      ██   ██\n"
	// 		"██ ████ ██ ███████   ███   █████   ██████  ██    ██ ██ ██  ██ ██ ██  ██ █████   ██████\n"
	// 		"██  ██  ██ ██   ██  ███    ██      ██   ██ ██    ██ ██  ██ ██ ██  ██ ██ ██      ██   ██\n"
	// 		"██      ██ ██   ██ ███████ ███████ ██   ██  ██████  ██   ████ ██   ████ ███████ ██   ██\n\n";
	// cout << "---------------------------------------------------------------------------------------"<< endl;
	// cout << "Loading '" << filename << "'..." << endl;

	// Sleep(4000);
	// system("cls");

	// --------------------------------------------

	// Find P
	Player player;
	player.find_p(maze_arr);
	int safezone_x = player.get_x();
	int safezone_y = player.get_y();
	
	// Initialize enemies
	Enemy enemy_1, enemy_2, enemy_3;
	vector<int> locs = enemy_1.find_all_enemies(maze_arr);
	enemy_1.set_x(locs[0]);
	enemy_1.set_y(locs[1]);
	enemy_2.set_x(locs[2]);
	enemy_2.set_y(locs[3]);
	enemy_3.set_x(locs[4]);
	enemy_3.set_y(locs[5]);

	srand(time(0));


	while (true) {

	maze_display(player, maze_arr);

	if (!move_player(player, maze_arr, safezone_x, safezone_y)) { 
		break;
	}

	enemy_1.move_enemy(maze_arr, safezone_x, safezone_y);
	enemy_2.move_enemy(maze_arr, safezone_x, safezone_y);
	enemy_3.move_enemy(maze_arr, safezone_x, safezone_y);
	
} 

	cout << "Check!";

	return 0;
}
