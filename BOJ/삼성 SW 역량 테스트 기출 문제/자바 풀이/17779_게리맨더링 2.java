/*
선거구 경계 조건 이해에 시간이 걸리긴 했지만 어떻게 이해는 했다.
처음에는 x, y, d1, d2가 주어져서 되게 쉬운줄 알았는데 그냥 N 하나만 주어졌다.
N이 최대 20이어서 완전탐색으로 해도 시간초과가 안날 것 같았고 모든 좌표를 돌면서 선거구를 구하는 방식을 사용했다.

d1, d2도 범위가 정해져 있었기 때문에 1~N까지 하나씩 대입해서 범위를 만족하는지 보고 만족하면 그대로 경게선을 구했다.
경계선의 경우 범위가 다 주어졌기 때문에 어렵지 않았다.
경계선을 구한 후 구역 안에 5를 채워넣었고 남은 선거구의 경우도 범위가 정해져서 주어진 대로 설정하고 인구수를 구했다.

예제가 다 맞게 나와서 의외로 쉬운문제였네 하고 냈는데 바로 틀려버렸다 머쓱;;
예제가 다 잘 나오고 반례도 검색해서 안나오길래 못푸는건가 싶었는데 다른사람 블로그를 보니 5를 채워넣는 과정에서 잘못됐다고 했다.

나도 설마 5를 채워넣는게 잘못됐나 싶어 5를 넣지 않고 경계선에 따라 조건을 설정해서 1~4 선거구를 설정하고 인구수를 구했다.
5구역은 전체 인구수 합에서 1~4 인구수를 빼는 방식으로 했고 제출하니 됐다...

어찌저찌 풀긴 했지만 반례도 없고 5를 채우는게 잘못됐다는 다른사람의 글을 보지 못했다면 아마도 못 푼상태지 않았을까 싶다...
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {

	static int N;
	static int[][] person;
	static int[][] area;

	static int diff;
	static int total;
	static int notFiveTotal;	// 5번 선거구 제외한 인구수
	static List<Integer> list;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;

		N = Integer.parseInt(br.readLine());

		person = new int[N+1][N+1];
		area = new int[N+1][N+1];

		for(int i=1; i<=N; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=1; j<=N; ++j) {
				person[i][j] = Integer.parseInt(st.nextToken());
				total += person[i][j];
			}
		}

		diff = Integer.MAX_VALUE;
		for(int i=1; i<=N; ++i) {
			for(int j=1; j<=N; ++j) {
				searchCond(i, j);

			}
		}
		System.out.println(diff);

	}



	private static void searchCond(int x, int y) {
		for(int i=1; i<=N; ++i) {
			for(int j=1; j<=N;++j) {
				if(!cond1(x, y, i, j) || !cond2(x, y,i, j)) break;
				divideArea(x, y, i, j);
			}
		}
	}

	private static void divideArea(int x, int y, int d1, int d2) {

		// 5번 경계선 표시
		area[x][y] = 5;
		// 왼쪽 위
		leftTop(x, y, d1);

		// 오른쪽 위
		rightTop(x, y, d2);

		// 왼쪽 아래
		leftBottom(x, y, d1, d2);

		// 오른쪽 아래
		rightBottom(x, y, d1, d2);

		list = new ArrayList<>();
		notFiveTotal = 0;

		// 남은 구역 채우기
		putOne(x, y, d1);
		putTwo(x, y, d2);
		putThree(x, y, d1, d2);
		putFour(x, y, d1, d2);

		list.add(total-notFiveTotal);	// 5번선거구 인구수 추가


		Collections.sort(list);

		// 가장 인구수가 많은 선거구와 적은 수 차이 최소값
		diff = Integer.min(diff, list.get(4)-list.get(0));

		clear();
	}

	private static void putOne(int x, int y, int d1) {
		int sum=0;
		for(int i=1; i<x+d1; ++i) {
			for(int j=1; j<=y; ++j) {
				// 5선거구 경계선을 만나면 바로 다음 행 탐색
				if(area[i][j]==5) break;
				area[i][j] =1;
				sum+=person[i][j];
			}
		}
		list.add(sum);
		notFiveTotal += sum;
	}

	private static void putTwo(int x, int y, int d2) {
		int five=0;	// 5가 처음으로 나오는 경계선
		int sum=0;
		for(int i=1; i<=x+d2; ++i) {
			for(int j=y+1; j<=N; ++j) {
				// 5경계선을 만날때마다 five 갱신하고 j가 5보다 작거나 같으면 5구역 안에 있는 것.
				if(area[i][j] == 5 ) five=j;
				else if(five>=j) continue;
				else {
					area[i][j] =2;
					sum+=person[i][j];
				}
			}
		}
		list.add(sum);
		notFiveTotal += sum;
	}



	private static void putThree(int x, int y, int d1, int d2) {
		int sum=0;
		for(int i=x+d1; i<=N; ++i) {
			for(int j=1; j<y-d1+d2; ++j) {
				// 5선거구 경계선을 만나면 바로 다음 행 탐색
				if(area[i][j]==5) break;
				area[i][j] =3;
				sum+=person[i][j];
			}
		}
		list.add(sum);
		notFiveTotal += sum;
	}



	private static void putFour(int x, int y, int d1, int d2) {
		int five= 0;
		int sum=0;
		for(int i=x+d2+1; i<=N; ++i) {
			for(int j=N; j>=y-d1+d2; --j){
				// 4번의 경우 반대로 N열부터 시작해서 감소하는 방식
				// 5경계선을 만날때마다 five 갱신하고 j가 5보다 작으면 5구역 안에 있는 것.
				if(area[i][j] == 5 ) five=j;
				else if(five>j) continue;
				else {
					area[i][j] =4;
					sum+=person[i][j];
				}
			}

		}
		list.add(sum);
		notFiveTotal += sum;
	}

	private static void clear() {
		for(int i=1; i<=N; ++i)
			for(int j=1; j<=N; ++j)
				area[i][j] = 0;
	}

	private static void print() {
		for(int i=1; i<=N; ++i)
			System.out.println(Arrays.toString(area[i]));
		System.out.println();
	}

	private static void rightBottom(int x, int y, int d1, int d2) {
		for(int i=1; i<=d1; ++i) {
			int nx = x+d2+i;
			int ny = y+d2-i;
			if(!isIn(nx, ny)) continue;	// 범위 아웃
			area[nx][ny] = 5;
		}
	}

	private static void leftBottom(int x, int y, int d1, int d2) {
		for(int i=1; i<=d2; ++i) {
			int nx = x+d1+i;
			int ny = y-d1+i;
			if(!isIn(nx, ny)) continue;	// 범위 아웃
			area[nx][ny] = 5;
		}
	}

	private static void rightTop(int x, int y, int d2) {
		for(int i=1; i<=d2; ++i) {
			int nx = x+i;
			int ny = y+i;
			if(!isIn(nx, ny)) continue;	// 범위 아웃
			area[nx][ny] = 5;
		}
	}

	private static void leftTop(int x, int y, int d1) {
		for(int i=1; i<=d1; ++i) {
			int nx = x+i;
			int ny = y-i;
			if(!isIn(nx, ny)) continue;	// 범위 아웃
			area[nx][ny] = 5;
		}
	}

	// 배열 범위
	private static boolean isIn(int x, int y) {
		return 1<=x&&x<=N && 1<=y&&y<=N;
	}

	// d1, d2 범위
	private static boolean cond2(int x, int y, int d1, int d2) {
		// 1 ≤ y-d1 < y < y+d2 ≤ N
		return 1<=y-d1 && y-d1<y && y<y+d2 && y+d2<=N;
	}

	private static boolean cond1(int x, int y, int d1, int d2) {
		//  1 ≤ x < x+d1+d2 ≤ N
		return 1<=x && x<x+d1+d2 && x+d1+d2<=N;
	}

}