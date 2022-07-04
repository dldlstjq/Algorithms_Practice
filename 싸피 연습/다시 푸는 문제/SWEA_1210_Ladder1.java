/*
도착지점이 한군데 밖에 없기 때문에 2부터 시작해서 거꾸로 올라갔다.
bfs로 해도 될것 같아서 해봤는데 사다리타기는 하나를 계속 타고 올라가야해서 dfs로 풀어보니까 답이 나왔다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Solution {
	
	static int map[][];
	static boolean visited[][];
	static int rr, rc;
	static int dr[]= {0,0,-1};
	static int dc[]= {-1,1,0};
	static int ret;
    
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("input.txt"));
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		for(int test_case = 1; test_case <= 10; test_case++)
		{
			ret = 0;
			map = new int[100][100];
			visited = new boolean[100][100];
			
			int n = Integer.parseInt(br.readLine());
			
			for(int i=0; i<100; ++i) {
				StringTokenizer st= new StringTokenizer(br.readLine());
				for(int j=0; j<100; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
					if(map[i][j] == 2) {
						rr = i;
						rc = j;
					}
				}
			}
			
			ret = dfs(rr, rc);
			
			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(ret);
			System.out.println(sb);
			
		}
	}

	static int dfs(int r, int c) {
		if(r==0) {
			return c;
		}
		visited[r][c] = true;
		for(int i=0; i<3; ++i) {
			int nr = r+dr[i];
			int nc = c+dc[i];
			
			if(!(0<=nr&&nr<100 && 0<=nc&&nc<100)) continue;
			if(map[nr][nc] == 0 || visited[nr][nc]) continue;
		
			return dfs(nr, nc);
		}
		return 0;
	}
}