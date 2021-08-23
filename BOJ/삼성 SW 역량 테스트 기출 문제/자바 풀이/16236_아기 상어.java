/*
맞게 푼 것 같았는데 계속 틀렸다.
일단 거리를 구하는 기준이 이동하는 칸의 개수인데 상어 위치와 직접적으로 구해 틀렸다.
두번째로 먹을 수 있는 물고기를 찾으면 더 이상 큐에 새로운 좌표를 집어넣지 않고 현재 있는 것만 다 탐색해야 한다.
안그러면 전체 배열을 다 탐색하기 때문에 시간적으로도 손해가 있을 것 같다.
근데 굳이 안그러더라도 풀 수 있을 것 같은데 잘 안되는 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main {
	
	static class Pos {
		int r, c;

		public Pos(int r, int c) {
			super();
			this.r = r;
			this.c = c;
		}
	}
	
	static class Cand implements Comparable<Cand>{
		int r, c, dist;

		public Cand(int r, int c, int dist) {
			super();
			this.r = r;
			this.c = c;
			this.dist = dist;
		}

		@Override
		public int compareTo(Cand o) {
			if(this.dist == o.dist) {
				if(this.r == o.r)
					return this.c - o.c;
				return this.r - o.r;
			}
			return this.dist-o.dist;
		}
		
	}
	
	static int N;
	static int map[][];
	static Pos shark;			// 상어 위치
	
	static int shark_size = 2;	// 아기상어 크기
	static int dr[] = {-1,0,1,0};
	static int dc[] = {0,1,0,-1};
	
	static int sec;	// 초
	static int eatCnt;	// 먹은 물고기 수
	
	
	private static boolean searchFish() {
		ArrayList <Cand> list= new ArrayList<>();	// 먹을 수 있는 물고기 후보
		Queue<Cand> q = new LinkedList<>();
		boolean visited[][] = new boolean[N][N];	// 방문 여부
		boolean flag = false;
		
		q.offer(new Cand(shark.r, shark.c, 0));
		visited[shark.r][shark.c] = true;
		
		boolean edible=  false;    // 먹을 물고기가 있는지
		
		while(!q.isEmpty()) {
			Cand now = q.poll();
			
			for(int i=0; i<4; ++i) {
				int nr = now.r+ dr[i];
				int nc = now.c+ dc[i];
				
				// 범위를 벗어나거나 이미 방문한 곳은 못감
				if(!(0<=nr && nr<N &&0<=nc && nc<N) || visited[nr][nc])
					continue;
				// 자기 크기보다 큰 물고기는 먹을수도, 지나갈 수도 없다.
				if(map[nr][nc] > shark_size) 
					continue;
				
				if(map[nr][nc] <= shark_size) {
                    // 먹을 물고기가 없으면 갈 수 있는 곳 다 탐색
					if(!edible) {
						// 물고기가 없거나 크기가 같으면 지나만 갈 수 있다
						if(map[nr][nc] == 0 || map[nr][nc] == shark_size) {
							q.offer(new Cand(nr, nc, now.dist+1));
							visited[nr][nc] = true;
						}
						
						// 상어 크기보다 작으면서 먹을 수 있으면 후보군에 삽입
						else if(map[nr][nc] < shark_size && map[nr][nc] != 0) {
							list.add(new Cand(nr, nc, now.dist+1));
							visited[nr][nc] = true;
							edible = true;
						}
					}
                    // 먹을 수 있는 물고기를 찾으면 현재 큐에 있는 것만 탐색
					else {
						if(map[nr][nc] < shark_size && map[nr][nc] != 0) {
							list.add(new Cand(nr, nc, now.dist+1));
							visited[nr][nc] = true;
						}
					}
				}
			}
		}
		
		Collections.sort(list);	// 정렬
		// 리스트에 먹을 수 있는 물고기가 있으면 먹고 아니면 끝
		if(!list.isEmpty()) {
			flag = true;
			map[list.get(0).r][list.get(0).c] = 0;	// 먹은 물고기는 0
			// 이동한 거리만큼 초 증가
			sec += list.get(0).dist;
			eatCnt++;
			// 먹은 물고기 수가 자기의 크기와 같다면 크기 증가
			if(eatCnt == shark_size) {
				shark_size++;
				eatCnt = 0;
			}
				
			// 상어 위치 변경
			map[shark.r][shark.c] = 0; 
			shark.r = list.get(0).r;
			shark.c = list.get(0).c;
			
		}
		return flag;
	}
	
	
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		
		N = Integer.parseInt(br.readLine());
		map = new int[N][N];
		
		for(int i=0; i<N; ++i) {
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<N; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
				if(map[i][j] == 9) 
					shark = new Pos(i, j);
			}
		}
		
		while(true) {
			if(!searchFish())
				break;
			
		}
		System.out.println(sec);
	}
}