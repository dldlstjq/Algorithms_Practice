/*
모든 순열을 구하려면 bool 배열 초기 상태가 내림 차순 정렬이 되어 있어야 한다. (그래야 모든 수열을 다 구할 수 있으니까)
👉 즉, true가 false보다 앞에 와야 한다. (true는 r개 존재)
ex) 6C2 라면{ true, true, false, false, false, false } 모양이 초기값이어야 함. (내림 차순 되어 있는 형태. false < true 니까)
    이건 내림 차순 정렬이 되어 있는 상태다. (ture > false니까!) 따라서 true (= 1)와 false (= 0) 끼리의 “크기를 비교하여 이전 순열을 결정한다.”
    따라서 4C2의 경우 bool배열은 아래와 같은 모양으로 while문이 진행될 것이다.이 ture 값과 같은 인덱스에 대응하는 배열의 원소들끼리를 조합하면 된다.
{true, true, false, false} 👉 'a' 'b' 에 대응시킴
{ true, false, true, false } 👉 'a' 'c' 에 대응시킴
{ true, false, false, true } 👉 'a' 'd' 에 대응시킴
{ false, true, true, false } 👉 'b' 'c' 에 대응시킴
{ false, true, false, true } 👉 'b' 'd' 에 대응시킴
{ false, false, true, true } 👉 'c' 'd' 에 대응시킴
그리고 이 bool 배열을 바탕으로 prev_permutation 연산을 수행하며 이 때 True 가 되는 것에 대응시켜서 조합을 구하면 된다.
중복이 있는 원소들은 제외하고 순열을 만들어준다.

중복되지 않게 팀원을 구해야 하므로 조합이 생각났다. nCn/2 를 해서 팀을 나누고 각 팀마다 능력치를
더하면 된다. 조합은 위의 방식대로 하면 조합이 나온다.
그리고 모든 쌍에 대해 능력치 합을 구해야 하기 때문에 계산을 잘해야한다.
처음에 이거를 생각 못해서 예제에 맞는 답이 안나왔다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAX = 20 + 1;
int n;
int S[MAX][MAX];
int ret;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<int> v;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        v.push_back(i);
        for (int j = 0; j < n; ++j)
            cin >> S[i][j];
    }

    //조합으로 간다.
    //n명 중 두 팀으로 나누어 해당 점수를 모두 더해 최소가 되게 한다.
    //nCr -> 앞에서 부터 r개의 1이 채워진다. 나머지 뒤는 0
    //이 문제에서는 n/2명이 한 팀이므로 nCn/2 이다. 

    //조합 구하기 위해 n/2개는 1, 0을 만든다
    vector<int> temp(n, 0);
    for (int i = 0; i < n / 2; ++i)
        temp[i] = 1;

    int ret = 987654321;
    do {
        //반씩 나눠서 temp[i]가 1이면 start에 아니면 link로 나눠서 저장한다.
        int sum1 = 0, sum2 = 0;
        vector<int> start;
        vector<int> link;
        for (int i = 0; i < v.size(); ++i) {
            if (temp[i])
                start.push_back(v[i]);
            else
                link.push_back(v[i]);
        }

        //모든 쌍에 대해 능력치 합을 구한다.
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < n / 2; ++j) {
                sum1 += S[start[i]][start[j]];
                sum2 += S[link[i]][link[j]];
            }
        }
        //능력 최소치 저장
        ret = min(ret, abs(sum1 - sum2));
    } while (prev_permutation(temp.begin(), temp.end()));

    cout << ret;

    return 0;
}



/////////////////////////////////////////
/*
2021.04.08 다시 품
백트래킹을 이용해서 한 명씩 배열에 넣고 배열 크기가 N/2가 되면 나머지 인원을 link에 넣었다.
그 후 능력치 합을 계산해 차가 최소가 되는 값을 갱신했다.

처음 푼 풀이를 보니 조합을 이용해서 해결했는데 그 때는 이런 생각을 어떻게 이런 생각을 했는지 신기하다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int graph[20][20];
bool member[20];
int ret = 987654321;

//능력치 합
int calc(vector<int>& v) {
    int ability = 0;
    for (int i = 0; i < v.size() - 1; ++i) {
        for (int j = i + 1; j < v.size(); ++j) {
            ability += graph[v[i]][v[j]] + graph[v[j]][v[i]];
        }
    }
    return ability;
}

void solve(int idx, vector<int>& start) {
    //한 팀의 팀원이 절반이면 나머지 반을 link에 넣는다.
    if (start.size() == N / 2) {
        vector<int> link;
        for (int j = 0; j < N; ++j) {
            if (!member[j])
                link.push_back(j);
        }

        //능력치 계산 후 최소값 갱신
        int sum1 = calc(start);
        int sum2 = calc(link);
        ret = min(ret, abs(sum1 - sum2));
        return;
    }

    //0~N-1까지 멤버를 한명씩 넣어본다.
    for (int i = idx; i < N; ++i) {
        start.push_back(i);
        member[i] = true;
        solve(i + 1, start);
        start.pop_back();
        member[i] = false;
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> graph[i][j];

    vector<int> v;
    solve(0, v);

    cout << ret;
    return 0;
}
