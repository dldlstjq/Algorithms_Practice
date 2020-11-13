/*
벡터로 두 배열 입력받고 첫번째 v1 벡터에 v2 벡터를 삽입해서 정렬하여 출력했다.
머지소트처럼 새로운 배열에다 저장하는 방법도 있다.
*/

//내가 푼 풀이
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;

    cin >> n >> m;

    vector<int> v1(n);
    vector<int> v2(m);

    for (int i = 0; i < n; i++)
        cin >> v1[i];

    for (int i = 0; i < m; i++)
        cin >> v2[i];

    v1.insert(v1.end(), v2.begin(), v2.end());
    sort(v1.begin(), v1.end());

    for (int i = 0; i < n + m; i++) {
        cout << v1[i] << " ";
    }

    return 0;
}



////////////////////////////////////
/* 다른 사람 풀이*/
#include <iostream>
using namespace std;
int a[1000001];
int b[1000001];
int c[2000001];
int main()
{

    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }

    int a_num = 0, b_num = 0;
    int k = 0;
    while (a_num < n && b_num < m) {
        if (a[a_num] <= b[b_num]) {
            c[k++] = a[a_num++];
        }
        else c[k++] = b[b_num++];
    }
    while (a_num < n) c[k++] = a[a_num++];
    while (b_num < m) c[k++] = b[b_num++];
    for (int i = 0; i < k; i++) {
        printf("%d ", c[i]);
    }
    return 0;
}