/*

카쿠로는 흔히 십자말풀이 수학 버전이라고 불리는 논리 퍼즐이다.
카쿠로는 위와 같이 생긴 정사각형의 게임판을 가지고 하는 퍼즐로, 이 게임판의 각 칸은 흰 칸이거나, 검은 칸이거나, 힌트 칸이다.
(힌트 칸은, 대각선으로 갈라져 있고 숫자가 씌여 있는 칸을 말한다)
모든 흰 칸에 적절히 숫자를 채워 넣어 규칙을 만족시키는 것이 이 게임의 목표이다.
카쿠로의 규칙은 다음과 같다.
1. 모든 흰 칸에는 1 부터 9 까지의 정수를 써넣어야 한다.

2. 세로로 연속한 흰 칸들의 수를 모두 더하면, 그 칸들의 바로 위에 있는 힌트 칸의 왼쪽 아래에 씌인 숫자가 나와야 한다.

3. 가로로 연속한 흰 칸들의 수를 모두 더하면, 그 칸들의 바로 왼쪽에 있는 힌트 칸의 오른쪽 위에 씌인 숫자가 나와야 한다.

4. 이 때 한 줄을 이루는 연속된 흰 칸들에는 같은 수를 두 번 넣을 수 없다. 예를 들어, 두 개의 흰 칸의 숫자를 더해서 4가 나와야 한다고 하면, 1+3=4 이거나 3+1=4 만이 가능하고, 2+2=4 는 불가능하다.

각 칸의 색깔과 힌트가 주어졌을 때 답을 출력하시오
*/

#include <iostream>
#include <algorithm>
#include <bitset>
#include <cstring> //memset

using namespace std;


const int MAX = 20;

//candidates[len][sum][known] = getCandidates(len, sum, known)
//len 1~9, sum 최대 1~9의 합: 45, known: 비트로 표현 최대 1111111110
int candidates[10][46][1024];
//게임판의 정보
//color: 각 칸의 색깔(검은칸, 힌트칸=0, 흰칸=1)
//value: 각 흰칸에 쓴 숫자(아직 쓰지 않은 칸은 0)
//hint: 각 칸에 해당하는 두 힌트의 번호
int N, color[MAX][MAX], value[MAX][MAX], hint[MAX][MAX][2];
//각 힌트의 정보
//sum:힌트 칸에 쓰인 숫자
//length: 힌트 칸에 해당하는 흰칸의 수
//known: 힌트 칸에 해당하는 흰칸에 쓰인 숫자들의 집합
int hintNum, sum[MAX * MAX], length[MAX * MAX], known[MAX * MAX];

//(y, x)에 val을 입력
void put(int y, int x, int val)
{
    for (int i = 0; i < 2; i++)
        known[hint[y][x][i]] += (1 << val);
    value[y][x] = val;
}

//(y, x)에 val을 지운다
void remove(int y, int x, int val)
{
    for (int i = 0; i < 2; i++)
        known[hint[y][x][i]] -= (1 << val);
    value[y][x] = 0;
}


//힌트번호가 주어질 때 후보의 집합 반환
int getCandHint(int hint)
{
    return candidates[length[hint]][sum[hint]][known[hint]];
}

//좌표가 주어질 때 해당 칸에 들어갈 수 있는 후보의 집합 반환
int getCandCoord(int y, int x)
{
    //세로 힌트와 가로 힌트를 모두 만족시켜야하므로 교집합
    return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}

//mask에 속한 원소들의 개수 반환
int getSize(int mask)
{
    int num = 0, compare = 1;
    for (int i = 1; i <= 9; ++i)
    {
        compare = compare << 1;
        if (compare & mask) num++;
    }
    return num;
}

