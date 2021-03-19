/*
문제이해는 별로 어렵지 않았다.
원판을 시게, 반시계 방향으로 돌리는 것도 쉽게 구현했다.
문제는 인접한 수를 지우는 것이었는데 같은 원판에서 지우는것, 다른 원판에서 지우는 것 두개로 나눴다.
같은 원판의 경우 0번째랑 M-1번째는 인덱스 설정을 따로 해줘서 지웠고 나머지는 +1,-1을 해서 지웠다.
다른 원판도 첫번째 원판과 N번쨰 원판만 따로 설정했다.
지운 수는 0으로 표시했는데 나중에 수를 지울때 0인 것은 넘어가줘야 제대로 계산이 된다.
처음에 그냥 같은면 지우는 걸로 했는데 0의 경우 이미 지운 수이기 때문에 넘어가야하는데 넘어가지 않고 
flag=true로 만들어줘서 답이 제대로 안나왔다.

다른 사람의 풀이를 보니 원판 저장을 deque을 이용한 사람이 있었다.
그거보다 인접한 값을 지울떄 bfs를 활용하여 왼쪽, 오른쪽 ,위, 아래를 검사하여 같으면 다른 벡터에 넣어주고
그 벡터에 든 좌표의 원소 값을 0으로 만들었다. 내가 짠 코드보다는 확실히 더 간결하고 이해가 잘 되는 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 50 + 1;
int circle[MAX][MAX];
int temp[MAX][MAX];
int N, M, T;

void copy() {
    for (int i = 1; i <= N; ++i)
        for (int j = 0; j < M; ++j)
            temp[i][j] = circle[i][j];
}

//원판에 수가 남아있는지 검사
//지운 수는 0이다.
bool is_number() {
    bool flag = false;
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (circle[i][j] != 0) {
                flag = true;
                return flag;
            }
        }
    }
    return flag;
}

//일일이 하나씩 확인한다.
bool eliminate() {
    bool flag = false;
    //원판에 수가 남아있고 인접하면서 수가 같은 것을 모두 찾는다.
    //하나라도 같은 게 있어 지운게 있다면 flag=true로 설정한다.
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < M; ++j) {
            //지운 수가 아니어야 한다.
            if (temp[i][j] != 0) {
                //같은 원판에서 인접한 경우
                if (j == 0) {
                    if (temp[i][j] == temp[i][j + 1]) {
                        circle[i][j] = circle[i][j + 1] = 0;
                        flag = true;
                    }

                    if (temp[i][j] == temp[i][M - 1]) {
                        circle[i][M - 1] = 0;
                        flag = true;
                    }

                }
                else if (j == M - 1) {
                    if (temp[i][j] == temp[i][j - 1]) {
                        circle[i][j] = circle[i][j - 1] = 0;
                        flag = true;
                    }

                    if (temp[i][j] == temp[i][0]) {
                        circle[i][0] = 0;
                        flag = true;
                    }

                }
                else {
                    if (temp[i][j] == temp[i][j - 1]) {
                        circle[i][j] = circle[i][j - 1] = 0;
                        flag = true;
                    }
                    if (temp[i][j] == temp[i][j + 1]) {
                        circle[i][j + 1] = 0;
                        flag = true;
                    }

                }
                //다른 원판에서 인접한 경우
                if (i == 1) {
                    if (temp[i][j] == temp[i + 1][j]) {
                        circle[i][j] = circle[i + 1][j] = 0;
                        flag = true;
                    }
                }
                else if (i == N) {
                    if (temp[i][j] == temp[i - 1][j]) {
                        circle[i][j] = circle[i - 1][j] = 0;
                        flag = true;
                    }
                }
                else {
                    if (temp[i][j] == temp[i + 1][j]) {
                        circle[i][j] = circle[i + 1][j] = 0;
                        flag = true;
                    }
                    if (temp[i][j] == temp[i - 1][j]) {
                        circle[i][j] = circle[i - 1][j] = 0;
                        flag = true;
                    }
                }
            }

        }
    }
    return flag;
}

//bfs를 활용한 풀이
bool eliminate() {
    bool flag = false;
    //원판에 수가 남아있고 인접하면서 수가 같은 것을 모두 찾는다.
    //하나라도 같은 게 있어 지운게 있다면 flag=true로 설정한다.
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < M; ++j) {
            memset(visited, false, sizeof(visited));
            queue<pair<int, int>> q;
            vector<pair<int, int>> v;   //수가 같은 인접한 좌표 저장

            if (circle[i][j] != 0) {
                int value = circle[i][j];
                q.push({ i,j });
                visited[i][j] = true;
                while (!q.empty()) {
                    int y = q.front().first;
                    int x = q.front().second;
                    q.pop();

                    //시작하는 좌표를 넣는다.
                    //인접한 수가 있을 경우에는 벡터사이즈가 2이상이 된다.
                    v.push_back({ y,x });

                    for (int d = 0; d < 4; ++d) {
                        int ny = y + movedir[d].y;
                        int nx = x + movedir[d].x;

                        //위 아래는 인접 x
                        if (ny == 0 || ny > N)
                            continue;

                        //양 옆 인접 o
                        if (nx == -1)
                            nx = M - 1;
                        else if (nx == M)
                            nx = 0;

                        if (visited[ny][nx])
                            continue;

                        if (circle[ny][nx] == value) {
                            visited[ny][nx] = true;
                            q.push({ ny,nx });
                        }
                    }
                }
                //인접한 숫자가 있을 경우에만 제거
                if (v.size() >= 2) {
                    flag = true;
                    for (int a = 0; a < v.size(); ++a) {
                        int y = v[a].first;
                        int x = v[a].second;
                        circle[y][x] = 0;
                    }
                }
            }
        }
    }
    return flag;
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> T;

    for (int i = 1; i <= N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> circle[i][j];

    for (int t = 0; t < T; ++t) {
        int x, d, k;
        cin >> x >> d >> k;

        copy(); //배열 복사
        for (int i = 1; i <= N; ++i) {
            //x의 배수인 것만
            if (i % x == 0) {
                //시계방향 k칸 회전
                //(j+k)%M 하면 인덱스를 잘 설정할 수 있다.
                if (d == 0) {
                    for (int j = 0; j < M; ++j) {
                        circle[i][(j + k) % M] = temp[i][j];
                    }
                }
                //반시계방향 k칸 회전
                //k만큼 감소시킨 자리에 넣으면 되는데 음수로 가는경우 M을 더한 후 K를 빼주면 된다. 
                else {
                    for (int j = 0; j < M; ++j) {
                        if (j - k < 0)
                            circle[i][j + M - k] = temp[i][j];
                        else
                            circle[i][j - k] = temp[i][j];
                    }
                }
            }
        }

        copy(); //배열 복사
        //원판에 수가 남아 있는지 검사
        bool num = false;
        num = is_number();

        bool flag = false;
        //남아 있다면 수를 지운다.
        if (num)
            flag = eliminate();

        //flag=false면 적힌 수 평균을 구하고
        //그 수보다 큰 수-1, 작은수+1을 해준다.
        if (!flag) {
            double avg = 0;
            int cnt = 0;
            for (int i = 1; i <= N; ++i)
                for (int j = 0; j < M; ++j)
                    //0이 아닌 수들만 더한다.
                    if (circle[i][j]) {
                        avg += circle[i][j];
                        cnt++;
                    }
            //평균을 내서 크면 +1, 작으면 -1 한다.
            avg /= cnt;
            for (int i = 1; i <= N; ++i)
                for (int j = 0; j < M; ++j)
                    if (circle[i][j] != 0) {
                        if (avg > circle[i][j])
                            circle[i][j] += 1;
                        else if (avg < circle[i][j])
                            circle[i][j] -= 1;
                    }
        }

    }

    //계산을 다 한 후 적힌 수의 합을 구한다
    int sum = 0;
    for (int i = 1; i <= N; ++i)
        for (int j = 0; j < M; ++j)
            sum += circle[i][j];

    cout << sum;

    return 0;
}