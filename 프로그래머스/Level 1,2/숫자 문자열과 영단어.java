/*
상반기때 풀었던게 기억났다.
그때도 0~9까지 모두 영어와 매칭시킨뒤에 하나씩 알파벳을 저장해 숫자와 비교하는 방식을 썼었다.
다른 사람 풀이를 보니 replaceAll()이라는 함수를 써서 영어로 저장된 것을 숫자로 바꾸는 방식을 써서 간단하게 해결했다.
String에 대해 아직 모르는 함수가 많은 것 같다.
*/

import java.util.*;

class Solution {
    public int solution(String s) {
        int answer = 0;
        
        HashMap<String, Integer> map =  new HashMap<>();
        map.put("zero", 0);map.put("one", 1);map.put("two", 2);
        map.put("three", 3);map.put("four", 4);map.put("five", 5);
        map.put("six", 6);map.put("seven", 7);map.put("eight", 8);
        map.put("nine", 9);
        
        String ret= "";
        String tmp = "";
        for(int i=0; i<s.length(); ++i){
            if('0'<=s.charAt(i) && s.charAt(i)<='9'){
                ret += Character.toString(s.charAt(i));
            }
               
            else{
                tmp += Character.toString(s.charAt(i));
                System.out.println(tmp);
                if(map.containsKey(tmp)){
                    ret += Character.toString(map.get(tmp)+'0');
                    tmp = "";
                }  
            }
            
        }
        System.out.println(ret);
        answer = Integer.parseInt(ret);
        return answer;
    }
}



// replaceAll() 사용
import java.util.*;

class Solution {
    public int solution(String s) {
        int answer = 0;
        StringBuilder sb = new StringBuilder("");
        int len = s.length();
        String[] digits = {"0","1","2","3","4","5","6","7","8","9"};
        String[] alphabets = {"zero","one","two","three","four","five","six","seven","eight","nine"};

        for(int i=0; i<10; i++){
            s = s.replaceAll(alphabets[i],digits[i]);
        }

        return Integer.parseInt(s);
    }
}