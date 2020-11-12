/*
1158번 보다 시간이 덜 걸려야한다.
처음에는 시간초과 때문에 못풀어서 다른 블로그 참고해서 풀었는데도 시간초과가 났다.
모듈러를 사용해서 푸는 풀이는 시간제한이 바뀌어서 오답처리가 났다.
세그먼트 트리 방법을 이용한 코드를 올려보니 정답 처리가 됐다.
세그먼트 트리를 공부 해야겠다...
*/

//오답처리난 코드
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);


    int n, k, temp;

    cin >> n >> k;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        v[i] = i + 1;
    }

    int idx = 0;
    vector<int> ans;
    while (!v.empty()) {
        idx = (idx + k - 1) % v.size();
        ans.push_back(v[idx]);
        v.erase(v.begin() + idx);
    }

    cout << "<";
    for (int i = 0; i < n; ++i) {
        cout << ans[i];
        if (i < n - 1)
            cout << ", ";
    }
    cout << ">";

    return 0;
}


/////////////////////////////////////////
//정답 처리 코드. 아직 이해 못함...
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int seg[400040];
int n, m;
vector<int> ans;
int update(int pos, int val, int node, int x, int y) {
    if (pos < x || y < pos)
        return seg[node];
    if (x == y)
        return seg[node] = val;
    int mid = (x + y) >> 1;
    return seg[node] = update(pos, val, node * 2, x, mid) + update(pos, val, node * 2 + 1, mid + 1, y);
}
int query(int val, int node, int x, int y) {
    if (x == y)
        return x;
    if (seg[node * 2] >= val)
        return query(val, node * 2, x, (x + y) / 2);
    else
        return query(val - seg[node * 2], node * 2 + 1, (x + y) / 2 + 1, y);
}
int squery(int lo, int hi, int node, int x, int y) {
    if (y < lo || hi < x)
        return 0;
    if (lo <= x && y <= hi)
        return seg[node];
    int mid = (x + y) >> 1;
    return squery(lo, hi, node * 2, x, mid) + squery(lo, hi, node * 2 + 1, mid + 1, y);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        update(i, 1, 1, 1, n);
    int mod = n - 1;
    ans.push_back(m);
    update(m, 0, 1, 1, n);
    for (int i = 2; i <= n; i++) {
        int x = (squery(1, ans.back(), 1, 1, n) + m) % mod;
        if (!x)x = mod;
        ans.push_back(query(x, 1, 1, n));
        update(ans.back(), 0, 1, 1, n);
        mod--;
    }
    printf("<");
    for (int i = 0; i < ans.size(); i++) {
        if (i == ans.size() - 1)
            printf("%d>\n", ans[i]);
        else
            printf("%d, ", ans[i]);
    }
    return 0;
}