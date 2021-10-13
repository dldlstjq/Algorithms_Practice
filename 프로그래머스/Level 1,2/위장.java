/*
삽질하다 못풀었다.
해시를 이용해서 옷의 종류와 이름을 분류하고 또 해당 옷을 입었는지 아닌지를 나타내는 맵을 하나 더 선언해서 조합을 이용했다.
일일이 조합을 다 구하니까 시간초과가 났다.

분명 무슨 공식이 있을 것 같았는데 몰라서 못풀었다.
찾아보니 간단하게 공식을 구할 수 있고
맵에서 value 값을 계속 증가시켜야할 때 getOrDefault라는 함수를 사용할 수 있다.
*/

import java.util.*;
class Solution {
    
   
    public int solution(String[][] clothes) {
        int answer = 1;
        HashMap<String, Integer> map = new HashMap<>();  

        for(int i=0; i<clothes.length; ++i){
            map.put(clothes[i][1], map.getOrDefault(clothes[i][1],0)+1);
        }
        /*
        상의의 수를 A 하의의 수를 B라고 하면 상의와 하의의 조합하는 경우의 수는 A * B
        상의만 선택하고 하의는 선택하지 않을 수도 있고, 하의만 선택하고 상의를 선택하지 않을 수도 있습니다. 
        때문에 (A+1)*(B+1)의 경우의 수가 나옵니다. 
        여기서 아무것도 입지 않는 수가 있을 수 있기 때문에 최종적으로 -1을 해주면 
        (A+1)*(B+1) - 1이라는 공식을 얻을 수가 있습니다.
        */
       
        for(String key : map.keySet()) { 
            answer *= (map.get(key)+1); 
        } 
        
        answer -=1;

        
        return answer;
    }
}