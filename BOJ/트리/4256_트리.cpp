/*
종만북에서 나온 코드를 사용하니 시간초과를 받았다.
여기서는 단순히 벡터를 따로 구하지 않고 인덱스만 옮겨도 정답을 받을 수 있었다.
*/

#include <iostream>
#include <vector>
using namespace std;

int preorder[1001];
int inorder[1001];


void solution(int root, int s, int e) {
    for (int i = s; i < e; i++) {
        if (inorder[i] == preorder[root]) {
            solution(root + 1, s, i); // left sub tree
            solution(root + i + 1 - s, i + 1, e); // right sub tree
            cout << preorder[root] << " ";
        }
    }
}

int main(void) {
    int test_case;
    cin >> test_case;
    while (test_case--) {
        int n; cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> preorder[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> inorder[i];
        }
        solution(0, 0, n);
        cout << '\n';
    }
    return 0;
}