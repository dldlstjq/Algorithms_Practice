/*
mCn인 조합으로 바로 해결됐다.
원래 점화식은 이런 형태이다.

for(i=0;i<=m;i++) d[1][i] = i;
for(i=2;i<=n;i++){
	for(j=i;j<=m;j++){
		for(k=j;k>=i;k--){
			d[i][j]+=d[i-1][k-1];
		}
	}
}
N=2, M=4인 경우를 해당 식으로 계산해보면 
d[2][4] = (d[1][3] + d[1][2] + d[1][1]) 이 된다.

*/

// 다시 품. 조합으로 풀면 쉽게 풀리는 듯. 조합을 dp로 구현할 수 있는지 묻는 문제.

#include <iostream>
#include <cstring>

using namespace std;

int N, M;
long long cache[31][31];

int solve(int n, int r) {
	if (n == r || r == 0)
		return 1;
	long long& ret = cache[n][r];
	if (ret != -1)return ret;
	ret = solve(n - 1, r - 1) + solve(n - 1, r);
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		memset(cache, -1, sizeof(cache));
		cin >> N >> M;
		cout << solve(M, N) << "\n";
	}

	return 0;
}