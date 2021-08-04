/*
예전 같았으면 for문을 여러개 써서 경계 체크하고 이랬을 건데 
이제는 dy, dx를 활용해서 한 번에 끝낼 수 있다.
확실히 처음보단 실력이 많이 는 것 같긴 하다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {


	public static void main(String[] args) throws Exception {
		
		System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		for(int test_case = 1; test_case <= T; test_case++)
		{
			int N = Integer.parseInt(br.readLine());
			StringBuilder sb = new StringBuilder();
			
			int [][] arr = new int[N][N];
			int dy[] = {0,1,0,-1};
			int dx[] = {1,0,-1,0};
			
			int num = 1;
			
			int ny=0, nx=0, dir=0;
			arr[ny][nx] = num++;	// (0,0)은 1
			
			while(num <= N*N) {
				ny += dy[dir];
				nx += dx[dir];
				// 범위를 벗어나거나 0이 아니면 다시 돌아간 뒤 방향 전환
				if(!(0<=ny&&ny<N && 0<=nx&&nx<N) || arr[ny][nx] != 0) {
					ny -= dy[dir];
					nx -= dx[dir];
					dir = (dir+1)%4;
					continue;
				}
				
				arr[ny][nx] = num++;
			}
			
			for(int i=0; i<N; ++i) {
				for(int j=0; j<N; ++j)
					sb.append(arr[i][j]).append(' ');
				sb.append('\n');
			}
			sb.setLength(sb.length()-1);
			System.out.printf("#%d%n", test_case);
			System.out.println(sb);
		}
	}

}

