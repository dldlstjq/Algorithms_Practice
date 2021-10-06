/*
조건에 맞게 정렬 기준을 세우면 된다.
다만 승률을 구할 때 경기를 아무도 하지 않으면 0이 되는데 0으로 값을 나누는 에러가 발생하기 때문에 그걸 고려해 줘야 한다.
프로그래머스는 디버깅이 불가능하니 중간중간 프린트로 값이 잘 들어가는지 확인하자.
*/

import java.util.*;
class Solution {
    static class Boxer implements Comparable<Boxer>{
        double winRate; // 승률
        int cnt;    // 자기보다 무거운 복서 이긴 횟수
        int weight; // 자기 몸무게
        int num;    // 복서 번호

       Boxer (double winRate, int cnt, int weight, int num){
           this.winRate = winRate;
           this.cnt = cnt;
           this.weight = weight;
           this.num = num;
       }

        @Override
        public int compareTo(Boxer o){
            if(this.winRate == o.winRate){
                if(this.cnt == o.cnt){
                    if(this.weight == o.weight){
                        return Integer.compare(this.num, o.num);
                    }
                    return Integer.compare(o.weight, this.weight);
                }
                return Integer.compare(o.cnt, this.cnt);
            }
            return Double.compare(o.winRate, this.winRate);
        }
    }

    public int[] solution(int[] weights, String[] head2head) {
        int[] answer = {};


        int r = head2head.length;
        int c = head2head[0].length();
        answer = new int[r];
        char[][] fight = new char[r][c];

        for(int i=0; i<r; ++i)
            fight[i] = head2head[i].toCharArray();

        ArrayList<Boxer> list = new ArrayList<>();
        for(int i=0; i<r; ++i){
            int game = c; // 게임 수. 자기자신과 싸우는 것 제외
            int win = 0, winBigger = 0; // 이긴 수, 자기보다 몸무게가 많이 나가는 사람 이긴 수
            for(int j=0; j<c; ++j){
                if(fight[i][j] == 'W')   win++;
                if(fight[i][j] == 'W' && weights[i] < weights[j]) winBigger++;
                if(fight[i][j] == 'N') game--;  // 붙어본 적이 없으면 경기 수 감소
            }
            //System.out.println(game+" "+win+" "+winBigger);
            double rate = 0.0;
            if(game>0)
                rate = (double)win/game;
            //System.out.println(rate+" "+winBigger+" "+weights[i]+" "+(i+1));
            list.add(new Boxer(rate, winBigger, weights[i], i+1));
        }
        Collections.sort(list);
        for(int i=0; i<r; ++i)
            answer[i] = list.get(i).num;
        return answer;
    }
}



// 더 간단한 풀이. 익명 함수이용. 
// 익명함수는 아직 익숙하지 않아서 그냥 클래스 자체 정렬이 더 편하게 느껴진다.
import java.util.*;
class Solution {
    public int[] solution(int[] weights, String[] head2head) {
        int len = weights.length;
        int[][] rank = new int[len][4];
        for(int i = 0; i < len; i++) {
            int w = weights[i], cnt = 0, win = 0, over = 0;
            for(int j = 0; j < len; j++) {
                char c = head2head[i].charAt(j);
                cnt += c == 'N' ? 0 : 1;
                win += c == 'W' ? 1 : 0;
                over += c == 'W' && weights[i] < weights[j] ? 1 : 0;
            }
            rank[i][0] = i + 1;
            rank[i][1] = (int)((double)win / cnt * 10000000);
            rank[i][2] = over;
            rank[i][3] = weights[i];
        }
        Arrays.sort(rank, (a, b) -> {
            if(a[1] != b[1]) return b[1] - a[1];
            if(a[2] != b[2]) return b[2] - a[2];
            if(a[3] != b[3]) return b[3] - a[3];
            return a[0] - b[0];
        });
        int[] answer = new int[len];
        for(int i = 0; i < len; i++) answer[i] = (int)rank[i][0];
        return answer;
    }
}