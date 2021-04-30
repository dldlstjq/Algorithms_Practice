/*
15663 N과 M(9) 문제랑 같은데 비내림차순이라는 조건만 붙었다.
중복인지 확인하는 것과 동시에 이전에 고른 숫자보다 크거나 같은지 확인해주면 끝이다.
*/

#include <iostream> 
#include <vector> 
#include <algorithm> 
using namespace std;

int N, M;
vector<int> v;
int ret[8];    //결과값 저장
bool visited[8];    //방문 확인

void solve(int idx, int prev) {
    if (idx == M) {
        for (int i = 0; i < M; ++i)
            cout << ret[i] << " ";
        cout << "\n";
        return;
    }

    int check = -1; //바로 직전에 골랐던 수 저장
    for (int i = 0; i < N; ++i) {
        //아직 선택하지 않았고 이전의 수보다 크거나 같으며 중복이 아니면 선택
        if (!visited[i] && prev <= v[i] && check != v[i]) {
            visited[i] = true;
            check = v[i];
            ret[idx] = v[i];
            solve(idx + 1, v[i]);
            visited[i] = false;
        }
    }
}


int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        int num;
        cin >> num;
        v.push_back(num);
    }

    sort(v.begin(), v.end());
    solve(0, 0);

    return 0;
}