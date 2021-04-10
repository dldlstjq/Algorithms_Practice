/*
위상정렬로 접근하려 했는데 도통 그래프를 어떻게 정해야 할지 생각이 안났다.
최대는 9에서 9-k 까지 이고 최소는 0~k까지인 숫자 중 부등호에 맞는 수가 정답인 것까지는 알았다.
또한 부등호를 한 줄로 전부 입력받아 수를 비교하려 하니 어려움이 많아 끝내 해결하지 못했다.

다른 풀이를 참고하니 위상정렬을 쓰지 않고 순열을 이용해서 풀이를 했다.
부동호의 경우 하나씩 입력받아 string에 공백없이 저장해 한결 더 쉽게 수를 비교할 수 있었다.

위상정렬 풀이의 경우 최소, 최대 힙을 이용하여야 하고 그래프의 경우 0~k까지 수로 나타낸 뒤
마지막에 최대를 구할때 9를 더하는 방식으로 했다.

순열로 풀면 간단한데 위상정렬로도 풀 수 있다는 걸 보여주는 것 같다.
근데 위상정렬 풀이는 너무 복잡하다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int k;
char ch;
string str;
vector<int> maxNum, minNum;

//부등호가 성립하는지 확인
bool valid(const vector<int>& v) {
    //모순을 찾는다.
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '<' && v[i] > v[i + 1])
            return false;
        else if (str[i] == '>' && v[i] < v[i + 1])
            return false;
    }
    //모순이 없을 경우
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> k;

    for (int i = 0; i < k; ++i) {
        cin >> ch;
        str += ch;
    }

    //최소
    for (int i = 0; i <= k; ++i)
        minNum.push_back(i);

    while (1) {
        if (valid(minNum))
            break;
        next_permutation(minNum.begin(), minNum.end());
    }

    //최대
    for (int i = 9; i >= 9 - k; --i)
        maxNum.push_back(i);

    while (1) {
        if (valid(maxNum))
            break;
        prev_permutation(maxNum.begin(), maxNum.end());
    }

    for (int i = 0; i < maxNum.size(); ++i)
        cout << maxNum[i];
    cout << "\n";
    for (int i = 0; i < minNum.size(); ++i)
        cout << minNum[i];
    cout << "\n";
    return 0;
}




/////////////////////////////////////////
//위상정렬 풀이
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

int arr[11];

int lineMax[11];
int resultMax[11];
int cntMax[10];
vector<int> vcMax[11];

int lineMin[11];
int resultMin[11];
int cntMin[10];
vector<int> vcMin[11];

int main()
{
    int n;
    scanf("%d", &n);

    // 위상 정렬을 위해 정보 입력
    getchar();
    for (int i = 0; i < n; i++)
    {
        char ch;
        scanf("%c", &ch);
        getchar();
        int prev = i;
        int cur = i + 1;

        if (ch == '<')
        {
            // max, min 값을 위해 따로 저장한다.
            lineMax[prev]++;
            vcMax[cur].push_back(prev);

            lineMin[prev]++;
            vcMin[cur].push_back(prev);
        }

        else if (ch == '>')
        {
            // max, min 값을 위해 따로 저장한다.
            lineMax[cur]++;
            vcMax[prev].push_back(cur);

            lineMin[cur]++;
            vcMin[prev].push_back(cur);
        }
    }

    // max를 구하기위한 pq
    priority_queue<int, vector<int>, greater<int>> qMax;

    for (int i = 0; i < n + 1; i++)
        if (lineMax[i] == 0)
            qMax.push(i);

    for (int i = 0; i < n + 1; i++)
    {
        int here = qMax.top();
        qMax.pop();

        resultMax[i] = here;

        for (int j = 0; j < vcMax[here].size(); j++)
        {
            int there = vcMax[here][j];
            if (--lineMax[there] == 0)
                qMax.push(there);
        }
    }

    // min을 구하기 위한 pq
    priority_queue<int, vector<int>, less<int>> qMin;

    for (int i = 0; i < n + 1; i++)
        if (lineMin[i] == 0)
            qMin.push(i);

    for (int i = 0; i < n + 1; i++)
    {
        int here = qMin.top();
        qMin.pop();

        resultMin[i] = here;

        for (int j = 0; j < vcMin[here].size(); j++)
        {
            int there = vcMin[here][j];
            if (--lineMin[there] == 0)
                qMin.push(there);
        }
    }

    // 출력 코드
    int ans = 9;

    // 자신의 위치에 ans를 넣어준다.
    for (int i = 0; i < n + 1; i++)
    {
        cntMax[resultMax[i]] = ans;
        ans--;
    }

    for (int i = 0; i < n + 1; i++)
        printf("%d", cntMax[i]);

    printf("\n");

    ans = n;

    // 자신의 위치에 ans를 넣어준다.
    for (int i = 0; i < n + 1; i++)
    {
        cntMin[resultMin[i]] = ans;
        ans--;
    }

    for (int i = 0; i < n + 1; i++)
        printf("%d", cntMin[i]);

    return 0;
}


출처: https://www.crocus.co.kr/725 [Crocus]