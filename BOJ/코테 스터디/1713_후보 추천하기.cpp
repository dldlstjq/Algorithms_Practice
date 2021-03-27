/*
처음에는 사진틀, 추천수, 시간 세개의 배열을 가지고 시작했다.
조건에 맞게 한 줄 알았는데 틀려서 사진, 시간을 pair로 하는 벡터를 설정해서 다시 풀었다.
출력할때 모든 사진틀에 후보가 있는 것이 아니기 때문에 있는 후보만 출력한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 100 + 1;
int n, m;
int recommend[MAX];
vector<pair<int, int>> picture;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    //{시간, 사진}순으로 저장
    picture.resize(n, { 0,0 });

    for (int i = 0; i < m; ++i) {
        int cand;
        cin >> cand;

        bool replace = true;

        for (int j = 0; j < n; ++j) {
            //사진틀이 비어있으면 넣는다
            if (picture[j].second == 0) {
                picture[j].first = i;   //i가 작을수록 시간이 오래 됐다
                picture[j].second = cand;
                recommend[cand]++;
                replace = false;
                break;
            }

            //후보가 이미 있으면
            else if (picture[j].second == cand) {
                recommend[cand]++;
                replace = false;
                break;
            }
        }
        //사진을 바꿔야 하는 경우
        if (replace) {

            int idx = 0;
            for (int j = 1; j < n; ++j) {
                //추천 횟수가 가장 적은 학생 삭제
                if (recommend[picture[idx].second] > recommend[picture[j].second]) {
                    idx = j;
                }

                //같다면 오랜 시간 순으로 삭제
                else if (recommend[picture[idx].second] == recommend[picture[j].second]) {
                    if (picture[idx].first > picture[j].first)
                        idx = j;
                }
            }

            recommend[picture[idx].second] = 0; //추천수 초기화
            //새로 넣은 후보
            picture[idx].first = i;
            picture[idx].second = cand;
            recommend[cand]++;

        }
    }

    vector<int> ans;
    for (int i = 0; i < n; ++i)
        ans.push_back(picture[i].second);

    sort(ans.begin(), ans.end());
    //후보가 있는 것만 출력
    for (int i = 0; i < ans.size(); ++i)
        if (ans[i] != 0)
            cout << ans[i] << " ";

    return 0;
}


/*
9%에서 틀린다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 987654321;
int picture[21];    //사진 틀
int recommend[101]; //추천받은 횟수
int time[101];  //얼마나 오래 있었는가
int n, m;

//사진틀이 얼마나 오래있었는지 체크
void time_count() {
    for (int i = 0; i < n; ++i)
        if (picture[i] != 0)
            time[picture[i]]++;
}

void solve(int cand) {
    bool is_in = false;  //사진틀에 후보를 넣었는지 여부
    for (int i = 0; i < n; ++i) {
        //이미 후보에 있으면 추천수 증가
        if (picture[i] == cand) {
            recommend[cand]++;
            //time[cand]++;
            is_in = true;
            break;
        }

        //사진이 없으면 사진틀에 학생을 넣고 추천수 증가
        else if (picture[i] == 0) {
            picture[i] = cand;
            recommend[cand]++;
            //time[cand]++;
            is_in = true;
            break;
        }
    }

    //사진틀이 꽉 찬 경우
    if (!is_in) {
        int min_vote = INF;
        int max_time = 0;
        int idx = 0;
        //투표 횟수가 가장 작은 후보를 구한다.
        for (int i = 0; i < n; ++i) {
            int vote = recommend[picture[i]];
            int long_time = time[picture[i]];
            //투표횟수가 작은 후보가 있으면 갱신
            if (min_vote > vote) {
                min_vote = vote;
                max_time = long_time;
                idx = i;
            }
            //만약 투표수가 같은 후보가 있으면 시간 비교
            else if (min_vote == vote) {
                if (max_time < long_time) {
                    max_time = long_time;
                    idx = i;
                }
            }

        }

        //기존 후보의 추천수, 시간 리셋
        recommend[picture[idx]] = 0;
        time[picture[idx]] = 0;
        //새로운 후보로 등록하고 추천수, 시간 증가
        picture[idx] = cand;
        recommend[cand]++;
        time[cand]++;
    }
    else
        time_count();

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int tmp;
        cin >> tmp;
        solve(tmp);
    }

    sort(picture, picture + n);
    //0이 아니면 출력
    for (int i = 0; i < n; ++i)
        if (picture[i] != 0)
            cout << picture[i] << " ";

    return 0;
}