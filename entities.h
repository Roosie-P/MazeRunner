#include <vector>
#include <utility>

#ifndef ENTITIES_H
#define ENTITIES_H

using namespace std;

class Player {
    private:
        int x;
        int y;
        int lives = 3;
        int score = 0;
    public:
        int get_x() {
            return x;
        }
        int get_y() {
            return y;
        }
        void set_x(int new_x) { 
            x = new_x;
        }
        void set_y(int new_y) {
            y = new_y;
        }
        void find_p(char maze[20][20]) {
            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 20; j++) {
                    char cur = maze[i][j];
                    if (cur == 'P') {
                        x = j;
                        y = i;
                    }
                }
            }
        } 
        
        int get_lives() {
            return lives;
        }
        int get_score() {
            return score;
        }
        void sub_lives() {
            lives -= 1;
        }
        void add_score() {
            score += 10;
        }

};


class Enemy {
    private:
    int x;
    int y;

    public:
        int get_x() {
            return x;
        }
        int get_y() {
            return y;
        }
        void set_x(int new_x) { 
            x = new_x;
        }
        void set_y(int new_y) {
            y = new_y;
        }

        vector<int> find_all_enemies(char maze[20][20]) {
            vector<int> locations;
            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 20; j++) {
                    char cur = maze[i][j];
                    if (cur == 'E') {
                        locations.push_back(j);
                        locations.push_back(i);
                    }
                }
            }
            return locations;
            }

        void move_enemy(char maze[20][20], int safezone_x, int safezone_y) {
            
            int x = get_x();
            int y = get_y();

            // determine allowed positions
            vector<int> dirs;

            if (maze[y - 1][x] == '.' && !((y - 1) == safezone_y && x == safezone_x)) {
                dirs.push_back(0);
            }
            if (maze[y][x - 1] == '.' && !(y == safezone_y && (x - 1) == safezone_x)) {
                dirs.push_back(1);
            }
            if (maze[y + 1][x] == '.' && !((y + 1) == safezone_y && x == safezone_x)) {
                dirs.push_back(2);
            }
            if (maze[y][x + 1] == '.' && !(y == safezone_y && (x + 1) == safezone_x)) {
                dirs.push_back(3);
            }

            if (dirs.empty()) {
                return;
            }

            //generate random direction
            int index = rand() % dirs.size();
            int num = dirs[index];
            char move;

            // translate random number into directional character
            if (num == 0) {
                move = 'w';
            }
            else if (num == 1) {
                move = 'a';
            }
            else if (num == 2) {
                move = 's';
            }
            else {
                move = 'd';
            }

            // UP
            if (move == 'w') {
                char new_pos = maze[y - 1][x];
				maze[y][x] = '.'; // remove E from current position
				maze[y - 1][x] = 'E'; // move E to new position
				set_y(y - 1); // update enemy position
			}
            
            // LEFT
            else if (move == 'a') {
		        char new_pos = maze[y][x - 1];
				maze[y][x] = '.'; // remove E from current position
				maze[y][x - 1] = 'E'; // move E to new position
				set_x(x - 1); // update enemy position
			} 
            
            // DOWN
	        else if (move == 's') {
		        char new_pos = maze[y + 1][x];
				maze[y][x] = '.'; // remove E from current position
				maze[y + 1][x] = 'E'; // move E to new position
				set_y(y + 1); // update enemy position
			}
            
            // RIGHT
	        else if (move == 'd') {
		        char new_pos = maze[y][x + 1];
				maze[y][x] = '.'; // remove E from current position
				maze[y][x + 1] = 'E'; // move E to new position
				set_x(x + 1); // update enemy position
			}
        }
    };

#endif