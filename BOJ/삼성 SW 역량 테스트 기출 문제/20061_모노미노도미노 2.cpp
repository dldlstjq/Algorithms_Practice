/*
문제에 맞게 구현했고 예제도 다 맞게 나오는데 틀렸다.
시작부터 틀려 입력에 문제가 있다고 생각했고 다른 사람의 풀이를 참고해 입력을 고치니 정답이었다.
한개짜리 블록은 쉬운데 1x2 블록을 옮기는 과정에서 복잡하게 접근했던 것 같다.

블록을 옮기는 과정에서 점수가 난 후 블록을 옮겨줄때 끝에서부터 연한색 칸까지 블록을 옮겨줘야 한다.
처음에 이 부분을 간과해서 시간이 제법 걸렸다.
그리고 몇개의 블록이 사라졌는지 갯수와 행을 저장한 다음 없어진 행이나 열의 끝에서부터 없어진 수 만큼
이동하도록 했다. row와 col의 사이즈가 없어진 행, 열의 갯수인데 r,c라는 변수를 하나 더 생성했다.
*/

//2021.04.20 다시 풀이
//블록을 내려줄때 인덱스 설정을 for문 안에서 말고(9-cnt) 값을 바꿔줄때 i-cnt로 해주는게 더 보기 좋을 것 같다.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 10;
int board[MAX][MAX];
int copy_board[MAX][MAX];

int N;
int ret;

void move_block(int t, int x, int y) {

    if (t == 1) {
        int r = x, c = y;
        //초록색 칸
        while (1) {
            r += 1;
            if (r >= MAX || board[r][c] == 1) {
                r -= 1;
                break;
            }
        }
        board[r][c] = 1;

        r = x, c = y;
        //파란색 칸
        while (1) {
            c += 1;
            if (c >= MAX || board[r][c] == 1) {
                c -= 1;
                break;
            }
        }
        board[r][c] = 1;
    }

    else if (t == 2) {
        int r = x, c = y;
        //초록색 칸. 밑으로 내려갈 때 둘다 검사
        while (r + 1 < MAX && board[r + 1][c] != 1 && board[r + 1][c + 1] != 1) {
            r += 1;
        }
        board[r][c] = 1; board[r][c + 1] = 1;

        r = x, c = y;
        //파란색 칸. 가장 오른쪽 블록만 확인
        while (c + 2 < MAX && board[r][c + 2] != 1) {
            c += 1;
        }
        board[r][c] = 1; board[r][c + 1] = 1;
    }

    else if (t == 3) {
        int r = x, c = y;
        //초록색 칸. 밑으로 내려갈 때 둘다 검사
        while (r + 2 < MAX && board[r + 2][c] != 1) {
            r += 1;
        }
        board[r][c] = 1; board[r + 1][c] = 1;

        r = x, c = y;
        //파란색 칸. 가장 오른쪽 블록만 확인
        while (c + 1 < MAX && board[r][c + 1] != 1 && board[r + 1][c + 1] != 1) {
            c += 1;
        }
        board[r][c] = 1; board[r + 1][c] = 1;
    }
}

//초록색, 파란색 칸 확인
void is_full() {
    //초록색
    vector<int> v;
    for (int i = 6; i < MAX; ++i) {
        int cnt = 0;
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 1)
                cnt++;
        }
        //해당 행에 블록이 가득 차면 점수 올리고 지운다.
        if (cnt == 4) {
            ret++;
            v.push_back(i);
            for (int j = 0; j < 4; ++j)
                board[i][j] = 0;
        }

    }

    if (!v.empty()) {
        int last_row = v.back();
        int size = v.size();
        //last_row-size 부터 연한 칸까지 없어진 수만큼 블록을 내린다.
        for (int i = last_row - size; i >= 4; --i) {
            for (int j = 0; j < 4; ++j) {
                board[i + size][j] = board[i][j];
                board[i][j] = 0;
            }
        }
    }


    v.clear();

    //파란색
    for (int i = 6; i < MAX; ++i) {
        int cnt = 0;
        for (int j = 0; j < 4; ++j) {
            if (board[j][i] == 1)
                cnt++;
        }
        //해당 행에 블록이 가득 차면 점수 올리고 지운다.
        if (cnt == 4) {
            ret++;
            v.push_back(i);
            for (int j = 0; j < 4; ++j)
                board[j][i] = 0;
        }

    }

    if (!v.empty()) {
        int last_row = v.back();
        int size = v.size();
        //last_row-size 부터 연한 칸까지 없어진 수만큼 블록을 내린다.
        for (int i = last_row - size; i >= 4; --i) {
            for (int j = 0; j < 4; ++j) {
                board[j][i + size] = board[j][i];
                board[j][i] = 0;
            }
        }
    }

}

