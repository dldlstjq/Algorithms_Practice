/*
1이 있는 곳부터 시작해서 재귀를 이용해 2를 만나면 그만두는 방식으로 풀었다.
하지만 2부터 시작해서 거꾸로 올라가는 것도 되게 괜찮은 방법인 것 같다.
거꾸로 생각하는 것을 다시 한번 깨달을 수 있는 문제였다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main_1210_이인섭 {
	
	static int dy[] = {0,0,1};	// 오른쪽, 왼쪽, 아래 순으로 검색
	static int dx[] = {1,-1,0};
	static boolean[][] visited;
	static int map[][] = new int[100][100];
	static int ret;
	static boolean flag;
	
	static void check(int start, int y, int x) {
		if(map[y][x] == 2) {
			ret = start;
			flag = true;
			return;	
		}
	
		for(int d=0; d<3; ++d) {
			int ny = y+dy[d];
			int nx = x+dx[d];

			if(!(0<=ny && ny <100 &&0<=nx && nx <100 ) || map[ny][nx]==0
				|| visited[ny][nx])
				continue;

			visited[ny][nx]=true;
			check(start, ny, nx);
			visited[ny][nx]=false;
			
			// 다른 방향 탐색을 하지 않고 바로 종료해야 한다.
			break;
		}
		
	}

	public static void main(String[] args) throws IOException {
		
		System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		for(int test_case = 1; test_case <= 10; test_case++)
		{
			int a = Integer.parseInt(br.readLine());
			// 초기화
			ret = 0;	
			flag = false;
			visited = new boolean[100][100];
			
			for(int i=0; i<100; ++i) {
				st = new StringTokenizer(br.readLine(), " ");
				for(int j=0; j<100; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			for(int i=0; i<100; ++i) {
				if(map[0][i] == 1)
					check(i, 0, i);
				if(flag)
					break;
			}
			
			StringBuilder sb = new StringBuilder();	// 정답 출력
			sb.append("#").append(a).append(" "+ret);
			System.out.println(sb.toString());
		}
	}
	 
}
