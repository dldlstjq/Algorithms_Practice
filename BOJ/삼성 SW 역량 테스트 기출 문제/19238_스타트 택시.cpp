/*
문제 이해는 됐지만 구현이 어려웠다.

1. 손님의 위치와 번호, 목적지를 어떻게 저장하는지
2. 가장 가까운 거리의 손님이 있다면 같은 거리에 손님이 있는지 어떻게 확인하는지
2. 가장 가까운 거리의 손님이 여러명일경우 어떻게 선택할건지
3. 택시의 연료는 어떻게 계산할건지

전체 4가지 경우를 구현하지 못했다.

다른 답을 보니 별도의 벡터를 선언해 손님의 번호를 저장했고
손님 선택은 벡터 페어로 저장하여 sort를 이용해 가장 가까운 손님을 선택했다.

반복적인 연습이 많이 필요하다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 20 + 2;
int N, M, oil;
int map[MAX][MAX];

bool visited[MAX][MAX];
pair<int, int> taxi; //택시의 위치
vector<pair<int, int>> dest;    //손님 목적지 저장
int customer = 2;   //손님번호 (map의 0은 빈칸, 1은 벽이라서 2번부터 표시)

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int des_num = 0;    //택시가 태운 손님 번호
int ret = 0;    //목적지까지 데려다 준 승객

pair<int, int> find_customer() {
    queue<pair<int, int>> q;
    memset(visited, false, sizeof(visited));

    //택시출발지가 바로 다른손님 출발지이면
    if (map[taxi.first][taxi.second] >= 2) {
        des_num = map[taxi.first][taxi.second];
        return { taxi.first, taxi.second };
    }

    q.push({ taxi.first, taxi.second });
    visited[taxi.first][taxi.second] = true;
    vector<pair<pair<int, int>, int>> temp; //손님 번호와 위치 저장
    bool finish = false;

    while (!q.empty() && oil >= 0 && !finish) {
        int size = q.size();
        while (size--) {
            int y = q.front().first;
            int x = q.front().second;
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int ny = y + dy[i];
                int nx = x + dx[i];

                //범위 밖
                if (!(0 <= ny && ny < N && 0 <= nx && nx < N))
                    continue;
                //방문했거나 벽
                if (visited[ny][nx] || map[ny][nx] == 1)
                    continue;

                if (map[ny][nx] >= 2) {
                    temp.push_back({ {ny,nx},map[ny][nx] });
                    //손님을 찾은 거리와 동일 거리에 있는 다른 손님들만 찾기 위해 이용
                    finish = true;
                }
                visited[ny][nx] = true;
                q.push({ ny,nx });
            }
        }
        oil--;
    }

    //가장 가까운 거리에 있는 손님들을 찾음
    if (temp.size() >= 1) {
        if (temp.size() > 1)
            //여러명일 경우 행번호가 작은 승객. 열번호가 작은 승객 순
            sort(temp.begin(), temp.end());
        des_num = temp[0].second;
        return { temp[0].first.first, temp[0].first.second };
    }
    else
        return { -1,-1 };
}

bool delivery() {
    queue<pair<int, int>> q;
    memset(visited, false, sizeof(visited));


    q.push({ taxi.first, taxi.second });
    visited[taxi.first][taxi.second] = true;
    int first = oil;    //목적지 가기 전 택시가 가진 초기 연료

    while (!q.empty() && oil >= 0) {
        int size = q.size();
        while (size--) {
            int y = q.front().first;
            int x = q.front().second;
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int ny = y + dy[i];
                int nx = x + dx[i];

                //범위 밖
                if (!(0 <= ny && ny < N && 0 <= nx && nx < N))
                    continue;
                //방문했거나 벽
                if (visited[ny][nx] || map[ny][nx] == 1)
                    continue;

                //목적지 도착
                if (ny == dest[des_num].first && nx == dest[des_num].second) {
                    oil--;
                    if (oil < 0)
                        return false;   //도착했는데 연료 다 쓰면 실패
                    oil += (first - oil) * 2;   //소모한 연료 2배 충전
                    taxi.first = ny;    //택시 목적지 초기화
                    taxi.second = nx;
                    return true;
                }
                visited[ny][nx] = true;
                q.push({ ny,nx });
            }
        }
        oil--;
    }

    return false;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> oil;


    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> map[i][j];

    cin >> taxi.first >> taxi.second;
    taxi.first -= 1; taxi.second -= 1;

    dest.resize(M + 2); //손님번호 2번부터 시작

    for (int i = 0; i < M; ++i) {
        int a, b, c, d; //손님 출발지와 목적지 좌표
        cin >> a >> b >> c >> d;
        a -= 1; b -= 1; c -= 1; d -= 1;
        map[a][b] = customer;   //map에 손님 초기 위치 표시
        dest[customer].first = c;
        dest[customer].second = d;
        customer++;
    }

    //손님 수 M만큼 수행
    for (int i = 0; i < M; ++i) {
        //1. 가장 가까운 손님 번호 찾기
        pair<int, int> c = find_customer();
        if (c.first == -1)
            break;  //만약 연료 부족해서 손님 못태운 경우

        taxi.first = c.first;   //택시 위치를 손님 위치로 초기화
        taxi.second = c.second;
        map[c.first][c.second] = 0; //손님이 있던 자리는 빈칸으로 초기화 -> 나중에 다시 계산할 일 없게

        //2. 손님 목적지까지 데려다 주기
        bool check = delivery();

        if (oil < 0 || check == false)
            break;

        ret++;
    }

    if (ret == M)
        cout << oil;
    else
        cout << -1;

    return 0;
}