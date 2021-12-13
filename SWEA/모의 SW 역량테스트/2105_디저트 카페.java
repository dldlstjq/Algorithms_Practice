/*
문제 자체는 이해하기 어렵지 않았다.
다만 사각형으로 돌아야 하는 것을 어떻게 구현해야 하나에서 너무 오래 헤맸다.
대각선 사각형으로 돌기 때문에 어떤 대각선이든 한 방향으로만 돌아도 상관 없어서 오른쪽 아래부터 시작하도록 했다.
문제는 한쪽 대각선으로 가다가 방향을 바꿔서 사각형을 만들어야 했는데 일반적인 사방탐색으로 하면 마름모 모양이 나오지 않는다.
그래서 한쪽 방향으로 계속 가다가 갈 수 없으면 방향을 바꾸고 또 그 방향으로 계속 가다가 다시 방향을 바꾸는 방식으로 진행해야 한다.
또, 백트래킹을 이용해서 다시 다른 좌표를 검사해야 하는 것도 고려해야 한다.
다른 사람의 풀이를 보고나서 for문 시작을 현재 방향으로 시작하게 했으면 됐는데 그게 생각이 나지 않아 여러 방법을 사용했고 틀렸다.
만약 이게 시험에 나왔다면 최대 1시간 안에는 풀고 다른 문제로 넘어가야 하는 그런 문제인데 생각보다 너무 못풀었다.
빨리 감각이 돌아오도록 알고리즘 문제를 많이 풀어봐야겠다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {
	
	static int N;
	static int[][] map;
	static boolean[][] visited;
	static boolean[] isEat;
	static int dr[]= {1,1,-1,-1};
	static int dc[]= {1,-1,-1,1};
	
	static int ret;
	static int startR, startC;
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("sample_input.txt"));

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
			N = Integer.parseInt(br.readLine());
			map = new int[N][N];
			
			
			StringTokenizer st = null;
			for(int i=0; i<N; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<N; ++j)
					map[i][j] = Integer.parseInt(st.nextToken()); 
			}
			
			ret = -1;
			for(int i=0; i<N-1; ++i) {
				for(int j=1; j<N-1; ++j) {
					visited = new boolean[N][N];
					isEat = new boolean[101];
                    // 시작 좌표 저장, 현재 좌표 방문 및 먹은 디저트 표시
					startR= i; startC= j;
					visited[i][j] = true;
					isEat[map[i][j]] = true;
					// 현재 좌표, 길이, 방향
					searchCafe(i, j, 1, 0);
					isEat[map[i][j]] = false;
					visited[i][j] = false;
				}
			}
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case+" ").append(ret);
			System.out.println(sb.toString());
		}
		
	}
	
	// r,c : 현재 좌표
	// dessert: 먹은 디저트 수
	// dir: 이동 방향
	private static void searchCafe(int r, int c, int dessert, int dir) {
		// 현재 방향부터 계속 이어나간다
		for(int i=dir; i<4; ++i) {
			int nr = r+dr[i];
			int nc = c+dc[i];
			// 출발 방향으로 돌아오고 먹은 디저트 개수가 2개 넘을 경우 갱신
			if(nr == startR && nc == startC && dessert > 2) {
				ret = Math.max(ret,  dessert);
				return;
			}
			// 범위를 벗어나거나 먹었거나 방문 했으면 방향 전환
			if(!(0<=nr && nr<N && 0<=nc && nc<N) || isEat[map[nr][nc]] || visited[nr][nc]) continue;
			
            // 백트래킹
			visited[nr][nc] = true;
			isEat[map[nr][nc]] = true;
			searchCafe(nr, nc, dessert+1, i);
			visited[nr][nc] = false;
			isEat[map[nr][nc]] = false;

		}
		
	}
	
}
