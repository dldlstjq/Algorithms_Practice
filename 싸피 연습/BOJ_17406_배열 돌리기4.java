/*
기존 배열돌리기 1에 순열까지 추가된 문제이다.
순열로 모든 경우의 연산 정보를 구하여 이를 토대로 배열을 회전시켜 답을 구하면 된다.
배열을 돌릴줄만 알면 해결할 수 있는데 인덱스 설정을 잘 해야한다.
또한 원본 배열이 아닌 임시배열을 따로 만들어야 나중에 다른 케이스일 때 정확한 값이 나온다.
배열 돌리기는 이번 기회에 마스터해서 더는 헷갈릴 일 없게 하자.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

class Info{
	int r; 
	int c;
	int s;
	public Info(int r, int c, int s) {
		super();
		this.r = r;
		this.c = c;
		this.s = s;
	}
}

public class Main {
	
	static int N, M, K;
	static int[][] A;	// 원본 배열
	static int[][] tmp;	// 임시 배열
	static Info[] op;		// 회전연산 정보 저장
	static Info[] arr;		// 연산 정보 순열로 저장
	static boolean[] visited;		// 연산 정보 순열로 저장
	
	static int dr[] = {1,0,-1,0};
	static int dc[] = {0,1,0,-1};
	
	static int ret = Integer.MAX_VALUE; 	// 최종 정답
	
	static void rotate() {
		for(int i=0; i<arr.length; ++i) {
			// 시작과 끝 좌표의 중간 지점 좌표일 때 까지 반복
			int a = arr[i].r-arr[i].s;
			int b = arr[i].r+arr[i].s;
			int mid = (a+b)/2;
			
			for(int j=0;  ; ++j) {
				int r = arr[i].r-arr[i].s + j;	// 최초 시작 좌표
				int c = arr[i].c-arr[i].s + j;
				
				// r 값이 크기 중앙에 오면 종료
				if(r == mid)
					break;
				
				int dir = 0;	// 하 방향
				// 경계 체크 위한 시작, 끝 좌표
				int start_r = r;
				int start_c = c;
				int end_r = arr[i].r+arr[i].s - j;
				int end_c = arr[i].c+arr[i].s - j;
				
				int temp = tmp[r][c];
				// 방향전환 4번 전까지
				while(dir<4) {
					// 다음 좌표
					int nr = r+dr[dir];
					int nc = c+dc[dir];

					// 경계 내에 있다면?
					if(nr>=start_r && nr<=end_r && nc>=start_c && nc<=end_c) {
						// 다음 값을 현재 위치에 넣어주기
						tmp[r][c] = tmp[nr][nc];

						// 다음 위치로 이동
						r = nr;
						c = nc;
					}
					// 경계 밖에 있다면?
					else {
						dir++;
					}
				}
				tmp[start_r][start_c+1] = temp;
//				print();
//				System.out.println();
			}
		}
	}
	
	// 각 행의 최솟값 저장
	static void calc() {
		
		for(int i=1; i<=N; ++i) {
			int sum = 0;
			for(int j=1; j<=M; ++j) {
				sum += tmp[i][j];
			}
			ret = Math.min(ret, sum);
		}
	}
	
	static void print() {
		for(int i=1; i<=N; ++i) {
			for(int j=1; j<=M; ++j) {
				System.out.print(tmp[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	static void perm(int idx) {
		// 회전 연산 계산
		if(idx == K) {
			for(int k=1; k<=N; ++k)
				tmp[k] = A[k].clone();
			// arr에 연산 정보가 저장되어 있음.
			rotate();
			
//			print();
//			System.out.println();
			// 최솟값 계산
			calc();
			return;
		}
			
			
		for(int i=0; i<K; ++i) {
			if(visited[i])	continue;
			arr[idx] = op[i];
			visited[i] = true;
			perm(idx+1);
			visited[i] = false;
		}
	}
	
	public static void main(String[] args) throws Exception{
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		
		A = new int[N+1][M+1];
		tmp = new int[N+1][M+1];
		
		visited = new boolean[K];
		op = new Info[K];
		arr = new Info[K];
		
		for(int i=1; i<=N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=1; j<=M; ++j) {
				A[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		// 회전 연산 정보 저장
		for(int i=0; i<K; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			int r = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			int s = Integer.parseInt(st.nextToken());
			op[i] = new Info(r,c,s);
		}
		
		// 회전 연산 정보를 순열로 해서 하나씩 계산
		perm(0);
		
		System.out.println(ret);
	}

}