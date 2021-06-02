/*
0이 몇 개냐에 따라 최대, 최저 순위가 바뀐다.
최대는 0의 개수와 일치하는 개수를 더하면 되고 최저는 숫자가 일치하는 것만 계산하면 된다.
*/

// 내 풀이
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    vector<int> answer;

    int min_cnt = 0;
    int max_cnt = 0;

    for (int i = 0; i < lottos.size(); ++i) {
        // 0인 부분은 무조건 맞아야 최대
        if (lottos[i] == 0) {
            max_cnt++;
        }
        else {
            if (find(win_nums.begin(), win_nums.end(), lottos[i]) != win_nums.end()) {
                max_cnt++;
                min_cnt++;
            }
        }
    }

    switch (max_cnt) {
    case 2: answer.push_back(5); break;
    case 3: answer.push_back(4); break;
    case 4: answer.push_back(3); break;
    case 5: answer.push_back(2); break;
    case 6: answer.push_back(1); break;
    default: answer.push_back(6); break;
    }

    switch (min_cnt) {
    case 2: answer.push_back(5); break;
    case 3: answer.push_back(4); break;
    case 4: answer.push_back(3); break;
    case 5: answer.push_back(2); break;
    case 6: answer.push_back(1); break;
    default: answer.push_back(6); break;
    }

    return answer;
}



//다른 사람 풀이.
// 순위 계산을 하나만 해서 코드가 더 간결하다.
#include <string>
#include <vector>

using namespace std;

int func(int n) {
    if (n == 6) return 1;
    else if (n == 5) return 2;
    else if (n == 4) return 3;
    else if (n == 3) return 4;
    else if (n == 2) return 5;
    else return 6;
}

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    vector<int> answer;

    // 0의 갯수를 담는 변수
    int zero = 0;
    for (int i = 0; i < lottos.size(); i++) {
        if (lottos[i] == 0) zero++;
    }

    // lottos와 win_nums에서 일치하는 번호 갯수를 담는 변수
    int check = 0;
    int visited[6] = { 0, };
    for (int i = 0; i < lottos.size(); i++) {
        for (int j = 0; j < win_nums.size(); j++) {
            if (visited[i] == 0 && lottos[i] == win_nums[j]) {
                visited[i] = 1;
                check++;
            }
        }
    }

    answer.push_back(func(zero + check));
    answer.push_back(func(check));
    return answer;
}