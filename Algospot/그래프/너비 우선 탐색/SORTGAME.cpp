/*
bfs를 이용해서 모든 배열마다 뒤집는데 얼마나 걸리는지 계산한다.
들어온 배열을 하나씩 다 수행하기에는 시간이 많이 걸린다.
최적화를 통해 0, ... ,n-1 까지 도달하는데 필요한 뒤집기 수를 미리 계산해놓고
입력 값을 0, ..., n-1로 바꿔 계산하면 시간이 더 적게 걸린다.

처음에는 이 말을 이해하지 못해 solve()함수가 왜 필요하나 싶었는데
숫자가 큰 경우도 0~n-1 까지의 수로 바꾸기 위해 solve()를 사용했다.
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

map<vector<int>, int> toSort;
//[0, ..., n-1]의 모든 순열에 대해 toSort[]를 계산해 저장한다.
void precalc(int n) {
    vector<int> perm(n);
    for (int i = 0; i < n; ++i)
        perm[i] = i;
    queue<vector<int>> q;
    q.push(perm);
    toSort[perm] = 0;
    while (!q.empty()) {
        vector<int> here = q.front();
        q.pop();
        int cost = toSort[here];
        for (int i = 0; i < n; ++i) {
            for (int j = i + 2; j <= n; ++j) {
                reverse(here.begin() + i, here.begin() + j);
                if (toSort.count(here) == 0) {
                    toSort[here] = cost + 1;
                    q.push(here);
                }
                reverse(here.begin() + i, here.begin() + j);
            }
        }
    }
}

int solve(const vector<int>& perm) {
    //perm을 [0, ... , n-1]의 순열로 반환한다.
    int n = perm.size();
    vector<int> fixed(n);
    for (int i = 0; i < n; ++i) {
        int smaller = 0;
        for (int j = 0; j < n; ++j) {
            if (perm[j] < perm[i])
                ++smaller;
        }
        fixed[i] = smaller;
    }
    return toSort[fixed];
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int n;
        cin >> n;
        vector<int> v(n, 0);
        for (int i = 0; i < n; ++i)
            cin >> v[i];

        precalc(n);
        cout << solve(v) << "\n";
    }

    return 0;
}

