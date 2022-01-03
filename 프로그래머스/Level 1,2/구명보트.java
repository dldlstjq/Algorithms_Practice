/*
2022년 새해 첫 문제 풀이다.
모처럼 그리디를 풀었는데 잘 안됐다.
가장 처음 든 생각은 오름차순 정렬 후 가장 무게가 덜 나가는 순서대로 넣는 것이었다.
하지만 보트에 탈 수 있는 인원은 최대 2명인것을 간과한 것, 무게가 적은 인원 순서는 최선의 방법이 아니었다.
오름차순 정렬 후 맨앞, 맨 뒤를 하나씩 넣어서 두명이 되면 둘 다 삭제, 아니면 맨 뒤에것만 삭제 하는 방식을 사용하면 효율성, 정확성을 모두 통과할 수 있다.
*/

import java.util.*;
class Solution {
   
    public int solution(int[] people, int limit) {
        
        Arrays.sort(people);    // 오름차순 정렬
        
        List<Integer> list = new ArrayList<>();
        
        for(int i=0; i<people.length; ++i)
            list.add(people[i]);
        
        // 꼭 사이즈 지정 필요
        ArrayDeque<Integer> dq = new ArrayDeque<>(50505);
        for(int x : list) dq.add(x);

        int answer = 0;
        // 덱이 비어있지 않을때 까지 반복
        while(!dq.isEmpty()) {
            // 맨 마지막 무게
            int weight = dq.pollLast();
            // 덱이 비어있지 않고 가장 처음무게를 추가했을 떄 limit 이하이면 맨 앞의 것 삭제
            if(!dq.isEmpty() && weight + dq.peekFirst() <= limit) { dq.pollFirst(); }
            answer++;   // 최대 2명이기 때문에 무조건 보트 추가
        }

       
        return answer;
    }
}