void check_light() {
    //연한 초록색. 행이나 열에 블록이 있으면 cnt가 카운트된다.
    int cnt = 0;
    for (int i = 4; i <= 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j]) {
                cnt++;
                break;
            }

        }
    }

    if (cnt != 0) {
        //cnt 수만큼 블록을 내린다.
        for (int i = 9 - cnt; i >= 4; --i) {
            for (int j = 0; j < 4; ++j) {
                board[i + cnt][j] = board[i][j];
                board[i][j] = 0;
            }
        }
    }


    //연한 파란색
    cnt = 0;
    for (int i = 4; i <= 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[j][i]) {
                cnt++;
                break;
            }

        }
    }

    if (cnt != 0) {
        //cnt 수만큼 블록을 내린다.
        for (int i = 9 - cnt; i >= 4; --i) {
            for (int j = 0; j < 4; ++j) {
                board[j][i + cnt] = board[j][i];
                board[j][i] = 0;
            }
        }
    }

}

int block_cnt() {
    int cnt = 0;

    for (int i = 6; i < MAX; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 1)
                cnt++;
        }
    }

    for (int i = 6; i < MAX; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[j][i] == 1)
                cnt++;
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i) {
        int t, x, y;
        cin >> t >> x >> y;

        move_block(t, x, y);    //블록 이동

        is_full();  //행이나 열이 가득찼는지 확인
        check_light();  //연한 부분 체크

    }
    cout << ret << "\n";
    cout << block_cnt();
    return 0;
}

///////////////////////// 다른 사람 참고한 풀이

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int board[10][10];
int N;
int T, X, Y;

int point;

//가득 찬 행과 열을 저장한다.
vector<int> row;
vector<int> col;

int r, c;

//입력에 맞는 블록을 초록색, 파란색 칸으로 계속이동한다.
//중간에 블록이 있거나 경계에 도착하면 멈춘다.
void input(int t, int x, int y) {
    //1x1 (x,y)
    if (t == 1) {
        //초록색 칸
        for (int i = 4; i <= 9; ++i) {
            if (i == 9) {
                board[i][y] = 1;
                break;
            }
            if (board[i + 1][y] == 1) {
                board[i][y] = 1;
                break;
            }
        }
        //파란색 칸
        for (int i = 4; i <= 9; ++i) {
            if (i == 9) {
                board[x][i] = 1;
                break;
            }
            if (board[x][i + 1] == 1) {
                board[x][i] = 1;
                break;
            }
        }
    }

    //1x2 (x,y) (x,y+1)
    else if (t == 2) {
        int tmpidx = 10;
        //초록색 칸
        for (int i = 4; i <= 9; ++i) {
            if (board[i][y] == 1 || board[i][y + 1] == 1) {
                tmpidx = i;
                break;
            }
        }
        board[tmpidx - 1][y] = 1;
        board[tmpidx - 1][y + 1] = 1;

        //파란색 칸
        tmpidx = 10;
        for (int i = 4; i <= 9; ++i) {
            if (board[x][i] == 1) {
                tmpidx = i;
                break;
            }
        }
        board[x][tmpidx - 1] = 1;
        board[x][tmpidx - 2] = 1;
    }

    //2x1 (x,y) (x+1,y)
    else if (t == 3) {
        //초록색 칸
        int tmpidx = 10;
        for (int i = 4; i <= 9; ++i) {
            if (board[i][y]) {
                tmpidx = i;
                break;
            }
        }
        board[tmpidx - 1][y] = 1;
        board[tmpidx - 2][y] = 1;

        //파란색 칸
        tmpidx = 10;
        for (int i = 4; i <= 9; ++i) {
            if (board[x][i] == 1 || board[x + 1][i] == 1) {
                tmpidx = i;
                break;
            }
        }
        board[x][tmpidx - 1] = 1;
        board[x + 1][tmpidx - 1] = 1;
    }
}

