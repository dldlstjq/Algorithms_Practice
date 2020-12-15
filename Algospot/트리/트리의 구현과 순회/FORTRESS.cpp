/*
트리를 이용해서 풀 수 있다.
트리를 생성하는 것 부터 원이 포함되는지 안되는지,
트리의 높이를 구하는 것까지 해서 생각해야 될게 많다.
기하적인 부분까지 있어 아직은 많이 어렵다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 100;

struct TreeNode {
    vector<TreeNode*> children;
};
int n, y[MAX], x[MAX], radius[MAX];
//지금까지 찾은 가장 긴 leaf~leaf 경로의 길이를 저장
int longest;

//root를 루트로 하는 서브트리의 높이를 반환한다.
int height(TreeNode* root) {
    //각 자식을 루트로 하는 서브트리의 높이를 계산한다.
    vector<int> heights;
    for (int i = 0; i < root->children.size(); ++i)
        heights.push_back(height(root->children[i]));
    //만약 자식이 하나도 없다면 0을 반환한다
    if (heights.empty())
        return 0;
    //서브트리 개수가 2개 이상인지 확인
    sort(heights.begin(), heights.end());
    //root를 최상위 노드로 하는 경로를 고려하자.
    //서브트리 개수가 2개 이상인지 확인
    if (heights.size() >= 2)
        //오름차순 정렬했으므로, 가장 큰 높이 2개 추출
        longest = max(longest, 2 + heights[heights.size() - 2] +
            heights[heights.size() - 1]);
    //트리의 높이는 서브트리 높이의 최대치에 1을 더해 계산한다.
    return heights.back() + 1;
}

int solve(TreeNode* root) {
    longest = 0;
    //트리의 높이와 최대 잎-잎 경로 길이 중 큰 것을 선택한다.
    int h = height(root);
    return max(longest, h);
}

//x^2를 반환한다.
int sqr(int x) {
    return x * x;
}

//두 성벽 a,b의 중심점 간의 거리의 제곱을 반환한다.
int sqrdist(int a, int b) {
    return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);
}

//성벽 a가 성벽 b를 포함하는지 확인한다.
bool encloses(int a, int b) {
    return radius[a] > radius[b] &&
        sqrdist(a, b) < sqr(radius[a] - radius[b]);
}

//'성벽'트리에서 parent가 child의 부모인지 확인한다.
//parent는 child를 꼭 직접 포함해야 한다.
bool isChild(int parent, int child) {
    if (!encloses(parent, child))
        return false;
    //두 성벽 사이에 다른 성벽이 있는지 확인
    //즉, 직계 부모-자식 관계인지 확인
    for (int i = 0; i < n; ++i) {
        //부모도 자식도 아닌 성벽(노드, 원)이 부모 노드에 포함되면서, child를 포함하는지 확인
        if (i != parent && i != child &&
            encloses(parent, i) && encloses(i, child))
            return false;
        return true;
    }
}

//0번 성벽 바로 밑에 들어갈 성벽들을 찾고
//각각의 성벽을 루트로 하는 서브트리를 재귀적으로 생성
TreeNode* getTree(int root) {
    TreeNode* result = new TreeNode();
    //ch 성벽이 root 성벽에 직접적으로 포함되어 있다면
    //트리를 만들고 자손 목록에 추가한다.
    for (int ch = 0; ch < n; ++ch) {
        if (isChild(root, ch))
            result->children.push_back(getTree(ch));
    }
    return result;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int n;
        cin >> n;
        vector<pair<pair<int, int>, int>>wall;
        for (int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i] >> radius[i];
        }
        TreeNode* t = getTree(0);
        cout << solve(t) << "\n";
    }


    return 0;
}