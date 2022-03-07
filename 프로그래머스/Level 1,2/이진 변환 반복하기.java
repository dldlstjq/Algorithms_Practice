/*
문제대로 수행하면 된다.
이진수로 바꾸는 것은 Integer.binary 함수가 따로 있는 것 같다.
*/

class Solution {
    public int[] solution(String s) {
        int[] answer = {};
        answer = new int[2];
        
        int change = 0;
        int zero = 0;
        
        while(true){
            String tmp = "";
            
            for(int i=0; i<s.length(); ++i){
                if(s.charAt(i) == '1')
                    tmp += s.charAt(i);
                else
                    zero++;
            }
            change++;
            
            if("1".equals(tmp)) break;
            
            int len = tmp.length();
            s = binaryFunc(len);
        }
        answer[0] = change;
        answer[1] = zero;
        return answer;
    }
    
    static String binaryFunc(int num){
        String str = "";
        while(num > 1){
            str += String.valueOf(num%2);
            num /= 2;
        }
        str += "1";
        str = new StringBuilder(str).reverse().toString();

        return str;
    }
}