/*
처음엔 dfs 사용하지 않고 품.
수열 규칙에 따라 수를 계산해 벡터에 집어넣음.
벡터에 넣을 때 해당하는 수가 있는지 검사하고 없으면 집어넣고 있으면 해당 인덱스 기록.
해당 인덱스부터 벡터 끝까지 원소가 반복되는 부분이므로 삭제하고 남은 수의 갯수가 정답
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> v;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a, p;
    int num;
    int flag = 0, index = 0;
    cin >> a >> p;

    v.push_back(a);
    while (1) {
        //수 계산
        int num = 0;
        while (a != 0)
        {
            num += (int)pow(a % 10, p);
            a = a / 10;
        }

        //벡터에 수 있는지 검사. 있으면 flag= 1로 설정하고 index 저장
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == num) {
                flag++;
                index = i;
                break;
            }
        }
        //벡터에 수가 없으면 삽입
        if (flag == 0) {
            v.push_back(num);
            a = num;
        }
        else
            break;

    }

    //해당 인덱스부터 끝까지 반복수열 삭제. 남은 배열의 사이즈가 수열에 남게되는 수 갯수
    v.erase(v.begin() + index, v.end());
    cout << v.size();

    return 0;
}



//////////////////////////////////
/*
dfs 사용
*/
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

const int MAX = 300000 + 1;
int P;
int visited[MAX];

void DFS(int num)
{
    visited[num]++;
    //반복구간이 한번 반복되었다는 것을 의미
    if (visited[num] == 3)
        return;

    int sum = 0;
    while (num)
    {
        sum += (int)pow((num % 10), P);
        num /= 10;
    }
    DFS(sum);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int A;
    cin >> A >> P;

    DFS(A);
    int result = 0;
    //한번만 등장한 숫자들이 반복구간에 속하지 않은 숫자들
    for (int i = 0; i < MAX; i++)
        if (visited[i] == 1)
            result++;

    cout << result << "\n";
    return 0;
}