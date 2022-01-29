/*
복잡해 보여도 문제 이해는 쉽다.
다만 처음과 끝이 연결되어있어 범위를 벗어나면 다시 맨 끝으로 보내줘야 하는 예외를 잘 잡아줘야 한다.
그리고 현재 기준으로 이전에 구름이 생성된 곳에는 구름이 생성되지 않기 때문에 이 예외도 잘 처리해줘야 답이 잘 나온다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main {
	
	static class Pos{
		int r; int c;
		Pos(int r, int c){
			this.r=r;
			this.c=c;
		}
	}
	
	static int N,M;
	static int[][] water;
	static boolean[][] cloud;
	static boolean[][] isCloud;
	static int[][] tmp;
	static List<Pos> prevList;
	static List<Pos> nowList;
	
	// 이동 8방향
	static int dr[] = {0,0,-1,-1,-1,0,1,1,1};
	static int dc[] = {0,-1,-1,0,1,1,1,0,-1};
	
	// 대각선 4방향
	static int diagR[] = {-1,-1,1,1};
	static int diagC[] = {-1,1,1,-1};
	
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		water = new int[N][N];
		
		isCloud = new boolean[N][N];
		prevList = new ArrayList<>();
		nowList = new ArrayList<>();
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; ++j)
				water[i][j] = Integer.parseInt(st.nextToken());
		}
		
		// (N, 1), (N, 2), (N-1, 1), (N-1, 2)에 비구름이 생긴다
		prevList.add(new Pos(N-1, 0));
		prevList.add(new Pos(N-1, 1));
		prevList.add(new Pos(N-2, 0));
		prevList.add(new Pos(N-2, 1));
		
		for(int i=0; i<M; ++i) {
			st = new StringTokenizer(br.readLine());
			int d = Integer.parseInt(st.nextToken());
			int s = Integer.parseInt(st.nextToken());
			
			moveCloud(d, s);	// 구름 이동
			
			rain();	// 비가 내려 물의 양 1 증가
			
			copyWater();	// 물 복사 마법 시전
			
			makeCloud();	// 구름 생성
		}
		// r,c = 바구니
		// A[r][c] = 바구니 저장된 물의 양
		//(N, 1), (N, 2), (N-1, 1), (N-1, 2)에 비구름이 생긴다.
		
		System.out.println(answer());
	}

	private static int answer() {
		int sum=0;
	
		for(int i=0; i<N; ++i) 
			for(int j=0; j<N; ++j) 
				sum += water[i][j];
		return sum;
	}

	private static void makeCloud() {
		prevList.clear();
		for(int i=0; i<N; ++i) {
			for(int j=0; j<N; ++j) {
				if(water[i][j] >= 2 && !cloud[i][j]) {
					water[i][j] -= 2;
					prevList.add(new Pos(i, j));
				}
			}	
		}
	}

	private static void copyWater() {
		for(int i=0; i<nowList.size(); ++i) {
			int r = nowList.get(i).r;
			int c = nowList.get(i).c;
			
			int cnt = 0;
			for(int k=0; k<4; ++k) {
				int nr = r+diagR[k];
				int nc = c+diagC[k];
				
				// 경계 넘어가는 칸은 대각선 방향 1이 아니다.
				if(!(0<=nr && nr<N && 0<=nc && nc<N)) continue;
				
				// 물이 있는 바구니 수 카운트
				if(water[nr][nc] >= 1) cnt++;

			}
			// 대각선에 있는 개수만큼 물의 양 증가
			water[r][c] += cnt;
		}
	}

	private static void rain() {
		for(int i=0; i<nowList.size(); ++i) {
			int r = nowList.get(i).r;
			int c = nowList.get(i).c;
			
			water[r][c] += 1;
		}
	}


	private static void moveCloud(int d, int s) {
		nowList.clear();
		cloud = new boolean[N][N];
		
		for(int i=0; i<prevList.size(); ++i) {
			int r = prevList.get(i).r;
			int c = prevList.get(i).c;
			
			
			if(d==1) {	// 좌
				c=c+dc[d]*(s%N);
				if(c < 0) c+= N;
			}
				
			
			else if(d==3) {	// 상
				r=r+dr[d]*(s%N);
				if(r < 0) r+= N;
			}
				
			
			else if(d==5)	// 우
				c=(c+dc[d]*(s%N))%N;
			
			else if(d==7)	// 하
				r=(r+dr[d]*(s%N))%N;
			
			else  {	// 대각 방향
				r=(r+dr[d]*(s%N));
				c=(c+dc[d]*(s%N));
				if(r<0) r+=N;
				else if(r>=N) r-=N;
				if(c<0) c+=N;
				else if(c>=N) c-=N;
			}
			
			nowList.add(new Pos(r, c));
			cloud[r][c] = true;	// 구름 생성
		}
	}
}
