/*
처음에는 어떻게 풀어야했는데 자세히보니까 글자를 나누는 기준이 일정했다.
2글자면 계속 2글자로만 묶어야 하고 3글자면 3글자로만 묶어야 한다.
처음에 부분문자열을 가져와서 그 크기만큼 반복하는게 있는지 확인해서 길이를 비교한다.
2글자, 3글자, 4글자 이런식으로는 묶지 못하는 것을 알면 쉽게 풀린다.
*/

class Solution {
    public int solution(String s) {
        int answer = Integer.MAX_VALUE;

        String str="";

        for(int i=1; i<=s.length(); ++i){
            // 1개부터 전체 길이까지 부분 문자열
            String tmp = s.substring(0, i);

            int cnt = 1;    // 압축 개수
            for(int j=i; j<s.length(); j+=i){
                String tmp2 = "";
                // tmp이후부터 i개 만큼 부분 문자열 생성
                if(j+i < s.length()) tmp2 = s.substring(j, j+i);
                else tmp2 = s.substring(j, s.length());
                // 같으면 카운트. 다르면 붙이고 tmp 갱신
                if(tmp.equals(tmp2)){
                    cnt++;
                }
                else{
                    if(cnt == 1) str += tmp;
                    else str += cnt+tmp;
                    tmp = tmp2;
                    cnt = 1;
                }
            }
            // 제일 마지막 문자 붙여서 길이 갱신
            if(cnt == 1) str += tmp;
            else str += cnt+tmp;

            answer = Math.min(answer, str.length());
            str="";
        }

        return answer;
    }
}