/*
재귀함수를 이용해야 할 것 같아 다른 재귀 문제를 찾아보며 해결하려 했다.
거의 다 푼 줄 알았는데 인덱스 설정에서 막혀서 풀지 못했다.
다행히 그렇게 이해하기 어려운 재귀함수는 아니었다.
*/

// 2021.07.02 파라미터 값만 잘 설정하면 금방 풀린다.
#include <iostream> 
#include <vector> 
#include <algorithm>
using namespace std;

int k;
vector<int> v;

void solve(int idx, int num, vector<int> lotto) {
    if (num == 6) {
        for (int i = 0; i < num; ++i)
            cout << lotto[i] << ' ';
        cout << "\n";
        return;
    }

    for (int i = idx; i < k; ++i) {
        lotto.push_back(v[i]);
        solve(i + 1, num + 1, lotto);
        lotto.pop_back();
    }
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (1) {
        v.clear();
        cin >> k;
        if (k == 0)
            break;
        for (int i = 0; i < k; ++i) {
            int num;
            cin >> num;
            v.push_back(num);
        }
        vector<int> lotto;
        solve(0, 0, lotto);
        cout << "\n";
    }


    return 0;
}


///////////////////////////////////////////

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int k;
int lotto[13];
vector<int> ans;
int result[13];

//pos는 lotto 인덱스, idx는 result의 인덱스
void dfs(int pos, int idx) {
    //6개면 출력
    if (idx == 6) {
        for (int k = 0; k < 6; k++)
            cout << result[k] << " ";
        cout << "\n";
        return;
    }

    //하나씩 넣어본다
    for (int i = pos; i < k; i++) {
        result[idx] = lotto[i];
        dfs(i + 1, idx + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (1) {
        cin >> k;
        if (k == 0) {
            break;
        }
        for (int i = 0; i < k; i++)
            cin >> lotto[i];

        dfs(0, 0);
        cout << "\n";
    }


    return 0;
}