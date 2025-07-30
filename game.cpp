/*
Minimal Tetris Game in C++ (Terminal, ncurses)
Controls:
  Left/Right Arrow: Move piece
  Up Arrow: Rotate piece
  Down Arrow: Move down faster
  q: Quit
Compile with: g++ game.cpp -lncurses -o tetris
*/
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

// Tetromino shapes (4x4)
const char tetromino[7][4][4] = {
    { // I
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', '#'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    { // O
        {' ', ' ', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '}
    },
    { // T
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    { // S
        {' ', ' ', ' ', ' '},
        {' ', '#', '#', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    { // Z
        {' ', ' ', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '}
    },
    { // J
        {' ', ' ', ' ', ' '},
        {'#', ' ', ' ', ' '},
        {'#', '#', '#', ' '},
        {' ', ' ', ' ', ' '}
    },
    { // L
        {' ', ' ', ' ', ' '},
        {' ', ' ', '#', ' '},
        {'#', '#', '#', ' '},
        {' ', ' ', ' ', ' '}
    }
};

struct Piece {
    int type, x, y, rot;
};

vector<vector<char>> board(HEIGHT, vector<char>(WIDTH, ' '));

void draw_board(const Piece& p, int score) {
    clear();
    // Draw board
    for (int i = 0; i < HEIGHT; ++i) {
        move(i, 0);
        printw("|");
        for (int j = 0; j < WIDTH; ++j) {
            printw("%c", board[i][j]);
        }
        printw("|");
    }
    // Draw bottom border
    move(HEIGHT, 0);
    printw("+");
    for (int j = 0; j < WIDTH; ++j) printw("-");
    printw("+");
    // Draw current piece
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int px = p.x + j;
            int py = p.y + i;
            char c = tetromino[p.type][(i + p.rot) % 4][j];
            if (c == '#' && py >= 0 && py < HEIGHT && px >= 0 && px < WIDTH) {
                move(py, px + 1);
                printw("#");
            }
        }
    }
    // Display score
    move(1, WIDTH + 4);
    printw("Score: %d", score);
    refresh();
}

bool check_collision(const Piece& p, int dx, int dy, int drot) {
    int new_rot = (p.rot + drot) % 4;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            char c = tetromino[p.type][(i + new_rot) % 4][j];
            if (c == '#') {
                int nx = p.x + j + dx;
                int ny = p.y + i + dy;
                if (nx < 0 || nx >= WIDTH || ny >= HEIGHT) return true;
                if (ny >= 0 && board[ny][nx] != ' ') return true;
            }
        }
    }
    return false;
}

void merge_piece(const Piece& p) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            char c = tetromino[p.type][(i + p.rot) % 4][j];
            if (c == '#') {
                int nx = p.x + j;
                int ny = p.y + i;
                if (ny >= 0 && ny < HEIGHT && nx >= 0 && nx < WIDTH)
                    board[ny][nx] = '#';
            }
        }
    }
}

// Modify clear_lines to return number of lines cleared
int clear_lines() {
    int lines = 0;
    for (int i = HEIGHT - 1; i >= 0; --i) {
        bool full = true;
        for (int j = 0; j < WIDTH; ++j) {
            if (board[i][j] == ' ') {
                full = false;
                break;
            }
        }
        if (full) {
            for (int k = i; k > 0; --k) {
                board[k] = board[k - 1];
            }
            board[0] = vector<char>(WIDTH, ' ');
            ++i; // recheck this line
            lines++;
        }
    }
    return lines;
}

int main() {
    srand(time(0));
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    Piece curr = {rand() % 7, WIDTH / 2 - 2, 0, 0};
    int tick = 0, speed = 20;
    bool game_over = false;
    int score = 0;

    while (!game_over) {
        draw_board(curr, score);
        int ch = getch();
        if (ch == KEY_LEFT) {
            if (!check_collision(curr, -1, 0, 0)) curr.x--;
        } else if (ch == KEY_RIGHT) {
            if (!check_collision(curr, 1, 0, 0)) curr.x++;
        } else if (ch == KEY_UP) {
            if (!check_collision(curr, 0, 0, 1)) curr.rot = (curr.rot + 1) % 4;
        } else if (ch == KEY_DOWN) {
            if (!check_collision(curr, 0, 1, 0)) curr.y++;
        } else if (ch == 'q' || ch == 'Q') {
            break;
        }
        // Gravity
        if (tick++ >= speed) {
            tick = 0;
            if (!check_collision(curr, 0, 1, 0)) {
                curr.y++;
            } else {
                merge_piece(curr);
                int lines = clear_lines();
                if (lines > 0) score += lines * 100;
                curr = {rand() % 7, WIDTH / 2 - 2, 0, 0};
                if (check_collision(curr, 0, 0, 0)) {
                    game_over = true;
                }
            }
        }
        napms(30);
    }
    // Game Over
    move(HEIGHT / 2, WIDTH / 2 - 4);
    printw("GAME OVER");
    move(HEIGHT / 2 + 1, WIDTH / 2 - 6);
    printw("Final Score: %d", score);
    refresh();
    nodelay(stdscr, FALSE);
    getch();
    endwin();
    return 0;
}
