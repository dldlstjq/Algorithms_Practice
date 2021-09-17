/*
문제 푼지 한달이 조금 넘었는데 다행히 빠른시간내에 해결한 것 같다.
완전탐색으로 벽을 만들 수 있는 모든 곳에다 벽을 놓고 바이러스를 퍼트린 뒤 안전영역을 세면 된다.
벽을 만들 수 있는 곳은 dfs로 해야 풀이가 한결 쉽고 바이러스를 퍼트릴 때 퍼트릴 배열을 따로 만들어서 수행해야 벽을 놓는 배열과 겹치지 않는다.

삼성유형은 유독 배열을 복사하고 복사한 배열로 수행한 뒤 다시 원배열로 돌아오는 문제가 많은 것 같다.
연습이 숙달되면 1시간내에 문제를 푸는것을 목표로 해야겠다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	
	static class Pos{
		int r,c;
		Pos(int r, int c){
			this.r=r;
			this.c=c;
		}
	}
	
	static int N, M;
	static int result = -1;	// 최대 안전영역
	
	static int dr[] = {-1,0,1,0};
	static int dc[] = {0,1,0,-1};
	
	static Queue<Pos> virus = new LinkedList<>();
	
	// 벽을 세워본다. 완전탐색
	static void makeWall(int wall, int[][] arr) {
		// 벽을 다 세웠으면 바이러스 퍼지고 안전영역 계산
		if(wall == 3) {
			int tmp[][] = new int[N][M];
			copyArr(arr, tmp);
			spreadVirus(tmp);
			result = Math.max(result, countSafeArea(tmp));
			return;
		}
		
		for(int i=0; i<N; ++i) {
			for(int j=0; j<M; ++j) {
				if(arr[i][j] == 0) {
					arr[i][j] = 1;
					makeWall(wall+1, arr);
					arr[i][j] = 0;
				}
			}
		}
	}
	
	// 바이러스가 퍼진다
	static void spreadVirus(int[][] arr) {
		Queue<Pos> q = new LinkedList<>(virus);
		
		while(!q.isEmpty()) {
			Pos curr = q.poll();
			
			for(int i=0; i<4; ++i) {
				int nr = curr.r+dr[i];
				int nc = curr.c+dc[i];
				
				// 범위 밖이거나 0이 아니면
				if(nr<0 || nr>=N || nc<0 || nc>=M || arr[nr][nc] != 0)
					continue;
				// 바이러스 퍼지고 큐에 추가
				arr[nr][nc] = 2;
				q.offer(new Pos(nr, nc));
			}
		}
	}
    
	// 안전영역 개수 카운트
	private static int countSafeArea(int[][] arr) {
		int cnt = 0;
		for(int i=0; i<N; ++i) 
			for(int j=0; j<M; ++j) 
				if(arr[i][j] == 0)
					cnt++;
		return cnt;
	}
    
	// 배열 복사
	static void copyArr(int[][] a, int[][] b) {
		for(int i=0; i<N; ++i)
			b[i] = a[i].clone();
	}
	
	public static void main(String[] args) throws Exception{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		int[][] map = new int[N][M];
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<M; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
				if(map[i][j] == 2)
					virus.offer(new Pos(i, j));
			}	
		}
		
		makeWall(0, map);
		System.out.println(result);
	}
}