/*
싸피에서 풀었던 걸 다시 풀어봤다.
처음에 너무 쉽게 생각했던 건지 8%에서 계속 틀렸다.
백트래킹인것 같아 visited=false로 계속 바꿨는데도 답이 안나왔다.
그냥 틀리기도 하고 시간초과도 나왔다.

1. 한 번 경로를 찾으면 바로 종료
2. 이동한 경로로 파이프라인을 설치하지 못하면 false 처리를 하면 안된다.
-> 한번 갔을 때 경로가 없는데 false 처리 해버리면 다음에 또 방문하기 때문에 시간초과가 나는 것 같다.
3. 대각선 오른쪽 위, 오른쪽, 오른쪽 아래 순서로 방문해야 된다.
위 두가지만 알고 있으면 문제는 쉽게 풀리는 것 같다.

1을 해결하기 위해 ok라는 boolean 변수를 뒀다. 재귀가 끝나고 다시 돌아왔을 떄 ok=true이면 return 해버리면 된다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	
	static int R,C;
	static char[][] map;
	static boolean[][] visited;
	static boolean ok;
	
	static int dr[]= {-1,0,1};
	
	static int ret;
	
	public static void main(String[] args) throws Exception {
//		System.setIn(new FileInputStream("sample_input.txt"));
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st= new StringTokenizer(br.readLine());
		
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		
		map = new char[R][C];
		visited = new boolean[R][C];
		
		for(int i=0; i<R; ++i) 
			map[i] = br.readLine().toCharArray();
		
		for(int i=0; i<R; ++i) {
            ok = false;
			findPath(i, 0);
		}
		
		System.out.println(ret);
		
	}

	private static void findPath(int r, int c) {
		visited[r][c] = true;
		if(c == C-1) {
			ret++;
			ok = true;
			return;
		}
		
		for(int i=0; i<3; ++i) {
			int nr = r+dr[i];
			int nc = c+1;
			
			if(!(0<=nr&&nr<R && 0<=nc&&nc<C) || visited[nr][nc] || map[nr][nc] == 'x') continue;
			
			findPath(nr, nc);
			if(ok) return;
			
 		}
	}
}
