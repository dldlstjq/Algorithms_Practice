/*
장장 4~5시간 걸친 끝에 해결했다.
다른 방법이 있는줄 알았는데 그냥 큐브 돌렸을때 해당하는 곳을 직접 바꿔줬다.

처음엔 돌아가는 면과 연결된 부분만 바꿔줬다.
그런데 제대로 된 답이 안나와서 큐브 시뮬레이션 프로그램으로 확인해보니
돌리는 면 자체도 돌아가야 했다.

그걸 생각못해서 답이 안나왔던 것이었다.

결국 면과 연결된 부분이 돌아가고 면 자체도 돌아가기때문에 이 부분을 생각해서 하나씩 구현하니까 답이 나왔다.
*/
#include<iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

//정육면체
char cube[9][12] = {
	{0,0,0,'w','w','w',0,0,0,0,0,0},
	{0,0,0,'w','w','w',0,0,0,0,0,0},
	{0,0,0,'w','w','w',0,0,0,0,0,0},
	{'g','g','g','r','r','r','b','b','b','o','o','o'},
	{'g','g','g','r','r','r','b','b','b','o','o','o'},
	{'g','g','g','r','r','r','b','b','b','o','o','o'},
	{0,0,0,'y','y','y',0,0,0,0,0,0},
	{0,0,0,'y','y','y',0,0,0,0,0,0},
	{0,0,0,'y','y','y',0,0,0,0,0,0}
};

char origin[9][12];	//원래 큐브 형태 저장
char tmp[9][12];	//임시 큐브


