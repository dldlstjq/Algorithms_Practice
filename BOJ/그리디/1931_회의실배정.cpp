﻿/*
처음엔 회의 시작시간을 기준으로 현재 시작시간이 전 시작시간 보다 안겹치면 되는 쪽으로 풀었다.
밑의 코드가 그 풀이인데 시간초과가 났다.
시간초과를 해결하지 못해 다른 블로그를 보고 해결했다.

시작시간이 기준이 아니라 종료시간을 기준으로 정렬해서 문제를 풀면 됐다.
거꾸로 생각해 보는 것도 좋다는 걸 배웠다.
*/

// 2021.06.13 기본적인 그리디 문제이기 때문에 다시 풀어보기.

//정답 코드

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//종만북 회의실 알고리즘
//각 회의는 [begin,end) 구간 동안 회의실을 사용한다.
int n;
int start[100001], finish[100001];
int schedule() {
    //일찍 끝나는 순서대로 정렬한다.
    vector<pair<int, int>> order;
    for (int i = 0; i < n; ++i)
        order.push_back(make_pair(finish[i], start[i]));
    sort(order.begin(), order.end());
    //earliest: 다음 회의가 시작할 수 있는 가장 빠른 시간
    //selected: 지금까지 선택한 회의의 수
    int earliest = 0, selected = 0;
    for (int i = 0; i < order.size(); ++i) {
        int meetingBegin = order[i].second, meetingEnd = order[i].first;
        if (earliest <= meetingBegin) {
            //earliest를 마지막 회의가 끝난 시간 이후로 갱신한다.
            earliest = meetingEnd;
            ++selected;
        }
    }
    return selected;
}

bool cmp(const pair<int, int>& a, const pair<int, int>& b)
{
    if (a.second == b.second)
        return a.first < b.first;
    else
        return a.second < b.second;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    int cnt = 0;
    cin >> n;

    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;

    }

    //종료시간 기준으로 정렬. 종료시간 같으면 시작시간 기준으로 오름차순 정렬
    sort(v.begin(), v.end(), cmp);

    //시작시간이 종료시간보다 크거나 같으면 회의 수 증가
    int min = v[0].second;
    cnt++;
    for (int i = 1; i < n; i++) {
        if (v[i].first >= min) {
            min = v[i].second;
            cnt++;
        }
    }

    cout << cnt;
    return 0;
}



///////////////////////////////////
/*
처음 내가 푼 풀이. 틀린 코드
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    int cnt = 0;
    int conference = 0;
    cin >> n;
    vector<pair<int, int>> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }

    sort(v.begin(), v.end());

    //1부터 시작해서 현재 시작시간이 전에 시작시간 보다 안겹치면 됨
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (v[j - 1].first < v[j].first && v[j].first < v[j - 1].second) {
                continue;
            }
            else {
                cnt++;
                conference = max(conference, cnt);

            }
        }
        cnt = 0;
    }

    cout << conference;
    return 0;
}