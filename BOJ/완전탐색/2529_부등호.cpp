/*
순열을 이용해 다시 풀어봤다.
확실히 순열을 이용하니 편하게 풀 수 있었다.
크기가 작은건 0부터 k개까지 저장해놓고 큰거는 9부터 시작해서 k개 될때까지 줄이면서 저장한다.
그리고 부등호에 맞게 순열을 돌려서 맞는 순열이 나오면 출력한다.
*/

// 2021.07.02 순열을 이용하지 않고 백트래킹으로 풀어도 된다. 다만 숫자를 비교할때 0이 앞에 오면 0이 삭제되기 때문에 string 형으로 비교해야한다.
// 가장 먼저 나오는게 제일 작은 숫자이고 제일 나중에 올수록 큰 숫자여서 이렇게 저장하면 된다.
#include <iostream> 
#include <vector> 
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

// 부등호 있는걸 겹쳐서 저장.
// 0~9까지 백트래킹으로 검사.
int k;
vector<char> v;
bool visited[10];
string max_num;
string min_num;

bool possible(int i, int j, int k) {
    if (k == '<')
        return i < j;
    if (k == '>')
        return i > j;
    return true;
}

void solve(int cnt, string s) {
    if (cnt == k + 1) {
        if (!min_num.size())
            min_num = s;
        else
            max_num = s;
        return;
    }


    for (int i = 0; i <= 9; ++i) {
        if (visited[i])
            continue;

        if (cnt == 0 || possible(s[cnt - 1], i + '0', v[cnt - 1])) {
            visited[i] = true;
            solve(cnt + 1, s + to_string(i));
            visited[i] = false;
        }
    }
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> k;
    for (int i = 0; i < k; ++i) {
        char c;
        cin >> c;
        v.push_back(c);
    }

    memset(visited, false, sizeof(visited));

    solve(0, "");

    cout << max_num << '\n' << min_num;


    return 0;
}


//////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int k;
string str;
char ch;

bool solve(const vector<int>& v) {
    int j = 0;
    for (int i = 0; i < v.size() - 1; ++i) {
        if (str[j] == '<' && v[i] > v[i + 1]) {
            return false;
        }
        else if (str[j] == '>' && v[i] < v[i + 1]) {
            return false;
        }
        else
            j++;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<int> v1;
    vector<int> v2;

    cin >> k;
    int num = 9;
    //v1에는 0부터 k개까지, v2는 9부터 k개까지 저장
    for (int i = 0; i <= k; ++i) {
        v1.push_back(i);
        v2.push_back(num--);
    }
    for (int i = 0; i < k; ++i) {
        cin >> ch;
        str += ch;
    }
    //v1, v2를 순열함수를 통해 조건 만족할때까지 반복한다.
    do {
        if (solve(v1))
            break;
    } while (next_permutation(v1.begin(), v1.end()));

    do {
        if (solve(v2))
            break;
    } while (prev_permutation(v2.begin(), v2.end()));

    for (int i = 0; i < v2.size(); ++i)
        cout << v2[i];
    cout << "\n";
    for (int i = 0; i < v1.size(); ++i)
        cout << v1[i];

    return 0;
}