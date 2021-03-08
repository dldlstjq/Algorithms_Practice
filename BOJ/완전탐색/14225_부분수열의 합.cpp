/*
처음엔 결과값을 한 배열에다 저장하는 방식으로 접근했는데 
1에서 MAX까지 수 중 안나온값이 제일 먼저 있는게 최소인 수라는걸 생각했다.
1~20*100000 까지 수 중 덧셈해서 나온 값은 체크하고 전체 중 false인 인덱스가 먼저 나온게 최솟값이다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 2000000 + 1;
bool range[MAX];
vector<int> v;
int n;

vector<int> ret;

void solve(int idx, int sum) {
    //인덱스가 n과 같으면 범위 넘어갔기 때문에 sum이 있다는 것을 체크
    if (idx == n) {
        range[sum] = true;
        return;
    }

    solve(idx + 1, sum + v[idx]);
    solve(idx + 1, sum);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        v.push_back(num);
    }
    solve(0, 0);

    //false인 부분이 최소인 자연수
    for (int i = 1; i <= MAX; ++i) {
        if (range[i] == false) {
            cout << i;
            break;
        }
    }

    return 0;
}