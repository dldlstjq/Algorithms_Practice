/*
처음에 벡터 페어로 짝을 저장하는 식으로 코드를 짰다.
이걸 재귀함수로 적용해 구하는 방법이 생각나지 않아 책의 코드를 볼 수 밖에 없었다.
중복을 없애기 위해 isPairing이라는 배열을 둬서 이미 짝이 된 학생은
다시 안되게 했는데 잘 안됐다.
세번째 케이스에서 
(0,1) (2,3) (4,5)를 선택하고
(0,1) (2,4) (3,5)까지는 잘 됐는데 
(0,2) (1,3) (4,5)를 선택하는 과정에서 4,5가 이미 짝으로 선택된 것으로
구현되어 이 경우를 셀 수 없었다.

책에서는 남아있는 학생들 중 가장 번호가 빠른 학생(사전순)의 짝을 찾도록 했다.
그러면 중복되는 경우를 해결할 수 있었다.
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n;
bool areFreinds[100][100];

//taken[i]=i번째 학생이 짝을 이미 찾았으면 true, 아니면 false
int countPairings(bool taken[10]) {
    //남은 학생들 중 가장 번호가 빠른 학생을 찾는다.
    int firstFree = -1;
    for (int i = 0; i < n; ++i) {
        if (!taken[i]) {
            firstFree = i;
            break;
        }
    }
    //기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
    if (firstFree == -1)
        return 1;
    int ret = 0;
    //서로 친구인 두 학생을 찾아 짝을 지어 준다.
    for (int i = firstFree + 1; i < n; ++i) {
        if (!taken[i] && areFreinds[firstFree][i]) {
            taken[firstFree] = taken[i] = true;
            ret += countPairings(taken);
            taken[firstFree] = taken[i] = false;
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int m;
        cin >> n >> m;
        memset(areFreinds, false, sizeof(areFreinds));
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            areFreinds[a][b] = areFreinds[b][a] = true;
        }
        bool friends[10] = { false };
        cout << countPairings(friends) << "\n";
    }

    return 0;
}



///////////////////////////////////////////////
//중복 여부를 제거하기 위한 내 풀이
//짝이 됐는지 중복 여부 검사
//(0,1) (1,0)은 같은 경우이기 때문에 이를 검사
bool isPairing[100][100];

//taken[i]=i번째 학생이 짝을 이미 찾았으면 true, 아니면 false
int countPairings(bool taken[10]) {
    //기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
    bool finished = true;
    for (int i = 0; i < n; ++i)
        if (!taken[i])
            finished = false;
    if (finished)
        return 1;
    int ret = 0;
    //서로 친구인 두 학생을 찾아 짝을 지어 준다.
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (!taken[i] && !taken[j] && areFreinds[i][j]
                && !isPairing[i][j]) {
                taken[i] = taken[j] = true;
                isPairing[i][j] = isPairing[j][i] = true;
                ret += countPairings(taken);
                taken[i] = taken[j] = false;

            }
    return ret;
}