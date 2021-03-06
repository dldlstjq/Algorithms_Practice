/*
구간 트리는 흔히 일차원 배열의 특정 구간에 대한 질문을 빠르게 대답하는데 사용합니다.
*/
//배열의 구간 최소 쿼리(RMQ)문제를 해결하는 구간트리의 초기화
struct RMQ {
	//배열의 길이
	int n;
	//각 구간의 최소치
	vector<int> rangeMin;
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}
	//node 노드가 array[left..right]배열을 표현할 때
	//node를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소치를 반환한다
	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
};

//RMQ문제를 푸는 구간 트리에서의 질의 연산의 구현
const int INT_MAX = numeric_limits<int>::max();
struct RMQ {
	//위의 구조체
	//node가 표현하는 범위 array[nodeLeft..nodeRight]가 주어질 때
	//이 범위와 array[left..right]의 교집합의 최소치를 구한다.
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		//두 구간이 겹치지 않으면 아주 큰 값을 반환한다: 무시됨
		if (right < nodeLeft || nodeRight < left)return INT_MAX;
		//node가 표현하는 범위가 array[left..right]에 완전히 포함되는 경우
		if (left <= nodeLeft && nodeRight <= right)
			return rangeMin[node];
		//양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid),
			query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	//query()를 외부에서 호출하기 위한 인터페이스
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}
};

//RMQ문제를 푸는 구간 트리에서의 갱신 연산의 구현
struct RMQ {
	//위의 구조체
	//array[index]=newValue로 바뀌었을 때 node를 루트로 하는
	//구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다.
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		//index가 노드가 표현하는 구간과 상관없는 경우엔 무시한다.
		if (index <= nodeLeft && nodeRight <= index)
			return rangeMin[node];
		//트리의 리프까지 내려온 경우
		if (nodeLeft == nodeRight)return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node]=min(
			update(index, newValue, node * 2, nodeLeft, mid),
			update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
	//query()를 외부에서 호출하기 위한 인터페이스
	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n - 1);
	}
};



//펜윅 트리: 빠르고 간단한 구간 합
/*
펜윅 트리가 사용하는 중요한 아이디어는 구간 합 대신 부분 합만을 빠르게 계산할 수 있는 자료 구조를 만들어도
구간 합을 계산할 수 있다는 것입니다.
배열 A의 위치 pos에 대해 배열의 부분 합 psum[pos]=A[0]+A[1]+...+A[pos]를 빠르게
계산할 수 있다고 합시다. 그러면 [i, j] 구간의 합은 psum[j]-psum[i-1]으로 계산할 수 있습니다.

계속 변하는 배열의 구간 합을 구할 때는 구간 트리보다 펜윅 트리를 훨씬 자주 쓰게 됩니다.
*/
//펜윅 트리의 구현. 가상의 배열 A[]의 부분 합을
//빠르게 구현할 수 있도록 한다. 초기화시에는 A[]의
//원소가 전부 0이라고 생각한다.
struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n):tree(n+1){}
	//A[0..pos]의 부분 합을 구한다.
	int sum(int pos) {
		//인덱스가 1부터 시작한다고 생각하자.
		++pos;
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			//다음 구간을 찾기 위해 최종 비트를 지운다.
			ret &= (pos - 1);
		}
		return ret;
	}
	//A[pos]에 val을 더한다.
	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};