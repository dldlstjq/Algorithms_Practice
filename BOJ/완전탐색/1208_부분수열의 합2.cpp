/*
1182번 부분수열의 합과 비슷한 문제인데 이번엔 N이 늘어났다.
똑같은 방식으로 풀면 2^N이 되어 시간초과가 난다.

두 가지 풀이가 있다.
두가지 풀이 다 이해못해서 나중에 다시 풀기로 했다.
*/

/*
풀이1 - 투 포인터 알고리즘 이용

1. 배열을 두개로 나누고 각각의 배열에 대해 모든 부분집합의 합을 전처리해줍니다.
2. 각각의 배열을 정렬을 하는데 하나는 오름차순 반대는 내림차순으로 정렬하여 투 포인터 알고리즘을 적용합니다.
3. 배열을 두개로 나누었기 때문에 S=0일 경우 답이 하나 더 크게 나옵니다.
-> 각 배열의 부분집합이 공집합을 포함하고 있기 때문입니다. 따라서, S=0일 경우 답을 하나 줄입니다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, S;
    cin >> N >> S;

    vector<int> v(N);
    for (int i = 0; i < N; i++)
        cin >> v[i];

    //배열을 반으로 나누고
    int half = N / 2;

    //나눈 배열 중 첫 번째 배열의 모든 부분 집합의 합을 저장
    vector<int> first(1 << (N - half));
    for (int i = 0; i < 1 << (N - half); i++)
        for (int j = 0; j < N - half; j++)
            if (i & (1 << j))
                first[i] += v[j];

    //나머지 배열의 모든 부분 집합의 합을 저장
    vector<int> second(1 << half);
    for (int i = 0; i < 1 << half; i++)
        for (int j = 0; j < half; j++)
            if (i & (1 << j))
                second[i] += v[j + (N - half)];



    //오름차순 정렬
    sort(first.begin(), first.end());

    //내림차순 정렬
    sort(second.begin(), second.end(), greater<int>());


    int idx = 0, idx2 = 0;
    long long result = 0;
    while (idx < 1 << (N - half) && idx2 < 1 << half)
    {
        if (first[idx] + second[idx2] == S)
        {
            long long cnt = 1, cnt2 = 1;
            idx++, idx2++;
            while (idx < 1 << (N - half) && first[idx] == first[idx - 1])
            {
                idx++;
                cnt++;
            }

            while (idx2 < 1 << half && second[idx2] == second[idx2 - 1])
            {
                idx2++;
                cnt2++;
            }

            result += cnt * cnt2;
        }

        else if (first[idx] + second[idx2] < S)
            idx++;

        else if (first[idx] + second[idx2] > S)
            idx2++;
    }

    //배열을 반으로 나누었으므로 공집합(0)이 원래는 하나인데 두번 나옴
    if (S == 0)
        result--;

    cout << result << "\n";
    return 0;
}



/////////////////////////
/*
풀이 2
먼저 왼쪽 절반에 대해 모든 부분집합의 합을 구해줍시다. O(2N/2)가 걸립니다. 결과는 map에 mp[num] = cnt 형태로 저장을 합시다.
오른쪽 절반으로 만들 수 있는 부분집합의 합을 i라고 합시다. 모든 i에 대해 mp[s-i]의 합을 구해주면 문제의 정답을 구할 수 있습니다.
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> v;
int n, s, half;
long long ans;
map<int, int> mp;

void dfsLeft(int idx, int sum) {
    if (idx == half) {
        mp[sum]++; return;
    }
    dfsLeft(idx + 1, sum);
    dfsLeft(idx + 1, sum + v[idx]);
}

void dfsRight(int idx, int sum) {
    if (idx == n) {
        ans += mp[s - sum]; return;
    }
    dfsRight(idx + 1, sum);
    dfsRight(idx + 1, sum + v[idx]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> s;
    half = n / 2; v.resize(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    dfsLeft(0, 0);
    dfsRight(half, 0);
    if (s == 0) ans--;
    cout << ans;
}