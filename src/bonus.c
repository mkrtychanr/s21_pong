#include <stdio.h>
#include <ncurses.h>

const int Width = 80;
const int Height = 25;
int ball_x = 0;
int ball_y = 0;
int direction_x = 0;
int direction_y = 0;
int left_platform_y = 13;
int right_platform_y = 13;
int score1 = 0;
int score2 = 0;

void printPlatforms();

void printscore();

void win();

void start();

void checkPlafororm();

void updateBallPosition();

void update();

void printLines();

void control(char c);

void printMiddleLine() {
    for (int i = 2; i < 27; i++) {
        mvaddch(i, 40, '|');
        mvaddch(i, 41, '|');
    }
}


int main() {
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    start();
    printLines();
    char c = 0;
    double lastTimeCall = 0;

    while (score1 < 21 && score2 < 21) {
        printscore();
        control(c);
        checkPlafororm();
        c = getch();
        printPlatforms();
        if (lastTimeCall > 1) {
            updateBallPosition();
            lastTimeCall = 0;
        }
        refresh();
        lastTimeCall += 0.00015;
    }
    win();
    scanf("%c", &c);
    endwin();
    return 0;
}

void printLines() {
    mvprintw(1, 0, "--------------------------------------------------------------------------------");
    mvprintw(27, 0, "--------------------------------------------------------------------------------");
}

void printscore() {
    mvprintw(0, 29, "Player 1 %d - %d Player 2", score1, score2);
}

void control(char c) {
    if (c == 'a' && left_platform_y > 3) {
        mvaddch(left_platform_y + 1, 1, ' ');
        left_platform_y--;
    }
    if (c == 'z' && left_platform_y < 25) {
        mvaddch(left_platform_y - 1, 1, ' ');
        left_platform_y++;
    }
    if (c == 'k' && right_platform_y > 3) {
        mvaddch(right_platform_y + 1, 79, ' ');
        right_platform_y--;
    }
    if (c == 'm' && right_platform_y < 25) {
        mvaddch(right_platform_y - 1, 79, ' ');
        right_platform_y++;
    }
}


void printPlatforms() {
    mvaddch(left_platform_y, 1, '#');
    mvaddch(left_platform_y-1, 1, '#');
    mvaddch(left_platform_y+1, 1, '#');
    mvaddch(right_platform_y, 79, '#');
    mvaddch(right_platform_y-1, 79, '#');
    mvaddch(right_platform_y+1, 79, '#');
}

void addScore(int winner) {
    if (winner == 1) {
        score1++;
    } else {
        score2++;
    }
}

void win() {
    printscore();
    if (score1 == 21) {
        mvprintw(30, 0, "Player 1 WIN!");
    } else {
        mvprintw(30, 0, "Player 2 WIN!");
    }
    mvprintw(31, 0, "Press any key to exit.");
    refresh();
}

void start() {
    mvaddch(left_platform_y, 1, ' ');
    mvaddch(left_platform_y-1, 1, ' ');
    mvaddch(left_platform_y+1, 1, ' ');
    mvaddch(right_platform_y, 79, ' ');
    mvaddch(right_platform_y-1, 79, ' ');
    mvaddch(right_platform_y+1, 79, ' ');
    mvaddch(ball_y, ball_x, ' ');
    ball_x = 40;
    ball_y = 19;
    direction_x = -1;
    direction_y = 1;
    left_platform_y = 13;
    right_platform_y = 13;
    mvaddch(ball_y, ball_x, '@');
}

void checkPlafororm() {
    if (ball_x == 2 && direction_x == -1) {
        if (ball_y != left_platform_y && ball_y != left_platform_y - 1 && ball_y != left_platform_y + 1) {
            addScore(2);
            start();
        }
    }
    if (ball_x == 77 && direction_x == 1) {
        if (ball_y != right_platform_y && ball_y != right_platform_y - 1 && ball_y != right_platform_y + 1) {
            addScore(1);
            start();
        }
    }
}

void updateBallPosition() {
    mvaddch(ball_y, ball_x, ' ');
    if (direction_y == 1) {
        if (ball_y == 2) {
            ball_y = 3;
            direction_y = -1;
        } else {
            ball_y = ball_y - 1;
        }

    } else {
        if (ball_y == 26) {
            ball_y = 25;
            direction_y = 1;
        } else {
            ball_y = ball_y + 1;
        }
    }
    if (direction_x == 1) {
        if (ball_x == 77) {
            ball_x = 76;
            direction_x = -1;
        } else {
            ball_x = ball_x + 1;
        }
    } else {
        if (ball_x == 2) {
            ball_x = 3;
            direction_x = 1;
        } else {
            ball_x = ball_x - 1;
        }
    }
    printMiddleLine();
    mvaddch(ball_y, ball_x, '@');
}
