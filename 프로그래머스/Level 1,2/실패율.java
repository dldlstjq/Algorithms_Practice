/*
문제 이해는 어렵지 않았다.
다만 실패율을 구하는 과정에서 double이나 float를 붙여서 타입캐스팅을 해야 소수점까지 값이 잘 나오고 올림을 통해 맞는 값을 구할 수 있었다.
하반기 카카오코테에서도 비율을 구할 때가 있었는데 유의해야겠다.
*/
import java.util.*;

class Solution {
    
    // 실패율이 높은 스테이지부터 내림차순, 같으면 작은 번호 먼저 오도록
    class Rate implements Comparable<Rate>{
        double failRate;
        int num;
        
        public Rate(double failRate, int num){
            this.failRate = failRate;
            this.num = num;
        }
        
        @Override
        public int compareTo(Rate o){
            if(this.failRate == o.failRate)
                return this.num-o.num;
            return Double.compare(o.failRate, this.failRate);
            //return (int)o.failRate-this.failRate;
        }
    }
    
    public int[] solution(int N, int[] stages) {
        int[] answer = {};
        answer = new int[N];
        boolean[] isFin = new boolean[stages.length];
        
        ArrayList<Rate> list= new ArrayList<>();
        
        for(int stage=1; stage<=N; ++stage){
            int cnt = 0;
            int user = 0;    // 스테이지에 참가한 사용자
             for(int i=0; i<stages.length; ++i){
                 if(!isFin[i])
                     user++;
                 // 실패한 유저 카운트
                 if(stages[i] < stage+1 && !isFin[i]){
                     cnt++;
                     isFin[i] = true;
                 }
                     
             }
            System.out.printf("%d %d %d\n", cnt, user, stage);
            // 스테이지에 도달한 사람이 있으면 실패 확률을 구하고 없으면 0
             if(user != 0)
            	list.add(new Rate((double)cnt/user, stage));
            else
            	list.add(new Rate(0, stage));
        }
       Collections.sort(list);
        
        for(int i=0; i<N; ++i){
            answer[i] = list.get(i).num;
        }
        
        return answer;
    }
}