//초록색 칸 점수
void green_point() {
    r = 0;
    row.clear();
    //초록색 칸에 가득 찬 행이 있으면 점수를 올린다.
    for (int i = 6; i < 10; ++i) {
        int cnt = 0;
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 1)
                cnt++;
        }
        //점수를 올리고 해당 행이 뭔지 벡터에 넣고 수를 카운트한다.
        if (cnt == 4) {
            row.push_back(i);
            point++;
            r++;
        }
    }
}

//파란색 칸 점수
void blue_point() {
    c = 0;
    col.clear();
    //파란색 칸에 가득 찬 행이 있으면 점수를 올린다.
    for (int i = 6; i < 10; ++i) {
        int cnt = 0;
        for (int j = 0; j < 4; ++j) {
            if (board[j][i] == 1)
                cnt++;
        }
        //점수를 올리고 해당 열이 뭔지 벡터에 넣고 수를 카운트한다.
        if (cnt == 4) {
            col.push_back(i);
            point++;
            c++;
        }
    }
}

//연한 칸 체크
void check_light() {
    int cnt = 0;
    //연한 초록색
    for (int i = 4; i <= 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 1) {
                cnt++;
                break;
            }
        }
    }
    //초록색칸 블록을 이동한다.
    if (cnt != 0) {
        for (int i = 9; i >= 4; --i) {
            for (int j = 0; j < 4; ++j) {
                board[i][j] = board[i - cnt][j];
            }
        }
    }
    //기존 연한칸 블록은 지워준다.
    for (int i = 4; i <= 5; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }

    //연한 파란색
    cnt = 0;
    for (int i = 4; i <= 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[j][i] == 1) {
                cnt++;
                break;
            }
        }
    }
    //파란색칸 블록을 이동한다.
    if (cnt != 0) {
        for (int i = 9; i >= 4; --i) {
            for (int j = 0; j < 4; ++j) {
                board[j][i] = board[j][i - cnt];
            }
        }
    }
    //기존 연한칸 블록은 지워준다.
    for (int i = 4; i <= 5; i++) {
        for (int j = 0; j < 4; j++) {
            board[j][i] = 0;
        }
    }
}

//칸의 블록 개수 출력
void print() {
    int cnt = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 6; j < 10; ++j) {
            if (board[i][j] == 1)
                cnt++;
            if (board[j][i] == 1)
                cnt++;
        }
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> T >> X >> Y;

        //블록을 입력한다.
        input(T, X, Y);

        //초록색, 파란색 칸에 대한 점수를 확인한다.
        green_point();
        blue_point();

        //점수가 나면 없앤 행 만큼 밑으로 내려준다.
        //row벡터에 저장된 행 중 제일 마지막에 있는 원소가
        //가장 마지막에 점수가 난 행이다. 이 행의 위에서 부터 한칸씩 내려주면 된다.
        if (r != 0) {
            int start = row.back();
            for (int i = start; i >= 4; --i) {
                for (int j = 0; j < 4; ++j) {
                    board[i][j] = board[i - r][j];
                }
            }

        }
        //점수가 나면 없앤 열 만큼 밑으로 내려준다.
        if (c != 0) {
            int start = col.back();
            for (int i = start; i >= 4; --i) {
                for (int j = 0; j < 4; ++j) {
                    board[j][i] = board[j][i - c];
                }
            }
        }

        //연한 색깔 체크
        check_light();

    }

    cout << point << "\n";
    print();

    return 0;
}




//참고한 다른 사람 풀이.
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;


int N, t, x, y;
int ground[10][10]; //0~9
int resultscore;
int resultblock;

