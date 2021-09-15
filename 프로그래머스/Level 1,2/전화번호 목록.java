/*
해시라고 분류되어 있는데 어떻게 적용해야 할지 몰랐다.
그냥 2차원 for문으로 하나씩 돌면서 비교하면 효율성에서 틀렸다.
풀이를 보니 모든 전화번호를 해시맵에 저장하고 각 전화번호에서 마지막 번호만을 제외한 접두사들을 해시맵에서 탐색하며
있는지 없는지 확인하면 됐다.

IDE에 많이 익숙해져 있어 해시맵 함수를 잘 모르는것, 며칠 코테를 공부 안해서 많이 잊어먹은 것이 잘 안풀리는 이유인 것 같다.

하루라도 코테공부를 안하면 어떻게 풀어야 하는지 머리가 다 굳는 것 같다.
못해도 한문제라도 꾸준히 계속 풀어야겠다. 
*/

import java.util.*;

class Solution {
    public boolean solution(String[] phone_book) {
        boolean answer = true;
      
        HashMap<String, Integer> map = new HashMap<>();
        
        for(int i=0; i<phone_book.length; ++i)
            map.put(phone_book[i], i);
        
        for(int i=0; i<phone_book.length; ++i){
            for(int j= 1; j<phone_book[i].length(); ++j){
                // 0~j-1 길이까지 잘라서 접두사 비교
               if(map.containsKey(phone_book[i].substring(0, j)))
                   return false;
            }
        }
        return answer;
    }
}