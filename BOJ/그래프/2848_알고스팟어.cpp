/*
알고스팟의 고대어사전이랑 비슷한 문제여서 쉽게 해결할 수 있겠다 했는데 못 풀었다.
단순히 알파벳 순서대로 그래프를 만들어 풀었는데 틀렸다.
abc
ab
이렇게 입력이 들어오면 애초에 !를 출력해야된다.
다른 사람의 풀이 코드를 보고 해결해야 했다.
*/

#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int N;
int indegree[26], alphaCheck[26], check[26][26];
vector<vector<char>> list, adj;
vector<char> ans;

int main(void)
{
    char input[11], alphaNum = 0;
    scanf("%d", &N);
    list.resize(N);
    for (int i = 0; i < N; i++) {
        list[i].resize(10);
    }
    adj.resize(26);
    for (int n = 0; n < N; n++) {
        scanf("%s", input);
        for (int i = 0; input[i] != '\0'; i++) {
            list[n][i] = input[i];
            if (alphaCheck[input[i] - 'a'] == 0) {
                alphaCheck[input[i] - 'a'] = 1;
                alphaNum++;
            }
        }
    }
    for (int n = 0; n < N - 1; n++) {
        for (int m = n + 1; m < N; m++) {
            for (int c = 0; c < 10; c++) {
                if (list[n][c] == list[m][c]) continue;
                else if (!(list[n][c] == 0 || list[m][c] == 0)) {
                    if (check[list[n][c] - 'a'][list[m][c] - 'a']) break;
                    check[list[n][c] - 'a'][list[m][c] - 'a'] = 1;
                    adj[list[n][c] - 'a'].push_back(list[m][c]);
                    indegree[list[m][c] - 'a']++;
                    break;
                }
            }
        }
    }
    queue<char> q;
    for (int i = 0; i < 26; i++) {
        if (alphaCheck[i] && indegree[i] == 0) {
            q.push(i + 'a');
        }
    }
    for (int i = 0; i < alphaNum; i++) {
        if (q.empty()) {
            printf("!\n");
            exit(0);
        }
        if (q.size() > 1) {
            printf("?\n");
            exit(0);
        }
        char node = q.front(); q.pop();
        ans.push_back(node);
        for (int n = 0; n < adj[node - 'a'].size(); n++) {
            char nextNode = adj[node - 'a'][n];
            indegree[nextNode - 'a']--;
            if (!indegree[nextNode - 'a']) q.push(nextNode);
        }
    }
    for (int i = 0; i < ans.size(); i++) {
        printf("%c", ans[i]);
    }printf("\n");

    return 0;
}



///////////////
//내가 구현한 코드.
//알고스팟이랑 비슷하게 따라했는데 해결하지 못했다.
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

const int MAX = 26;
vector<int> adj[MAX];
int indegree[MAX];
int alphabet[MAX];

void make_graph(const vector<string>& words) {
    for (int i = 1; i < words.size(); ++i) {
        int j = i - 1;
        int tmp = 0;
        int len = min(words[i].size(), words[j].size());
        for (int k = 0; k < len; ++k) {
            //알파벳이 서로 다를 때 인덱스가 더 낮은 알파벳의 순서가 더 높다.
            //words[j][k]->words[i][k]로 간선 연결
            if (words[i][k] != words[j][k]) {
                int a = words[j][k] - 'a';
                int b = words[i][k] - 'a';
                adj[a].push_back(b);
                indegree[b]++;
                break;
            }
            else
                tmp++;
            //나중에 있는 단어가 먼저 오는 단어의 접두사인 경우
            if (words[i].size() < words[j].size() && tmp == len) {
                cout << "!";
                exit(0);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<string> words;
    for (int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        words.push_back(str);
    }

    //입력에 나온 알파벳을 체크하고 개수를 카운트 한다.
    //큐가 끝났을 때 ret의 사이즈가 cnt만큼 있어야 성공
    int alphaNum = 0;
    for (int i = 0; i < words.size(); ++i) {
        for (int j = 0; j < words[i].size(); ++j) {
            if (alphabet[words[i][j] - 'a'] == 0) {
                alphabet[words[i][j] - 'a']++;
                alphaNum++;
            }
        }
    }

    //그래프 생성
    make_graph(words);

    queue<int> q;
    for (int i = 0; i < MAX; ++i) {
        //입력에 나온 알파벳이어야 하고 indegree가 0인 알파벳을 큐에 넣는다.
        if (alphabet[i] == 1 && indegree[i] == 0)
            q.push(i);
    }

    vector<char> ret;
    for (int i = 0; i < alphaNum; ++i) {
        //큐가 비면 사이클이 있다.
        if (q.empty()) {
            cout << "!";
            exit(0);
        }
        //큐 사이즈가 2 이상이면 어느 알파벳의 순서가 더 높은지 모른다.
        if (q.size() >= 2) {
            cout << "?";
            exit(0);
        }

        int cur = q.front();
        q.pop();
        ret.push_back(cur + 'a');

        for (int i = 0; i < adj[cur].size(); ++i) {
            int next = adj[cur][i];
            indegree[next]--;
            if (indegree[next] == 0)
                q.push(next);
        }

    }

    for (int i = 0; i < ret.size(); ++i)
        cout << ret[i];


    return 0;
}