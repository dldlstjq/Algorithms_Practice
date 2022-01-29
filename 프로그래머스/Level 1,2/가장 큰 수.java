/*
자릿수를 하나하나 비교하는 건 아닌 것 같아 문자열로 치환 후 정렬하니 가장 숫자가 큰 것부터 정렬이 되었다.
문제는 34 30 3 순서로 정렬된 것을 어떻게 해야 가장 큰 숫자로 조합하느냐였는데 자릿수 비교는 아무리 생각해도 좋은 방법이 생각나지 않았다.
검색해본 결과 comparator를 사용해서 자체적으로 정렬 기준을 만들어 줘야 했다.
comparator 사용을 잘 알고 있어야 할 것 같다.
*/

import java.util.*;

class Solution {
    public String solution(int[] numbers) {
        String answer = "";
        
        List<String> list = new ArrayList<>();
        
        for(int i=0; i<numbers.length; ++i)
            list.add(String.valueOf(numbers[i]));
        
        
        Collections.sort(list, (a, b) -> (b + a).compareTo(a + b));
        if(list.get(0).charAt(0) == '0') return "0";
        for(String str: list)
            answer += str;
        
        /*
         //내림차순 정렬
        Arrays.sort(str, new Comparator<String>() {
            @Override
            public int compare(String a, String b) {
                return (b+a).compareTo(a+b);
                //오름차순 정렬 (o1+o2).compareTo(o1+o2);
            }
        });
        */

        
        return answer;
    }
}