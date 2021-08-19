/*
처음에 백트래킹을 배웠기에 백트래킹으로 접근했다.
갈 수 있는 곳이면 가서 파이프를 설치하고 아니면 되돌아와서 다시 물렸다.
문제는 설치하고 나서 다음 행으로 넘어가기 위해 재귀함수를 종료시켜야 했는데 boolean 변수 하나를 둬서 해결했다.
쉽게 푼 것 같아 제출하니 시간초과가 나왔다.
아예 틀렸으면 모를까 시간초과라고 해서 어디를 고치면 될까 봤고 안되는 곳을 한 번 방문한 후에도 계속 같은 위치를 방문했다.
그래서 갈 수 없으면 visited=false 하지 않고 종료시켜버리도록 하니 정답을 맞았다.
파이프 설치가 안된다면 더 이상 탐색하지 않는 것이 핵심인듯 하다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	
	static int R,C;	// 행, 열
	static char map[][]; // 지도
	static boolean visited[][];	// 파이프가 있는지 여부
	
	static int dr[] = {-1,0,1};	// 오른쪽 위, 오른쪽, 오른쪽 아래
	static int dc[] = {1,1,1};
	
	static int cnt;
	
	private static boolean install_pipe1(int r, int c) {
		// 마지막 열에 도착했으면 설치했다는 의미로 is_Installed= true하고 종료
		if(c == C-1) {
			cnt++;
			return true;
		}
		
		for(int j=0; j<3; ++j) {
			int nr = r+dr[j];
			int nc = c+dc[j];

			// 다음 좌표가 범위를 벗어났거나 이미 파이프가 설치되었거나 건물이 있으면 다른 방향 탐색
			if(!(0<=nr && nr<R && 0<=nc && nc<C) || visited[nr][nc] || map[nr][nc] == 'x')
				continue;

			visited[nr][nc] = true;	// 파이프 설치
			
			if(install_pipe1(nr, nc))
				return true;
		}
		return false;
	}
	
	public static void main(String[] args) throws Exception{
		//System.setIn(new FileInputStream("sample_input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		
		map = new char[R][C];
		visited = new boolean[R][C];
		
		for(int i=0; i<R; ++i) {
			map[i] = br.readLine().toCharArray();
		}
		
		for(int i=0; i<R; ++i)
			install_pipe1(i, 0);	// 각 행의 0번째 열부터 탐색
		
		System.out.println(cnt);
	}
}


// 첫 풀이
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	
	static int R,C;	// 행, 열
	static char map[][]; // 지도
	static boolean visited[][];	// 파이프가 있는지 여부
	
	static int dr[] = {-1,0,1};
	static int dc[] = {1,1,1};
	
	static int cnt;
	static boolean is_Installed = false;
	
	private static void install_pipe(int r, int c) {
		// 마지막 열에 도착했으면 설치했다는 의미로 flag= true하고 종료
		if(c == C-1) {
			is_Installed = true;
			cnt++;
			return;
		}
		
		is_Installed = false;	// 종료 여부
		for(int j=0; j<3; ++j) {
			int nr = r+dr[j];
			int nc = c+dc[j];

			// 다음 좌표가 범위를 벗어났거나 이미 파이프가 설치되었거나 건물이 있으면 다른 방향 탐색
			if(!(0<=nr && nr<R && 0<=nc && nc<C) || visited[nr][nc] || map[nr][nc] == 'x')
				continue;

			visited[nr][nc] = true;	// 파이프 설치
			
			install_pipe(nr, nc);	// 다음 좌표 탐색
            // 여기서 더 갈 수 없으면 물려야 하고 갈 수 있으면 계속 가야함.
			// 갈 수 없다면 visited=false 하면 되고 마지막까지 도착했으면 어떻게 종료?
			// 핵심은 갈 수 있으면 계속 가서 그 경로를 표시해야함
			// 갈 수 없으면 다시 돌아와서 다른 경로를 탐색하면 됨. 근데 다 도착하면 아예 종료해버려야 하는데 그게 힘듬.
			// is_insatlled를 이용하여 다 찾았으면 리턴해서 종료시켜버림
			if (is_Installed)
				return;
		}

	}
	
	public static void main(String[] args) throws Exception{
		//System.setIn(new FileInputStream("sample_input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		
		map = new char[R][C];
		visited = new boolean[R][C];
		
		for(int i=0; i<R; ++i) {
			map[i] = br.readLine().toCharArray();
		}
		
		for(int i=0; i<R; ++i)
			install_pipe(i, 0);	// 각 행의 0번째 열부터 탐색
		
		System.out.println(cnt);
	}
}