/*
구현 문제에 많이 나오는 배열돌리기 인 것 같다.
삼성 코테 칠 때도 배열 돌리는 문제가 나왔는제 제대로 안돌아가서 해결하지 못했다.
이 문제 역시 1시간 더 걸려서 겨우 풀었는데 규칙을 빨리 잘 찾아야한다.
min(N, M) mod 2 = 0 조건으로 인해 애매한 경우는 생기지 않는다.
이걸 처음에 파악하지 못해 종료조건 설정에 애를 먹었고 배열 회전 역시 인덱스 설정이 힘들었다.
다른 사람 풀이를 보며 더 편한 방법을 찾아야겠다.
내가 푼 풀이보다 방향 설정한게 시간이 더 적게 걸린다.
*/

// 다른 풀이 820ms
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	
	static int N, M, R;
	static int[][] A;	// 원본 배열
	static int dr[] = {0,1,0,-1};
	static int dc[] = {1,0,-1,0};
	
	static void rotate() {
		for(int s=0; s < Math.min(N, M)/2; s++) {
			// 현재 위치
			int r = s;
			int c = s;
			int dir = 0;	// 우 방향
			
			int temp = A[r][c];	// 첫번째 값 저장
			
			// 방향전환 4번 전까지
			while(dir<4) {
				// 다음 좌표
				int nr = r+dr[dir];
				int nc = c+dc[dir];
				
				// 경계 내에 있다면?
				if(nr>=s && nr<N-s && nc>=s && nc<M-s) {
					// 다음 값을 현재 위치에 넣어주기
					A[r][c] = A[nr][nc];
					
					// 다음 위치로 이동
					r = nr;
					c = nc;
				}
				// 경계 밖에 있다면?
				else {
					dir++;
				}
			}
			A[s+1][s] = temp;
		}
	}
	
	public static void main(String[] args) throws Exception{
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		R = Integer.parseInt(st.nextToken());
		
		A = new int[N][M];
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<M; ++j) {
				A[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		// R번 회전
		for(int i=0; i<R; ++i) 
			rotate();
		
		
		StringBuilder sb = new StringBuilder();
		for(int i=0; i<N; ++i) {
			for(int j=0; j<M; ++j) {
				sb.append(A[i][j]+ " ");
			}
			sb.append('\n');
		}
		System.out.println(sb);
	}
}



// 내 풀이 1080ms
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	
	static int N, M, R;
	static int[][] A;	// 원본 배열
	
	// (r,c) 위치, r_length= 행 길이, c_length= 열 길이
	static void rotate(int r, int c, int r_length, int c_length, int size) {
		if(r == size || c == size)
			return;
		
		// 첫번째 행
		int tmp = A[r][c];	// 시작 위치
		for(int k=c+1; k<c_length; ++k) {
			A[r][k-1] = A[r][k];
		}
		
		// 마지막 열
		for(int k=r+1; k<r_length; ++k) {
			A[k-1][c_length-1] = A[k][c_length-1];
		}	

		// 마지막 행
		for(int k=c_length-1; k>c; --k) {
			A[r_length-1][k] = A[r_length-1][k-1];
		}
		
		// 첫번째 열
		for(int k=r_length-1; k>r; --k) {
			A[k][c] = A[k-1][c];
		}
		A[r+1][c] = tmp;	// tmp에 저장해둔 (r,c)를 (r+1, c)에 넣어줌.
		
		rotate(r+1, c+1, r_length-1, c_length-1, size);
	}
	
	public static void main(String[] args) throws Exception{
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		R = Integer.parseInt(st.nextToken());
		
		A = new int[N][M];
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<M; ++j) {
				A[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		int size = (int)Math.min(N, M)/2;
		// R번 회전
		for(int i=0; i<R; ++i) 
			rotate(0, 0, N, M, size);
		
		
		StringBuilder sb = new StringBuilder();
		for(int i=0; i<N; ++i) {
			for(int j=0; j<M; ++j) {
				sb.append(A[i][j]+ " ");
			}
			sb.append('\n');
		}
		System.out.println(sb);
	}
}

