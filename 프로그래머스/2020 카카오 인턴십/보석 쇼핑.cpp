/*
정확성과 효율성을 따진다는 설명을 보며 알고리즘 선택이 중요하다고 생각했다.
2중 for문을 돌리면 무조건 시간초과가 날 것이었고 좋은 방법이 없을까 생각하다 투포인터 알고리즘이 생각났다.
최근 네이버나 카카오에서 많이 나오는 알고리즘이었는데 이 방법을 쓰면 O(n)만에 전체 배열을 검사할 수 있었다.

다만 이걸 실제로 적용하는데서 많이 헤맸는데 map을 이용하는 것 까지는 좋았으나 보석이 다 들어왔는지 확인하는것,
lo, hi 인덱스 조정하는 것에서 많이 헷갈려서 해결하지 못했다.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer;

    int as = 1, ae = 100001;
    int total = 0;
    map<string, int> jewel, check;
    vector<string> name;
    //보석의 종류를 name에 저장
    for (int i = 0; i < gems.size(); ++i) {
        if (!check[gems[i]]) {
            check[gems[i]] = 1;
            jewel[gems[i]] = 0;
            total++;
        }
    }

    jewel[gems[0]] = 1;

    //투포인터 알고리즘. 보석의 종류를 확인한다.
    int lo = 0, hi = 0, cnt = 1;
    while (1) {

        if (cnt < total)
        {
            hi++;
            if (hi == gems.size())
                break;
            if (jewel[gems[hi]] == 0)
                cnt++;
            jewel[gems[hi]] += 1;
        }

        //모든 보석이 있다
        else if (cnt == total) {
            if (ae - as > hi - lo) {
                ae = hi + 1;
                as = lo + 1;
            }
            if (jewel[gems[lo]] == 1)
                cnt--;
            jewel[gems[lo]] -= 1;
            lo++;
        }

    }
    //이 풀이도 가능
    /*  while(lo <= hi){

         if (cnt < total && flag)
          {
              hi++;
              if (jewel[gems[hi]] == 0)
                  cnt++;
              jewel[gems[hi]] += 1;
          }

          //모든 보석이 있다
          else if(cnt == total){
              if(ae-as>hi-lo){
                  ae=hi+1;
                  as=lo+1;
              }
              if(jewel[gems[lo]] == 1)
                  cnt--;
              jewel[gems[lo]] -= 1;
              lo++;
          }
          else
              break;
          if(hi == gems.size() - 1)
              flag = false; // end가 더이상 증가 못하게 막음

      }*/
    answer.push_back(as);
    answer.push_back(ae);

    return answer;
}