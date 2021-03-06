//트리의 노드를 표현하는 객체의 구현
//이진 검색 트리의 경우 자식 노드 포인터 배열 대신 left, right를 이용해 자식들을 저장
//힙에서는 배열을 사용해 트리 표현
struct TreeNode {
	string label;	//저장할 자료(물론 꼭 문자열일 필요는 없다.)
	TreeNode* parent;	//부모 노드를 가리키는 포인터
	vector<TreeNode*> children;	//자손 노드들을 가리키는 포인터의 배열
};


//트리를 순회하며 모든 노드에 포함된 값을 출력하기
//주어진 트리의 각 노드에 저장된 값을 모두 출력한다.
void printLabels(TreeNode* root) {
	//루트에 저장된 값을 출력한다.
	cout << root->label << "\n";
	//각 자손들을 루트로 하는 서브트리에 포함된 값들을 재귀적으로 출력한다.
	for (int i = 0; i < root->children.size(); ++i)
		printLabels(root->chlidren[i]);
}


//순회를 이용해 트리의 높이를 계산하기
//root를 루트로 하는 트리의 높이를 구한다.
int height(TreeNode* root) {
	int h = 0;
	for (int i = 0; i < root->children.size(); ++i)
		h = max(h, 1 + height(root->children[i]));
	return h;
}


//트리에서 가장 긴 경로를 찾는 재귀 호출 알고리즘
//입력의 크기가 작으면 BFS나 플로이드 알고리즘을 사용해도 되긴 하다.
/*
최장 경로의 길이는 다음 둘 중 더 큰 값
1. 가장 긴 루트-잎 경로의 길이
2. 가장 긴 잎-잎 경로의 길이
*/

struct TreeNode {
	vector<TreeNode*> children;	
};
//지금까지 찾은 가장 긴 잎-잎 경로의 길이를 저장한다.
int longest;
//root를 루트로 하는 서브트리의 높이를 반환한다.
int height(TreeNode* root) {
	//각 자식을 루트로 하는 서브트리의 높이를 계산한다.
	vector<int> heights;
	for (int i = 0; i < root->children.size(); ++i)
		heights.push_back(height(root->children[i]));
	//만약 자식이 하나도 없다면 0을 반환한다.
	if (heights.empty()) return 0;
	sort(heights.begin(), heights.end());
	//root를 최상위 노드로 하는 경로를 고려하자.
	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
	//트리의 높이는 서브트리의 높이의 최대치에 1을 더해 계산한다.
	return heights.back() + 1;
}

//두 노드 사이의 가장 긴 경로의 길이를 계산한다.
int solve(TreeNode* root) {
	longest = 0;
	//트리의 높이와 최대 잎-잎 경로 길이 중 큰 것을 선택한다.
	int h = height(root);
	return max(longest, h);
}