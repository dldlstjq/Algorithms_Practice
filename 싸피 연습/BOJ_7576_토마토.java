/*
코테를 막 시작했을 때 푼 문제인데 다시 풀어보니 금방 풀 수 있었다.
이전에는 bfs의 레벨 탐색을 잘 몰라서 못 풀었던 기억이 난다.
다만 bfs를 돌며 인접한 토마토를 익는데 걸린 시간을 구하고 다시 2중 for문을 돌면서 다 익었는지를 확인했다.
이렇게 되면 시간이 조금 더 걸리기 때문에 빈칸, 날짜, 익은 토마토개수를 변수로 설정해서 한번의 bfs로 다 구할 수 있게 하면 시간이 덜 걸린다.

카운트 변수 설정: 672ms
bfs후 다시 맵 탐색: 740ms
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	
	static class Pos{
		int r, c;
		Pos(int r, int c){
			this.r=r;
			this.c=c;
		}
	}
	
	static int N, M;
	static int[][]map;

	static int dr[] = {-1,0,1,0};
	static int dc[] = {0,1,0,-1};
	
	static Queue<Pos> q;
	
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		M = Integer.parseInt(st.nextToken());
		N = Integer.parseInt(st.nextToken());
		map = new int[N][M];
		q = new LinkedList<>();
		
		int blank = 0;
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<M; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
				if(map[i][j] == 1)
					q.offer(new Pos(i, j));
				if(map[i][j] == 0)
					blank++;
			}
		}
		
		System.out.println(bfs(blank));
	}

	// 토마토가 익는다.
	private static int bfs(int blank) {
		
		int cnt = 0;
		int day = 0;
		while(!q.isEmpty()) {
			int size = q.size();
			day++;
			
			while(size-- > 0) {
				Pos curr = q.poll();
				
				for(int i=0; i<4; ++i) {
					int nr = curr.r+dr[i];
					int nc = curr.c+dc[i];
					
					// 경계 체크
					if(nr<0 || nr>=N || nc<0 || nc>=M) continue;
					
					// 익지 않은 토마토만 익을 수 있다.
					if(map[nr][nc] != 0) continue;
					
					// 익은 토마토에 +1을 해서 저장
					map[nr][nc] = map[curr.r][curr.c]+1;
					q.offer(new Pos(nr, nc));
					cnt++;
				}
			}
		}
		
		if(cnt != blank)
			day = 0;
		return day-1;
	}
}
