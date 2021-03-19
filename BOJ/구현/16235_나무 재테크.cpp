/*
구현, 시뮬레이션 문제는 문제 이해가 제일 우선인 것 같다.
그래야 입력 값이 뭘 나타내는지, 변수는 어떻게 잡아야하는지를 알 수 있다.

해결하지 못한 이유 중에 하나는 같은 칸에 나무가 여러개 들어갈 수 있다는 것이었다.
같은 칸에 들어가려면 한 좌표마다 나무 나이를 저장할 벡터가 필요했는데 이를 어떻게 설정해야 하는지 잘 몰랐다.
찾아보니 간단하게 3차원으로 만들면 됐었다.

그 이후에는 조건에 맞게 하면 되는데 이것도 헷갈릴 여지가 많았다.
양분을 먹되 자기 나이만큼 먹어야되고 양분을 못먹으면 죽으며, 죽은 나무는 다시 양분이 된다는 점을 만들어야 한다.
그리고 죽은 나무를 제외하고 다시 나이먹은 나무를 재추가 해서 나무벡터를 새로 갱신해야된다.

가을, 겨울의 작업은 그렇게 어렵지 않았다.

결과적으로 좌표마다 나무가 여러개 들어갈 수 있는데 이걸 잘 잡아야하고
문제 조건을 하나씩 따져가면서 코드를 짜야한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, k;
int nutrient[10][10]; //겨울에 추가되는 양분
int arr[10][10];    //처음 양분의 양
vector<int> v[10][10];  //나무 위치, 나이

int dy[8] = { -1,-1,-1,0,0,1,1,1 };
int dx[8] = { -1,0,1,-1,1,-1,0,1 };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> nutrient[i][j];  //겨울에 추가할 양분
            arr[i][j] = 5;  //양분은 전부 5
        }


    for (int i = 0; i < m; ++i) {
        int y, x, age;
        cin >> y >> x >> age;
        v[y - 1][x - 1].push_back(age);
    }

    for (int i = 0; i < k; ++i) {
        //봄, 여름
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                //나이 적은 순으로 정렬
                if (v[y][x].size()) {
                    int dead = 0;
                    vector<int> temp;

                    sort(v[y][x].begin(), v[y][x].end());
                    for (int j = 0; j < v[y][x].size(); ++j) {
                        int age = v[y][x][j];
                        //(y,x)에 있는 양분이 나무의 나이보다 크거나 같으면 양분을 먹는다.
                        if (arr[y][x] >= age) {
                            arr[y][x] -= age;
                            temp.push_back(age + 1);    //살아있는 나무를 temp에 저장
                        }
                        else
                            //양분을 못먹은 나무는 죽는다.
                            dead += age / 2;
                    }

                    //죽은 나무를 제외하고 살아있는 나무의 나이를 추가하기 위해 갱신한다.
                    v[y][x].clear();
                    for (int j = 0; j < temp.size(); ++j)
                        v[y][x].push_back(temp[j]);
                    arr[y][x] += dead;  //죽은 나무는 양분이 된다.

                }
            }
        }

        //가을, 겨울
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                if (v[y][x].size()) {
                    for (int j = 0; j < v[y][x].size(); ++j) {
                        int age = v[y][x][j];
                        //나이가 5의 배수일때
                        if (age % 5 == 0) {
                            //나무 번식
                            for (int j = 0; j < 8; ++j) {
                                int ny = y + dy[j];
                                int nx = x + dx[j];
                                if (0 <= ny && ny < n && 0 <= nx && nx < n)
                                    v[ny][nx].push_back(1); //나이가 1인 나무 추가
                            }
                        }
                    }
                }
                //겨울에 양분 추가
                arr[y][x] += nutrient[y][x];
            }

        }
    }

    //나무 갯수만큼 더해서 출력
    int ret = 0;
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            if (v[y][x].size()) {
                ret += v[y][x].size();
            }

        }
    }

    cout << ret;
    return 0;
}