/*
알고스팟- 트라이문제와 비슷한 문제.
비슷하면서도 알고스팟보다는 조금 더 쉬워 보였는데 아직은 어렵게 느껴졌다.
문자열 문제는 많이 보고 풀어봐야겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

//자판 횟수 저장
int ans;
//첫 글자 입력 여부
bool isRoot;

//알파벳 대문자를 저장하는 경우 각 노드는 26개의 자손을 가질 수 있다.
const int ALPHABETS = 26;
//주어진 문자를 [0, ALPHABETS-1] 범위의 숫자로 변환
int toNumber(char ch) {
    return ch - 'a';
}

//트라이의 한 노드를 나타내는 객체
struct TrieNode {
    TrieNode* children[ALPHABETS];
    //종료노드인지 확인
    bool terminal;
    //자식 노드의 개수
    int branch;
    TrieNode() : terminal(false), branch(0) {
        memset(children, 0, sizeof(children));
    }
    //소멸자
    ~TrieNode() {
        for (int i = 0; i < ALPHABETS; ++i)
            if (children[i])
                delete children[i];
    }

    //이 노드를 루트로 하는 트라이에 문자를 추가한다.
    void insert(const char* key) {

        //문자열이 끝났다면 terminal만 바꾸고 종료
        if (*key == 0) {
            terminal = true;
        }
        else {
            int next = toNumber(*key);
            //해당 자식 노드가 없다면 생성한다.
            //자식이 생기기 때문에 branch 증가
            if (children[next] == NULL) {
                children[next] = new TrieNode();
                branch++;
            }

            //해당 자식 노드로 재귀호출
            children[next]->insert(key + 1);
        }
    }

    // 현재 노드에서 더 필요한 총 타이핑 횟수를 세는 재귀 함수
    void type(const char* key) {
        if (*key == 0)
            return;
        //루트일때: 첫 글자는 사용자가 버튼을 눌러야 한다.
        if (isRoot) {
            ans++;
            isRoot = false;
        }

        else {
            //자식이 2이상이거나 가는 도중 끝나는 단어를 포함할때 버튼 누른다.
            if (branch >= 2)
                ans++;
            else if (terminal)
                ans++;
        }
        int next = toNumber(*key);
        children[next]->type(key + 1);
    }
};


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    while (cin >> n) {
        //트라이 생성
        TrieNode* trie = new TrieNode();
        vector<string> input;
        for (int i = 0; i < n; ++i) {
            string str;
            cin >> str;
            input.push_back(str);
            trie->insert(input[i].c_str());
        }

        //버튼 횟수 구하기. 
        //isRoot는 첫글자 누르는 것을 나타내고 그 뒤로 계산
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            isRoot = true;
            ans = 0;
            trie->type(input[i].c_str());
            ret += ans;
        }

        //소수점 두자리 출력
        cout << fixed;
        cout.precision(2);
        cout << (double)ret / n << "\n";
        delete trie;
    }
    return 0;
}