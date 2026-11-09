
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