//인접한것 뿐만 아니라 해당 면도 같이 돌아간다
void rotate(char face, char dir) {
	//윗면
	if (face == 'U' && dir == '-') {
		//윗면 자체도 돌아간다.
		int w = 3;
		for (int i = 0; i < 3; ++i) {
			int h = 2;
			for (int j = 3; j < 6; ++j) {
				cube[h--][w] = tmp[i][j];
			}
			w++;
		}
		for (int i = 0; i < 12; ++i) {
			cube[3][i] = tmp[3][(i + 9) % 12];

		}
	}
	else if (face == 'U' && dir == '+') {
		int w = 5;
		for (int i = 0; i < 3; ++i) {
			int h = 0;
			for (int j = 3; j < 6; ++j) {
				cube[h++][w] = tmp[i][j];
			}
			w--;
		}
		for (int i = 0; i < 12; ++i) {
			cube[3][i] = tmp[3][(i + 3) % 12];
		}
	}

	//아랫면
	else if (face == 'D' && dir == '-') {
		int w = 3;
		for (int i = 6; i < 9; ++i) {
			int h = 8;
			for (int j = 3; j < 6; ++j) {
				cube[h--][w] = tmp[i][j];
			}
			w++;
		}
		for (int i = 0; i < 12; ++i) {
			cube[5][i] = tmp[5][(i + 3) % 12];

		}
	}
	else if (face == 'D' && dir == '+') {
		int w = 5;
		for (int i = 6; i < 9; ++i) {
			int h = 6;
			for (int j = 3; j < 6; ++j) {
				cube[h++][w] = tmp[i][j];
			}
			w--;
		}
		for (int i = 0; i < 12; ++i) {
			cube[5][i] = tmp[5][(i + 9) % 12];

		}
	}

	//앞면
	else if (face == 'F' && dir == '-') {
		int w = 3;
		for (int i = 3; i < 6; ++i) {
			int h = 5;
			for (int j = 3; j < 6; ++j) {
				cube[h--][w] = tmp[i][j];
			}
			w++;
		}

		cube[2][3] = tmp[3][6]; cube[2][4] = tmp[4][6]; cube[2][5] = tmp[5][6];
		cube[3][2] = tmp[2][5]; cube[4][2] = tmp[2][4]; cube[5][2] = tmp[2][3];

		cube[6][3] = tmp[3][2]; cube[6][4] = tmp[4][2]; cube[6][5] = tmp[5][2];
		cube[3][6] = tmp[6][5]; cube[4][6] = tmp[6][4]; cube[5][6] = tmp[6][3];
	}
	else if (face == 'F' && dir == '+') {
		int w = 5;
		for (int i = 3; i < 6; ++i) {
			int h = 3;
			for (int j = 3; j < 6; ++j) {
				cube[h++][w] = tmp[i][j];
			}
			w--;
		}

		cube[2][3] = tmp[5][2]; cube[2][4] = tmp[4][2]; cube[2][5] = tmp[3][2];
		cube[3][2] = tmp[6][3]; cube[4][2] = tmp[6][4]; cube[5][2] = tmp[6][5];

		cube[6][3] = tmp[5][6]; cube[6][4] = tmp[4][6]; cube[6][5] = tmp[3][6];
		cube[3][6] = tmp[2][3]; cube[4][6] = tmp[2][4]; cube[5][6] = tmp[2][5];
	}

	//뒷면
	else if (face == 'B' && dir == '-') {
		int w = 9;
		for (int i = 3; i < 6; ++i) {
			int h = 5;
			for (int j = 9; j < 12; ++j) {
				cube[h--][w] = tmp[i][j];
			}
			w++;
		}

		cube[0][3] = tmp[5][0]; cube[0][4] = tmp[4][0]; cube[0][5] = tmp[3][0];
		cube[3][0] = tmp[8][3]; cube[4][0] = tmp[8][4]; cube[5][0] = tmp[8][5];

		cube[8][3] = tmp[5][8]; cube[8][4] = tmp[4][8]; cube[8][5] = tmp[3][8];
		cube[3][8] = tmp[0][3]; cube[4][8] = tmp[0][4]; cube[5][8] = tmp[0][5];
	}

	else if (face == 'B' && dir == '+') {
		int w = 11;
		for (int i = 3; i < 6; ++i) {
			int h = 3;
			for (int j = 9; j < 12; ++j) {
				cube[h++][w] = tmp[i][j];
			}
			w--;
		}

		cube[0][3] = tmp[3][8]; cube[0][4] = tmp[4][8]; cube[0][5] = tmp[5][8];
		cube[3][0] = tmp[0][5]; cube[4][0] = tmp[0][4]; cube[5][0] = tmp[0][3];

		cube[8][3] = tmp[3][0]; cube[8][4] = tmp[4][0]; cube[8][5] = tmp[5][0];
		cube[3][8] = tmp[8][5]; cube[4][8] = tmp[8][4]; cube[5][8] = tmp[8][3];
	}

	//왼면
	else if (face == 'L' && dir == '-') {
		int w = 0;
		for (int i = 3; i < 6; ++i) {
			int h = 5;
			for (int j = 0; j < 3; ++j) {
				cube[h--][w] = tmp[i][j];
			}
			w++;
		}

		for (int i = 0; i < 6; ++i)
			cube[i][3] = tmp[(i + 3) % 12][3];

		cube[6][3] = tmp[5][11]; cube[7][3] = tmp[4][11]; cube[8][3] = tmp[3][11];
		cube[3][11] = tmp[2][3]; cube[4][11] = tmp[1][3]; cube[5][11] = tmp[0][3];

	}
	else if (face == 'L' && dir == '+') {
		int w = 2;
		for (int i = 3; i < 6; ++i) {
			int h = 3;
			for (int j = 0; j < 3; ++j) {
				cube[h++][w] = tmp[i][j];
			}
			w--;
		}

		for (int i = 3; i < 9; ++i)
			cube[i][3] = tmp[(i + 9) % 12][3];

		cube[0][3] = tmp[5][11]; cube[1][3] = tmp[4][11]; cube[2][3] = tmp[3][11];
		cube[3][11] = tmp[8][3]; cube[4][11] = tmp[7][3]; cube[5][11] = tmp[6][3];
	}

	//오른면
	else if (face == 'R' && dir == '-') {
		int w = 6;
		for (int i = 3; i < 6; ++i) {
			int h = 5;
			for (int j = 6; j < 9; ++j) {
				cube[h--][w] = tmp[i][j];
			}
			w++;
		}

		for (int i = 3; i < 9; ++i)
			cube[i][5] = tmp[(i + 9) % 12][5];

		cube[0][5] = tmp[5][9]; cube[1][5] = tmp[4][9]; cube[2][5] = tmp[3][9];
		cube[3][9] = tmp[8][5]; cube[4][9] = tmp[7][5]; cube[5][9] = tmp[6][5];

	}
	else if (face == 'R' && dir == '+') {
		int w = 8;
		for (int i = 3; i < 6; ++i) {
			int h = 3;
			for (int j = 6; j < 9; ++j) {
				cube[h++][w] = tmp[i][j];
			}
			w--;
		}

		for (int i = 0; i < 6; ++i)
			cube[i][5] = tmp[(i + 3) % 12][5];

		cube[6][5] = tmp[5][9]; cube[7][5] = tmp[4][9]; cube[8][5] = tmp[3][9];
		cube[3][9] = tmp[2][5]; cube[4][9] = tmp[1][5]; cube[5][9] = tmp[0][5];
	}
}

void print_up() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 3; j < 6; ++j) {
			cout << cube[i][j];
		}
		cout << "\n";
	}
}

void copy(char a[9][12], char b[9][12]) {
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 12; ++j)
			b[i][j] = a[i][j];
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	copy(cube, origin);

	while (t--) {
		int n;
		cin >> n;

		copy(origin, cube);
		copy(cube, tmp);
		for (int i = 0; i < n; ++i) {

			string str;
			cin >> str;

			rotate(str[0], str[1]);


			copy(cube, tmp);
		}
		print_up();
	}

	return 0;
}