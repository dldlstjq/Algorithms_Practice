/*
c++ 코드를 자바로 옮겨봤는데 변수 선언, 입력 방법을 제외하면 큰 차이가 없다.
*/

import java.io.*;
import java.util.StringTokenizer;

public class Main {

	static final int MAX = 50+3;
	static int N,M;
	static int r,c,d;
	static int[][] map = new int[MAX][MAX];

	static int[] dy = { -1,0,1,0 };
	static int[] dx = { 0,1,0,-1 };
	
	static int ret;
	
	static void clean() {
	    // 현재 위치 청소
	    map[r][c] = 2;
	    ret++;
	    while (true) {
	        int i = 0;
	        for (i = 0; i < 4; ++i) {
	            int dir = (d + 3) % 4;

	            // 범위 조건도 추가
	            if (!(0 <= r + dy[dir] && r + dy[dir] < N && 0 <= c + dx[dir] && c + dx[dir] < M))
	                continue;

	            // 왼쪽 방향 검사. 청소하지 않았으면 회전한 다음 한칸 전진
	            if (map[r + dy[dir]][c + dx[dir]] == 0) {
	                d = (d + 3) % 4;
	                r += dy[d];
	                c += dx[d];
	                map[r][c] = 2;
	                ret++;
	                break;
	            }

	            // 왼쪽 방향 갈 수 없으면 회전 후 다시 조사
	            else if (map[r + dy[dir]][c + dx[dir]] != 0)
	                d = (d + 3) % 4;
	                continue;

	        }
	        
	        // 네 방향 모두 청소되었을 때 
	        if (i == 4) {
	            // 후진 방향이 벽이면 종료
	            if (map[r - dy[d]][c - dx[d]] == 1)
	                break;
	            r -= dy[d];
	            c -= dx[d];
	        }  
	    }
	}
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		st = new StringTokenizer(br.readLine(), " ");
		r = Integer.parseInt(st.nextToken());
		c = Integer.parseInt(st.nextToken());
		d = Integer.parseInt(st.nextToken());
		
		 for (int i = 0; i < N; ++i) {
			 st = new StringTokenizer(br.readLine(), " ");
		     for (int j = 0; j < M; ++j)
		            map[i][j]=Integer.parseInt(st.nextToken());
		 }
		 
		 clean();
		 System.out.println(ret);
		
	}
}