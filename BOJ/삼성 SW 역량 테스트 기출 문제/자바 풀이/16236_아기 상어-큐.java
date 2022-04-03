/*
맞게 푼 것 같았는데 계속 틀렸다.
일단 거리를 구하는 기준이 이동하는 칸의 개수인데 상어 위치와 직접적으로 구해 틀렸다.
두번째로 먹을 수 있는 물고기를 찾으면 더 이상 큐에 새로운 좌표를 집어넣지 않고 현재 있는 것만 다 탐색해야 한다.
안그러면 전체 배열을 다 탐색하기 때문에 시간적으로도 손해가 있을 것 같다.
근데 굳이 안그러더라도 풀 수 있을 것 같은데 잘 안되는 것 같다.

수업시간에 문제로 나와서 다시 풀어봤다.
푼 지 얼마 안되어서 그런지 조건을 잘 걸었고 코드 중복도 줄인것 같았다.
혹시나 다른 사람 풀이를 봤는데 우선순위 큐를 사용하면 무조건 최소거리가 먼저 나오기 때문에 코드가 더 간결해졌다.
bfs만 생각했지 우선순위 큐를 사용하는건 생각도 못했는데 역시 고수는 많은 것 같다.
이렇게 또 하나 배웠다.

2022.04.03
풀이는 거의 비슷하게 풀었다. 우선순위 큐 방법도 다시 한번 익힐 수 있었다.
상어 위치를 확인하는 동시에 0으로 만들던가 물고기를 먹은 후 상어 위치를 0으로 만들어야 하는 것이 중요하다.
그거 빼고는 그렇게 어려웠던 것 같지는 않다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	
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
	
	static ArrayList<Pos> list = new ArrayList<>();	// 먹을 수 있는 물고기 후보
	
	// 자신의 크기보다 큰 물고기는 지나갈 수 없다. 
	// 자신의 크기보다 작은 물고기만 먹을 수 있다.
	// 크기가 같은 물고기는 먹을 수 없지만, 그 물고기가 있는 칸은 지나갈 수 있다.
	
	// 아기 상어의 이동은 1초 걸리고, 이동과 동시에 물고기를 먹는다. 물고기를 먹으면, 그 칸은 빈 칸이 된다.
	// 아기 상어는 자신의 크기와 같은 수의 물고기를 먹을 때 마다 크기가 1 증가한다. 예를 들어, 크기가 2인 아기 상어는 물고기를 2마리 먹으면 크기가 3이 된다.
	
	// 먹을 수 있는 물고기를 찾는다.
	private static boolean find_fish() {
		Queue<Pos> q = new LinkedList<>();	// BFS 사용
		boolean[][] visited = new boolean[N][N];	// 방문여부
		list.clear();	// 리스트 초기화
		q.offer(shark);	// 상어의 초기 위치
		visited[shark.r][shark.c] = true;
		
		boolean isFind = false;
		
		// bfs로 현재 상어 위치에서 먹을 수 있는 물고기 위치와 거리를 모두 탐색
		while(!q.isEmpty()) {
			Pos now = q.poll();
			
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
				
				// 자신의 크기보다 작은 물고기만 먹을 수 있다.
				if(map[nr][nc] != 0 && map[nr][nc] < shark.size) {
					visited[nr][nc] = true;	//방문 표시
					list.add(new Pos(nr, nc, now.dist+1, 0));	// 먹을 수 있는 물고기 후보
					isFind = true;	// 먹을 수 있는 물고기를 찾았다고 표시
					continue;
				}
				
				// 크기가 같은 물고기는 먹을 수 없지만, 그 물고기가 있는 칸은 지나갈 수 있다.
				// 물고기가 없는 부분도 지나갈 수 있다.
				else if(map[nr][nc] == shark.size || map[nr][nc] == 0) {
					visited[nr][nc] = true;
					
					// 먹을 수 있는 물고기를 못찾으면, 큐에 새로운 좌표를 넣는다. 
					// bfs를 사용했기 때문에 먹을 수 있는 물고기가 나온 지점이 최단거리
					if(!isFind)
						q.offer(new Pos(nr, nc, now.dist+1, 0));
				}
			}
		}
		
		// 먹을 수 있는 물고기가 없다 -> 종료
		if(list.isEmpty())
			return false;
		return true;
	}
	
	
	private static void move_and_eat() {
		Collections.sort(list);	// 물고기 후보를 정렬한다.
		
		// 먹을 수 있는 물고기의 좌표와 이동 거리
		int fish_r= list.get(0).r;
		int fish_c= list.get(0).c;
		int dist = list.get(0).dist;
		
		// 아기 상어의 이동은 1초 걸리고, 이동과 동시에 물고기를 먹는다. 물고기를 먹으면, 그 칸은 빈 칸이 된다.
		// 아기 상어는 자신의 크기와 같은 수의 물고기를 먹을 때 마다 크기가 1 증가한다. 예를 들어, 크기가 2인 아기 상어는 물고기를 2마리 먹으면 크기가 3이 된다.
		
		map[shark.r][shark.c] = 0;	// 원래 상어위치 값은 0으로.
		map[fish_r][fish_c] = 0;	// 물고기를 먹으면, 그 칸은 빈 칸
		shark = new Pos(fish_r, fish_c, dist, shark.size);	// 상어 정보를 먹은 물고기의 위치와 이동거리로 갱신
		
		// 자신의 크기와 같은 수의 물고기를 먹을 때 마다 크기가 1 증가
		eatCnt++;
		if(shark.size == eatCnt) {
			shark.size++;
			eatCnt = 0;
		}
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
				if(map[i][j] == 9) 
					shark = new Pos(i,j, 0, 2);	// 상어의 위치와 이동거리, 크기를 넣어준다.
			}
		}
		
		while(true) {
			// 물고기 탐색. 먹을 수 있는 물고기가 없으면 종료
			if(!find_fish())
				break;
			
			move_and_eat();	// 이동 후 물고기를 먹는다.
		}
		
		System.out.println(shark.dist);	// 상어가 이동한 거리가 걸린 시간
	}
}