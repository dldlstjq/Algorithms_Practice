/*
문제 그대로 R, C 값에 따라 연산을 해주면 됐다.
배열 값과 그 수가 등장한 횟수를 같이 저쟝해야했기 때문에 vector<pair>를 사용했고
(수, 나온 횟수)로 저장해 정렬했다. 나온 횟수를 기준으로 하기 위해 cmp를 따로 설정했는데
(나온 횟수, 수)로 저장하면 굳이 cmp를 안 만들어도 됐다. 이런건 잘 생각해서 불필요한 코드를 줄여야겠다.

그리고 새로 만든 행, 열의 수에 따라 row, col값을 갱신해서 이어나가면 된다.
처음엔 테스트케이스 답이 제대로 안나왔다. 새로 만든 배열이면 기존의 배열 값들은 모두 지워져야 한다.
이걸 생각못해서 기존 배열 값이 남아있는 상태여서 예제가 제대로 작동하지 않았다.

->코드에서는 새로 만든 배열을 삽입하고 남은 부분을 삭제하는 방식으로 했는데 애초에 기존 행렬의 원소를 모두 저장해서
기존 배열을 초기화 시킨 다음 하나씩 값을 넣어도 된다. 그럴 경우엔 vector<pair>를 2차원으로 선언해야 한다.

제출했을 때도 오답을 받았는데 100초가 넘으면 -1 출력이기 때문에 100초도 값을 출력해야 했다.
따라서 전체 반복문을 0~100까지로 설정했다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int num[101];
int arr[101][101];

vector<pair<int, int>> v;
int temp[101];

bool cmp(pair<int, int>a, pair<int, int>b) {
    if (a.second == b.second)
        return a.first < b.first;
    else
        return a.second < b.second;
}

//수가 얼마나 나왔는지 체크
void count() {
    for (int k = 1; k <= 100; ++k) {
        if (num[k] != 0)
            v.push_back({ k,num[k] });
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int r, c, k;
    cin >> r >> c >> k;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cin >> arr[i][j];

    int row = 3;
    int col = 3;
    int time = 0;
    bool is_ans = false;
    //0초에서 100초 동안 반복
    for (int t = 0; t <= 100; ++t) {
        //인덱스0부터 배열을 잡았기 때문에 r-1,c-1로 한다.
        if (arr[r - 1][c - 1] == k) {
            time = t;
            is_ans = true;
            break;
        }

        //행의 수>=열의 수
        if (row >= col) {
            int new_col = 0;
            //열의 수만큼 반복하면서 arr배열에 있는 수만큼 카운트한다.
            for (int i = 0; i < row; ++i) {
                memset(num, 0, sizeof(num));
                memset(temp, 0, sizeof(temp));
                v.clear();

                for (int j = 0; j < col; ++j) {
                    num[arr[i][j]]++;
                }

                //1~100중 배열에 나온 수가 있으면 해당 수와 카운트를 페어로 넣어준다.
                count();

                //정렬해서 새로운 배열로 만든다.
                sort(v.begin(), v.end(), cmp);
                //정렬 결과를 임시 배열에 저장한 후
                int cur = 0;
                int length = v.size() * 2;
                for (int k = 0; k < length; k += 2) {
                    temp[k] = v[cur].first;
                    temp[k + 1] = v[cur].second;
                    cur++;
                }
                //새로운 정렬값을 원래 배열에 삽입
                for (int k = 0; k < length; ++k)
                    arr[i][k] = temp[k];
                //length부터 끝까지는 원래 있던 원소를 지운다.
                for (int k = length; k < 101; ++k)
                    arr[i][k] = 0;

                //크기가 가장 큰 행은 열의 개수가 가장 많다
                if (i == 0)
                    new_col = length;
                else
                    new_col = max(new_col, length);

            }
            //열의 갯수 갱신
            col = new_col;
        }

        else {
            int new_row = 0;
            //열의 수만큼 반복하면서 arr배열에 있는 수만큼 카운트한다.
            for (int i = 0; i < col; ++i) {
                memset(num, 0, sizeof(num));
                memset(temp, 0, sizeof(temp));
                v.clear();

                for (int j = 0; j < row; ++j) {
                    num[arr[j][i]]++;
                }

                //1~100중 배열에 나온 수가 있으면 해당 수와 카운트를 페어로 넣어준다.
                count();

                //정렬해서 새로운 배열로 만든다.
                sort(v.begin(), v.end(), cmp);
                //정렬 결과를 임시 배열에 저장한 후
                int cur = 0;
                int length = v.size() * 2;
                for (int k = 0; k < length; k += 2) {
                    temp[k] = v[cur].first;
                    temp[k + 1] = v[cur].second;
                    cur++;
                }

                for (int k = 0; k < v.size() * 2; ++k)
                    arr[k][i] = temp[k];
                //length부터 끝까지는 원래 있던 원소를 지운다.
                for (int k = length; k < 101; ++k)
                    arr[k][i] = 0;

                //크기가 가장 큰 열은 행의 개수가 가장 많다
                if (i == 0)
                    new_row = length;
                else
                    new_row = max(new_row, length);

            }
            //행의 갯수 갱신
            row = new_row;
        }

    }

    if (is_ans)
        cout << time;
    else
        cout << -1;

    return 0;
}