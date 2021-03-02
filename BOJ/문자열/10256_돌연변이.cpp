/*
백준문제에서 아호코라식 응용문제로 제일 유명하다는데 어렵다.
모든 돌연변이 마커 구하는 것도 잘 생각이 나지 않았고 아호코라식을 어떻게 적용해야 하는지
도통 생각이 안났다.
며칠 쉬다 접하니 어떻게 접근하고 코드를 짜야 하는지 잘 생각이 안난다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

int ans;

//쓰는 문자가 4개밖에 없기 때문에 간단하게 한다.
int toNumber(char ch) {
	if (ch == 'A')
		return 0;
	else if (ch == 'C')
		return 1;
	else if (ch == 'G')
		return 2;
	else if (ch == 'T')
		return 3;

}
//트라이의 한 노드를 나타내는 객체
struct TrieNode {
	TrieNode* children[4];
	//이 노드가 종료노드인가?
	bool terminal;

	//실패 연결: 이 노드에서 매칭이 실패했을 때 이 곳으로 가서 계속한다.
	//이 노드에 대응되는 문자열의 접미사이면서 트라이에 포함된 최대 문자열.
	TrieNode* fail;
	//출력 문자열 목록: 이 노드가 방문되었을 때 등장하는 바늘 문자열들의 번호
	vector<int> output;

	TrieNode() :terminal(false) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < 4; ++i)
			if (children[i])
				delete children[i];
	}
	//이 노드를 루트로 하는 트라이에 문자열 key를 추가한다.
	void insert(const char* key) {
		//문자열이 끝나면 terminal만 참으로 바꾸고 종료
		if (*key == 0)
			terminal = true;
		else {
			int next = toNumber(*key);
			//해당 자식 노드가 없다면 생성한다.
			if (children[next] == NULL)
				children[next] = new TrieNode();
			//해당 자식 노드로 재귀 호출
			children[next]->insert(key + 1);
		}
	}
};

//아호-코라식 알고리즘에서 실패함수의 계산
void computeFailFunc(TrieNode* root) {
	//루트에서부터 시작해 한 단계씩 아래로 내려가며 각 노드의 실패 연결을 계산한다.
	queue<TrieNode*> q;
	//루트의 실패 연결은 자기자신
	root->fail = root;
	q.push(root);
	while (!q.empty()) {
		TrieNode* here = q.front();
		q.pop();
		//here의 모든 자손에 대해 실패연결을 계산하고 이들을 큐에 넣는다.
		for (int edge = 0; edge < 4; ++edge) {
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

//아호코라식 알고리즘의 실제 탐색 과정
//trie에 포함된 패턴들을 s에서 찾는다.
void ahoCorasick(const string& s, TrieNode* root) {
	TrieNode* state = root;
	//실제 반복문 내는 KMP와 별로 다를 것이 없다.
	for (int i = 0; i < s.size(); ++i) {
		int chr = toNumber(s[i]);
		while (state != root && state->children[chr] == NULL)
			state = state->fail;
		if (state->children[chr])
			state = state->children[chr];
		//DNA문자열의 각 index에서 끝나는 돌연변이가 있는지를 체크하고, 있다면 ans++만 해주면 충분하다.
		if (state->terminal == true)
			ans++;
	}

}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		string dna, marker;
		cin >> dna >> marker;

		TrieNode* root = new TrieNode();
		ans = 0;
		root->insert(marker.c_str());
		//돌연변이를 만들어서 trie에 넣는다.
		for (int i = 0; i < marker.size(); ++i) {
			for (int j = i + 1; j < marker.size(); ++j) {
				string tmp = marker;
				reverse(tmp.begin() + i, tmp.begin() + j + 1);
				root->insert(tmp.c_str());
			}
		}
		computeFailFunc(root);
		ahoCorasick(dna, root);
		cout << ans << "\n";
		delete root;
	}

	return 0;
}