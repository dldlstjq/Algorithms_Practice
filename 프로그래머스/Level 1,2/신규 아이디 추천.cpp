/*
작년 처음 카카오 코테를 볼 때 풀었던 문제이다.
그 때는 코테 준비가 전혀 되어있지 않아 이게 가장 쉬운 문제였는데더 2~3시간씩 걸려서 푼 기억이 있다.

지금 풀어보니 조건에 맞게 하나씩 하면 되는데 주의해야 할 게 있다.

1. 2, 3단계에서 erase 연산 시 문자 하나가 삭제되면 인덱스 값을 재조정 해줘야 한다.
그냥 넘어가면 인덱스가 지워야할 문자를 가리키지 않고 그 다음 문자를 가리켜서 지워지지 않는 일이 일어난다.

2. 4단계에서 맨 처음, 끝의 .을 삭제할 때 둘 다 if문을 사용해야 한다.
맨 처음과 끝에 .이 있는데 if, elseif 를 쓰면 한쪽만 삭제되고 다른 한쪽은 남아있게 된다.

이 두가지만 주의하면 string 내장함수를 잘 사용해서 구현하면 된다.
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string new_id) {
    string answer = "";

    // 1단계. 대문자를 소문자로
    for (int i = 0; i < new_id.length(); ++i) {
        if (new_id[i] >= 'A' && new_id[i] <= 'Z')
            new_id[i] = tolower(new_id[i]);
    }

    // 2단계. 알파벳 소문자, 숫자, 빼기(-), 밑줄(_), 마침표(.)를 제외한 모든 문자를 제거
    for (int i = 0; i < new_id.length(); ++i) {
        if ((new_id[i] >= 'a' && new_id[i] <= 'z') ||
            (new_id[i] >= '0' && new_id[i] <= '9') ||
            new_id[i] == '-' || new_id[i] == '_' || new_id[i] == '.')
            continue;

        new_id.erase(new_id.begin() + i);
        i--;
    }

    // 3단계. 마침표 2번 이상이면 하나의 마침표로 치환
    for (int i = 0; i < new_id.length(); ++i) {
        if (new_id[i] == '.' && new_id[i + 1] == '.') {
            new_id.erase(new_id.begin() + i);
            i--;
        }
    }


    // 4단계. new_id에서 마침표(.)가 처음이나 끝에 위치한다면 제거
    if (new_id.front() == '.')
        new_id.erase(new_id.begin());
    if (new_id.back() == '.')
        new_id.pop_back();


    // 5단계. new_id가 빈 문자열이라면, new_id에 "a"를 대입
    if (new_id.empty())
        new_id = "a";


    // 6단계. new_id의 길이가 16자 이상이면, new_id의 첫 15개의 문자를 제외한 나머지 문자들을 모두 제거.
    // 만약 제거 후 마침표(.)가 new_id의 끝에 위치한다면 끝에 위치한 마침표(.) 문자를 제거합니다.
    if (new_id.length() >= 16) {
        new_id.erase(15);
        if (new_id.back() == '.')
            new_id.pop_back();
    }


    // 7단계. new_id의 길이가 2자 이하라면, new_id의 마지막 문자를 new_id의 길이가 3이 될 때까지 반복해서 끝에 붙입니다.
    if (new_id.length() <= 2) {
        while (new_id.length() < 3) {
            new_id += new_id.back();
        }
    }

    answer = new_id;
    return answer;
}