/*
문제가 그리 어렵지 않아 30분정도 걸린것 같다.
하나의 좌표에 여러 세포가 들어오는 경우 기준점을 잡아야 해서 기준점을 저장하는 NxN 배열을 하나 더 선언했다.
2차원 배열이 3개나 되니 메모리도 많이 차지하고 시간도 제법 걸렸다.

더 효율적인 방법이 없나 봤더니 굳이 2차원 배열 선언하지 않고 리스트 하나만 이용해서 모든 세포를 저장한다.
그리고 세포번호와 카운트를 기준으로 정렬 한 후 겹치는 부분은 가장 큰 것으로 방향을 잡아줘서 해결했다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {
	static class Cell{
		int num; int dir;
		Cell(int num, int dir){
			this.num=num;
			this.dir=dir;
		}
	}
	
	static int N, M, K;
	static Cell[][] map;
	static Cell[][] tmp;	// 시간마다 이동하는 세포 임시 저장
	static Cell[][] big;	// 여러개 세포 들어가는 경우 기준 세포 저장
	
	static int dr[]= {0,-1,1,0,0};
	static int dc[]= {0,0,0,-1,1};
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("sample_input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());
			
			map = new Cell[N][N];
			
			for(int i=0; i<K; ++i) {
				st = new StringTokenizer(br.readLine());
				int r = Integer.parseInt(st.nextToken());
				int c = Integer.parseInt(st.nextToken());
				int n = Integer.parseInt(st.nextToken());
				int d = Integer.parseInt(st.nextToken());
				
				map[r][c] = new Cell(n, d);
			}
			
			for(int i=0; i<M; ++i) {
				start();
			}
			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(getSum());
			System.out.println(sb);
			
		}
	}

	private static int getSum() {
		int sum = 0;
		for(int i=0; i<N; ++i) {
			for(int j=0; j<N; ++j) {
				if(map[i][j]==null) continue;
				sum += map[i][j].num;
			}
		}
		return sum;
	}

	private static void start() {
		tmp = new Cell[N][N];
		big = new Cell[N][N];
		for(int i=0; i<N; ++i) {
			for(int j=0; j<N; ++j) {
				if(map[i][j]==null) continue;
				moveCell(i, j);
			}
				
		}
		copy();
	}

	private static void copy() {
		for(int i=0; i<N; ++i) {
			for(int j=0; j<N; ++j) {
				map[i][j] = tmp[i][j];
			}
		}
	}

	private static void moveCell(int r, int c) {
		int n = map[r][c].num;
		int d = map[r][c].dir;
		int nr = r+dr[d];
		int nc = c+dc[d];
		
		// 빨간 약품
		if(nr==0 || nr==N-1 || nc==0 || nc==N-1) {
			if(tmp[nr][nc] == null) {
				if(d==1 || d==3) d+=1;
				else d-=1;
				tmp[nr][nc] = new Cell(n/2, d);
			}
		}
		
		else {
			// 이동하는 쪽이 비었다면 그대로 저장
			if(tmp[nr][nc] == null) {
				tmp[nr][nc] = new Cell(n, d);
				big[nr][nc] = new Cell(n, d);
			}
			
			else {
				tmp[nr][nc].num += n;	// 미생물은 합쳐짐
				
				// 현재 미생물의 수가 기준 보다 많다면 기준 갱신
				if(big[nr][nc].num < n) {
					big[nr][nc].num = n;
					big[nr][nc].dir = d;
					tmp[nr][nc].dir = d;
				}
			}
		}
	}
}
