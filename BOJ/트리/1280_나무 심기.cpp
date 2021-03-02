/*
구간 트리를 사용해도 되고 펜윅 트리를 사용해도 되는데 
둘 다 해결하지 못했다.
아무래도 세그먼트 트리 문제를 많이 풀어보지 못해서 응용문제가 나왔을 때
어떻게 해야 하는지 잘 몰라서 그러는 것 같다.
*/
//펜윅 트리를 이용해봤는데 잘 안된다.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;
const int MAX = 200010;
//int arr[MAX];
int N;

//나무의 개수를 센다.
struct countTree {
	vector<long long> tree;
	countTree(int n) :tree(n + 1) {}
	//A[0..pos]의 부분 합을 구한다.
	long long sum(int pos) {
		//인덱스가 1부터 시작한다고 생각하자.
		//++pos;
		long long ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			//다음 구간을 찾기 위해 최종 비트를 지운다.
			ret &= (pos - 1);
		}
		return ret;
	}

	//나무 갯수를 반환한다.
	void count(int pos) {
		//++pos;
		while (pos <= MAX) {
			tree[pos] += 1;
			pos += (pos & -pos);
		}
	}
};

//나무 간 거리 구한다.
struct distTree {
	vector<long long> tree;
	distTree(int n) :tree(n + 1) {}
	//A[0..pos]의 부분 합을 구한다.
	long long sum(int pos) {
		//인덱스가 1부터 시작한다고 생각하자.
		//++pos;
		long long ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			//다음 구간을 찾기 위해 최종 비트를 지운다.
			ret &= (pos - 1);
		}
		return ret;
	}
	//A[pos]에 val을 더한다.
	void add(int pos, int val) {
		//++pos;
		while (pos <= MAX) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};



int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	vector<int> v(N);
	countTree cnt_tree(MAX);
	distTree dist_tree(MAX);

	for (int i = 1; i <= N; ++i) {
		int pos;
		cin >> pos;
		v[i] = pos;
	}

	cnt_tree.count(v[1]);
	dist_tree.add(v[1], v[1]);

	long long ans = 1;
	for (int i = 2; i <= N; ++i) {
		long long leftCnt = cnt_tree.sum(v[i] - 1);
		long long rightCnt = cnt_tree.sum(MAX) - cnt_tree.sum(v[i]);
		long long leftDist = dist_tree.sum(v[i] - 1);
		long long rightDist = dist_tree.sum(MAX) - dist_tree.sum(v[i]);

		long long leftRet = v[i] * leftCnt - leftDist;
		leftRet %= MOD;
		long long rightRet = rightDist - v[i] * rightCnt;
		rightRet %= MOD;

		long long ret = (leftRet + rightRet) % MOD;
		ans *= ret;
		ans %= MOD;

		cnt_tree.count(v[i]);
		dist_tree.add(v[i], v[i]);
	}

	cout << ans % MOD;
	return 0;
}



////////////////////////////
//세그먼트 트리 풀이
/*
node를 나무들의 좌표를 기준으로 Segment tree를 구성하면 해결할 수 있다.

현재 나무보다 큰나무들의 합, 작은 나무들의 합, 큰 나무들의 개수, 작은 나무들의 개수를 구해서
해결하면 된다.
*/
#include <cstdio>
#include <vector>

using namespace std;
#define MAX 200001
#define mod 1000000007

typedef long long ll;

struct Segment {
	vector<ll> tree;
	int size;

	Segment() {
		tree.resize(4 * MAX, 0);
		size = MAX;
	}

	ll update(int idx, int node, ll val, int nL, int nR) {
		if (idx < nL || idx > nR) return tree[node];
		if (nL == nR) {
			return tree[node] += val;
		}
		int mid = (nL + nR) / 2;
		return tree[node] = update(idx, node * 2, val, nL, mid) + update(idx, node * 2 + 1, val, mid + 1, nR);
	}

	ll update(int idx, ll val) {
		return update(idx, 1, val, 0, size - 1);
	}

	ll query(int node, int l, int r, int nL, int nR) {
		if (r < nL || l > nR) return 0;
		if (l <= nL && nR <= r) return tree[node];
		int mid = (nL + nR) / 2;
		return query(node * 2, l, r, nL, mid) + query(node * 2 + 1, l, r, mid + 1, nR);
	}

	ll query(int l, int r) {
		return query(1, l, r, 0, size - 1);
	}
};

int N;
int input;
int main() {
	Segment seg_sum, seg_cnt;
	scanf("%d", &N);

	scanf("%d", &input);
	seg_sum.update(input, input);        // 구간 거리 합
	seg_cnt.update(input, 1);            // 구간 카운트 합

	long long ans = 1;

	for (int n = 1; n < N; n++) {
		scanf("%d", &input);
		seg_sum.update(input, input);
		seg_cnt.update(input, 1);

		ll sum1 = seg_sum.query(0, input - 1);        //기준보다 작은경우
		ll sum2 = seg_sum.query(input + 1, MAX);    //기준보다 큰 경우
		ll cnt1 = seg_cnt.query(0, input - 1);
		ll cnt2 = seg_cnt.query(input + 1, MAX);

		ll cost = (sum2 - input * cnt2) % mod + (input * cnt1 - sum1) % mod;
		ans *= cost % mod;
		ans %= mod;
	}
	printf("%lld\n", ans);
	return 0;
}
