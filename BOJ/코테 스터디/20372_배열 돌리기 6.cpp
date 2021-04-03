#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 128;
int N, R;  //배열 연산 횟수
int A[MAX][MAX];
int tmp[MAX][MAX];  //A배열 복사본

int k, l;

void copy() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            tmp[i][j] = A[i][j];
}

void one(int y, int x) {



    int k = (int)pow(2, l);
    int n = N / k;
    int m = N / k;

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            one(y + i * n, x + j * m);
        }
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> R;
    N = (int)pow(2, N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> A[i][j];


    for (int i = 0; i < R; ++i) {
        //A배열을 tmp에 복사
        copy();

        cin >> k >> l;

        //1번연산: 부분배열 상하 반전
        if (k == 1) {

        }
        //2번연산: 부분배열 좌우 반전

        //3번연산: 부분배열 오른쪽 90도 회전

        //4번연산: 부분배열 왼쪽 90도 회전

        //5번연산: 부분배열 한칸으로 생각. 상하 반전

        //6번연산: 부분배열 한칸으로 생각. 좌우 반전

        //7번연산: 부분배열 한칸으로 생각. 오른쪽 90도 회전

        //8번연산: 부분배열 한칸으로 생각. 왼쪽 90도 회전


    }



    return 0;
}