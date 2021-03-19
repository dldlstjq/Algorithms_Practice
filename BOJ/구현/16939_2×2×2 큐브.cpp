/*
한 번만 돌리면 되기 때문에 돌리고 난 후 하나씩 비교해보면 된다고 생각했다.
돌릴 수 있는 경우가 총 12가지인데 8가지로 생각해서 한 번 틀렸다.
오른쪽, 왼쪽, 위, 아래, 앞, 뒷 부분을 양옆 또는 위아래로 돌릴 수 있기 때문에 12가지 경우가 존재한다.
그리고 돌리고 난 후 인덱스끼리 값을 바꿔서 모든 면이 같은 색인지 체크했다.

경우의 수를 몇가지 잊어먹은것, 인덱스 비교를 잘못한 것, 큐브를 돌릴때마다 색깔을 확인해주고
다시 다른 방향으로 돌릴 때는 원래 큐브로 돌려놔야 하는 것 때문에 해결에 애를 먹었다.
*/

#include <iostream>
#include <algorithm>

using namespace std;

int cube[25];
int temp[25];
int origin[25];

//큐브를 돌리는 12가지 방법
//해당하는 칸에 맞는 색깔을 넣어준다.
void right_down() {
    cube[2] = temp[23]; cube[4] = temp[21];
    cube[6] = temp[2];   cube[8] = temp[4];
    cube[10] = temp[6]; cube[12] = temp[8];
    cube[21] = temp[12]; cube[23] = temp[10];
}

void right_up() {
    cube[2] = temp[6]; cube[4] = temp[8];
    cube[6] = temp[10];   cube[8] = temp[12];
    cube[10] = temp[23]; cube[12] = temp[21];
    cube[21] = temp[4]; cube[23] = temp[2];
}

void left_down() {
    cube[1] = temp[24]; cube[3] = temp[22];
    cube[5] = temp[1];   cube[7] = temp[3];
    cube[9] = temp[5]; cube[11] = temp[7];
    cube[22] = temp[11]; cube[24] = temp[9];
}

void left_up() {
    cube[1] = temp[5]; cube[3] = temp[7];
    cube[5] = temp[9];   cube[7] = temp[11];
    cube[9] = temp[24]; cube[11] = temp[22];
    cube[22] = temp[3]; cube[24] = temp[1];
}

void up_right() {
    cube[5] = temp[13]; cube[6] = temp[14];
    cube[13] = temp[21]; cube[14] = temp[22];
    cube[17] = temp[5]; cube[18] = temp[6];
    cube[21] = temp[17]; cube[22] = temp[18];
}

void up_left() {
    cube[5] = temp[17]; cube[6] = temp[18];
    cube[13] = temp[5]; cube[14] = temp[6];
    cube[17] = temp[21]; cube[18] = temp[22];
    cube[21] = temp[13]; cube[22] = temp[14];
}

void down_right() {
    cube[7] = temp[15]; cube[8] = temp[16];
    cube[15] = temp[23]; cube[16] = temp[24];
    cube[19] = temp[7]; cube[20] = temp[8];
    cube[23] = temp[19]; cube[24] = temp[20];
}

void down_left() {
    cube[7] = temp[19]; cube[8] = temp[20];
    cube[15] = temp[7]; cube[16] = temp[8];
    cube[19] = temp[23]; cube[20] = temp[24];
    cube[23] = temp[15]; cube[24] = temp[16];
}

void front_left() {
    cube[3] = temp[17]; cube[4] = temp[19];
    cube[14] = temp[4]; cube[16] = temp[3];
    cube[9] = temp[14]; cube[10] = temp[16];
    cube[17] = temp[10]; cube[19] = temp[10];
}

void front_right() {
    cube[3] = temp[16]; cube[4] = temp[14];
    cube[14] = temp[9]; cube[16] = temp[10];
    cube[9] = temp[19]; cube[10] = temp[17];
    cube[17] = temp[3]; cube[19] = temp[4];
}

void back_left() {
    cube[1] = temp[18]; cube[2] = temp[20];
    cube[13] = temp[2]; cube[15] = temp[1];
    cube[11] = temp[13]; cube[12] = temp[15];
    cube[18] = temp[12]; cube[20] = temp[11];
}

void back_right() {
    cube[1] = temp[15]; cube[2] = temp[13];
    cube[13] = temp[11]; cube[15] = temp[12];
    cube[11] = temp[20]; cube[12] = temp[18];
    cube[18] = temp[1]; cube[20] = temp[2];
}


bool complete() {
    bool flag = true;
    for (int i = 1; i <= 24; i += 4)
        for (int j = i; j < i + 3; ++j) {
            if (cube[j] != cube[j + 1]) {
                flag = false;
                return flag;
            }
        }
    return flag;
}

//값을 비교하기 위해 temp에 cube를 복사한다.
void copy() {
    for (int i = 1; i <= 24; ++i)
        temp[i] = cube[i];
}

//원래 큐브로 돌아가기 위해 origin을 cube에 복사한다.
void original() {
    for (int i = 1; i <= 24; ++i)
        cube[i] = origin[i];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 1; i <= 24; ++i)
        cin >> cube[i];

    //원래 큐브 색깔 저장
    for (int i = 1; i <= 24; ++i)
        origin[i] = cube[i];

    //총 12번 돌릴 수 있다.
    //오른쪽, 왼쪽을 위, 아래로 돌리거나
    //위, 아래를 왼쪽, 오른쪽으로 돌리거나
    //앞, 뒤를 왼쪽, 오른쪽으로 돌리거나
    bool is_complete = false;
    copy();
    right_up();
    is_complete = complete();
    if (is_complete) {
        cout << 1;
        return 0;
    }

    //원래 큐브로 맞추고 난 후 돌려서 맞춰지는지 확인한다.
    //맞춰지면 1 출력하고 종료, 아니면 다른 방향으로 계속 시도
    original();
    is_complete = false;
    copy();
    right_down();
    is_complete = complete();
    if (is_complete) {
        cout << 1;
        return 0;
    }

    original();
    is_complete = false;
    copy();
    left_down();
    is_complete = complete();
    if (is_complete) {
        cout << 1;
        return 0;
    }

    original();
    is_complete = false;
    copy();
    left_up();
    is_complete = complete();
    if (is_complete) {
        cout << 1;
        return 0;
    }

    original();
    is_complete = false;
    copy();
    up_right();
    is_complete = complete();
    if (is_complete) {
        cout << 1;
        return 0;
    }

    original();
    is_complete = false;
    copy();
    up_left();
    is_complete = complete();
    if (is_complete) {
        cout << 1;
        return 0;
    }

    original();
    is_complete = false;
    copy();
    down_right();
    is_complete = complete();
    if (is_complete) {
        cout << 1;
        return 0;
    }

    original();
    is_complete = false;
    copy();
    down_left();
    is_complete = complete();
    if (is_complete) {
        cout << 1;
        return 0;
    }

    original();
    is_complete = false;
    copy();
    front_left();
    is_complete = complete();
    if (is_complete) {
        cout << 1;
        return 0;
    }

    original();
    is_complete = false;
    copy();
    front_right();
    is_complete = complete();
    if (is_complete) {
        cout << 1;
        return 0;
    }

    original();
    is_complete = false;
    copy();
    back_left();
    is_complete = complete();
    if (is_complete) {
        cout << 1;
        return 0;
    }

    original();
    is_complete = false;
    copy();
    back_right();
    is_complete = complete();
    if (is_complete) {
        cout << 1;
        return 0;
    }

    if (!is_complete)
        cout << 0;

    return 0;
}