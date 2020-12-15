﻿/*
기본 함수만 세팅. 나중에 다시 보기
*/


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
            child->output = child->fail->output;
            if (child->terminal != -1)
                child->output.push_back(child->terminal);
            q.push(child);
        }
    }
}

//trie에 포함된 패턴들을 s에서 찾는다.
//s 내에서 패턴이 출현할 때마다(마지막 글자, 패턴 번호)의 쌍을 저장한다.
vector<pair<int, int>> ahoCorasick(const string& s, TrieNode* root) {
    vector<pair<int, int>> ret;
    TrieNode* state = root;
    //실제 반복문 내는 KMP와 별로 다를 것이 없다.
    for (int i = 0; i < s.size(); ++i) {
        int chr = toNumber(s[i]);
        while (state != root && state->children[chr] == NULL)
            state = state->fail;
        if (state->children[chr])
            state = state->children[chr];
        for (int j = 0; j < state->output.size(); ++j)
            ret.push_back(make_pair(i, state->output[j]));
    }
    return ret;
}
