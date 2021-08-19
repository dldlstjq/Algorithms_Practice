import java.util.Scanner;

public class 오목 {
	public static void main(String[] args) {
		//상하좌우에 한줄씩 크게 잡아서 그 자리들을 0으로 두면
		//낭떠러지 검사를 하지 않고, 그냥 내가 찾는 돌이 있는지만 보면서 검사하면됨
		int[][] board = new int[21][21];
		//0행, 0열, 20행, 20열은 어차피 안 쓸거임.
		Scanner sc = new Scanner(System.in);
		for(int i = 1; i < 20; i++) {
			for(int j = 1; j < 20; j++)
				board[i][j] = sc.nextInt();
		}
		boolean isOk = false;
		int r=0,c=0; //시작위치
		int color = 0;//돌의색깔
		//모든 칸을 검사하기 시작
		out:for(int i = 1; i < 20; i++) {
			for(int j = 1; j < 20; j++){
				//현재 위치에 돌이 있다면.
				if( board[i][j] != 0 ) {
					int count = 1; //연속된 돌의 갯수를 셀 변수
					//오른쪽으로 같은 돌이 나오는한 계속 검사해볼게요
					//board[i][j]는 시작돌
					//내가 오른쪽으로 가려는데 왼쪽에 같은 돌이 있다면
					//나는 시작돌이 아님.
					while(board[i][j] != board[i][j-1] && board[i][j] == board[i][j + count]) {
						count++;
					}
					if( count == 5 ) {
						//오목 성공
						isOk = true;
						r = i; c = j;
						color = board[i][j];
						break out;
					}
					
					
					count = 1; //연속된 돌의 갯수를 셀 변수
					while(board[i][j] != board[i-1][j] && board[i][j] == board[i + count][j]) {
						count++;
					}
					if( count == 5 ) {
						//오목 성공
						isOk = true;
						r = i; c = j;
						color = board[i][j];
						break out;
					}
					
					count = 1; //연속된 돌의 갯수를 셀 변수
					while(board[i][j] != board[i-1][j-1] && board[i][j] == board[i + count][j + count]) {
						count++;
					}
					if( count == 5 ) {
						//오목 성공
						isOk = true;
						r = i; c = j;
						color = board[i][j];
						break out;
					}
					
					count = 1; //연속된 돌의 갯수를 셀 변수
					while( board[i][j] != board[i+1][j-1] && board[i][j] == board[i - count][j + count]) {
						count++;
					}
					if( count == 5 ) {
						//오목 성공
						isOk = true;
						r = i; c = j;
						color = board[i][j];
						break out;
					}
				}
			}
		}
		if(isOk) {
			System.out.println(color);
			System.out.println(r + " " + c);
		}
		else
			System.out.println(0);
	}
}
