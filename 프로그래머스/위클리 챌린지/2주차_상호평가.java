/*
네이버 상반기때 풀었던 문제인 것 같다.
아마 1번이었던 것 같은데 문제자체도 이해가 어렵지 않기 때문에 많이 걸려봤자 20분 이내로는 풀어야할 것 같다.
솔직히 10분 이내로 풀어야 하는 것 같다.
자기가 자신을 평가할 때 최대나 최소면 제외해야 하는데 다 더해준 다음에 scores[i][i]를 사용해 값을 가져오고 최대보다 크거나 최소보다 작으면 유일하므로 이렇게 계산하는게 더 간단한 것 같다.

프로그래머스는 디버깅이 불가능하기 때문에 중간중간 값을 출력해주자.
*/

//내 풀이
import java.util.*;
class Solution {
    public String solution(int[][] scores) {
        String answer = "";
        
        int len = scores.length;
        for(int i=0; i<len; ++i){
            int sum = 0;
            int score = 0;
            int max = Integer.MIN_VALUE;
            int min = Integer.MAX_VALUE;
           
            HashMap<Integer, Integer> map = new HashMap<>();
            
            int cnt = len;
            for(int j=0; j<len; ++j){
                if(j == i){
                    score = scores[j][i];
                }
                if(!map.containsKey(scores[j][i]))
                    map.put(scores[j][i], 1);
                else{
                    int tmp = map.get(scores[j][i]);
                    map.put(scores[j][i], tmp+1);
                }
                    
                max = Math.max(max, scores[j][i]);
                min = Math.min(min, scores[j][i]);
                sum += scores[j][i];
            }
            
            //System.out.println(max+" "+min);
            // 최대, 최소값이 score이고 유일하다면 합에서 제외
            if(max == score){
                if(map.get(score) == 1){
                    sum -= score;
                    cnt -= 1;
                }
                    
            }
            if(min == score){
                if(map.get(score) == 1){
                    sum -= score;
                    cnt -= 1;
                }
            }
            
            double avg = (double)sum/cnt;
            //System.out.println(avg);
            
            if(avg >= 90) answer += "A";
            else if(avg >= 80 && avg < 90) answer += "B";
            else if(avg >= 70 && avg < 80) answer += "C";
            else if(avg >= 50 && avg < 70) answer += "D";
            else answer += "F";
            
        }
        return answer;
    }
}



// 다른사람 풀이
class Solution {
    public String solution(int[][] scores) {
        StringBuilder builder = new StringBuilder();
        for(int i=0; i<scores.length; i++) {
            int max = 0;
            int min = 101;
            int sum = 0;
            int divide = scores.length;
            for(int j=0; j<scores.length; j++) {
                int score = scores[j][i];
                if(i != j) {
                    if(score < min) {
                        min = score;
                    }
                    if(score > max) {
                        max = score;
                    }
                }
                sum += score;
            }
            if(scores[i][i] < min || scores[i][i] > max) {
                sum -= scores[i][i];
                divide--;
            }
            double score = (double) sum / divide;
            builder.append(score >= 90 ? "A" : score >= 80 ? "B" : score >= 70 ? "C" : score >= 50 ? "D" : "F" );
        }
        return builder.toString();
    }
}