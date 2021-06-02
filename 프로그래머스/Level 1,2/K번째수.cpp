/*
문제조건 대로 범위내에 있는 배열을 잘라 정렬 후 k번째 수를 구하면 된다.
인덱스를 1 줄여주는 것만 고려하면 어려울 게 없다.
*/
// 내 풀이
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;

    for (int i = 0; i < commands.size(); ++i) {
        vector<int> temp;
        for (int k = commands[i][0] - 1; k <= commands[i][1] - 1; ++k) {
            temp.push_back(array[k]);
        }
        sort(temp.begin(), temp.end());

        answer.push_back(temp[commands[i][2] - 1]);
    }

    return answer;
}


// 다른 사람 풀이
// 정렬을 할 때 배열 범위를 같이 처리한다.
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    vector<int> temp;

    for (int i = 0; i < commands.size(); i++) {
        temp = array;
        sort(temp.begin() + commands[i][0] - 1, temp.begin() + commands[i][1]);
        answer.push_back(temp[commands[i][0] + commands[i][2] - 2]);
    }

    return answer;
}