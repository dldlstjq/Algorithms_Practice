/*
처음에는 문제 이해를 못했다가 이해하고 나니 쉬운 문제였다.
상화좌우로 연결된 숫자가 다 같으면 한 영역으로 친다.
dfs, bfs 둘 중 하나를 써서 구현하면 된다.
bfs를 쓸 때 좌표 클래스에서 this.r=r을 해야 하는데 반대로 해서 값이 잘 안들어갔다.
너무 오랜만에 하니까 잊어먹는 것도 많은데 자주 문제를 풀면서 빨리 감을 찾아야 한다.
*/

import java.util.*;
class Solution {
    static class Pos{
        int r; int c;
        Pos(int r, int c){
            this.r=r;
            this.c=c;
        }
    }
    
    static int dr[] = {-1,0,1,0};
    static int dc[] = {0,1,0,-1};
    
    static int M, N;
    static int[][] arr;
    static boolean[][] visited;
    
    public int[] solution(int m, int n, int[][] picture) {
        int numberOfArea = 0;
        int maxSizeOfOneArea = 0;

        M = m;
        N = n;
        arr = new int[m][n];
        
        for(int i=0; i<picture.length; ++i)
            arr[i] = picture[i].clone();
        
        visited = new boolean[M][N];
        
        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                if(picture[i][j] != 0 && !visited[i][j]){
                    maxSizeOfOneArea = Math.max(maxSizeOfOneArea, bfs(picture[i][j], i, j));
                    numberOfArea++;
                }
            }
        }
        
        int[] answer = new int[2];
        answer[0] = numberOfArea;
        answer[1] = maxSizeOfOneArea;
        
        return answer;
    }
    
    public static int bfs(int num, int r, int c){       
        Queue<Pos> q = new LinkedList<>();
        
        q.offer(new Pos(r, c));
        visited[r][c] = true;
        
        int cnt=1;  // 같은 블록 개수
        while(!q.isEmpty()){
            Pos now = q.poll();
            
            for(int i=0; i<4; ++i){
                int nr = now.r+dr[i];
                int nc = now.c+dc[i];
                
                if(!(0<=nr && nr<M && 0<=nc && nc<N) || visited[nr][nc]) continue;
                if(arr[nr][nc] != num) continue;
                
                cnt++;
                q.offer(new Pos(nr, nc));
                visited[nr][nc] = true;
            }
        }
        
        return cnt;
    }
}