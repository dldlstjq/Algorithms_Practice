/*
우선순위 큐 풀이.
거리가 가장 짧은 것이 맨 앞에 나오기 때문에 먹을 물고기가 있으면 바로 리턴해주면 된다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.PriorityQueue;
import java.util.StringTokenizer;


public class Main_BJ_16236_아기상어_이인섭2 {
	
	static class Pos implements Comparable<Pos>{
		int r, c, dist, size;

		public Pos(int r, int c, int dist, int size) {
			super();
			this.r = r;
			this.c = c;
			this.dist = dist;
			this.size = size;
		}
		// 거리가 짧은순, 가장 위에 있는 순, 가장 왼쪽에 있는 순서로 정렬
		@Override
		public int compareTo(Pos o) {
			if(this.dist == o.dist) {
				if(this.r == o.r)
					return this.c-o.c;
				return this.r-o.r;
			}
			return this.dist-o.dist;
		}
	}

	static int N;	// 크기
	static int map[][];
	static Pos shark;	// 아기 상어 위치 
	static int eatCnt;		// 먹은 물고기의 수
	
	static int dr[] = {-1,0,1,0};	// 상우하좌
	static int dc[] = {0,1,0,-1};
	
	
	// 자신의 크기보다 큰 물고기는 지나갈 수 없다. 
	// 자신의 크기보다 작은 물고기만 먹을 수 있다.
	// 크기가 같은 물고기는 먹을 수 없지만, 그 물고기가 있는 칸은 지나갈 수 있다.
	
	// 아기 상어의 이동은 1초 걸리고, 이동과 동시에 물고기를 먹는다. 물고기를 먹으면, 그 칸은 빈 칸이 된다.
	// 아기 상어는 자신의 크기와 같은 수의 물고기를 먹을 때 마다 크기가 1 증가한다. 예를 들어, 크기가 2인 아기 상어는 물고기를 2마리 먹으면 크기가 3이 된다.
	
	// 먹을 수 있는 물고기를 찾는다.
	private static boolean find_fish() {
		PriorityQueue<Pos> pq = new PriorityQueue<>();	// BFS 사용
		boolean[][] visited = new boolean[N][N];	// 방문여부

		pq.offer(shark);	// 상어의 초기 위치
		visited[shark.r][shark.c] = true;
		
		
		// bfs로 현재 상어 위치에서 먹을 수 있는 물고기 위치와 거리를 모두 탐색
		while(!pq.isEmpty()) {
			Pos now = pq.poll();
			
			// 자신의 크기보다 작은 물고기만 먹을 수 있다.
			if(map[now.r][now.c] != 0 && map[now.r][now.c] < shark.size) {
				map[now.r][now.c] = 0;
				shark = new Pos(now.r, now.c, now.dist, shark.size);
				eatCnt++;
				if(eatCnt == shark.size) {
					shark.size++;
					eatCnt = 0;
				}
				return true;
			}
			
			// 아기 상어는 1초에 상하좌우로 인접한 한 칸씩 이동
			for(int i=0; i<4; ++i) {
				int nr = now.r+dr[i];
				int nc = now.c+dc[i];
				
				// 배열 범위를 벗어나거나 이미 방문한 곳이면 패스
				if(!(0<=nr && nr<N && 0<=nc && nc<N) || visited[nr][nc])
					continue;
				
				// 자신의 크기보다 큰 물고기는 지나갈 수 없다. 
				if(map[nr][nc] > shark.size)
					continue;
				
				
				// 크기가 같은 물고기는 먹을 수 없지만, 그 물고기가 있는 칸은 지나갈 수 있다.
				// 물고기가 없는 부분도 지나갈 수 있다.
				else if(map[nr][nc] <= shark.size) {
					visited[nr][nc] = true;
					pq.offer(new Pos(nr, nc, now.dist+1, 0));
				
				}
			}
		}
		return false;
	}
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;
		
		N = Integer.parseInt(br.readLine());
		
		map = new int[N][N];
		
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<N; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
				// 아기 상어 위치 저장
				if(map[i][j] == 9) {
					shark = new Pos(i,j, 0, 2);	// 상어의 위치와 이동거리, 크기를 넣어준다.
					map[i][j] = 0;	// 상어 위치는 빈 칸
				}
					
			}
		}
		
		while(true) {
			// 물고기 탐색. 먹을 수 있는 물고기가 없으면 종료
			if(!find_fish())
				break;
		}
		
		System.out.println(shark.dist);	// 상어가 이동한 거리가 걸린 시간
	}
}