/*
배열 반전, 회전 등을 연습하기 좋은 문제인 것 같다.
반전은 인덱스 설정만 하면 쉽게 할 수 있고 회전이 문제였는데
r, c라는 인덱스를 하나 더 줘서 돌아가게 설정했다.
이건 다른 사람들 풀이를 보면서 좀 더 간단하고 쉬운 방법을 찾아서 내것으로 만들어야겠다.
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {
	
	static int N,M,R;
	static int[][] arr = new int[100][100];
	static int[][] tmp = new int[100][100];
	static int[] order;
	
	
	static void copy() {
		for(int i=0; i<N; ++i)
			tmp[i] = arr[i].clone();
	}
	
	// 상하 반전
	static void Rotate_One() {
		for(int i=0; i<M; ++i) {
			for(int j=0; j<N; ++j) {
				arr[N-1-j][i] = tmp[j][i];
			}
		}
	}
	
	// 좌우 반전
	static void Rotate_Two() {
		for(int i=0; i<N; ++i) {
			for(int j=0; j<M; ++j) {
				arr[i][M-1-j] = tmp[i][j];
			}
		}
	}
	
	// 오른족으로 90도 회전
	static void Rotate_Three() {
		int r=0, c=N-1;
		for(int i=0; i<N; ++i) {
			for(int j=0; j<M; ++j) {
				arr[r++][c] = tmp[i][j];
			}
			c--;
			r=0;
		}
		// 회전했으므로 N과 M을 서로 교환
		int box=N;
		N=M;
		M=box;
	}
	
	// 왼쪽으로 90도 회전
	static void Rotate_Four() {
		int r=M-1, c=0;
		for(int i=0; i<N; ++i) {
			for(int j=0; j<M; ++j) {
				arr[r--][c] = tmp[i][j];
			}
			c++;
			r=M-1;
		}
		// 회전했으므로 N과 M을 서로 교환
		int box=N;
		N=M;
		M=box;
	}
	
	// N/2 x M/2로 나눠어 시계방향 이동
	static void Rotate_Five() {
		// 상위 행 2개
		for(int i=0; i<N/2; ++i) {
			for(int j=0; j<M/2; ++j) 
				arr[i][j+M/2] = tmp[i][j];
			
			for(int j=M/2; j<M; ++j) 
				arr[i+N/2][j] = tmp[i][j];
		}
		
		// 하위 행 2개
		for(int i=N/2; i<N; ++i) {
			for(int j=0; j<M/2; ++j) 
				arr[i-N/2][j] = tmp[i][j];
			
			for(int j=M/2; j<M; ++j) 
				arr[i][j-M/2] = tmp[i][j];
		}
	}
	
	// N/2 x M/2로 나눠어 반시계방향 이동
		static void Rotate_Six() {
			// 상위 행 2개
			for(int i=0; i<N/2; ++i) {
				for(int j=0; j<M/2; ++j) 
					arr[i+N/2][j] = tmp[i][j];
				
				for(int j=M/2; j<M; ++j) 
					arr[i][j-M/2] = tmp[i][j];
			}
			
			// 하위 행 2개
			for(int i=N/2; i<N; ++i) {
				for(int j=0; j<M/2; ++j) 
					arr[i][j+M/2] = tmp[i][j];
				
				for(int j=M/2; j<M; ++j) 
					arr[i-N/2][j] = tmp[i][j];
			}
		}
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		R = Integer.parseInt(st.nextToken());
		
		order = new int[R];
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<M; ++j) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		st = new StringTokenizer(br.readLine(), " ");
		for(int i=0; i<R; ++i) 
			order[i] = Integer.parseInt(st.nextToken());
			
		// 명령 실행
		for(int i=0; i<R; ++i) {
			copy();	// 실행 전 항상 arr를 tmp로 복사
			switch(order[i]) {
			case 1:Rotate_One();break;
			case 2:Rotate_Two();break;
			case 3:Rotate_Three();break;
			case 4:Rotate_Four();break;
			case 5:Rotate_Five();break;
			case 6:Rotate_Six();break;
			}
		}
		
		StringBuilder sb = new StringBuilder();
		for(int i=0; i<N; ++i) {
			for(int j=0; j<M; ++j) {
				sb.append(arr[i][j] + " ");
			}
			sb.append('\n');
		}
		System.out.println(sb);
	}
}