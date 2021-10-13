/*
1번에서 출발해 다른 마을로 가는 거리가 K 이하인 마을을 모두 구하는 것이다.
가장먼저 생각난 것은 플로이드 와샬이었다.
다른 마을까지 거리를 전부 구해야 하는 줄 알았는데 1번에서 출발한 것만 구하면 됐다.
두번째로 다익스트라를 이용했다.
1번에서 출발해 다른 마을로 갈 수 있는 최소 거리를 구했다.

두 개 다 시도해보니 플로이드 와샬이 확실히 코드가 간단했다.
다익스트라도 알고나면 괜찮은데 잠깐 알고리즘 안 풀다가 다시 보면 어떻게 로직이 가는지 헷갈린다.

코테를 꾸준히 공부해서 언제 어디서 코테를 보더라도 풀 수 있도록 해야겠다.
*/

import java.util.*;
class Solution {
    
    class Node implements Comparable<Node>{
        int node, weight;
        Node(int node, int weight){
            this.node= node;
            this.weight=weight;
        }
        
        @Override
        public int compareTo(Node o){
            return Integer.compare(this.weight, o.weight);
        }
    }
    
    public int solution(int N, int[][] road, int K) {
        int answer = 0;
       
        // 다익스트라
        ArrayList<Node>list[] = new ArrayList[N+1];
        for(int i=0; i<=N; ++i)
            list[i] = new ArrayList<>();
        
        for(int i=0; i<road.length; ++i){
            int a = road[i][0];
            int b = road[i][1];
            int w = road[i][2];
            list[a].add(new Node(b,w));
            list[b].add(new Node(a,w));
        }
        
        for(int i=1; i<=N; ++i)
            Collections.sort(list[i]);
        
        int[] dist = new int[N+1];
        Arrays.fill(dist, Integer.MAX_VALUE);
        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.offer(new Node(1, 0));   // 1번에서 시작
        dist[1] = 0;
        
        while(!pq.isEmpty()){
            Node curr = pq.poll();
            
            if(dist[curr.node] < curr.weight) continue;
            
            for(int i=0; i<list[curr.node].size(); ++i) {
				int vertex = list[curr.node].get(i).node;
				int nextDist = list[curr.node].get(i).weight + curr.weight;
				// 더 짧은 경로를 발견하면 dist[]를 갱신하고 우선순위 큐에 넣는다.
				if(dist[vertex] > nextDist) {
					dist[vertex] = nextDist;
					pq.offer(new Node(vertex, nextDist));
				}
			}
        }
        
        for(int i=1; i<=N; ++i)
            if(dist[i] <= K)
                answer++;
        
        /*
        // 플로이드 와샬
         
        int[][] adj = new int[N+1][N+1];
        for(int i=0; i<=N; ++i){
            Arrays.fill(adj[i], 600000);
        }
        
        for(int i=0; i<road.length; ++i){
            int a = road[i][0];
            int b = road[i][1];
            int w = road[i][2];
            adj[a][b] = Math.min(adj[a][b], w);
            adj[b][a] = Math.min(adj[b][a], w);
            adj[a][a] = adj[b][b] = 0;
        }
        
        for(int k=1; k<=N; ++k)
            for(int i=1; i<=N; ++i)
                for(int j=1; j<=N; ++j)
                    adj[i][j] = Math.min(adj[i][j], adj[i][k] + adj[k][j]);
        
        for(int i=1; i<=N; ++i){
            if(adj[1][i] <= K)
                answer++;
        }
        */
        return answer;
    }
}