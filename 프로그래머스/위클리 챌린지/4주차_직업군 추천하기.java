/*
복잡해보여도 하나씩 뜯어보면 그렇게 어렵지 않다.
그래서 최소 10분 내로는 풀 수 있는 그런 문제인데 헷갈려서 더 시간이 걸리고 말았다.
1. 직업군에 따라 점수를 구해야 하는데 언어에 따라 점수를 구한 것
2. 직업군 선호 언어를 찾을 때 binarySearch를 사용했는데 정렬된 것이 아니기 때문에 직접 구해야 했다.

크게는 이 두가지 때문에 시간이 제법 걸렸다.
이런 문제들은 문제를 잘 읽고 실수없이 한 방에 풀어야 시간을 많이 확보할 수 있다.
*/

import java.util.*;
class Solution {
    class Work implements Comparable<Work>{
        String work;
        int score;
        Work (String work, int score){
            this.work = work;
            this.score= score;
        }
        @Override
        public int compareTo(Work o){
            if(this. score == o.score)
                 return this.work.compareTo(o.work);
            return Integer.compare(o.score, this.score);
        }
    }
    public String solution(String[] table, String[] languages, int[] preference) {
        String answer = "";

        String[][] company = new String[5][6];
        for(int i=0; i<table.length; ++i){
            company[i] = table[i].split(" ");
        }

        ArrayList<Work> list = new ArrayList<>();

        for(int i=0; i<company.length; ++i){
            int sum = 0;
             String lang = null;
            for(int j=0; j<languages.length; ++j){
                lang = languages[j];
                int idx = getPoint(company[i], lang);   // 인덱스 반환
                //  선호 언어가 있을때만 계산
                // 언어 선호도 x 직업군 언어 점수
                if(idx >= 0) {
                    sum += preference[j]*(5-idx+1);
                }
            }

            list.add(new Work(company[i][0], sum));
        }

        Collections.sort(list);
        answer = list.get(0).work;
        return answer;
    }

    private static int getPoint(String[] company, String lang){
        for(int i=0; i<company.length; ++i){
            if(company[i].equals(lang))
                return i;
        }
        return -1;
    }
}