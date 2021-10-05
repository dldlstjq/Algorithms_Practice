/*
상반기때 한 번 풀었던 것 같은데 다행히 1시간 안에 해결한 것 같다.
같은 위치에 공을 계속 쏠 수 있기 때문에 중복조합이고 다른 맵을 하나 더 생성해서 해결해야 한다.
그래도 실력이 올랐구나 체감할 수 있었고 삼성은 배열을 하나 더 생성해서 이전 상태를 유지하는 것, 배열 회전을 잘 익혀가야 쉽게 문제를 풀 수 있는 것 같다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;


public class Solution {
	
	static int N,W,H;
	static int[][] map;
	static int[] dr = {-1,0,1,0};
	static int[] dc = {0,1,0,-1};
	
	static int[] order;	// 구슬을 쏘는 위치
	static int ans;

	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("sample_input.txt"));
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T;
		T= Integer.parseInt(br.readLine());	

		StringTokenizer st = null;
		StringBuilder sb = null;
		for(int test_case = 1; test_case <= T; test_case++)
		{
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			W = Integer.parseInt(st.nextToken());
			H = Integer.parseInt(st.nextToken());
			
			map = new int[H][W];
			for(int i=0; i<H; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<W; ++j)
					map[i][j] = Integer.parseInt(st.nextToken());
			}
			
			ans = Integer.MAX_VALUE;
			
			play(0);
			
			sb = new StringBuilder();
			sb.append("#"+test_case+" "+ans);
			System.out.println(sb);
		}
	}

	private static void play(int n) {
		// 모든 공 사용
		if(n == N) {
			// 남은 벽돌이 최소가 되도록 체크
			int cnt = checkBrick();
			ans = Math.min(ans, cnt);
			return;
		}
		
		int[][] tmp =  new int[H][W];
		copyArray(map, tmp);
		
		// W 크기만큼만 공이 움직임
		for(int i=0; i<W; ++i) {
			breakBrick(i);	// 벽돌을 깬다.
			downBrick();	// 남은 벽돌을 내린다.
			play(n+1);	// 다음 구슬로 플레이
			
			copyArray(tmp, map);	// 원래 배열로 복귀
		}
		
	}
	
	private static int checkBrick() {
		int cnt =0;
		for(int i=0; i<H; ++i)
			for(int j=0; j<W; ++j)
				if(map[i][j] != 0)
					cnt++;
		return cnt;
	}

	// 부서지고 남은 벽돌을 내린다.
	private static void downBrick() {
		ArrayList<Integer> list = new ArrayList<>();
		for(int i=0; i<W; ++i) {
			list.clear();
			
			// 행 밑에서부터 올라가면서 벽돌인 부분만 리스트에 저장.
			for(int j=H-1; j>=0; --j) {
				if(map[j][i] != 0) {
					list.add(map[j][i]);
					map[j][i] = 0;
				}
			}
			
			// 다시 행 밑에서부터 시작해 리스트에 저장된 벽돌을 채운다
			int k=0;
			for(int j=H-1; j>=0; --j) {
				if(k == list.size()) break;
				map[j][i] = list.get(k++);
			}
			
		}
	}

	// start열에서 0부터 내려가며 먼저 만나는 벽돌을 부순다.
	private static void breakBrick(int start) {
		for(int i=0; i<H; ++i) {
			if(map[i][start] != 0) {
				breakStart(i, start);
				break;
			}
		}
	}

	// 벽돌 부수기 시작. dfs
	private static void breakStart(int r, int c) {
		int num = map[r][c];
		map[r][c] = 0;
		// 벽돌에 적힌 숫자만큼 부순다.
		for(int i=0; i<4; ++i) {
			for(int j=0; j<num; ++j) {
				int nr = r+dr[i]*j;
				int nc = c+dc[i]*j;
				
				if(nr<0 || nr>=H || nc<0 || nc>=W || map[nr][nc] == 0)
					continue;
				
				breakStart(nr, nc);
			}
		}
	}

	private static void copyArray(int[][] a, int[][] b) {
		for(int i=0; i<H; ++i)
			b[i] = a[i].clone();	
	}
}