/*
인형이 밑에서부터 쌓이기때문에 스택을 이용하면 쉽게 풀 수 있다.
다만 인형을 뽑고나서 바로 스택을 확인해서 비었거나 같은 인형이 아니면 푸시하고
같은 인형이면 answer+=2를 해주면 되는데 flag 설정해서 코드가 오히려 길어지게 만들었다.

이 점은 반성해야겠다.
*/

//내 풀이. 조금 복잡해보인다.
#include <string>
#include <vector>
#include <stack>
using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;

    stack<int> st;
    int N = board.size();

    for (int i = 0; i < moves.size(); ++i) {
        int tmp = 0;
        int idx = moves[i] - 1;
        bool flag = false;  //크레인에 인형이 있는지 여부

        for (int j = 0; j < N; ++j) {
            if (board[j][idx] != 0) {
                tmp = board[j][idx];
                board[j][idx] = 0;    //board에서 인형제거
                flag = true;
                break;
            }
        }

        //인형이 없다면 다음 moves 실행
        if (!flag)
            continue;

        //스택이 비었다면 tmp를 넣고 다음 명령 실행 
        if (st.empty()) {
            st.push(tmp);
            continue;
        }
        //인형이 있다면 같은 인형인지 확인하고 터뜨림
        else {
            if (st.top() != tmp) {
                st.push(tmp);
            }
            else {
                st.pop();
                answer += 2;
            }
        }

    }

    return answer;
}



//////////////////////////////////////
//다른 사람 풀이. 훨씬 더 깔끔하고 짧다.
int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    stack<int> s;
    for (int i = 0; i < moves.size(); i++)
    {
        int check = moves[i] - 1;
        for (int j = 0; j < board.size(); j++)
        {
            if (board[j][check] != 0)
            {
                //여기서 바로 스택을 확인한다.
                if (!s.empty() && s.top() == board[j][check])
                {
                    s.pop();
                    answer += 2;
                }
                else
                    s.push(board[j][check]);
                board[j][check] = 0;
                break;
            }
        }
    }
    return answer;
}