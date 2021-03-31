/*
처음엔 톱니바퀴를 vector<string>으로 저장했는데 각 톱니바퀴마다 회전여부와 시계,반시계 방향 여부를 알아야 해서 구조체로 선언했다.
현재 톱니바퀴의 오른쪽, 왼쪽을 쭉 돌면서 현재 톱니바퀴가 회전한 경우 극이 같은지 조사하고 회전하지 않으면 이후 톱니바퀴는 회전하지 않는다.
맞닿아 있는 인덱스끼리 극이 같은지 다른지 조사해서 회전하는 톱니바퀴만 적절하게 옮겨준다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T;
struct gear {
    string str;
    bool change;    //회전여부
    int clock;  //시계, 반시계
};
vector<gear> v;

void move_gear(int idx, int dir) {
    //오른쪽
    for (int i = idx; i < v.size() - 1; ++i) {
        //톱니바퀴가 회전하지 않으면 break
        if (!v[i].change)
            break;

        //현재 톱니의 2번 인덱스와 오른쪽 톱니의 6번 인덱스가 맞닿아 있다.
        if (v[i].str[2] != v[i + 1].str[6]) {
            v[i + 1].change = true; //다음 톱니바퀴 회전
            //현재 톱니바퀴의 회전 방향과 반대로 설정
            v[i].clock == 1 ? v[i + 1].clock = -1 : v[i + 1].clock = 1;
        }
    }

    //왼쪽
    for (int i = idx; i > 0; --i) {
        //톱니바퀴가 회전하지 않으면 break
        if (!v[i].change)
            break;

        //현재 톱니의 6번 인덱스와 왼쪽 톱니의 2번 인덱스가 맞닿아 있다.
        if (v[i].str[6] != v[i - 1].str[2]) {
            v[i - 1].change = true; //다음 톱니바퀴 회전
            //현재 톱니바퀴의 회전 방향과 반대로 설정
            v[i].clock == 1 ? v[i - 1].clock = -1 : v[i - 1].clock = 1;
        }
    }

    //톱니바퀴를 회전시킨다.
    for (int i = 0; i < T; ++i) {
        //회전여부가 true인 것만 회전한다.
        if (!v[i].change)
            continue;

        //시계방향
        if (v[i].clock == 1) {
            string tmp = v[i].str;
            for (int j = 0; j < 8; ++j) {
                v[i].str[(j + 1) % 8] = tmp[j];
            }
        }
        //반시계방향
        else {
            string tmp = v[i].str;
            v[i].str[7] = tmp[0];
            for (int j = 0; j < 7; ++j) {
                v[i].str[j] = tmp[j + 1];
            }
        }

    }
}

//회전여부, 시계방향 초기화
void init() {
    for (int i = 0; i < T; ++i) {
        v[i].change = false;
        v[i].clock = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;

    for (int i = 0; i < T; ++i) {
        gear g;
        string s;
        cin >> s;

        g.str = s;
        g.change = false;
        g.clock = 0;
        v.push_back(g);
    }

    int k = 0;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        //톱니 방향, 회전여부 초기화
        init();

        //현재 톱니바퀴, 시계방향 따라 바퀴회전을 정한다.
        int num, dir;
        cin >> num >> dir;
        v[num - 1].change = true;
        v[num - 1].clock = dir;
        move_gear(num - 1, dir);
    }

    int ret = 0;
    //12시 방향이 S극인 톱니바퀴 갯수
    for (int i = 0; i < T; ++i) {
        if (v[i].str[0] == '1')
            ret++;
    }
    cout << ret;
    return 0;
}




////////////////////////////////////////////////
//큐를 이용한 풀이도 있다.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <deque> 
using namespace std;

const int MAX = 1000; //톱니바퀴
deque<int> dq[MAX];
int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    int T; 
    cin >> T;
    for (int t = 0; t < T; t++) { 
        string s; 
        cin >> s;
        for (int i = 0; i < s.length(); i++) 
            dq[t].push_back(s[i] - '0'); 
    } 

    int K;
    cin >> K; 
    for (int k = 0; k < K; k++) {
        int num, dir; 
        cin >> num >> dir; 
        num -= 1; 
        vector<pair<int, int>> v;
        v.push_back({ num, dir }); //횐전시킬 톱니바퀴 찾음 
        queue<pair<int, int>> q; 
        q.push({ num, dir }); 

        bool visited[MAX] = { false, };
        visited[num] = true; 
        while (!q.empty()) { 
            int cur = q.front().first; 
            int d = q.front().second; 
            q.pop(); 

            //왼쪽 
            if(cur != 0) 
                if (dq[cur][6] != dq[cur - 1][2] && !visited[cur -1]) { 
                    visited[cur - 1] = true;
					q.push({ cur - 1, d * -1 });
					v.push_back({ cur - 1, d * -1 });
            } 
            //오른쪽
            if(cur != T - 1) 
                if (dq[cur][2] != dq[cur + 1][6] && !visited[cur + 1]) { 
                    visited[cur + 1] = true; 
                    q.push({ cur + 1, d * -1 }); 
                    v.push_back({ cur + 1, d * -1 });
                } 
        } 
        
        for (int i = 0; i < v.size(); i++) { 
            int cur = v[i].first; 
            int d = v[i].second; 
            if (d == 1) { 
                int temp = dq[cur].back();
                dq[cur].pop_back();
                dq[cur].push_front(temp); 
            } 
            
            else { 
                int temp = dq[cur].front();
                dq[cur].pop_front(); 
                dq[cur].push_back(temp); 
            } 
        } 
    } 
    
    int result = 0; 
    for (int t = 0; t < T; t++) 
        if (dq[t][0] == 1) 
            result++; 
    cout << result << "\n"; 
    return 0; 
}

