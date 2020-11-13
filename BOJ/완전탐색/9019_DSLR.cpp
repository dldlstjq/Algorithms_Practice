/*
D,S,L,R 각 경우를 전부 고려해서 BFS로 풀면 답을 구할 수 있다.
문제는 L,R 일 경우 수를 바꿔야 되는데 처음에는 함수를 따로 만들어 string 형으로 바꿔서 자리를 일일이 옮겼다.
다른 방법이 있을 것 같아 알아보니 수식 한 줄로 해결이 됐었다....
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;
#define MAX 10000
int n1, n2;
bool visited[MAX];

//L 회전. 10이하면 10곱하고 1000이상이면 위치 바꿔서 리턴
int rotate_L(int num) {
    if (num < 1000)
        return num * 10;

    string str = to_string(num);
    int d1 = str[1] - '0';
    int d2 = str[2] - '0';
    int d3 = str[3] - '0';
    int d4 = str[0] - '0';

    return ((d1 * 10 + d2) * 10 + d3) * 10 + d4;
}

//R 회전.
int rotate_R(int num) {
    // 10이하는 1000 곱함
    if (num < 10)
        return num * 1000;

    //자리 숫자마다 위치 바꿔서 계산해서 리턴
    else if (10 <= num && num < 100) {
        string str = to_string(num);
        int d1 = str[1] - '0';
        int d2 = 0;
        int d3 = 0;
        int d4 = str[0] - '0';
        return ((d1 * 10 + d2) * 10 + d3) * 10 + d4;
    }

    else if (100 <= num && num < 1000) {
        string str = to_string(num);
        int d1 = str[2] - '0';
        int d2 = 0;
        int d3 = str[0] - '0';
        int d4 = str[1] - '0';
        return ((d1 * 10 + d2) * 10 + d3) * 10 + d4;
    }

    else if (num >= 1000) {
        string str = to_string(num);
        int d1 = str[3] - '0';
        int d2 = str[0] - '0';
        int d3 = str[1] - '0';
        int d4 = str[2] - '0';
        return ((d1 * 10 + d2) * 10 + d3) * 10 + d4;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--) {
        cin >> n1 >> n2;

        memset(visited, false, sizeof(visited));
        queue<pair<int, string>> q;
        q.push({ n1,"" });

        string ans = "";
        int min = 987654321;
        while (!q.empty()) {
            int now = q.front().first;
            string order = q.front().second;
            q.pop();

            if (now == n2) {
                ans = order;
                break;
            }

            //1. D
            int D = (2 * now) % MAX;
            if (0 <= D && D < MAX && !visited[D]) {
                q.push({ D, order + "D" });
                visited[D] = true;
            }

            //2. S
            int S = (now - 1) < 0 ? 9999 : now - 1;
            if (0 <= S && S < MAX && !visited[S]) {
                q.push({ S, order + "S" });
                visited[S] = true;
            }

            //3. L
            /*한 줄로 해결 가능
            int L = (now % 1000) * 10 + now / 1000;*/
            int L = rotate_L(now);
            if (0 <= L && L < MAX && !visited[L]) {
                q.push({ L, order + "L" });
                visited[L] = true;
            }

            //4. R
            /*R 역시 한줄로 해결 가능
            int R = (now % 10) * 1000 + (now / 10);*/
            int R = rotate_R(now);
            if (0 <= R && R < MAX && !visited[R]) {
                q.push({ R, order + "R" });
                visited[R] = true;
            }
        }

        cout << ans << "\n";
    }


    return 0;
}