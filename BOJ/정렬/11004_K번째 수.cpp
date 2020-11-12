/*
벡터와 배열 둘다 사용해봤는데 벡터가 메모리 더 많이 잡아먹음
검색해보니 벡터가 메모리 공간 더 차지함. 속도도 배열보단 느림.
대신 삽입, 삭제가 빈번할때는 유용
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    int tmp;
    vector<int> v;

    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }

    sort(v.begin(), v.end());

    cout << v[k - 1];

    return 0;
}