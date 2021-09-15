/*
바깥쪽 공기와 접하는 치즈만 녹기 때문에 안쪽 공기와 접하는 치즈는 녹으면 안된다.
그래서 바깥쪽, 안쪽 공기를 구분해야 하는데 처음엔 바깥쪽 공기를 2로 만들어서 구분했다.
하지만 굳이 구분할 필요 없이 제일 바깥 경계는 치즈가 없기 때문에 0,0부터 시작해서 공기인 부분을 dfs로 탐색하고 치즈인 부분은 따로 큐에 저장했다.
dfs가 끝나면 큐에 저장된 치즈를 녹이고 갯수를 체크한 뒤 다시 바깥쪽부터 탐색하면 된다.

코드를 더 줄이는 방법은 큐에 저장하지 않고 바깥쪽 치즈면 바로 녹이면 된다.
그러면 탐색코드 하나만으로도 녹이는 것까지 완료가 돼서 더 깔끔한 코드가 나오는 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	
	static class Pos{
		int r, c;
		Pos(int r, int c){
			this.r=r;
			this.c=c;
		}
	}
	
	static int R, C;
	static int arr[][];
	
	static int cheeze;	// 초기 치즈 개수
	static int time;	// 모두 녹아서 없어지늗데 걸리는 시간
	static int cnt;	// 한시간 전 남은 치즈 조각
	
	static boolean visited[][];
	static int dr[] = {-1,0,1,0};
	static int dc[] = {0,1,0,-1};
	
	// 바깥쪽 공기를 탐색
	private static void outsideAir(int r, int c) {
		for(int i=0; i<4; ++i) {
			int nr = r+dr[i];
			int nc = c+dc[i];
			
			// 범위 아웃이거나 방문 했으면 패스
            if(nr<0 || nr>=R || nc<0 || nc>=C || visited[nr][nc])
                continue;
            
            visited[nr][nc] = true;
            // 저장하지 않고 바로 없애고 치즈를 1 감소시켜도 무방.
            if(arr[nr][nc] == 1) {
            	arr[nr][nc] = 0;
            	cheeze--;
            }
            // 바깥쪽 공기이면 계속 탐색
            else
            	outsideAir(nr, nc);
		}
	}
	
	public static void main(String[] args) throws Exception{
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		R =Integer.parseInt(st.nextToken());
		C =Integer.parseInt(st.nextToken());
		
		arr = new int[R][C];
		
		for(int i=0; i<R; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<C; ++j) {
				arr[i][j] = Integer.parseInt(st.nextToken());
				if(arr[i][j] == 1)
					cheeze++;
			}
		}
		
		int prevCheeze = 0;
		while(cheeze > 0) {
			time++;
			prevCheeze = cheeze;
			// 가장 바깥쪽인 0,0은 치즈가 없는 부분. 탐색 시작
			visited = new boolean[R][C];
			visited[0][0] = true;
			outsideAir(0, 0);
		}
		
		System.out.println(time);
		System.out.println(prevCheeze);
	}
}
