/*
교집합, 합집합을 제대로 구하지 못해 오랜 시간이 걸리고 못풀었다.
대, 소문자 구분을 하지 않기 때문에 처음부터 문자열을 대,소문자로 바꾸면 되는데 특수문자가 있으면 에러가 날 것 같아 그러질 못했다.
그러다 보니 2개씩 나눌 때 대문자, 소문자를 모두 검사해서 코드가 많이 복잡해졌다.

합집합, 교집합 구하는 것이 가장 어려웠는데 의외로 간단하게 생각하면 쉬웠다.
하나의 리스트에서 원소 하나씩 빼내면서 다른 리스트에 있다면 교집합에 넣고 다른 리스트에서 그 원소를 삭제하면 됐다.
합집합은 어차피 모두 넣어야 하고, 있을 때 하나씩 삭제하고 남은 원소를 전부 합집합 리스트에 넣으면 쉽게 구현이 됐다.
방법을 알면 쉽지만 모르면 되게 어려운 것 같다.
*/

import java.util.*;

class Solution {
    
    public int solution(String str1, String str2) {
        int answer = 1;
        
        str1 = str1.toLowerCase();
        str2 = str2.toLowerCase();
        
        List<String> list1 = new ArrayList<String>();
        List<String> list2 = new ArrayList<String>();
        List<String> union = new ArrayList<>();
        List<String> intersection = new ArrayList<>();
        
        for(int i=0; i<str1.length()-1; ++i){
            char first = str1.charAt(i);
            char second = str1.charAt(i+1);
            if(('a'<= first && first <= 'z')&& ('a'<= second && second <= 'z') ){
                list1.add(first+""+second);
            }
        }
        
        for(int i=0; i<str2.length()-1; ++i){
            char first = str2.charAt(i);
            char second = str2.charAt(i+1);
            if(('a'<= first && first <= 'z')&& ('a'<= second && second <= 'z') ){
                list2.add(first+""+second);
            }
        }
        
        if(list1.isEmpty() && list2.isEmpty())
           return answer*65536;
        
        // 중복 처리를 위해 정렬
        Collections.sort(list1);
        Collections.sort(list2);
        
        
        for(String str: list1){
            // list2에 같은 원소가 있으며 교집합에 추가
            if(list2.remove(str))
                intersection.add(str);
            union.add(str);
        }
        
        // list2에 남은 원소 전부 추가
        for(String str: list2){
            union.add(str);
        }

        double jacard = (double)intersection.size()/union.size()*65536;
        System.out.println((int)Math.floor(jacard));
        answer = (int)Math.floor(jacard);
      
        
        return answer;
    }
}