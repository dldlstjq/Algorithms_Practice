/*
가장 약하다고 생각되는 부분 중 하나인 문자열 문제다.
완전탐색을 통해 모든 연산자 순서를 고려하면 될 것 같았는데
숫자와 연산자를 나누어 저장하는 것 부터 일이었다.

나누어 저장한 다음에는 연산자 순서에 맞게 어떻게 계산해야 할 지 막막해서 해결하지 못했다.
카카오에서 제공한 풀이를 보니 연산자 인덱스를 따로 저장해서 해당 인덱스와 인덱스+1 값을 연산하고 그 값을
다시 숫자 배열에 넣는 식으로 하면 된다고 했다.

그마저도 어떻게 해야할지 몰라 다른 사람의 풀이를 보고 그나마 이해할 수 있었다.

벡터의 find, erase, insert 함수 사용법을 다시 한번 익힐 수 있었다.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

vector<long long> num;
vector<char> op;
vector<char> location;    //연산자 순서

string ex;
long long ret;


long long solution(string expression) {
    long long answer = 0;

    ex = expression;
    string tmp = "";
    for (int i = 0; i < expression.length(); ++i) {
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*') {
            num.push_back(stoll(tmp));
            tmp = "";
            if (find(op.begin(), op.end(), expression[i]) == op.end())  //해당 연산자가 없으면 삽입
                op.push_back(expression[i]);
            location.push_back(expression[i]);
        }

        else
            tmp += expression[i];
    }

    num.push_back(stoll(tmp));  //마지막 숫자 num에 추가
    sort(op.begin(), op.end());

    do {
        vector<long long> tmp_num = num;
        vector<char> tmp_loc = location;

        for (int i = 0; i < op.size(); i++)
        {
            for (int j = 0; j < tmp_loc.size(); j++)
            {
                if (op[i] == tmp_loc[j])
                {
                    if (tmp_loc[j] == '+')
                        tmp_num[j] = tmp_num[j] + tmp_num[j + 1];
                    else if (tmp_loc[j] == '-')
                        tmp_num[j] = tmp_num[j] - tmp_num[j + 1];
                    else if (tmp_loc[j] == '*')
                        tmp_num[j] = tmp_num[j] * tmp_num[j + 1];

                    tmp_num.erase(tmp_num.begin() + j + 1);
                    tmp_loc.erase(tmp_loc.begin() + j);
                    j--;
                }
            }
        }

        if (answer < abs(tmp_num[0]))
            answer = abs(tmp_num[0]);

    } while (next_permutation(op.begin(), op.end()));

    return answer;
}