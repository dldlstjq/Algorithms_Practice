/*
전위, 중위, 후위순회를 이용한 트리 순회문제.
트리를 직접 구현하지 않고 재귀함수로만 순회를 출력할 수 있다.
처음에 순회에 맞는 트리를 구현하려다 너무 복잡해서 해결할 수 없었다.
트리순회는 재귀함수로 생각하는 것이 좋다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;  //노드 수

vector<int> slice(const vector<int>& v, int a, int b) {
    return vector<int>(v.begin() + a, v.begin() + b);
}

//트리의 전위탐색 결과와 중위탐색 결과가 주어질 때 후위탐색 결과를 출력한다.
void printPostOrder(const vector<int>& preorder, const vector<int>& inorder) {
    //트리에 포함된 노드 수
    int n = preorder.size();
    //기저사례: 텅 빈 트리면 곧장 종료
    if (preorder.empty())
        return;
    //이 트리의 루트는 전위 탐색 결과로부터 곧장 알 수 있다.
    const int root = preorder[0];

    //이 트리의 왼쪽 서브트리의 크기는 중위 탐색 결과에서 루트위 위치를 찾아서 알 수 있다.
    const int left = find(inorder.begin(), inorder.end(), root) - inorder.begin();
    //오른쪽 서브트리의 크기는 n에서 왼쪽 서브르트리와 루트를 뺴면 알 수 있다.
    const int right = n - 1 - left;

    //왼쪽과 오른쪽 서브트리의 순회 결과를 출력
    printPostOrder(slice(preorder, 1, left + 1), slice(inorder, 0, left));
    printPostOrder(slice(preorder, left + 1, n), slice(inorder, left + 1, n));

    //후위 순회이므로 루트를 가장 마지막에 출력한다.
    cout << root << " ";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        cin >> N;
        vector<int> preorder;
        vector<int> inorder;
        for (int i = 0; i < N; ++i) {
            int node;
            cin >> node;
            preorder.push_back(node);
        }

        for (int i = 0; i < N; ++i) {
            int node;
            cin >> node;
            inorder.push_back(node);
        }

        printPostOrder(preorder, inorder);
        cout << "\n";
    }

    return 0;
}