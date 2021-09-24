/*
삼성 기출. 한 달 전에 풀었는데도 한 번에 풀 수 없었다...
대충 문제랑 방법은 알고 있었기 때문에 구현은 그리 오래 걸리지 않았는데 답이 제대로 안나왔다.
먼지를 옮겨지는 것과 퍼지는 함수는 맞는 것 같은데 최종 답이 안나와서 어디가 틀렸는지 찾지 못했다.
이전 풀이를 보고 나서야 문제점을 발견할 수 있었는데 미세먼지가 퍼지고 옮겨진 후 다시 미세먼지인 부분이 퍼져야 되는데 맨 처음 미세먼지만 퍼지도록 구현해서 틀린거였다.
너무 기본적인 실수였고 실제 시험장이었다면 1시간 이내로 해결할 걸 몇 십분이 더 걸릴수도 있을것이고 아예 틀린 부분을 찾지 못해 풀 수 없었을 수도 있을 것 같았다.
항상 문제를 잘 읽고 초기화 등을 신경써서 빨리 풀 수 있는건 빨리 풀자.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
	
	static class Pos{
		int r, c;
		Pos(int r, int c){
			this.r=r;
			this.c=c;
		}
	}
	
	static int R, C, T;
	static int[][] map;

	static int dr[] = {-1,0,1,0};	// 상 우 하 좌 순서
	static int dc[] = {0,1,0,-1};
	
	
	static int up[] = {1,0,3,2};	// 위쪽 공기: 우 상 좌 하
	static int down[] = {1,2,3,0};	// 아래쪽: 우 하 좌 상
	
	static Pos[] air;	// 공기 청정기 위치 저장
	
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		T = Integer.parseInt(st.nextToken());
		
		map = new int[R][C];
		air = new Pos[2];
		
		int k=0;
		for(int i=0; i<R; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<C; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
				// 공기청정기 위치 저장
				if(map[i][j] == -1)
					air[k++] = new Pos(i, j);
			}
		}
		
		for(int i=0; i<T; ++i) {
			spreadDust();	// 확산
			airCondition();	// 공기청정기 작동
		}
		
		// 미세먼지 계산
		System.out.println(getDust());		
	}
	
	private static void spreadDust() {
		int[][] dust = new int[R][C];	// 확산된 미세먼지 저장
		
		for(int i=0; i<R; ++i) {
			for(int j=0; j<C; ++j) {
				if(map[i][j] <= 0) continue;
				
				int cnt = 0;	// 확산된 방향의 개수
				for(int d=0; d<4; ++d) {
					int nr = i+dr[d];
					int nc = j+dc[d];
					
					// 인접한 방향에 공기청정기가 있거나, 칸이 없으면 그 방향으로는 확산이 일어나지 않는다.
					if(!inRange(nr, nc) || map[nr][nc] == -1) continue;
					
					// 인접 네 방향으로 미세먼지 확산
					dust[nr][nc] += map[i][j]/5;
					cnt++;
				}
				// 확산된 방향 개수 만큼 미세먼지 양 감소
				map[i][j] -= map[i][j]/5*cnt;
			}
		}
		
		// 확산이 끝난 후 미세먼지를 합친다.
		for(int i=0; i<R; ++i) 
			for(int j=0; j<C; ++j) 
				map[i][j] += dust[i][j];
	}

	
	
	private static void airCondition() {
		// 위쪽
		int r = air[0].r;
		int c = air[0].c;
		int[][] tmp = new int[R][C];
		
		for(int i=0; i<R; ++i)
			tmp[i] = map[i].clone();
		
		int dir = 0;
		while(dir < 4) {
			int nr = r+dr[up[dir]];
			int nc = c+dc[up[dir]];
			
			// 인접한 방향에 공기청정기가 있거나, 칸이 없으면 그 방향으로는 확산이 일어나지 않는다.
			if(!inRange(nr, nc) || map[nr][nc] == -1) {
				dir++;	// dir 증가
				continue;
			}
			
			map[nr][nc] = tmp[r][c];
			r= nr; c= nc;
		}
		
		// 공기청정기 바로 옆 칸은 0으로 만든다.
		map[air[0].r][air[0].c+1] = 0;
		
		// 아래쪽
		r = air[1].r;
		c = air[1].c;

		dir = 0;
		while(dir < 4) {
			int nr = r+dr[down[dir]];
			int nc = c+dc[down[dir]];

			// 인접한 방향에 공기청정기가 있거나, 칸이 없으면 그 방향으로는 확산이 일어나지 않는다.
			if(!inRange(nr, nc) || map[nr][nc] == -1) {
				dir++;	// dir 증가
				continue;
			}

			map[nr][nc] = tmp[r][c];
			r= nr; c= nc;
		}

		// 공기청정기 바로 옆 칸은 0으로 만든다.
		map[air[1].r][air[1].c+1] = 0;
	}
	
	private static int getDust() {
		int sum = 0;
		
		for(int i=0; i<R; ++i) 
			for(int j=0; j<C; ++j)
				sum += map[i][j];
		// 공기청정기 2칸인 -1 고려
		return sum+2;
	}
	
	
	// 경계 체크
	private static boolean inRange(int r, int c) {
		return 0<=r && r<R && 0<=c && c<C;
	}
}