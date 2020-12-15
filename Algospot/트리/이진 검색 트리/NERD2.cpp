/*
2차원 평면에다 그림으로 그려보면 쉽게 이해가 가능하다.
새로운 좌표가 추가될 때마다 기존 영역에 지배여부를 확인한다.
map이라는 stl함수가 이진탐색이라는 것을 알았다.
코드자체는 그렇게 이해하기 어렵진 않았다.
*/

#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

//현재 다른 점에 지배당하지 않는 점들의 목록을 저장한다.
//coords[x]=y
map<int, int> coords;

//새로운 점 (x,y)가 기존의 다른 점들에 지배당하는지 확인한다.
bool isDominated(int x, int y) {
    //x보다 오른쪽에 있는 점 중 가장 왼쪽에 있는 점을 찾는다.
    //lower_bound는 자기자신 포함
    map<int, int>::iterator it = coords.lower_bound(x);
    //그런 점이 없으면 (x,y)는 지배당하지 않는다.
    if (it == coords.end())
        return false;
    // 해당 점(x, y)에서 바로 오른쪽에 있는 좌표가 존재하면서
    // y 위치까지 작으면 지배받습니다.
    if (y < it->second) return true;
    else return false;
}

//새로운 점 (x,y)에 지배당하는 점들을 트리에서 지운다.
void removeDominated(int x, int y) {
    map<int, int>::iterator it = coords.lower_bound(x);
    //(x,y)보다 왼쪽에 있는 점이 없다!
    if (it == coords.begin())
        return;
    --it;
    //반복문 불변식: it는 (x,y)의 바로 왼쪽에 있는 점
    while (true) {
        //(x,y) 바로 왼쪽에 오는 점을 찾는다.
        //it가 표시하는 점이 (x,y)에 지배되지 않는다면 곧장 종료
        if (it->second > y)
            break;
        //이전 점이 더 없으므로 it만 지우고 종료한다.
        if (it == coords.begin()) {
            coords.erase(it);
            break;
        }
        //이전 점으로 이터레이터를 하나 옮겨 놓고 it를 지운다.
        else {
            map<int, int>::iterator jt = it;
            --jt;
            coords.erase(it);
            it = jt;
        }
    }
}

//새 점 (x,y)가 추가되었을 떄 coords를 갱신하고,
//다른 점에 지배당하지 않는 점들의 개수를 반환한다.
int registered(int x, int y) {
    //(x,y)가 이미 지배당하는 경우에는 그냥 (x,y)를 버린다.
    if (isDominated(x, y))
        return coords.size();
    //기존에 있던 점 중 (x,y)에 지배당하는 점들을 지운다.
    removeDominated(x, y);
    coords[x] = y;
    return coords.size();
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int N;
        cin >> N;
        int result = 0;
        for (int i = 0; i < N; ++i) {
            int p, q;
            cin >> p >> q;
            result += registered(p, q);
        }

        cout << result << "\n";
        coords.clear();
    }

    return 0;
}