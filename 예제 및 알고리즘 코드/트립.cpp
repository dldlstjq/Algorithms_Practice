/*
트립은 입력이 특정 순서로 주어질 때 그 성능이 떨어진다는 이진 검색 트리의
단점을 해결하기 위해 고안된 일종의 랜덤화된 이진 검색 트리입니다. 트립은
이진 검색 트리와 같은 성질을 가지고 있지만 트리의 형태가 원소들의 추가 순서에 따라
결정되지 않고 난수에 의해 임의대로 결정됩니다. 때문에 원소들이 어느 순서대로
추가되고 삭제되더라도 트리 높이의 기대치는 항상 일정합니다.

이와 같은 속성을 유지하기 위해 트립은 새 노드가 추가될 때마다 해당 노드에
우선순위(priority)를 부여합니다. 이 우선순위는 원소의 대소 관계나 입력되는 순서와
아무런 상관 없이 난수를 통해 생성합니다. 트립은 항상 부모의 우선순위가 자식의 우선순위보다
높은 이진 검색 트리를 만듭니다. 따라서 트립의 조건을 다음 두 가지로 정리할 수 있습니다.

이진 검색트리의 조건 : 모든 노드에 대해 왼쪽 서브트리에 있는 노드들의 원소는 해당 노드의
원소보다 작고, 오른쪽 서브트리에 있는 노드들의 원소는 해당 노드의 원소보다 큽니다.

힙의 조건: 모든 노드의 우선순위는 각자의 자식 노드보다 크거나 같습니다.

*/

//트립의 노드를 표현하는 객체의 구현
typedef int KeyType;
//트립의 한 노드를 저장한다.
struct Node {
	//노드에 저장된 원소
	KeyType key;
	//이 노드의 우선순위(priority)
	//이 노드를 루트로 하는 서브트리의 크기(size)
	int priority, size;
	//두 자식 노드의 포인터
	Node* left, * right;
	//생성자에서 난수 우선순위를 생성하고, size와 left/right를 초기화한다.
	Node(const KeyType& _key) :key(_key), priority(rand()),
		size(1), left(NULL), right(NULL) {
	}
	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	//size 멤버를 갱신한다.
	void calcSize() {
		size = 1;
		if (left)size += left->size;
		if (right)size += right->size;
	}
};

//트립에서의 노드 추가와 트립 쪼개기 연산의 구현
typedef pair<Node*, Node*> NodePair;
//root를 루토르 하는 트립을 key 미만의 값과 이상의 값을 갖는
//두 개의 트립으로 분리한다.
NodePair split(Node* root, KeyType key) {
	if (root == NULL)return NodePair(NULL, NULL);
	//루트가 key 미만이면 오른쪽 서브트리를 쪼갠다.
	if (root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	//루트가 key 이상이면 왼쪽 서브트리를 쪼갠다.
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

//root를 루트로 하는 트립에 새 노드 node를 삽입한 뒤 결과 트립의
//루트를 반환한다.
Node* insert(Node* root, Node* node) {
	if (root == NULL)return node;
	//node가 루트를 대체해야 한다. 해당 서브트리를 반으로 갈라
	//각각 자손으로 한다.
	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setLeft(splitted.second);
		return node;
	}
	else if (node->key < root->key)
		root->setLeft(insert(root->left, node));
	else
		root->setRight(insert(root->right, node));
	return root;
}

//트립의 루트를 가리키는 포인터 root가 있을 때, 새 값 value를 다음과 같이 추가할 수 있습니다.
root = insert(root, newNode(value));

//트립에서 노드의 삭제와 합치기 연산의 구현
//a와 b가 두 개의 트립이고, max(a) < max(b)일때 이 둘을 합친다.
Node* merge(Node* a, Node* b) {
	if (a == NULL)return b;
	if (b == NULL)return a;
	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

//root를 루트로 하는 트립에서 key를 지우고 결과 트립이 루트를 반환한다.
Node* erase(Node* root, KeyType key) {
	if (root == NULL)return root;
	//root를 지우고 양 서브트리를 합친 뒤 반환한다.
	if (root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
}

//트립에서 k번쨰 원소를 찾는 알고리즘의 구현
//root를 루트로 하는 트리 중에서 k번째 원소를 반환한다.
Node* kth(Node* root, int k) {
	//왼쪽 서브트리의 크기를 우선 개선한다.
	if leftSize = 0;
	if (root->left != NULL)leftSize = root->left->size;
	if (k <= leftSize)return kth(root->left, k);
	if (k == leftSize + 1)return root;
	return kth(root->right, k - leftSize - 1);
}

//트립에서 x보다 작은 원소의 수를 찾는 알고리즘의 구현
//key보다 작은 키값의 수를 반환한다.
int countLessThan(Node* root, KeyType key) {
	if (root == NULL)return 0;
	if (root->key >= key)
		return countLessThan(root->left, key);
	int ls = (root->left ? root->left->size : 0);
	return ls + 1 + countLessThan(root->right, key);
}