/*
a n t i c 까지는 읽어야 하고 그 후 백트래킹으로 하나씩 시도해보면서 모두 읽을 수 있으면
경우를 늘려주는 식으로 생각했다.

접근 방법은 맞았는데 함수를 만드는 과정에서 백트래킹을 어디서 적용해야 하는지, K개를 다 썼을 경우
단어 확인을 어떻게 하는지가 헷갈렸다. 코드를 보면 쉽게 이해가 가는데 과정이 생각보다 쉽지 않다. 
*/

// 2021.06.01 오랜만에 풀어보니 백트래킹이 생각 안났다. 다시 풀어보기

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
bool alphabet[26];    //배운 알파벳은 true
vector<string> v;
int ret;

void solve(int idx, int cnt) {
    //K개를 다 배운 경우
    if (cnt == K) {
        int temp = 0;
        for (int i = 0; i < N; ++i) {
            bool flag = true;
            //익히지 않은 알파벳이 있는 경우 배울수 없는 단어
            for (int j = 0; j < v[i].length(); ++j) {
                if (!alphabet[v[i][j] - 'a']) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                temp++;
        }
        ret = max(ret, temp);
        return;
    }

    //아직 K개를 배우지 않은 경우: 브루트포스
    for (int i = idx; i < 26; ++i) {
        if (!alphabet[i]) {
            alphabet[i] = true;
            solve(i, cnt + 1);
            alphabet[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    //anta tica는 읽어야 한다.
    if (K < 5) {
        cout << 0;
        return 0;
    }

    //전부 읽을 수 있다.
    if (K == 26) {
        cout << N;
        return 0;
    }

    for (int i = 0; i < N; ++i) {
        string str;
        cin >> str;
        string a = str.substr(4, str.length() - 8);
        v.push_back(a);
    }


    //anta tica는 읽어야 한다.
    alphabet['a' - 'a'] = true;
    alphabet['c' - 'a'] = true;
    alphabet['i' - 'a'] = true;
    alphabet['n' - 'a'] = true;
    alphabet['t' - 'a'] = true;

    K -= 5;

    solve(0, 0);

    cout << ret;

    return 0;
}