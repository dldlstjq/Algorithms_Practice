/*
전형적인 백트래킹문제인 것 같다.
함수를 하나 더 선언해서 백트래킹을 진행했고 벡터와 target을 같이 넣어줘도 되지만 가장 익숙한 방법으로 해결했다.

다른 사람 풀이는 비트를 써서 해결한 방법도 있다.
*/

// 내 풀이
#include <string>
#include <vector>

using namespace std;

vector<int> num;
int goal;
int answer;

void solve(int idx, int sum) {
    if (idx >= num.size()) {
        if (sum == goal)
            answer++;
        return;
    }

    solve(idx + 1, sum + num[idx]);
    solve(idx + 1, sum - num[idx]);
}

int solution(vector<int> numbers, int target) {

    num = numbers;
    goal = target;

    solve(1, num[0]);
    solve(1, -num[0]);

    return answer;
}

// 따로 전역변수를 만들지 않고 함수 인자에 넣어서 하는 방법
int total;

void DFS(vector<int>& numbers, int& target, int sum, int n) {
    if (n >= numbers.size()) {
        if (sum == target) total++;
        return;
    }

    DFS(numbers, target, sum + numbers[n], n + 1);
    DFS(numbers, target, sum - numbers[n], n + 1);
}

int solution(vector<int> numbers, int target) {
    int answer = 0;

    DFS(numbers, target, numbers[0], 1);
    DFS(numbers, target, -numbers[0], 1);

    answer = total;

    return answer;
}


// 비트 풀이
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> numbers, int target) {
    int answer = 0;
    int size = 1 << numbers.size();

    for (int i = 1; i < size; i++) {
        int temp = 0;
        for (int j = 0; j < numbers.size(); j++)
        {
            if (i & (1 << j)) {
                temp -= numbers[j];
            }
            else temp += numbers[j];
        }
        if (temp == target) answer++;
    }
    return answer;
}