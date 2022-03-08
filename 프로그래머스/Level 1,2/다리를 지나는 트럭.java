/*
두 개의 큐를 이용했다.
첫번째 큐는 트럭 정보 저장, 두번쨰 큐는 다리 정보 저장 큐이다.
Truck 클래스를 선언해 트럭의 무게와 시간을 저장한다.

첫번쨰 트럭은 바로 다리에 올린다.
그 다음 다리 큐에 든 트럭의 시간을 증가 시켜 다리 통과 유무에 따라 다시 다리 큐에 넣는다.

그 다음, 트럭 큐의 맨 앞을 확인해서 다리에 올릴 수 있으면 올리고 아니면 올리지 않는다.

트럭 큐의 경우 마지막 트럭이 다리에 올라간 후에는 비어있기 때문에 트럭 큐가 비어있는지 조건을 확인해야 한다.
*/

import java.util.*;

class Solution {
    static class Truck{
        int w; int len;
        Truck(int w, int len){
            this.w=w;
            this.len=len;
        }   
    }

    public int solution(int bridge_length, int weight, int[] truck_weights) {
        int answer = 1;

        int bridgeWeight = 0;
        Queue<Truck> truck = new LinkedList<>();
        for(Integer tmp: truck_weights)
            truck.offer(new Truck(tmp, 0));

        Queue<Truck> q = new LinkedList<>();
        // 첫 트럭
        Truck first = truck.poll();
        q.offer(new Truck(first.w, 1));
        bridgeWeight += first.w;   // 다리 무게 추가

        while(true){

            int size = q.size();
            for(int i=0; i<size; ++i){
                Truck t = q.poll();
                t.len++;    // 1초 증가

                // 다리 길이보다 작으면 q에 저장
                if(t.len <= bridge_length) q.offer(new Truck(t.w, t.len));

                // 다리를 다 넘었으면 다리 무게에서 빼줌
                else bridgeWeight-=t.w; 
            }

            // 한 대 올라갔을 때 다리 무게 버틸 수 있으면 간다
            if(!truck.isEmpty() && weight >= bridgeWeight+truck.peek().w){
                int w = truck.poll().w;
                bridgeWeight += w;   // 다리 무게 추가
                q.offer(new Truck(w, 1));
            }

            answer++;

            if(truck.isEmpty() && q.isEmpty()) break;
        }


        return answer;
    }
}