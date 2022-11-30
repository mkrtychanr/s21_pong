// I WANT TO PLAY WITH YOU
//        YOUR FRIEND, AI
#include <stdio.h>

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

void control();

void print();

void printscore();

void win();

void start();

void checkPlafororm();

void updateBallPosition();

void update();

int main() {
    start();
    printscore();
    print();
    while (score1 != 21 && score2 != 21) {
        control();
        printf("\e[1;1H\e[2J");
        checkPlafororm();
        updateBallPosition();
        printscore();
        print();
    }
    printf("\e[1;1H\e[2J");
    win();
    return 0;
}

void control() {
    char d1, d2;
    fflush(stdin);
    if (scanf("%c%c", &d1, &d2) != 2) {
        printf("error\n");
        control();
    }

    if (d1 == 'a') {
        if (left_platform_y > 1) {
            left_platform_y--;
        }
    } else if (d1 == 'z') {
        if (left_platform_y < 23) {
            left_platform_y++;
        }
    } else if (d1 != ' ') {
        printf("error\n");
        control();
    }

    if (d2 == 'k') {
        if (right_platform_y > 1) {
            right_platform_y--;
        }
    } else if (d2 == 'm') {
        if (right_platform_y < 23) {
            right_platform_y++;
        }
    } else if (d2 != ' ') {
        printf("error\n");
        control();
    }
}

void printscore() {
    if (score1 > 9) {
        printf("%25sPlayer 1 %d - %d Player 2\n", " ", score1, score2);
    } else {
        printf("%26sPlayer 1 | %d - %d | Player 2\n", " ", score1, score2);
    }
}

void print() {
    for (int j = 0; j < Height; j++) {
        for (int i = 0; i < Width; i++) {
            if (ball_x == i && ball_y == j) {
                putchar('@');
            } else if (i == Width / 2 - 1 || i == Width / 2) {
                printf("|");
            } else if (((left_platform_y == j || left_platform_y - 1 == j || left_platform_y + 1 == j) &&
                        (i == 1))) {
                putchar('#');
            } else if ((right_platform_y == j || right_platform_y - 1 == j || right_platform_y + 1 == j) &&
                       (i == Width - 2)) {
                putchar('#');
            } else {
                putchar(' ');
            }
        }
        printf("\n");
    }
}

void addScore(int winner) {
    if (winner == 1) {
        score1++;
    } else {
        score2++;
    }
}

void win() {
    if (score1 == 21) {
        printf("Player 1 WIN!");
    } else {
        printf("Player 2 WIN!");
    }
}

void start() {
    ball_x = Width/2;
    ball_y = Height/2;
    direction_x = -1;
    direction_y = 1;
    left_platform_y = Height/2;
    right_platform_y = Height/2;
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
    if (direction_y == 1) {
        if (ball_y == 1) {
            ball_y = 2;
            direction_y = -1;
        } else {
            ball_y = ball_y - 1;
        }

    } else {
        if (ball_y == 24) {
            ball_y = 23;
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
}
