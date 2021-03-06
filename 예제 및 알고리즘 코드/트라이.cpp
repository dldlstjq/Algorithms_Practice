﻿//만약 트라이의 terminal 멤버 변수를 불린 값에서 다른 변수형으로 바꾸현 트라이를 
//사전자료구조로 이용할 수 있다.
//예를 들어 terminal을 정수형으로 바꾸면 간단하게 문자열을 정수로 대응하는 사전 자료구조가 되므로
//map<string, int>를 대체할 수 있다.

//트라이의 노드를 표현하는 객체의 선언
//알파벳 대문자를 저장하는 경우 각 노드는 26개의 자손을 가질 수 있다.
const int ALPHABETS = 26;
//알파벳을 숫자로 변환
int toNumber(char ch) { return ch - 'A'; }
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
			if (children[next] == NULL)
				children[next] = new TrieNode();
			//해당 자식 노드로 재귀 호출
			children[next]->insert(key + 1);
		}
	}
	//이 노드를 루트로 하는 트라이에 문자열 key와 대응되는 노드를 찾는다.
	//없으면 NULL을 반환한다.
	TrieNode* find(const char* key) {
		if (*key == 0)return this;
		int next = toNumber(*key);
		if (children[next] == NULL)return NULL;
		return children[next]->find(key + 1);
	}
};