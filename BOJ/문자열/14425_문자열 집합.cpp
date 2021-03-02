/*
집합안에 문자가 포함된 게 몇개인지 확인하는 것이다.
트라이로 풀어도 되고 set을 이용해서 간단하게 풀 수도 있다.
set으로 푼 문제의 시간 복잡도는 O(문자열의 갯수(10000)*set의 탐색시간(log10000))이고
trie를 이용한 문제의 시간복잡도는 o(문자열의 갯수(10000)* trie의 탐색 시간 즉 문자열의 길이(500)) 이므로
trie를 이요한 것이 set보다 시간이 더 오래 걸린다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

//트라이의 노드를 표현하는 객체의 선언
//알파벳 대문자를 저장하는 경우 각 노드는 26개의 자손을 가질 수 있다.
const int ALPHABETS = 26;
//알파벳을 숫자로 변환
int toNumber(char ch) { return ch - 'a'; }
//트라이의 한 노드를 나타내는 객체
struct TrieNode {
	TrieNode* children[ALPHABETS];
	//이 노드가 종료노드인가?
	bool terminal;

	TrieNode() :terminal(false) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < ALPHABETS; ++i)
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
			if (children[next] == NULL) {
				children[next] = new TrieNode();
			}
			//해당 자식 노드로 재귀 호출
			children[next]->insert(key + 1);
		}
	}
	//이 노드를 루트로 하는 트라이에 문자열 key와 대응되는 노드를 찾는다.
	//없으면 NULL을 반환한다.
	TrieNode* find(const char* key) {
		if (*key == 0) {
			//해당 노드가 완전히 끝나야 집합에 포함돼있다고 할 수 있다.
			if (terminal)
				return this;
		}
		int next = toNumber(*key);
		if (children[next] == NULL)return NULL;
		return children[next]->find(key + 1);
	}
};


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	//트라이 생성
	TrieNode* trie = new TrieNode();
	for (int i = 0; i < n; ++i) {
		string str;
		cin >> str;
		trie->insert(str.c_str());
	}

	int ans = 0;
	for (int i = 0; i < m; ++i) {
		string str;
		cin >> str;
		TrieNode* tmp = trie->find(str.c_str());
		//결과가 NULL이면 집합에 없다는 의미. NULL이 아니면 집합에 있다.
		if (tmp != NULL)
			ans++;
	}
	cout << ans;
	return 0;
}


/////////////////////////////////////////
//set을 이용한 풀이. 더 간단하다.
#include <iostream>
#include <set>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	set<string> s;

	for (int i = 0; i < n; ++i) {
		string str;
		cin >> str;
		s.insert(str);
	}

	int ans = 0;
	for (int i = 0; i < m; ++i) {
		string str;
		cin >> str;
		if (s.find(str) != s.end())
			ans++;
	}
	cout << ans;
	return 0;
}