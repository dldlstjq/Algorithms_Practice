/*
개념자체는 크게 어렵지 않았지만 코드로 구현하는 과정을 이해하는데 많은 시간이 걸렸다.
특히 노드의 first 값 바뀌는 것을 이해하는데 애를 먹었다.

결론은 루트는 아무 문자도 없기 때무에 first가 -1이고 
문자가 하나씩 들어올수록 먼저 들어온 문자에 따라 해당 노드의 first값이 바뀐다는 점이다.
terminal은 종료 노드일때만 값이 바뀌고 그게 아니면 -1이다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

//알파벳 대문자를 저장하는 경우 각 노드는 26개의 자손을 가질 수 있다.
const int ALPHABETS = 26;
//주어진 문자를 [0, ALPHABETS-1] 범위의 숫자로 변환
int toNumber(char ch) {
    return ch - 'A';
}

//트라이의 한 노드를 나타내는 객체
struct TrieNode {
    TrieNode* children[ALPHABETS];
    //이 노드에서 종료하는 문자열의 번호. 없으면 -1
    int terminal;
    //이 노드를 루트로 하는 트라이에 가장 먼저 추가된 단어의 번호. -1로 초기화
    int first;
    TrieNode() : terminal(-1), first(-1) {
        memset(children, 0, sizeof(children));
    }
    //소멸자
    ~TrieNode() {
        for (int i = 0; i < ALPHABETS; ++i)
            if (children[i])
                delete children[i];
    }

    //이 노드를 루트로 하는 트라이에 번호 id인 문자열 key를 추가한다.
    void insert(const char* key, int id) {
        //first를 우선 갱신
        //처음엔 first가 모두 -1로 초기화된 상태. 이후 먼저 추가되는 문자에 따라 노드의 first가 바뀜.
        //루트의 first는 -1.
        if (first == -1)first = id;
        //문자열이 끝났다면 terminal만 바꾸고 종료
        if (*key == 0)
            terminal = id;
        else {
            int next = toNumber(*key);
            //해당 자식 노드가 없다면 생성한다.
            if (children[next] == NULL)
                children[next] = new TrieNode();
            //해당 자식 노드로 재귀호출
            children[next]->insert(key + 1, id);
        }
    }

    //이 노드까지 타이핑해 왔을 때, 번호 id인 key를 타이핑하기 위해
    //최소 몇 번의 키를 더 눌러야 하나?
    int type(const char* key, int id) {
        //문자열 종료시
        if (*key == 0)
            return 0;
        //이 노드에서 추천되는 문자열이 이 문자열이면 탭 누르고 종료
        //루트는 길이 0인 문자열. 따라서 루트는 first가 -1임. 그 뒤 오는 문자에 따라 first 값이 달라짐
        if (first == id)
            return 1;
        //아니면 다음 문자를 타이핑한다.
        int next = toNumber(*key);
        return 1 + children[next]->type(key + 1, id);
    }

    //이 노드를 루트로 하는 트라이에 문자열 key와 대응하는 노드를 찾는다.
    //없으면 NULL을 반환한다.
    TrieNode* find(const char* key) {
        if (*key == 0)
            return this;
        int next = toNumber(*key);
        if (children[next] == NULL)return NULL;
        return children[next]->find(key + 1);
    }
};

//사전을 나타내느 트라이가 주어질 때, 단어 word를 타이핑하는데
//몇 번이나 키를 눌러야 하는지 계산한다.
int countKeys(TrieNode* trie, const char* word) {
    //이 문자열이 사전이 있는지 확인하고, 있다면 번호를 구한다.
    //node에는 제일 마지막 단어가 들어있는 종료노드가 저장된다.
    TrieNode* node = trie->find(word);
    //사전에 없으면 직접 타이핑할 수 밖에 없다.
    if (node == NULL || node->terminal == -1)
        return strlen(word);
    //탐색하면서 타이핑할 방법을 찾는다.
    return trie->type(word, node->terminal);
}

//입력에 주어지는 단어들을 정렬해서 트라이로 변환한다.
TrieNode* readInput(int words) {
    //단어들을 출현 빈도의 내림차순, 단어의 오름차순으로 정렬한다.
    vector<pair<int, string>> input;
    for (int i = 0; i < words; ++i) {
        char buf[11];
        int freq;
        cin >> buf >> freq;
        input.push_back({ -freq,buf });
    }
    sort(input.begin(), input.end());
    //이때 앞에 있는 단어일수록 우선순위가 높다.
    //배열의 인덱스를 각 단어의 번호로 쓰자.
    TrieNode* trie = new TrieNode();
    for (int i = 0; i < input.size(); ++i)
        trie->insert(input[i].second.c_str(), i);
    //루트의 first는 -1.
    //아무 글자도 입력하지 않을 경우에는 자동완성이 안됨.
    trie->first = -1;
    return trie;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int n, m;
        cin >> n >> m;

        TrieNode* trie = readInput(n);
        //스페이스바 누르는 횟수
        int result = m - 1;
        for (int i = 0; i < m; ++i) {
            char buf[11];
            cin >> buf;
            result += countKeys(trie, buf);
        }
        cout << result << "\n";
    }
    return 0;
}
