/*
마름모 계산을 잘못해서 시간이 많이 걸린 문제이다.
dfs로 계산했는데 방문표시에서 값이 설정이 잘 안돼서 정확한 마름모 계산이 안됐다.
bfs를 이용하면 더 쉽게 가능했는데 너무 생고생한 것 같다.
또 N*N 전체를 다 살펴보기 위해 N<=K+1 까지 설정해서 모두 검사했는데 굳이 그럴 필요 없이 K를 하나씩 증가시키면서 큐에서 진행하면 더 빠른 시간 내에 마무리 할 수 있다.
1시간도 안돼서 풀 수 있는 문제를 1시간 30분 다 써서 겨우 풀어냈다.
마름모 문제는 BFS를 써야한다는 것을 몸소 익힐 수 있었다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;
import java.util.StringTokenizer;

public class Solution {
	static class Pos{
		int x; int y;
		Pos(int x, int y){
			this.x=x;
			this.y=y;
		}
	}
	
	static int N,M;
	static int[][] map;
	static int home;	// 집 개수, 이익
	static int cnt;	// 방범 서비스에 속하는 집 개수
	
	static int dr[]= {-1,0,1,0};
	static int dc[]= {0,1,0,-1};
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("sample_input.txt"));
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
	
		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());
			
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			
			map = new int[N][N];
			
			for(int i=0; i<N; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<N; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			home=0;
			for(int i=0; i<N; ++i) {
				for(int j=0; j<N; ++j) {
					bfs(i, j);
				}
			}
			
			StringBuilder sb=  new StringBuilder();
			sb.append("#"+test_case+" "+home);
			System.out.println(sb.toString());
			
		}
		
				
	}

	private static void bfs(int r, int c) {
		Queue<Pos> q = new LinkedList<>();
		boolean[][] visited = new boolean[N][N];
		visited[r][c] = true;
		q.offer(new Pos(r, c));
		
		cnt = 0;
		int k=1;
		if(map[r][c] == 1) cnt++;
		
		if(opCost(k) <= M*cnt)
			home = Math.max(home, cnt);
		
		while(!q.isEmpty()) {
			int size=q.size();
			k++;
			
			for(int s=0; s<size; ++s) {
				Pos now = q.poll();
			
				for(int i=0; i<4; ++i) {
					int nr = now.x+dr[i];
					int nc = now.y+dc[i];
					// 범위 벗어나면 패스
					if(!(0<=nr && nr<N && 0<=nc && nc<N) || visited[nr][nc]) continue;
					
					if(map[nr][nc] == 1) cnt++;
					visited[nr][nc] = true;
					q.offer(new Pos(nr, nc));
				}
			}
			
			if(opCost(k) <= M*cnt)
				home = Math.max(home, cnt);
			
		}
	}

	private static int opCost(int k) {
		return k*k + (k-1)*(k-1);
	}
}
