/*
완전 탐색을 처음 공부할 때 스도쿠 문제 이해가 잘 안되어 꽤나 고생했는데 이제는 어떻게 접근해야 하는지 잘 알것 같다.
빈 칸에 1~9 중 하나를 넣는데 가로, 세로, 3x3 사각형에 겹치는 숫자가 하나도 없어야 한다.
넣고 다음 칸을 탐색하는데 1~9가 다 겹치면 이전 칸으로 와서 다시 다른 숫자를 넣는 백트래킹 방식을 사용한다.

가로, 세로, 3x3 사각형을 따로 배열로 만들어 저장하면 시간은 좀더 빠른데 메모리를 차지하는 것 같고
sudoku 맵 자체를 검사하는건 시간이 조금 더 걸리는 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
	
	static int[][] sudoku = new int[9][9];
	static boolean[][] row = new boolean[10][10];	// 가로 방향 row[i][j]: i행에 1~9 중에 숫자가 있다.
	static boolean[][] col = new boolean[10][10];	// 세로 방향 col[i][j]: i열에 1~9 중에 숫자가 있다.
	static boolean[][] square = new boolean[10][10];	// 3x3 사각형 square[i][j]: i번째 사각형에 1~9 중에 숫자가 있다.

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		for(int i=0; i<9; ++i) {
			char[] ch = br.readLine().toCharArray();
			for(int j=0; j<9; ++j) {
				sudoku[i][j] = ch[j]-'0';
				if(sudoku[i][j] != 0) {
					row[i][sudoku[i][j]] = true;	// 가로 방향 숫자 표시
					col[j][sudoku[i][j]] = true;	// 세로 방향 숫자 표시
					square[(i/3)*3+(j/3)][sudoku[i][j]] = true;	// 사각형 숫자 표시
				}
			}
		}
		
		play(0);
	}

	private static void play(int num) {
		// 종료조건
		if(num == 81) {
			print();
			System.exit(0);	// 종료
		}
		
		int r = num/9;
		int c=  num%9;
		
		// 해당 칸에 숫자가 0이면 1~9까지 하나씩 넣어본다.
		if(sudoku[r][c] == 0) {
			// 1~9중에서 없는 숫자를 넣는다.
			for(int i=1; i<=9; ++i) {
				// 행, 열, 3x3 사각형 안에 없는 숫자를 넣는다.
				if(!row[r][i] && !col[c][i] && !square[(r/3)*3+(c/3)][i]) {
					row[r][i] = true;
					col[c][i] = true;
					square[(r/3)*3+(c/3)][i] = true;
					sudoku[r][c] = i;
					play(num+1);
					row[r][i] = false;
					col[c][i] = false;
					square[(r/3)*3+(c/3)][i] = false;
					sudoku[r][c] = 0;
				}
			}
		}
		// 숫자가 없으면 다음 칸 탐색
		else
			play(num+1);
	}

	private static void print() {
		StringBuilder sb  = new StringBuilder();
		for(int i=0; i<9; ++i) {
			for(int j=0; j<9; ++j) {
				sb.append(sudoku[i][j]);
			}
			sb.append('\n');
		}
		System.out.println(sb);
	}
}




// 배열 사용하지 않고 sudoku 자체를 탐색하는 방법
import java.io.BufferedReader;
import java.io.InputStreamReader;


public class Main {
	
	static int[][] sudoku = new int[9][9];
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		for(int i=0; i<9; ++i) {
			char[] ch = br.readLine().toCharArray();
			for(int j=0; j<9; ++j) {
				sudoku[i][j] = ch[j]-'0';
			}
		}
		
		play(0);
	}

	private static void play(int num) {
		// 종료조건
		if(num == 81) {
			print();
			System.exit(0);	// 종료
		}
		
		int r = num/9;
		int c=  num%9;
		
		// 해당 칸에 숫자가 0이면 1~9까지 하나씩 넣어본다.
		if(sudoku[r][c] == 0) {
			// 1~9중에서 없는 숫자를 넣는다.
			for(int i=1; i<=9; ++i) {
				if(isValid(r,c,i)) {
					sudoku[r][c] = i;	// r,c 에 1~9 중 하나를 넣는다.
					play(num+1);
					sudoku[r][c] = 0;
				}
			}
		}
		// r,c에 숫자가 있으면 다음 칸 탐색
		else
			play(num+1);
	}
	
	private static boolean isValid(int r, int c, int n) {
		for(int i=0; i<9; ++i) {
			if(sudoku[r][i] == n || sudoku[i][c] == n)
				return false;
		}
		
		int sr = r/3*3;
		int sc = c/3*3;
		
		for(int i=sr; i<sr+3; ++i)
			for(int j=sc; j<sc+3; ++j)
				if(sudoku[i][j] == n)
					return false;
		return true;
	}

	private static void print() {
		StringBuilder sb  = new StringBuilder();
		for(int i=0; i<9; ++i) {
			for(int j=0; j<9; ++j) {
				sb.append(sudoku[i][j]);
			}
			sb.append('\n');
		}
		System.out.println(sb);
	}
}