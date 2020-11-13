/*
배열이 4개라서 4중 for문 돌리면 당연히 시간초과가 나온다.
1208번 문제를 보고 나서 그런지 배열을 두 개씩 묶어서 처리하는 것까지는 알 수 있었다.
그리고 두 배열에 대해 모든 경우의 수를 따지니까 시간초과가 나왔다.
여기서 시간초과가 안나는 다른 방법을 찾아야 했는데 찾지 못했다.
검색을 해보니 잊고 있었던 lower_bound, upper_bound를 쓰면 갯수를 쉽게 구할 수 있었다.

A,B,C,D 배열 4개를 선언하면 메모리초과가 난다. 2차원 배열로 선언하면 해결된다.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;
#define MAX 4001
long long arr[MAX][4];
int N;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> arr[i][j];
        }
    }

    //c랑 d만 더해서 따로 저장
    vector<long long> cd;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cd.push_back(arr[i][2] + arr[j][3]);
        }

    }

    //lower, upper_bound 쓰기 위해 cd 정렬
    sort(cd.begin(), cd.end());

    //a와 b를 더한 값의 절대값이 cd배열에 있으면 그 개수만큼 세줌
    long long ans = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            long long half = arr[i][0] + arr[j][1];
            long long low = lower_bound(cd.begin(), cd.end(), -half) - cd.begin();
            long long high = upper_bound(cd.begin(), cd.end(), -half) - cd.begin();
            if (half + cd[low] == 0)
                ans += (high - low);
        }

    }
    cout << ans;

    return 0;
}