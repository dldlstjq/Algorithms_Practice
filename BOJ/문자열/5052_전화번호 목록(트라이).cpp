/*
문자열 집합을 트리로 표현한 트라이 자료구조.
비교적 간단한 트라이에 속하는데 처음 접해보니 쉽지 않았다.
많은 연습이 필요하다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

//숫자만 취급하므로 10개
const int NUMBER = 10;
//주어진 문자를 [0, NUMBER-1] 범위의 숫자로 변환
int toNumber(char ch) {
    return ch - '0';
}

//트라이의 한 노드를 나타내는 객체
struct TrieNode {
    TrieNode* children[NUMBER];
    //현 위치에서 끝나는지 확인
    bool terminal;
    //자식이 있는지 없는지 확인
    bool consistent;
    //출력 문자열 목록: 이 노드가 방문되었을 때 등장하는 바늘 문자열들의 번호
    TrieNode() : terminal(false), consistent(false) {
        memset(children, 0, sizeof(children));
    }
    //소멸자
    ~TrieNode() {
        for (int i = 0; i < NUMBER; ++i)
            if (children[i])
                delete children[i];
    }

    //이 노드를 루트로 하는 트라이에 문자열 key를 추가한다.
    void insert(const char* key) {
        //문자열이 끝났다면 terminal만 바꾸고 종료
        if (*key == 0) {
            terminal = true;
        }

        else {
            int next = toNumber(*key);
            //해당 자식 노드가 없다면 생성한다.
            if (children[next] == NULL)
                children[next] = new TrieNode();
            //consistent를 true로. 자식이 있다는 뜻.
            consistent = true;
            //해당 자식 노드로 재귀호출
            children[next]->insert(key + 1);
        }
    }

    //insert와 동시에 일관성 확인
    bool insert1(const char* key) {

        //문자열이 끝났다면 terminal만 바꾸고 종료
        if (*key == 0) {
            terminal = true;
            //만약 자식이 있다면 일관성이 없다.
            //consistent가 true면 자식이 있다는 뜻이므로 그 반대인 false 리턴.
            return !consistent;
        }

        else {
            int next = toNumber(*key);
            //해당 자식 노드가 없다면 생성한다.
            if (children[next] == NULL)
                children[next] = new TrieNode();
            //consistent를 다시 false로
            consistent = true;
            //해당 자식 노드로 재귀호출. 자식이 있는데 여기서 끝나는 번호가 있다면 일관성이 없다.
            return !terminal && children[next]->insert1(key + 1);
        }
    }

    bool is_consistent() {
        //자식이 있으면서 끝나는 전화번호 있으면 일관성 없음
        if (consistent && terminal)
            return false;
        //자식들 중 하나라도 일관성이 없으면 이 노드도 일관성이 없음
        for (int i = 0; i < NUMBER; ++i) {
            if (children[i] && !children[i]->is_consistent())
                return false;
        }
        return true;
    }
};

//입력에 주어지는 단어들을 트라이로 변환한다.
TrieNode* readInput(int words) {
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

    int c;
    cin >> c;
    while (c--) {
        int n;
        cin >> n;
        //insert와 동시에 일관성 확인
        /*string input;
        bool ret = true;
        TrieNode* trie = new TrieNode();
        for (int i = 0; i < n; ++i) {
            cin >> input;
            trie->insert(input.c_str());
            if (ret && !trie->insert1(input.c_str()))
                ret = false;
        }
        if(ret)
            cout << "YES" << "\n";
        else
            cout << "NO" << "\n";*/

            //insert 따로, 일관성 확인 따로
        TrieNode* root = readInput(n);
        if (root->is_consistent())
            cout << "YES" << "\n";
        else
            cout << "NO" << "\n";

        delete root;
    }
    return 0;
}