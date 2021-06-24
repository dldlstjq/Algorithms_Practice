/*
문제를 봤을때 조금 까다로워 보였지만 직접 해보니 풀만한 문제였다.

1. 문자열을 파싱해서 명령어, 아이디, 닉네임을 따로 분리한다.2
2. Enter, change일 때 아이디와 닉네임을 map으로 매칭한다.
3. Enter와 leave, id를 따로 저장해놓고 그 순서대로 나갔습니다. 들어왔습니다를 닉네임에 따라 출력한다.

문자열을 파싱할 줄 알고 map을 사용해 아이디와 닉네임을 매칭시킬줄 알면 풀 수 있는 문제인 것 같다.
*/

#include <string>
#include <vector>
#include <map>
using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;

    vector<string> in_out;  // 채팅방 입, 퇴장 저장
    vector<string> id;      // 유저의 id 저장

    map<string, string> mp; // id와 닉네임 매칭

    // record 파싱
    for (int i = 0; i < record.size(); ++i) {
        string s = record[i];
        vector<string> order;   //파싱한 string 저장
        string tmp = "";

        for (int j = 0; j < s.length(); ++j) {
            if (s[j] != ' ')
                tmp += s[j];
            else {
                order.push_back(tmp);
                tmp = "";
            }
        }
        order.push_back(tmp);   //제일 마지막 문자열 넣어줌

        // enter, leave일 경우만 채팅방 메시지가 출력. 명령과 id를 따로 저장
        if (order[0] == "Enter" || order[0] == "Leave") {
            in_out.push_back(order[0]); // order[0]에는 입,퇴장, 변경여부가 저장
            id.push_back(order[1]);     // order[1]에는 유저 아이디가 저장
        }

        // enter, change일 때만 유저 아이디를 닉네임과 매칭
        if (order[0] == "Enter" || order[0] == "Change") {
            mp[order[1]] = order[2];   //map에 id와 이름을 저장
        }
    }

    // in_out에 들어있는 명령과 그에 따른 id값과 매칭되는 닉네임을 answer에 저장
    for (int i = 0; i < in_out.size(); ++i) {
        string name = mp[id[i]];
        if (in_out[i] == "Enter")
            answer.push_back(name + "님이 들어왔습니다.");

        else
            answer.push_back(name + "님이 나갔습니다.");
    }

    return answer;
}



// 다른 사람 풀이. stringstream을 사용했다. 이것도 알아두면 좋을 것 같다.
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;


vector<string> solution(vector<string> record) {
    vector<string> answer;
    string command;
    string ID;
    string uid;
    map<string, string> m;


    for (string input : record)
    {
        stringstream ss(input);
        ss >> command;
        ss >> uid;
        if (command == "Enter" || command == "Change")
        {
            ss >> ID;
            m[uid] = ID;
        }
    }

    for (string input : record)
    {
        stringstream ss(input);
        ss >> command;
        ss >> uid;
        if (command == "Enter")
        {
            ID = (m.find(uid)->second);

            string temp = ID + "님이 들어왔습니다.";
            answer.push_back(temp);

        }
        else if (command == "Leave")
        {
            ID = (m.find(uid)->second);
            string temp = ID + "님이 나갔습니다.";
            answer.push_back(temp);
        }
    }
    return answer;
}