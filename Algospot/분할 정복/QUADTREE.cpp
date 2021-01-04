/*
분할 정복의 유명한 문제인 쿼드트리 풀이 방법이다.
압축된 결과를 보고 압축전으로 되돌린 후 거기서 다시 압축하는 방법이 있지만
애초에 압축 해제하지 않고 각 부분을 뒤집은 뒤 순서대로 다시 더해주면 쉽게 풀린다.

분할 정복에 재귀호출이 들어가서 이해하면 쉽지만 이해하지 못하면
코드 자체가 이해가 안되고 디버깅도 힘든만큼 문제를 작은 문제로 잘 잘라내야 한다.
*/

#include <iostream>
#include <string>

using namespace std;

const int MAX_SIZE = 1001;

//쿼드 트리 압축 해제하는 재귀호출 알고리즘
char decompressed[MAX_SIZE][MAX_SIZE];
void decompress(string::iterator& it, int y, int x, int size) {
    //한 글자를 검사할 때 마다 반복자를 한 칸 앞으로 옮긴다.
    char head = *(it++);
    //기저 사례: 첫 글자가 b 또는 w인 경ㅇ우
    if (head == 'b' || head == 'w') {
        for (int dy = 0; dy < size; ++dy)
            for (int dx = 0; dx < size; ++dx)
                decompressed[dy][dx] = head;
    }
    else {
        //네 부분을 각각 순서대로 압축 해제한다.
        int half = size / 2;
        decompress(it, y, x, half);
        decompress(it, y, x + half, half);
        decompress(it, y + half, x, half);
        decompress(it, y + half, x + half, half);
    }
}

string reverse(string::iterator& it) {
    char head = *it;
    ++it;
    if (head == 'b' || head == 'w')
        return string(1, head);
    string upperLeft = reverse(it);
    string upperRight = reverse(it);
    string lowerLeft = reverse(it);
    string lowerRight = reverse(it);
    //각각 위와 아래 조각들의 위치를 바꾼다.
    return string("x") + lowerLeft + lowerRight + upperLeft +
        upperRight;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        string picture;
        cin >> picture;
        if (picture.size() > 1000)
            exit(-1);

        string::iterator it = picture.begin();
        cout << reverse(it) << "\n";
    }
    return 0;
}