/*
정석처럼 3진법으로 변환한뒤 일일이 계산했다.
다른 사람 풀이는 3진법을 10진법으로 바꾸는 것이 Integer.parseInt(3, 10)으로 가능했다.
왜 이렇게 되는지는 검색해보자.
그리고 int형 변수와 String형 변수도 +연산을 통해 합칠 수 있었다.
자바도 신기하게 되는게 있고 안되는게 있는데 결국엔 연습밖엔 답이 없는 것 같다.
*/

class Solution {
    
    String makeThree(int n){
        String str = "";
        
        while(n>0){
            str += Integer.toString(n%3);
            n/=3;
        }
        return str;
    }
    
    public int solution(int n) {
        int answer = 0;
        
        String tmp = makeThree(n);
        for(int i=0;i < tmp.length(); ++i){
            int num = tmp.charAt(i)-'0';
            int exp = tmp.length()-1-i;
            answer += (int)Math.pow(3, exp)*num;
        }
        return answer;
    }
}



/// 간단한 풀이
class Solution {
    public int solution(int n) {
        String a = "";

        while(n > 0){
            a = (n % 3) + a;
            n /= 3;
        }
        a = new StringBuilder(a).reverse().toString();


        return Integer.parseInt(a,3);
    }
}