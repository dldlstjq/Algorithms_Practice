#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <stack>
#include <queue>
#include <utility>
#include <deque>

using namespace std;
#define MAX 100001
long long histo[MAX];
bool visited[MAX];
int n;

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long histogram(int idx, long long area) {
    if (idx<0 || idx>n - 1) {
        return;
    }

    //방문표시
    visited[idx] = true;
    

    //idx 좌우에 넓이가 더 큰 쪽으로 계산
    if(idx-1>0)

    if (!visited[idx - 1] && histo[idx - 1] > histo[idx + 1]) {

    }

    if (histo[idx - 1] > histo[idx + 1]) {
        area = max(area, histo[idx - 1] * 2);
        histogram(idx - 1, area);
    }
    else {
        area = max(area, histo[idx + 1] * 2);
        histogram(idx + 1, area);
    }

    //long long max_area = 0;
    //for (int i = 0; i < n; i++) {
    //    if (i == 0) {
    //        if (histo[i] >= max_area)
    //            max_area = histo[i];
    //    }
    //    else {
    //        //크기가 작은건 고려 안함
    //        if (histo[i] == histo[i - 1]) {
    //            long long tmp=
    //            max_area = max(max_area, histo[i - 1] * 2);
    //        }
    //        else if (histo[i] > histo[i - 1]) {
    //            max_area = max(max_area, histo[i - 1] * 2, histo[i]);
    //        }
    //    }
    //}
    //return max_area;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

   
    cin >> n;
    long long max_area = 0;
    int idx = 0;
    for (int i = 0; i < n; i++) {
        cin >> histo[i];
        if (histo[i] > max_area) {
            max_area = histo[i];
            idx = i;
        }
            
    }
        

    cout << histogram(idx, max_area);
    return 0;
}