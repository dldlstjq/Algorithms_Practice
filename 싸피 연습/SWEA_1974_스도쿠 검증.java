/*
한 행, 한 열, 각 사각형마다 숫자가 있는지 없는지 체크하면 된다.
처음에 백트래킹으로 스도쿠 풀 때 풀이가 머릿속에 남아 있어 각 행, 열 ,사각형에 숫자가 있는지를 나타내는 2차원 배열 3개를 써서 풀었다.
좀 이해하기 쉽지 않을 것 같아 새로 해보려고 했는데 생각이 잘 안났다.
교수님께서 설명하시는 걸 보고 한 행, 한 열, 한 사각형 마다 따로 메소드를 만들어 검사해주면 끝났다.
*/

// 교수님 풀이
import java.util.Scanner;

public class 스도쿠검증 {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		for(int tc = 1; tc <= T; tc++) {
			for(int i = 0; i < 9; i++) {
				for(int j = 0; j < 9; j++)
					map[i][j] = sc.nextInt();
			}
			int ans = check();
			System.out.println("#" + tc + " " + ans);
		}
		
		//10칸짜리 배열(체크배열)을 만들어서 1번칸부터 9번칸까지를 
		//각각 1부터9가 존재했었는지 체크하는 공간으로 활용
		
		//행을 검사할때, 각 칸에서 만나는 숫자마다, 체크배열에 나를 위한 칸에 이미 체크가 있으면 false
		
		
		//0행부터 8행까지 모두
		//	한 행에 1부터9가 고루 있는지 검사
		//0열부터 8열까지 모두
		//	한 열에 1부터9가 고루 있는지 검사
	}
	static int check() {
		for(int i = 0; i < 9; i++) {
			//i행과 i열이 정상인지 검사
			if( !rowCheck(i) ) {
				return 0;
			}
			if( !colCheck(i) ) {
				return 0;
			}
		}
		//block검사.
		for(int i = 0; i < 9; i += 3 ) {
			for(int j = 0; j < 9; j += 3) {
				if( !blockCheck(i, j) )
					return 0;
			}
		}
		return 1;
	}
	
	static int[][] map = new int[9][9];
	static boolean rowCheck(int row) {
		boolean[] check = new boolean[10];
		for(int i = 0; i < 9; i++) {
			if( check[ map[row][i] ] )
				return false;
			else
				check[ map[row][i] ] = true;
		}
		return true;
	}
	
	static boolean colCheck(int col) {
		boolean[] check = new boolean[10];
		for(int i = 0; i < 9; i++) {
			if( check[ map[i][col] ] )
				return false;
			else
				check[ map[i][col] ] = true;
		}
		return true;
	}
	//r,c를 시작 행, 시작 열로 하는 블록이 괜찮은지 검사.
	static boolean blockCheck(int r, int c) {
		boolean[] check = new boolean[10];
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if( check[ map[r+i][c+j] ] )
					return false;
				else
					check[ map[r+i][c+j] ] = true;
			}
		}
		return true;
	}
}



// 내 풀이
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

class Solution
{
	public static void main(String args[]) throws Exception
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int T = Integer.parseInt(br.readLine());
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			int sudoku[][] = new int[9][9];
			boolean row[][] = new boolean[10][10];
			boolean col[][] = new boolean[10][10];
			boolean square[][] = new boolean[10][10];
			
			for(int i=0; i<9; ++i) {
				StringTokenizer st = new StringTokenizer(br.readLine()," ");
				for(int j=0; j<9; ++j) {
					sudoku[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			int tmp = 1;
			outer:
			for(int i=0; i<9; ++i) {
				for(int j=0; j<9; ++j) {
					int num = sudoku[i][j];
					if(row[i][num] || col[j][num] || square[i/3*3+j/3][num]) {
						tmp = 0;
						break outer;
					}
					row[i][num] = true;
					col[j][num] = true;
					square[i/3*3+j/3][num] = true;
				}
			}
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case+" "+tmp);
			System.out.println(sb);
		}
	}
}
