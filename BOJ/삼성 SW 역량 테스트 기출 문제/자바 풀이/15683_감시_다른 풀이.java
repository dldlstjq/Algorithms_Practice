/*
감시 방향을 미리 저장해놓고 푸는 방법이다.
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class BJ_15683_감시_sol {
	//상 우 하 좌
	final static int[] dr = {-1, 0, 1, 0};
	final static int[] dc = {0, 1, 0, -1};
	
	//각 cctv 번호의 방향 정보 cctvDirCase[ cctv 번호 ][ 방향 경우의 수 ]
	//cctvDirCase[ 2 ][ 1 ] : 2번 cctv의 1 경우의 수인 (좌, 우) 즉, { 1, 3}을 반환
	// {1, 3} 은 오른쪽, 왼쪽의 델타값 인덱스 의미
    static int[][][] cctvDirCase = {
            {},	//미사용인덱스
            {{0}, {1}, {2}, {3}}, // 1번 (상), (우), (하), (좌)
            {{0, 2}, {1, 3}}, // 2번		(상,하), (우,좌) 
            {{0, 1}, {1, 2}, {2, 3}, {3, 0}}, // 3번		(상,우), (우,하), (하,좌), (좌,상)
            {{0, 1, 2}, {1, 2, 3}, {2, 3, 0}, {3, 0, 1}}, // 4번	 (상,우,하), (우,하,좌), (하,좌,상), (좌,상,우)
            {{0, 1, 2, 3}}, // 5번	(상,우,하,좌)
    };
    
    static int minBlindCnt;	//사각지대 최솟값

	static int N,M;	//행열 크기
	static int[][] origin; //원본 정보
	static int[][] map; //사용할 배열
	
	static ArrayList<CCTV> cctv = new ArrayList<>();	//cctv 정보
	
	static int[] selectedDirCase;	//각 cctv의 경우의 수 선택정보
	
	static class CCTV{
		int r, c;
		int type;	//cctv 번호
		int caseCnt; // cctv 번호에 따른 방향 경우의 수 개수
		
		public CCTV(int r, int c, int type) {
			super();
			this.r = r;
			this.c = c;
			this.type = type;
			
			if(type==2) this.caseCnt = 2;	//2번 cctv 방향 경우의 수
			else if(type==5) this.caseCnt = 1;	//5번 cctv 방향 경우의 수
			else this.caseCnt = 4;	//나머지 cctv 방향 경우의 수
			
		}
	}
	
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		origin = new int[N][M];
		
		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<M; j++) {
				origin[i][j] = Integer.parseInt(st.nextToken());
				
				//cctv 정보 입력
				if(origin[i][j]!=0 && origin[i][j] !=6) cctv.add(new CCTV(i, j, origin[i][j]));
				
			}
		}
		
		selectedDirCase = new int[cctv.size()];
		
		minBlindCnt = Integer.MAX_VALUE;	//사각지대 개수 최소값 충분히 큰값으로 초기화
		
		permutation( 0 );
		
		System.out.println(minBlindCnt);//결과 출력

	}


	private static void permutation(int cnt) {
		//모든 cctv 방향 설정 완료
		if(cnt == cctv.size()) {
			
			copyArray();	//배열 복사
			
			watch();	//감시 영역 체크
			
			//사각지대 최솟값 비교
			minBlindCnt = Math.min(minBlindCnt, getCurBlindCnt());
			
			return;
		}
		
		
		for(int i=0; i < cctv.get(cnt).caseCnt; i++) {
			selectedDirCase[cnt] = i;	//cnt 인덱스 cctv의 경우의 수 설정
			permutation(cnt + 1);
			
		}
		
		
	}
	//현재 선택된 경우의 사각지대 개수 반환 메소드
	private static int getCurBlindCnt() {
		int cnt = 0;	//사각지대 개수
		
		for(int i=0; i< N;i ++) {
			for(int j=0; j<M; j++) {
				if(map[i][j] == 0) cnt++;
			}
		}
		
		return cnt;
	}


	//감시 영역 체크
	private static void watch() {
		
		//모든 cctv
		for(int i = 0; i<cctv.size(); i++) {
			CCTV cc = cctv.get(i);	//cctv 정보 받아오기
			int type = cc.type;
			
			//해당 cctv 선택된 경우의 수의 방향 검사
			for(int dir : cctvDirCase[ type ][ selectedDirCase[i]]) {
				//cctv 현재 위치
				int r = cc.r;
				int c = cc.c;
				
				while(true) {
					//이동
					r += dr[dir];
					c += dc[dir];
					
					//경계를 벗어나거나 6인 경우(벽인 경우)
					if(r<0 || r>=N || c<0 || c>=M || map[r][c] == 6) break;
					
					
					map[r][c] = -1;	//감시영역 마킹
					
				}
				
			}
			
		}
		
	}


	private static void copyArray() {
		// TODO Auto-generated method stub
		map = new int[N][];
		
		for(int i=0; i<N;i++) {
			map[i] = origin[i].clone();
		}
		
	}
}