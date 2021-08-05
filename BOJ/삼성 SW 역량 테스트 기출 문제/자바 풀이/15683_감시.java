/*
많이 헤맨 끝에 끝내 풀 수 있었다.
cctv 번호에 따라 감시할 수 있는 방법이 다르고 회전까지 가능하므로 가능한 모든 경우의 수 중 최소를 구해야 한다.
결국 재귀를 써야하는데 핵심은 한 번 감시 영역을 배열에 체크한 후에 최소 영역을 계산하고 체크하기 이전 배열 값을 가져와야 한다는 것이다.
그러기 위해서 클론을 써서 2차원 배열 전체를 복사했는데 같은 주소값을 가리켜
하나를 수정해도 두 개가 동시에 수정이 되는 문제가 발생했다.
왜 그런지는 정확하게 모르겠지만 1차원 배열로 하나씩 클론을 하니 다른 주소값을 가리켜
동시에 수정이 되는 문제가 해결됐다. 
이것때문에 시간을 많이 잡아먹었는데 어찌됐든 안된다는 것을 알았기에 이런 실수를 안할 것 같다.
코드 역시 중복되는 부분이 있으면 함수로 만들어서 간결하게 처리하는 습관을 들여야겠다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {
	
	static int N,M;
	static int dy[] = {-1,0,1,0};
	static int dx[] = {0,1,0,-1};
	static int point[][];	// cctv 위치 저장
	static int cnt = 0;		// cctv 개수
	static int ret = Integer.MAX_VALUE;	// 정답 저장
	
	// 사각지대 확인
	static void validate(int[][] arr) {
		int black_site = 0;	//사각지대 개수
		for(int i=0; i<N; ++i) 
			for(int j=0; j<M; ++j) 
				if(arr[i][j]== 0) 
					black_site++;
				
		ret = Math.min(ret, black_site)	;
	}
	
	// cctv로 감시할 수 있는 범위 체크
	static int[][] check_cctv(int y, int x, int dir, int[][] ary) {
		int ny = y, nx = x;
		while(true) {
			ny += dy[dir];
			nx += dx[dir];
			
			// 범위 벗어나거나 벽이 있으면 종료
			if(!(0<=ny&&ny<N && 0<=nx&&nx<M) || ary[ny][nx] == 6)
				break;
			
			// 0인 부분 -1로 해서 감시 표시
			if(ary[ny][nx] == 0)
				ary[ny][nx] = -1;
		}
		return ary;
	}
	
	static void solve(int idx, int[][] arr) {
		// 모든 cctv로 감시 체크하면 사각지대 확인
		if(idx == cnt) {
			validate(arr);
			return;
		}
		
		int y = point[idx][0];
		int x = point[idx][1];
		
		// 배열 복사. 2차원 배열을 그대로 클론하면 똑같은 주소값을 가리켜 값이 같이 수정된다.
		// 1차원 배열을 하나씩 클론해야 하나를 수정해도 다른 하나가 값이 바뀌지 않음.
		int [][] tmp = new int[N][M];
		for(int i=0; i<N; ++i) 
			tmp[i] = arr[i].clone();
	
		
		if(arr[y][x] == 1){
			// 1번은 한 쪽 방향으로 4군데 체크
			for(int i=0; i<4; ++i) {
				arr = check_cctv(y, x, i, arr);
				solve(idx+1, arr);
				for(int k=0; k<N; ++k) 
					arr[k] = tmp[k].clone();
			}
		}
		
		else if(arr[y][x] ==2) {
			// 2번은 상하, 좌우 2번 체크
			for(int i=0; i<2; ++i) {
				for(int j=i; j<4; j+=2) {
					arr = check_cctv(y, x, j, arr);
				}
				
				solve(idx+1, arr);
				for(int k=0; k<N; ++k) 
					arr[k] = tmp[k].clone();
			}
		}
		
		else if(arr[y][x] ==3) {
			// 3번은 0 1, 1 2, 2 3, 3 0 4번 체크
			for(int i=0; i<4; ++i) {
				arr = check_cctv(y, x, i, arr);
				arr = check_cctv(y, x, (i+1)%4, arr);
				solve(idx+1, arr);
				for(int k=0; k<N; ++k) 
					arr[k] = tmp[k].clone();
			}
		}
		
		else if(arr[y][x] ==4) {
			// 4번: 3 0 1, 0 1 2, 1 2 3, 2 3 0 4번 체크
			for(int i=0; i<4; ++i) {
				arr = check_cctv(y, x, i, arr);
				arr = check_cctv(y, x, (i+1)%4, arr);
				arr = check_cctv(y, x, (i+3)%4, arr);
				solve(idx+1, arr);
				for(int k=0; k<N; ++k) 
					arr[k] = tmp[k].clone();
			}
		}
		
		else if(arr[y][x] == 5) {
			// 5번 4방향 모두 체크
			for(int i=0; i<4; ++i) {
				arr = check_cctv(y, x, i, arr);
			}
			solve(idx+1, arr);
			for(int k=0; k<N; ++k) 
				arr[k] = tmp[k].clone();
		}
		
		
	}

	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		int[][] office = new int[N][M];
		
		
		// 입력 받음과 동시에 cctv 개수 cnt에 저장
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<M; ++j) {
				office[i][j] = Integer.parseInt(st.nextToken());
				if(office[i][j] == 1 || office[i][j] == 2 || office[i][j] == 3 || office[i][j] == 4 || office[i][j] == 5) {
					cnt++;
				}
					
			}
				
		}
		
		// cnt 만큼 배열 크기 잡아서 cctv 좌표를 point에 저장
		point = new int[cnt][2];
		int k = 0;
		for(int i=0; i<N; ++i) 
			for(int j=0; j<M; ++j) {
				if(office[i][j] == 1 || office[i][j] == 2 || office[i][j] == 3 || office[i][j] == 4 || office[i][j] == 5) {
					point[k][0] = i;
					point[k++][1] = j;
				}
					
			}
				
		solve(0, office);
		System.out.println(ret);
	}

}