//mask에 속한 원소들의 합 반환
int getSum(int mask
{
    int sum = 0, compare = 1;
    for (int i = 1; i <= 9; ++i)
    {
        compare = compare << 1;
        if (compare & mask)
            sum += i;
    }
    return sum;
}


//주석처리된 함수를 통해 조건에 부합하는 집합을 찾을 경우
//시간이 오래걸린다. 따라서 메모이제이션을 통해 수행속도를 높였다.
//generateCandidates() 참고
/*
//len칸의 합이 sum이고, 이 칸들에 이미 쓰인 수의 집합이 known일 때
//나머지 칸에 들어갈 수 있는 숫자의 집합 반환
int getCandidates(int len, int sum, int known)
{
        //조건에 부합하는 집합들의 교집합
        int allSets = 0;

        //1~9 부분집합(즉 모든 짝수)을 모두 생성, 그 중

        for (int set = 0; set < 1024; set += 2)

               //known을 포함하고 크기가 len이며 합이 sum인 집합을 모두 찾는다

               if ((set & known) == known && getSize(set) == len && getSum(set) == sum)

                       allSets |= set;

        //known에 이미 속한 숫자들은 답에서 제외

        return allSets & ~known;

}
*/


//candidates[][][]를 미리 계산
void generateCandidates()
{
    //우선 전부 0으로 초기화
    memset(candidates, 0, sizeof(candidates));
    //1~9 부분집합을 전부 생성
    for (int set = 0; set < 1024; set += 2)
    {
        //집합의 크기와 원소의 합을 계산
        int length = getSize(set), sum = getSum(set);
        //set의 모든 부분집합에 대해 candidates[][][]를 갱신
        int subset = set;
        while (1)
        {
            //숫자 하나의 합이 sum이고, 이미 subset 숫자가 쓰여있을 경우
            //전체 숫자의 집합이 set이 되도록 나머지 숫자를 채워넣을 수 있다
            candidates[length][sum][subset] |= (set & ~subset);
            if (subset == 0)
                break;
            subset = (subset - 1) & set;
        }
    }
}

//values[][]에 적힌 값 출력
void printSolution(void)
{
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            cout << value[i][j] << " ";
        cout << endl;
    }
}

//답 찾았을 경우 true
bool search(void)
{
    //아직 숫자를 쓰지 않은 흰칸 중 후보의 수가 최소인 칸을 찾는다
    int y = -1, x = -1, minCandidates = 1023;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (color[i][j] == 1 && value[i][j] == 0)
            {
                int candidate = getCandCoord(i, j);
                if (getSize(minCandidates) > getSize(candidate))
                {
                    minCandidates = candidate;
                    y = i, x = j;
                }
            }

    //이 칸에 들어갈 숫자가 없으면 실패
    if (minCandidates == 0)
        return false;

    //모든 칸이 채워졌으면 출력하고 종료
    if (y == -1)
    {
        printSolution();
        return true;
    }

    //숫자를 하나씩 채워보자
    for (int val = 1; val <= 9; val++)
        if (minCandidates & (1 << val))
        {
            put(y, x, val);
            if (search())
                return true;
            remove(y, x, val);
        }
    return false;

}


int main(void)
{
    int test_case;
    cin >> test_case;

    if (test_case < 1 || test_case>50)
        exit(-1);

    generateCandidates();

    for (int i = 0; i < test_case; i++)
    {
        memset(color, 0, sizeof(color));
        memset(value, 0, sizeof(value));
        memset(hint, 0, sizeof(hint));
        memset(sum, 0, sizeof(sum));
        memset(length, 0, sizeof(length));
        memset(known, 0, sizeof(known));

        cin >> N;

        if (N<1 || N>MAX)
            exit(-1);

        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                cin >> color[j][k];

        cin >> hintNum;

        for (int j = 0; j < hintNum; j++)
        {
            int y, x, dir, total;
            int moveY, moveX, nextY, nextX;
            int len = 0;
            cin >> y >> x >> dir >> total;
            hint[y - 1][x - 1][dir] = j; //해당 칸에 힌트 표시
            sum[hint[y - 1][x - 1][dir]] = total; //힌트칸에 쓰인 숫자

            if (dir) //y 증가
            {
                moveY = 1;
                moveX = 0;
            }

            else //x 증가
            {
                moveY = 0;
                moveX = 1;
            }
            //좌표 변경
            nextY = y - 1 + moveY, nextX = x - 1 + moveX;

            //흰칸이 어떤 힌트에 속하는지 표시
            while (1)
            {

                if (!color[nextY][nextX])
                    break;
                hint[nextY][nextX][dir] = j;
                len++;
                nextY += moveY;
                nextX += moveX;
            }
            length[hint[y - 1][x - 1][dir]] = len; //해당 힌트를 구성하는 흰칸의 길이
        }
        search();
    }

    return 0;

}
