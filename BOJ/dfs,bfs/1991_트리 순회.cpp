/*
배열로 트리를 저장.
처음에 .으로 초기화해서 데이터 입력하고 재귀로 출력
*/

#include <cstdio>

char tree[26][2] = { '.', };

void preorder(char root) {
    if (root == '.') return;
    else {
        printf("%c", root);
        preorder(tree[root - 'A'][0]);
        preorder(tree[root - 'A'][1]);
    }
}

void inorder(char root) {
    if (root == '.') return;
    else {
        inorder(tree[root - 'A'][0]);
        printf("%c", root);
        inorder(tree[root - 'A'][1]);
    }
}

void postorder(char root) {
    if (root == '.') return;
    else {
        postorder(tree[root - 'A'][0]);
        postorder(tree[root - 'A'][1]);
        printf("%c", root);
    }
}

int main() {

    int n, i;
    char root, left, right;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf(" %c %c %c", &root, &left, &right);
        tree[root - 'A'][0] = left;
        tree[root - 'A'][1] = right;
    }

    preorder('A');
    printf("\n");
    inorder('A');
    printf("\n");
    postorder('A');
    printf("\n");

    return 0;
}

/////////////////////////////////////
/*
클래스를 설정한 풀이.
문제 풀이용 C++만 익혀서 클래스 사용법 모르는 게 함정...
정확하게 뭔진 몰라도 익혀두자.
*/
#include <iostream>
#include <string>
using namespace std;
class Tree {
    string data;
    Tree* left, * right;
public:
    Tree() { data = ""; left = NULL; right = NULL; }
    void setData(char data) { this->data = data; }
    void setLeft(Tree* left) { this->left = left; }
    void setRight(Tree* right) { this->right = right; }
    void static preorder(Tree* root) { // 전위
        if (root) {
            cout << root->data;
            preorder(root->left);
            preorder(root->right);
        }
    }
    void static inorder(Tree* root) { // 중위
        if (root) {
            inorder(root->left);
            cout << root->data;
            inorder(root->right);
        }
    }
    void static postorder(Tree* root) { // 후위
        if (root) {
            postorder(root->left);
            postorder(root->right);
            cout << root->data;
        }
    }
};
int main() {
    int n;
    cin >> n;
    Tree* tree = new Tree[n];
    for (int i = 0; i < n; ++i) {
        char data, left, right;
        cin >> data >> left >> right;
        if (data != '.')
            tree[(int)(data - 'A')].setData(data);
        if (left != '.')
            tree[(int)(data - 'A')].setLeft(&tree[(int)(left - 'A')]);
        else
            tree[(int)(data - 'A')].setLeft(NULL);
        if (right != '.')
            tree[(int)(data - 'A')].setRight(&tree[(int)(right - 'A')]);
        else
            tree[(int)(data - 'A')].setRight(NULL);
    }
    Tree* root = &tree[0];
    //cout << "전위 순회 : ";
    Tree::preorder(root);
    cout << endl;
    //cout << "중위 순회 : ";
    Tree::inorder(root);
    cout << endl;
    //cout << "후위 순회 : ";
    Tree::postorder(root);
    cout << endl;
}