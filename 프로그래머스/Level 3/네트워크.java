/*
dfs, bfs를 이용해 연결된 그래프가 몇 개인지 찾으면 끝이다.
*/

import java.util.*;

class Solution {
    
    static boolean[] visited;
    public int solution(int n, int[][] computers) {
        int answer = 0;
        
        visited = new boolean[n];
        for(int i=0; i<n; ++i)
            if(!visited[i]){
                bfs(computers, i);
                answer++;
            }
                
        
        return answer;
    }
    
    static void bfs(int[][] arr, int num){
        visited[num] = true;
        Queue<Integer> q = new LinkedList<>();
        q.offer(num);
        
        while(!q.isEmpty()){
            int now = q.poll();
            for(int i=0; i<arr[now].length; ++i){
                if(now == i || visited[i]) continue;
                if(arr[now][i] == 0) continue;
                
                visited[i] = true;
                q.offer(i);
            }
        }
        
        
    }
}