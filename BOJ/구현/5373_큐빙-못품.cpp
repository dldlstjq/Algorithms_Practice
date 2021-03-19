/*
인덱스 땜에 너무 헷갈린다. 다음에 다시 보면 풀수있을지 모르겟다
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

char cube[9][12];
char temp[9][12];
char origin[9][12];
//
void up_left() {
    for (int i = 0; i < 3; ++i) {
        cube[3][i] = temp[3][i + 9];
        cube[3][i + 3] = temp[3][i];
        cube[3][i + 6] = temp[3][i + 3];
        cube[3][i + 9] = temp[3][i + 6];
    }
}
//
void up_right() {
    for (int i = 0; i < 3; ++i) {
        cube[3][i] = temp[3][i + 3];
        cube[3][i + 3] = temp[3][i + 6];
        cube[3][i + 6] = temp[3][i + 9];
        cube[3][i + 9] = temp[3][i];
    }
}
//
void down_left() {
    for (int i = 0; i < 3; ++i) {
        cube[5][i] = temp[5][i + 3];
        cube[5][i + 3] = temp[5][i + 6];
        cube[5][i + 6] = temp[5][i + 9];
        cube[5][i + 9] = temp[5][i];
    }
}
//
void down_right() {
    for (int i = 0; i < 3; ++i) {
        cube[5][i] = temp[5][i + 9];
        cube[5][i + 3] = temp[5][i];
        cube[5][i + 6] = temp[5][i + 3];
        cube[5][i + 9] = temp[5][i + 6];
    }
}
//
void front_left() {
    for (int i = 3; i < 6; ++i) {
        cube[2][i] = temp[i][6];
        cube[i][2] = temp[2][8 - i];
        cube[6][i] = temp[i][2];
        cube[i][6] = temp[6][8 - i];
    }
}
//
void front_right() {
    for (int i = 3; i < 6; ++i) {
        cube[2][i] = temp[8 - i][2];
        cube[i][2] = temp[6][i];
        cube[6][i] = temp[8 - i][6];
        cube[i][6] = temp[2][i];
    }
}
//다시 고치기
void back_right() {
    for (int i = 3; i < 6; ++i) {
        cube[0][i] = temp[i][8];
        cube[i][0] = temp[0][8 - i];
        cube[8][i] = temp[i][0];
        cube[i][8] = temp[8][8 - i];
    }
}
//
void back_left() {
    for (int i = 3; i < 6; ++i) {
        cube[0][i] = temp[8 - i][0];
        cube[i][0] = temp[8][i];
        cube[8][i] = temp[8 - i][8];
        cube[i][8] = temp[0][i];
    }
}
////////////////////////////////////////

//
void left_left() {
    int j = 5;
    for (int i = 0; i < 3; ++i) {
        cube[i][3] = temp[i + 3][3];
        cube[i + 3][3] = temp[i + 6][3];
        cube[i + 6][3] = temp[j--][11];
        cube[i + 3][11] = temp[2 - i][3];
    }
}
//
void left_right() {
    int j = 5; int k = 8;
    for (int i = 0; i < 3; ++i) {
        cube[i][3] = temp[j--][11];
        cube[i + 3][3] = temp[i][3];
        cube[i + 6][3] = temp[i + 3][3];
        cube[i + 3][11] = temp[k--][3];
    }
}

void right_left() {
    int j = 5; int k = 8;
    for (int i = 0; i < 3; ++i) {
        cube[i][5] = temp[j--][9];
        cube[i + 3][5] = temp[i][3];
        cube[i + 6][5] = temp[i + 3][3];
        cube[i + 3][9] = temp[k--][5];
    }
}


void right_right() {
    int j = 5; int k = 8;
    for (int i = 0; i < 3; ++i) {
        cube[i][5] = temp[i + 3][5];
        cube[i + 3][5] = temp[i + 6][5];
        cube[i + 6][5] = temp[j--][9];
        cube[i + 3][9] = temp[2 - i][5];
    }
}

//윗 면출력
void print() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 3; j < 6; ++j) {
            cout << cube[i][j];
        }
        cout << "\n";
    }
}
//큐브 복사
void copy() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 12; ++j) {
            temp[i][j] = cube[i][j];
        }
    }
}

//큐브를 2차원 평면에 저장
void make_cube() {
    for (int i = 0; i < 3; ++i)
        for (int j = 3; j < 6; ++j)
            cube[i][j] = 'w';

    for (int i = 3; i < 6; ++i) {
        for (int j = 0; j < 3; ++j)
            cube[i][j] = 'g';
        for (int j = 3; j < 6; ++j)
            cube[i][j] = 'r';
        for (int j = 6; j < 9; ++j)
            cube[i][j] = 'b';
        for (int j = 9; j < 12; ++j)
            cube[i][j] = 'o';
    }

    for (int i = 6; i < 9; ++i)
        for (int j = 3; j < 6; ++j)
            cube[i][j] = 'y';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 0;
    cin >> t;

    while (t--) {
        make_cube();
        copy();
        int num = 0;
        cin >> num;

        for (int i = 0; i < num; ++i) {
            string str;
            cin >> str;


            if (str[0] == 'U' && str[1] == '+') {
                up_right();
            }

            else if (str[0] == 'U' && str[1] == '-') {
                up_left();
            }

            else if (str[0] == 'D' && str[1] == '+') {
                down_right();
            }

            else if (str[0] == 'D' && str[1] == '-') {
                down_left();
            }

            else if (str[0] == 'F' && str[1] == '+') {
                front_right();
            }

            else if (str[0] == 'F' && str[1] == '-') {
                front_left();
            }

            else if (str[0] == 'B' && str[1] == '+') {
                back_right();
            }

            else if (str[0] == 'B' && str[1] == '-') {
                back_left();
            }

            else if (str[0] == 'L' && str[1] == '+') {
                left_right();
            }

            else if (str[0] == 'L' && str[1] == '-') {
                left_left();
            }

            else if (str[0] == 'R' && str[1] == '+') {
                right_right();
            }

            else if (str[0] == 'R' && str[1] == '-') {
                right_left();
            }
            copy();
        }
        print();

    }


    return 0;
}