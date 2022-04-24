/*
마름모 꼴로 증가하면서 손해를 안 볼 때 서비스 영역에 있는 최대 집을 구하는 문제다.
N*N 칸 전부를 돌면서 k를 증가시켜 하나씩 계산했다.
운영 비용이 모든 집을 서비스하는 것 보다 비싸면 종료하도록 해서 구했는데 왠걸 시간초과를 받았다.

싸피때 했던 코드를 살펴봤고 대충 비슷해보였는데 무슨 차이인지 처음엔 몰랐다.

알고보니 나는 같은 칸에 대해 k가 증가하면서 같은 칸을 계속 검사했기 때문에 시간초과가 났다.
예를 들어 i,j에서
k=1 (i,j) 검사
k=2 (i,j) (i+1,j) (i-1,j) (i,j+1) (i, j-1)
k=3 (i,j) (i+1,j) (i-1,j) (i,j+1) (i, j-1) ...
이런식으로 같은 좌표를 계속 검사하기 때문에 시간초과가 난다.

싸피때 했던 코드는 레벨별 탐색을 이용해서 현재 칸에서 계속 증가하는 방식으로 하기 때문에 같은 좌표를 한번만 검사하고 넘어간다.

문제가 너무 쉽다고 방심했는데 실제 시험에서 시간초과를 받아버리면 당황스러울거 같은데 레벨별 탐색도 잘 익혀놔야겠다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;

public class Solution {
	
	static class Pos{
		int r; int c; int n;
		Pos(int r, int c, int n){
			this.r=r;
			this.c=c;
			this.n=n;
		}
	}
	
	static int N, M;
	static int[][] map;
	
	static int dr[]= {-1,0,1,0};
	static int dc[]= {0,1,0,-1};
	
	static int totalHouse;	// 전체 집 개수
	
	static int ret;
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("sample_input.txt"));
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());
			N= Integer.parseInt(st.nextToken());
			M= Integer.parseInt(st.nextToken());
			
			map = new int[N][N];
			
			for(int i=0; i<N; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<N; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
					if(map[i][j]==1) totalHouse++;
				}
			}
			
			ret= 0;
			for(int i=0; i<N; ++i) {
				for(int j=0; j<N; ++j) {
					start(i, j);
				}
			}
		
			
			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(ret);
			System.out.println(sb);
		}
	}

	private static void start(int r, int c) {
		int k=1;
		while(true) {
			// 모든 집 서비스 비용보다 운영비용이 더 비싸면 할 필요 없음
			if(totalHouse*M - cost(k) < 0) break;
			
			int house = searchHouse(r, c, k);	// k영역일떄 집 개수
			
			// 기존 집보다 더 많이 제공가능한 경우
			if(house > ret) {
				int profit = house*M - cost(k);
				// 비용이 손해 안보면 갱신
				if(profit>=0) {
					ret = Math.max(ret, house);
//					System.out.println("("+r+" "+c+" "+")"+": "+profit+" "+k+" "+house);
				}
			}
			
			k++;
		}
	}

	private static int cost(int k) {
		return k*k+(k-1)*(k-1);
	}

	private static int searchHouse(int r, int c, int k) {
		int cnt = 0;
		Queue<Pos> q = new LinkedList<>();
		boolean[][] visited = new boolean[N][N];
		q.offer(new Pos(r, c, 1));
		visited[r][c] = true;
		if(map[r][c]==1) cnt++;
		
		while(!q.isEmpty()) {
			Pos now = q.poll();
			
			// k영역만큼만 진행
			if(now.n==k) continue;	
			
			for(int i=0; i<4; ++i) {
				int nr = now.r+dr[i];
				int nc = now.c+dc[i];
				
				if(!isIn(nr, nc) || visited[nr][nc]) continue;
				
				// 집이 있다면 카운트
				if(map[nr][nc] == 1) cnt++;
				
				q.offer(new Pos(nr, nc, now.n+1));
				visited[nr][nc] = true;
			}
		}
		
		
		return cnt;
	}

	private static boolean isIn(int r, int c) {
		return 0<=r&&r<N && 0<=c&&c<N;
	}

}
