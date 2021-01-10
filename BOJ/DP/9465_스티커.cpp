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



///////////////////////////////////////
/*재귀함수로 푼 풀이. 위의 방식대로 푼 것보다 메모리와 시간이 더 들었다.
종만북에서 설명한 대로 계산은 조금 느리게 나왔다.
*/
#include <iostream>
#include <cstring>

using namespace std;

int cache[2][100001];
int sticker[2][100001];
int n;

int solve(int y, int x) {
	//기저사례: x가 끝에 오면 해당 점수 반환
	if (x == n - 1)
		return sticker[y][x];
	int& ret = cache[y][x];
	if (ret != -1)return ret;
	ret = 0;
	//첫째 줄일때는 둘째 줄로 이동
	if (y == 0) {
		if (x + 1 <= n - 1)
			ret = max(ret, solve(y + 1, x + 1) + sticker[y][x]);
		if (x + 2 <= n - 1)
			ret = max(ret, solve(y + 1, x + 2) + sticker[y][x]);
	}
	//둘째 줄일때는 첫째 줄로 이동
	else {
		if (x + 1 <= n - 1)
			ret = max(ret, solve(y - 1, x + 1) + sticker[y][x]);
		if (x + 2 <= n - 1)
			ret = max(ret, solve(y - 1, x + 2) + sticker[y][x]);
	}
	return ret;

}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		memset(cache, -1, sizeof(cache));

		cin >> n;
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < n; ++j)
				cin >> sticker[i][j];
		//(0,0), (1,0) 둘 중 점수 더 높은 쪽이 최대값
		cout << max(solve(0, 0), solve(1, 0)) << "\n";
	}

	return 0;
}