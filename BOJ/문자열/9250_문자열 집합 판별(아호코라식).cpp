/*
아호코라식 알고리즘.
아직 확실하게 이해하지 못해 기본적인 문제만 풀었는데
응용문제는 공부를 더 한뒤 접근해 봐야겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

//알파벳 대문자를 저장하는 경우 각 노드는 26개의 자손을 가질 수 있다.
const int ALPHABETS = 26;
//주어진 문자를 [0, ALPHABETS-1] 범위의 숫자로 변환
int toNumber(char ch) {
    return ch - 'a';
}

//트라이의 한 노드를 나타내는 객체
struct TrieNode {
    TrieNode* children[ALPHABETS];
    //현 위치에서 끝나는 문자열 집합. 존재성만 따짐
    bool terminal;
    //실패 연결: 이 노드에서 매칭이 실패했을 때 이 곳으로 가서 계속한다.
    //이 노드에 대응되는 문자열의 접미사이면서 트라이에 포함된 최대 문자열.
    TrieNode* fail;

    //출력 문자열 목록: 이 노드가 방문되었을 때 등장하는 바늘 문자열들의 번호
    TrieNode() : terminal(false) {
        memset(children, 0, sizeof(children));
    }
    //소멸자
    ~TrieNode() {
        for (int i = 0; i < ALPHABETS; ++i)
            if (children[i])
                delete children[i];
    }

    //이 노드를 루트로 하는 트라이에 번호 id인 문자열 key를 추가한다.
    void insert(const char* key) {
        //문자열이 끝났다면 terminal만 바꾸고 종료
        if (*key == 0)
            terminal = true;
        else {
            int next = toNumber(*key);
            //해당 자식 노드가 없다면 생성한다.
            if (children[next] == NULL)
                children[next] = new TrieNode();
            //해당 자식 노드로 재귀호출
            children[next]->insert(key + 1);
        }
    }
};

//트라이가 주어질 때 각 노드에 대해 실패 연결과 출력 문자열 목록을 계산한다.
void computeFailFunc(TrieNode* root) {
    //루트에서부터 시작해 한 단계씩 아래로 내려가며 각 노드의 실패 연결을 계산한다.
    queue<TrieNode*> q;
    //루트의 실패연결은 자기자신
    root->fail = root;
    q.push(root);
    while (!q.empty()) {
        TrieNode* here = q.front();
        q.pop();
        //here의 모든 자손에 대해 실패연결을 계산하고 이들을 큐에 넣는다.
        for (int edge = 0; edge < ALPHABETS; ++edge) {
            TrieNode* child = here->children[edge];
            if (!child) continue;
            //1레벨 노드의 실패 연결은 항상 루트
            if (here == root)
                child->fail = root;
            else {
                //아닌 경우 부모의 실패 연결을 따라가면서 실패 연결을 찾는다.
                TrieNode* t = here->fail;
                while (t != root && t->children[edge] == NULL)
                    t = t->fail;
                if (t->children[edge])
                    t = t->children[edge];
                child->fail = t;
            }
            //출력 문자열 목록: 실패 연결을 따라간 노드에서 복사해온 뒤,
            //이 위치에서 끝나는 바늘 문자열이 있으면 추가한다.
            if (child->fail->terminal)
                child->terminal = true;
            q.push(child);
        }
    }
}

//trie에 포함된 패턴들을 s에서 찾는다.
//s 내에서 패턴이 출현할 때 마지막 노드이면 true, 아니면 false를 반환한다.
bool ahoCorasick(const string& s, TrieNode* root) {
    TrieNode* state = root;
    //실제 반복문 내는 KMP와 별로 다를 것이 없다.
    for (int i = 0; i < s.size(); ++i) {
        int chr = toNumber(s[i]);
        while (state != root && state->children[chr] == NULL)
            state = state->fail;
        if (state->children[chr])
            state = state->children[chr];
        if (state->terminal == true)
            return true;

    }
    return false;
}

//입력에 주어지는 단어들을 트라이로 변환한다.
TrieNode* readInput(int words) {
    //단어들을 트라이에 넣는다.
    string input;
    TrieNode* trie = new TrieNode();
    for (int i = 0; i < words; ++i) {
        cin >> input;
        trie->insert(input.c_str());
    }

    return trie;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    TrieNode* root = readInput(n);
    computeFailFunc(root);

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        string str;
        cin >> str;

        TrieNode* state = root;
        bool ret = false;
        //실제 반복문 내는 KMP와 별로 다를 것이 없다.
        for (int i = 0; i < str.size(); ++i) {
            int chr = toNumber(str[i]);
            while (state != root && state->children[chr] == NULL)
                state = state->fail;
            if (state->children[chr])
                state = state->children[chr];
            if (state->terminal == true) {
                ret = true;
                break;
            }
        }

        if (ret)
            cout << "YES" << "\n";
        else
            cout << "NO" << "\n";
    }
    delete root;
    return 0;
}
