/*
오랜만에 푸는 조합문제였다. 단순히 n개 중에서 m개를 뽑는 것이 아니라
중복되는 수열이 없게 뽑아야 하며 같은 수가 있어도 상관이 없다.

너무 단순하게만 접근해서 풀이가 생각나지 않았다. 중복체크를 하면서 백트래킹으로 접근하면 쉽게 풀리는 문제이다.
*/

#include <iostream> 
#include <vector> 
#include <algorithm> 
using namespace std;

int N, M;
vector<int> v;
int visited[8], ret[8];

void func(int idx) {
    if (idx == M) {
        for (int i = 0; i < M; ++i)
            cout << ret[i] << " ";
        cout << "\n";
        return;
    }

    int prev = -1;  //이전 숫자 저장
    for (int i = 0; i < N; ++i) {
        //선택안했거나 이전숫자와 다르면 진행
        if (!visited[i] && prev != v[i]) {
            visited[i] = true;
            ret[idx] = v[i];    //idx번째에 v[i] 저장
            prev = v[i];    //이전 숫자 저장
            func(idx + 1);
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

    func(0);
    return 0;
}