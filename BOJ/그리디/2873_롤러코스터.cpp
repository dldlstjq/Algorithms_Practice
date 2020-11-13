/*
세로 or 가로가 홀수인 경우는 모든 칸을 방문할 수 있기 때문에 별 문제가 안된다.

문제는 세로와 가로가 모두 짝수인 경우이다.
i) 모든 칸을 방문할 수 없습니다.(최소 1칸은 못 지나갑니다)

ii) 시작점을 흰 칸, 도착점은 검정색 칸인 체스판 형태로 본다면 방문한 칸은 흰색->검은색, 다음에 방문할 칸은 검은색->흰색 순서로 방문함을 알 수 있습니다.

	a) 따라서, 흰색 칸 하나를 방문하지 않기로 한다면 도착점까지 남은 칸을 모두 방문할 수 없습니다.
	
	b) 검은 칸 하나를 방문하지 않기로 한다면 도착점까지 남은 칸을 모두 방문할 수 있습니다.

	c) 따라서, 검은 칸에 있는 기쁨 점수 중 최소인 지점을 찾습니다.

iii) 우선, ii)번 하위 항목인 c에서 찾은 지점 최좌측 지점까지 갑니다.

iV) c에서 찾은 지점 대각선 아래(↙)까지 갑니다.

V) c에서 찾은 지점 최우측 지점까지 갑니다.

Vi) 도착점까지 갑니다.

dfs, bfs에서 풀었던 것처럼 4방향을 설정해서 차례대로 가는 것으로 코드를 짰는데 
세로, 가로가 짝수인 부분에서 해결을 못했다. 그래서 그냥 string 형태에서 방향을 단순히 더하는 걸로 정답을 저장하는게 더 낫다.
결론은 못 풀었다. 다시 한번 봐야되는 문제.
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX = 1000;
const int INF = 987654321;
int arr[MAX][MAX];
string result;

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); //cin 실행속도 향상

    int R, C;
    cin >> R >> C;

    //세로가 홀수
    if (R % 2)
    {
        for (int y = 0; y < R; y++)
        {
            for (int x = 0; x < C - 1; x++)
                if (y % 2 == 0)
                    result += 'R';

                else
                    result += 'L';

            if (y != R - 1)
                result += 'D';
        }
    }

    //세로가 짝수 가로가 홀수
    else if (!(R % 2) && C % 2)
    {
        for (int x = 0; x < C; x++)
        {
            for (int y = 0; y < R - 1; y++)
                if (x % 2 == 0)
                    result += 'D';

                else
                    result += 'U';

            if (x != C - 1)
                result += 'R';
        }
    }

    //세로가 짝수 가로가 짝수
    else if (!(R % 2) && !(C % 2))
    {
        pair<int, int> minHappy; //검은 칸이면서 지나지 말아야 할 지점
        int minScore = INF;

        for (int y = 0; y < R; y++)
            for (int x = 0; x < C; x++)
            {
                cin >> arr[y][x];

                //검은칸이고 최소점수
                if ((y + x) % 2 && minScore > arr[y][x])
                {
                    minScore = arr[y][x];
                    minHappy = { y, x };
                }
            }

        //지나지 말아야 할 좌표의 최좌측으로 내려오고
        int newR = minHappy.first % 2 ? minHappy.first - 1 : minHappy.first;
        for (int y = 0; y < newR; y++)
        {
            for (int x = 0; x < C - 1; x++)
                if (y % 2 == 0)
                    result += 'R';

                else
                    result += 'L';

            result += 'D';
        }

        //지나지 말아야 할 좌표의 대각선 아래까지 이동하고(↙)
        int newC = minHappy.second;
        for (int x = 0; x < newC; x++)
            if (x % 2 == 0)
                result += "DR";

            else
                result += "UR";

        //지나지 말아야 할 좌표의 최우측으로 이동
        for (int x = newC; x < C - 1; x++)
            if (x % 2 == 0)
                result += "RD";

            else
                result += "RU";

        //목적지까지
        if (minHappy.first % 2 == 0)
            newR = R - (minHappy.first + 2);

        else
            newR = R - (minHappy.first + 1);


        for (int y = 0; y < newR; y++)
        {
            result += 'D';
            for (int x = 0; x < C - 1; x++)
                if (y % 2 == 0)
                    result += 'L';

                else
                    result += 'R';
        }
    }

    cout << result << "\n";
    return 0;
}