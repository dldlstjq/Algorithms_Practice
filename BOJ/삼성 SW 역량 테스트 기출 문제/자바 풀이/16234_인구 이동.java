/*
처음에 너무 단순하게 생각해서 풀지 못했다.
그래프를 순회하긴 하는데 한 번 순회하고 끝이 아니라 더이상 인구 이동이 없을 때 까지 계속 배열을 탐색해야 한다.
그리고 인구수 차이가 적게 나는 곳이 여러군데 있을 수 있기 때문에 배열을 처음부터 쭉 돌아야한다.
이걸 이해하지 못해 처음만 순회하고 더이상 순회하지 않으니까 나중에 있을 인구 이동을 하지 못해 틀리기도 했다.

즉, 인구 이동이 없을 때 까지 계속 반복하는데 인접한 곳은 dfs, bfs를 활용하여 인구 수를 조절한다.
연결된 곳은 한 번에 처리하기 때문에 따로 저장해서 처리하지 않아도 된다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main {
	
	static class Nation{
		int r, c;

		public Nation(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}
	
	static int N,L,R;
	static int land[][];
	static int dr[] = {-1,0,1,0};
	static int dc[] = {0,1,0,-1};
	static boolean isMove;
	
	
	private static void check_population() {
		boolean visited[][] = new boolean[N][N];	// 해당 나라를 검사했는지 여부

		for(int i=0; i<N; ++i) {
			for(int j=0; j<N; ++j) {
				ArrayList<Nation> list = new ArrayList<>();
				
				// 이미 체크한 나라는 패스
				if(visited[i][j])
					continue;
				
				// 현재 위치부터 인접한 나라에 대해 인구 수 검사
				Queue<Nation> q = new LinkedList<>();
				q.offer(new Nation(i, j));
				list.add(new Nation(i, j));
				visited[i][j] = true;
				while(!q.isEmpty()) {
					Nation now = q.poll();
					
					for(int a=0; a<4; ++a) {
						// 인접한 두 나라
						int nr = now.r+dr[a];
						int nc = now.c+dc[a];
						// 범위 아웃이거나 이미 방문한 나라는 패스
						if(!(0<=nr&nr<N && 0<=nc&nc<N) || visited[nr][nc])
							continue;
						
						// 인접한 나라 인구 차이가 L이상 R 이하이면 연합
						int population = Math.abs(land[now.r][now.c]-land[nr][nc]);
						if(L <= population && population<=R) {
							// 현재 위치와 인접한 위치를 중복되지 않았으면 리스트에 삽입
							list.add(new Nation(nr, nc));
							visited[nr][nc] = true;
							q.offer(new Nation(nr, nc));	
						}
					}
				}
				
				// 나라가 2개 이상인 경우만 인구 이동
				if(list.size()>=2) {
					isMove = true;
					move_population(list); 
				}
					
			}
		}
	}
	
	// 인구 이동
	private static void move_population(ArrayList<Nation> list) {
		int sum=0;
		// 국경이 열린 나라 인구 수 총합
		for(Nation nation: list) 
			sum += land[nation.r][nation.c];
		
		// 연합을 이루고 있는 각 칸의 인구수는 (연합의 인구수) / (연합을 이루고 있는 칸의 개수)
		for(Nation nation: list) 
			land[nation.r][nation.c] = sum/list.size();
	}
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		L = Integer.parseInt(st.nextToken());
		R = Integer.parseInt(st.nextToken());
		
		land = new int[N][N];
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<N; ++j) {
				land[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		int day = 0;
		while(true) {
			isMove = false;
			check_population();
			
			if(isMove)
				day++;
			else 
				break;
		}
		System.out.println(day);
	}
}