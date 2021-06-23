/*
해시라는 말을 보고 map을 사용했다.
완주한 선수를 모두 map에 넣은 후 참가자 배열만큼 돌면서 참가자가 map에 없거나 map 값이 0이 아닌 경우 완주하지 못한 선수이다.

다른 사람 풀이를 보니 정렬로도 쉽게 풀이가 가능했다.
두 배열을 모두 정렬한 후 인덱스끼리 일치하지 않으면 그 인덱스 값이 정답이고
제일 마지막 사람이 완주하지 못했을 수 있으므로 마지막에 제일 마지막 참가자를 리턴한다.

다만 시간은 해시를 썼을 때가 좀 더 빠르다고 한다.
정렬은 O(k * nlogn), 해쉬는 O(k*n)입니다 (k는 문자열의 길이, n은 participant 원소 갯수)

해시를 이용한 또 다른 풀이로는 참가자를 모두 map에 넣고 완주자에 있는 사람을 하나씩 삭제한다.
그러면 한명만 map에 남기 때문에 이렇게도 풀이가 가능.
*/

// 내 풀이
#include <string>
#include <vector>
#include <map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";

    map<string, int> mp;

    // 완주한 선수를 map에 저장
    for (int i = 0; i < completion.size(); ++i) {
        mp[completion[i]]++;
    }

    // 참가자배열을 돌면서 map에 없으면 완주하지 못한 사람.
    bool flag = false;
    for (int i = 0; i < participant.size(); ++i) {
        if (!mp.count(participant[i])) {
            answer = participant[i];
            flag = true;
            break;
        }
        else {
            mp[participant[i]]--;
        }

    }

    // flag= false이면 동명이인이 있는 경우
    // map값이 0이 아니면 완주하지 못한 사람
    if (!flag) {
        for (int i = 0; i < participant.size(); ++i) {
            if (mp[participant[i]]) {
                answer = participant[i];
                break;
            }
        }
    }


    return answer;
}


// 또 다른 해시 풀이
// 아마 이게 정석적인 풀이인듯.
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    unordered_map<string, int> strMap;
    for (auto elem : completion)
    {
        if (strMap.end() == strMap.find(elem))
            strMap.insert(make_pair(elem, 1));
        else
            strMap[elem]++;
    }

    for (auto elem : participant)
    {
        if (strMap.end() == strMap.find(elem))
        {
            answer = elem;
            break;
        }
        else
        {
            strMap[elem]--;
            if (strMap[elem] < 0)
            {
                answer = elem;
                break;
            }
        }
    }
    return answer;
}

// 삭제하는 풀이
string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    unordered_multiset<string> names;

    for (int i = 0; i < participant.size(); i++)
    {
        names.insert(participant[i]);
    }

    for (int i = 0; i < completion.size(); i++)
    {
        unordered_multiset<string>::iterator itr = names.find(completion[i]);
        names.erase(itr);
    }

    return *names.begin();
}


// 정렬을 이용한 풀이
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());
    for (int i = 0; i < completion.size(); i++)
    {
        if (participant[i] != completion[i])
            return participant[i];
    }
    return participant[participant.size() - 1];
    //return answer;
}