void fillnemo() {
	if (t == 1) {
		for (int i = 4; i <= 9; i++) { //파란색
			if (i == 9) { ground[x][i] = 1; break; }
			if (ground[x][i + 1] == 1) { ground[x][i] = 1; break; }
		}
		for (int i = 4; i <= 9; i++) { //초록색
			if (i == 9) { ground[i][y] = 1; break; }
			if (ground[i + 1][y] == 1) { ground[i][y] = 1; break; }
		}
	}
	else if (t == 2) {
		int tmpindex = 10;
		for (int i = 4; i <= 9; i++) { //파란색
			if (ground[x][i] == 1) {
				tmpindex = i;
				break;
			}
		}
		ground[x][tmpindex - 1] = 1; ground[x][tmpindex - 2] = 1;

		tmpindex = 10;
		for (int i = 4; i <= 9; i++) { //초록색
			if (ground[i][y] == 1 || ground[i][y + 1] == 1) {
				tmpindex = i;
				break;
			}
		}
		ground[tmpindex - 1][y] = 1; ground[tmpindex - 1][y + 1] = 1;
	}
	else {
		int tmpindex = 10;
		for (int i = 4; i <= 9; i++) { //파란색
			if (ground[x][i] == 1 || ground[x + 1][i] == 1) {
				tmpindex = i;
				break;
			}
		}
		ground[x][tmpindex - 1] = 1; ground[x + 1][tmpindex - 1] = 1;
		tmpindex = 10;
		for (int i = 4; i <= 9; i++) { //초록색
			if (ground[i][y] == 1) {
				tmpindex = i;
				break;
			}
		}
		ground[tmpindex - 1][y] = 1; ground[tmpindex - 2][y] = 1;
	}
}

void delblock() {
	//파란색
	for (int i = 9; i >= 6; i--) {
		bool checking = false;
		for (int j = 0; j < 4; j++) {
			if (ground[j][i] == 0) { checking = true; break; }
		}
		if (checking == false) { //4블록이 꽉찬경우
			resultscore++;
			for (int k = i; k >= 4; k--) { //이동시키기
				for (int l = 0; l < 4; l++) { ground[l][k] = ground[l][k - 1]; }
			}
			i++; // 두줄이 한번에 꽉차는 경우를 위해서 이동시킨후 다시 그 행,렬부터 확인해야됨
		}
	}
	//초록색
	for (int i = 9; i >= 6; i--) {
		bool checking = false;
		for (int j = 0; j < 4; j++) {
			if (ground[i][j] == 0) { checking = true; break; }
		}
		if (checking == false) {
			resultscore++;
			for (int k = i; k >= 4; k--) { //이동시키기
				for (int l = 0; l < 4; l++) { ground[k][l] = ground[k - 1][l]; }
			}
			i++; // 두줄이 한번에 꽉차는 경우를 위해서 이동시킨후 다시 그 행,렬부터 확인해야됨
		}
	}
}

void moveblock() {
	//연한 파란색
	bool checking = false;
	int checkingcount = 0;
	for (int i = 4; i <= 5; i++) {
		for (int j = 0; j < 4; j++) {
			if (ground[j][i] == 1) { checkingcount++; break; }
		}
	}
	if (checkingcount != 0) {
		for (int i = 9; i >= 4; i--) {
			for (int j = 0; j < 4; j++) {
				ground[j][i] = ground[j][i - checkingcount];
			}
		}
	}
	for (int i = 4; i <= 5; i++) {
		for (int j = 0; j < 4; j++) {
			ground[j][i] = 0;
		}
	}
	//연한 초록색
	checking = false;
	checkingcount = 0;
	for (int i = 4; i <= 5; i++) {
		for (int j = 0; j < 4; j++) {
			if (ground[i][j] == 1) { checkingcount++; break; }
		}
	}
	if (checkingcount != 0) {
		for (int i = 9; i >= 4; i--) {
			for (int j = 0; j < 4; j++) {
				ground[i][j] = ground[i - checkingcount][j];
			}
		}
	}
	for (int i = 4; i <= 5; i++) {
		for (int j = 0; j < 4; j++) {
			ground[i][j] = 0;
		}
	}
}
void watchground() {
	cout << endl;
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			cout << ground[i][j];
		}
		cout << endl;
	}
}
void getblock() {
	for (int i = 6; i <= 9; i++) {
		for (int j = 0; j < 4; j++) {
			if (ground[j][i] == true) resultblock++;
		}
	}
	for (int i = 6; i <= 9; i++) {
		for (int j = 0; j < 4; j++) {
			if (ground[i][j] == true) resultblock++;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N;
	while (N--) {
		cin >> t >> x >> y;
		fillnemo(); // 블록 초록색 파란색으로 이동시키기
		delblock(); // 4블록이 꽉찬 행,또는 렬 삭제 (점수 획득)
		moveblock(); // 연한초록, 연한파란색에 블록이 있을 경우 이동
	}
	getblock();
	cout << resultscore << "\n";
	cout << resultblock << "\n";

	return 0;
}