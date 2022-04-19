/*
2시간 넘게 걸려도 해결 못했는데 문제를 잘 읽고 조건을 잘 봐야한다는걸 다시 깨닫게 되는 문제였다.
문제 이해 자체는 어렵지 않았지만 조건을 잘못 이해했다.
한 줄이나 열이 블록으로 가득차서 점수를 얻게 되면 없어진 행, 열 칸 만큼만 블록이 이동한다.
즉, 한 줄이 없어지면 한칸만 이동하고 두 줄이 없어지면 두 줄씩만 이동한다.
근데 그냥 중력작용하듯이 블록 하나를 빈틈없이 다 내려 버렸다...

그리고 점수계산의 경우 무조건 연속으로만 점수가 날 수 밖에 없다.
밑에서부터 블록이 채워지기 때문에 1, 3번째줄만 점수가 나고 2번쨰 줄은 점수가 안나는 그런 현상은 발생하지 않는다.
그렇기 때문에 가장 밑이나 오른쪽에 있는 행열 인덱스 번호를 이용해서 없어진 칸만큼 땡겨주면 된다.
그리고 없어진 칸 만큼만 땡기기 때문에 점수가 나게되면 바로 연한부분을 체크해버리면 된다.
중력처럼 블록 하나하나가 빈칸으로 다 이동하는 것이 아니어서 점수가 한 번 나고 블록 이동 후 또 점수가 나는 경우는 생기지 않는다.

블록 이동 조건, 블록이 연속으로만 파괴된다는것, 점수가 나고 바로 연한부분을 체크하면 되는것
이 세가지만 제대로 알고 있었으면 좀 더 빨리 풀 수 있었는데 너무 오래 걸려버렸다.

시험치기전에 꼭 다시 풀어보고 가야할 것 같다.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {

	static int[][] board = new int[10][10];
	static int N;

	static int ret;

	public static void main(String[] args) throws IOException {
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;

		N = Integer.parseInt(br.readLine());

		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine());
			int t = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());

			moveBlock(t, x, y);
			calcScore();
			moveshallowBlock();
		}

		System.out.println(ret);
		System.out.println(getBlock());

	}

	private static int getBlock() {
		int cnt = 0;
		for(int i=6; i<10; ++i) {
			for(int j=0; j<4; ++j) {
				if(board[i][j] == 1) cnt++;
			}
		}

		// 파란색 계산
		for(int i=6; i<10; ++i) {
			for(int j=0; j<4; ++j) {
				if(board[j][i] == 1) cnt++;
			}
		}
		return cnt;
	}

	private static void moveshallowBlock() {
		// 초록색
		int cnt = 0;
		for(int i=4; i<6; ++i) {
			for(int j=0; j<4; ++j) {
				if(board[i][j] == 0) continue;
				cnt++;
				break;
			}
		}

		if(cnt != 0) {
			for(int i=9-cnt; i>=4; --i) {
				for(int j=0; j<4; ++j) {
					board[i+cnt][j] = board[i][j];
					board[i][j] = 0;
				}
			}
		}


		// 파란색
		cnt = 0;
		for(int i=4; i<6; ++i) {
			for(int j=0; j<4; ++j) {
				if(board[j][i] == 0) continue;
				cnt++;
				break;
			}
		}

		if(cnt != 0) {
			for(int i=9-cnt; i>=4; --i) {
				for(int j=0; j<4; ++j) {
					board[j][i+cnt] = board[j][i];
					board[j][i] = 0;
				}
			}
		}
	}

	private static void calcScore() {
		// 초록색 계산
		Queue<Integer> q= new LinkedList<>();
		for(int i=9; i>=6; --i) {
			int cnt = 0;
			for(int j=0; j<4; ++j) {
				if(board[i][j] == 1) cnt++;
			}
			// 한 줄이 블록으로 차면 1점 추가, 블록 제거
			if(cnt==4) {
				ret++;
				q.offer(i);
				for(int j=0; j<4; ++j) board[i][j]=0;
			}
		}

		if(!q.isEmpty()) {
			int lastRow = q.peek();
			int size = q.size();
			for(int i=lastRow-size; i>=4; --i) {
				for(int j=0; j<4; ++j) {
					board[i+size][j] = board[i][j];
					board[i][j] = 0;
				}
			}
		}

		q.clear();
		// 파란색 계산
		for(int i=9; i>=6; --i) {
			int cnt = 0;
			for(int j=0; j<4; ++j) {
				if(board[j][i] == 1) cnt++;
			}
			// 한 줄이 블록으로 차면 1점 추가, 블록 제거
			if(cnt==4) {
				ret++;
				q.add(i);
				for(int j=0; j<4; ++j) board[j][i]=0;
			}
		}
		if(!q.isEmpty()) {
			int lastRow = q.peek();
			int size = q.size();
			for(int i=lastRow-size; i>=4; --i) {
				for(int j=0; j<4; ++j) {
					board[j][i+size] = board[j][i];
					board[j][i] = 0;
				}
			}
		}
	}

	private static void moveBlock(int t, int x, int y) {
		if (t == 1) {
			int r = x, c = y;
			//초록색 칸
			while (true) {
				r += 1;
				if (r >= 10 || board[r][c] == 1) {
					r -= 1;
					break;
				}
			}
			board[r][c] = 1;

			r = x; c = y;
			//파란색 칸
			while (true) {
				c += 1;
				if (c >= 10 || board[r][c] == 1) {
					c -= 1;
					break;
				}
			}
			board[r][c] = 1;
		}

		else if (t == 2) {
			int r = x, c = y;
			//초록색 칸. 밑으로 내려갈 때 둘다 검사
			while (r + 1 < 10 && board[r + 1][c] != 1 && board[r + 1][c + 1] != 1) {
				r += 1;
			}
			board[r][c] = 1; board[r][c + 1] = 1;

			r = x; c = y;
			//파란색 칸. 가장 오른쪽 블록만 확인
			while (c + 2 < 10 && board[r][c + 2] != 1) {
				c += 1;
			}
			board[r][c] = 1; board[r][c + 1] = 1;
		}

		else if (t == 3) {
			int r = x, c = y;
			//초록색 칸. 밑으로 내려갈 때 둘다 검사
			while (r + 2 < 10 && board[r + 2][c] != 1) {
				r += 1;
			}
			board[r][c] = 1; board[r + 1][c] = 1;

			r = x; c = y;
			//파란색 칸. 가장 오른쪽 블록만 확인
			while (c + 1 < 10 && board[r][c + 1] != 1 && board[r + 1][c + 1] != 1) {
				c += 1;
			}
			board[r][c] = 1; board[r + 1][c] = 1;
		}
	}


}