#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100001
int T;
int n;
int arr[2][MAX];
int DP[2][MAX];


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;

    while (T--) {
        cin >> n;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> arr[i][j];
            }
        }

        //DP 초기화
        memset(DP, 0, sizeof(DP));

        //처음과 두번째까지는 지그재그로 선택
        DP[0][0] = arr[0][0];
        DP[1][0] = arr[1][0];
        DP[0][1] = DP[1][0] + arr[0][1];
        DP[1][1] = DP[0][0] + arr[1][1];

        //세번째 부터 지그재그로 선택하는것, 두번째 전의 첫번째, 두번째 줄 고르는 것 중 최대값
        int ans = 0;
        for (int i = 2; i < n; ++i) {
            DP[0][i] = max(DP[1][i - 1] + arr[0][i], DP[1][i - 2] + arr[0][i]);
            DP[1][i] = max(DP[0][i - 1] + arr[1][i], DP[0][i - 2] + arr[1][i]);

        }

        cout << max(DP[0][n - 1], DP[1][n - 1]) << "\n";

    }

    return 0;
}