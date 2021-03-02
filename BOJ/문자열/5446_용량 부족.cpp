/*
여기서 파일 문자명이 특수문자를 포함하고 있기 때문에 아스키코드 범위 전체를 자식으로 가져야한다.
아스키코드가 0~127까지 있기 때문에 배열 크기를 128로 잡아준다.
그리고 노드의 끝을 나타내는 변수, 삭제해도 되는지 변수, 자식여부를 확인하는 변수(추측임)를 선언했다.
->exist 변수는 딱히 필요없는 듯 하다. 그냥 삭제 여부와 노드 끝 여부를 확인하는 변수만 있으면 된다.

그리고 입력할때 노드의 끝이면 삭제 여부와 노드 끝 변수를 true인지, false인지 확정한다.

지울 수 있는 조건은
1. del이 참일 때 지울 수 있다. 이 때는 *를 쓴다고 생각해 return 해준다
2. del이 거짓이여도 단어의 끝부분이여서 vaild==true일 때 지울 수 있다

이렇게 해서 트라이를 한 번 쭉 돌면 답을 구할 수 있다고 한다.

트라이 문제를 어떻게 해결해야 할지 전혀 감이 오지 않는다.
*/

#include <iostream>
using namespace std;
int ans;
char arr[22];
struct Trie {
    bool vaild, del;
    Trie* node[128];
    Trie() : vaild(false), del(false) {
        for (int i = 0; i < 128; i++) node[i] = 0;
    }
    ~Trie() {
        for (int i = 0; i < 128; i++)
            if (node[i]) delete node[i];
    }
    void add(const char* s, bool ok) {
        if (*s == 0) {
            del = ok;
            vaild = ok; return;
        }
        else {
            int pos = *s;
            if (node[pos] == NULL) node[pos] = new Trie();
            del = ok;
            node[pos]->add(s + 1, ok);
        }
    }
    void dfs() {
        //삭제해도 되면 rm *를 사용할 수 있다.
        if (del) {
            ans++; return;
        }
        //del=false여도 단어의 끝부분이여서 vaild==true일 때 지울 수 있다
        else if (vaild) ans++;
        for (int i = 0; i < 128; i++) {
            if (node[i]) node[i]->dfs();
        }
    }
};
int main() {
    int t, n, m; scanf(" %d", &t);
    while (t--) {
        scanf(" %d", &n);
        Trie* root = new Trie();
        //삭제해도 되는건 true로 넣어준다.
        for (int i = 0; i < n; i++) {
            scanf(" %s", &arr);
            root->add(arr, true);
        }
        scanf(" %d", &m);
        //삭제하면 안 되는건 false로 넣어준다.
        for (int i = 0; i < m; i++) {
            scanf(" %s", &arr);
            root->add(arr, false);
        }
        ans = 0;
        root->dfs();
        printf("%d\n", ans);
        delete root;
    }
}