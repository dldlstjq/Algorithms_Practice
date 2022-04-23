/*
처음 풀었을때도 비슷한 곳에서 헤맸었던 걸로 기억하는데 또 똑같은 곳에서 헤매서 시간내에 못풀었다.
일단 2차원 배열 리스트를 선언해서 하나의 좌표에 여러 영역이 있음을 미리 표시했다.

그 후 이동하면서 가장 큰 충전량이 되도록 계산해주면 되는데 너무 어렵게 생각한 것 같다.
단순히 각 칸을 내림차순 정렬한 후 겹치지 않는선에서 가장 큰 충전량을 선택하게 했다.
문제는 사용자가 있는 칸에서 여러 충전량이 있는 경우인데
1. 가장 큰 충전량이 겹치지 않는 경우
	-> 가장 큰 걸로 둘 다 충전가능
2. 가장 큰 충전량이 겹치는 경우
	2-1. 둘 다 하나의 충전량만 있는 경우
		-> 하나의 충전량을 두명이 분배한다
	2-2. A,B 중 하나만 충전량이 하나 있는 경우
		-> 충전량이 하나인 곳은 그대로 충전해주고 여러개인 곳은 두번째 충전량을 충전해준다(내림차순 정렬이므로 두번째게 그 다음으로 큰것)
	2-3. A,B 둘 다 여러 충전량이 있는 경우
	 	-> 내림차순 정렬이므로 두번째 충전량이 첫번쨰 다음으로 크다.
	 	   그렇기 때문에 A의 첫번째와 B의 두번쨰, A의 두번째와 B의 첫번째중 충전량이 큰 것을 계산해준다.

충전량이 여러개 있는 경우는 위처럼 조건을 걸어서 계산하면 된다.
내림차순 정렬을 했기 때문에 인덱스 0, 1로만 간단하게 접근해서 하면 되는데 두번째로 큰게 뭔지 계산한다고 뻘짓하다가 시간 다 보냈다.

그리고 2차원 배열 리스트로 미리 어느 영역에 충전이 있는지 선언하지 않고
좌표가 움직일 때 마다 거리 게산을 해서 거리 안에 들어오는 충전량을 여러개 같이 저장한 후에 계산해도 된다.

 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;

public class Solution {

	static class Battery implements Comparable<Battery>{
		int num; int p;
		Battery(int num, int p){
			this.num=num;
			this.p=p;
		}

		@Override
		public int compareTo(Battery o) {
			return Integer.compare(o.p, this.p);
		}
	}
	static class Pos{
		int x; int y; int n;
		Pos(int x, int y, int n){
			this.x=x;
			this.y=y;
			this.n=n;
		}
		Pos(int x, int y){
			this.x=x;
			this.y=y;
		}
	}

	static int M, A;
	static int user1[];	// 사용자 이동 방향
	static int user2[];

	static List<Battery> map[][];
	static int x1, y1;
	static int x2, y2;

	static int dr[]= {0,-1,0,1,0};
	static int dc[]= {0,0,1,0,-1};

	static int sum;

	public static void main(String[] args) throws IOException {
		//System.setIn(new FileInputStream("sample_input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());
			M = Integer.parseInt(st.nextToken());
			A = Integer.parseInt(st.nextToken());

			user1 = new int[M+1];
			user2 = new int[M+1];
			map = new ArrayList[10][10];
			for(int i=0; i<10; ++i) {
				for(int j=0; j<10; ++j)
					map[i][j] = new ArrayList<>();
			}

			st = new StringTokenizer(br.readLine());
			for(int i=1; i<=M; ++i)
				user1[i] = Integer.parseInt(st.nextToken());

			st = new StringTokenizer(br.readLine());
			for(int i=1; i<=M; ++i)
				user2[i] = Integer.parseInt(st.nextToken());

			for(int i=1; i<=A; ++i) {
				st = new StringTokenizer(br.readLine());
				int y = Integer.parseInt(st.nextToken());
				int x = Integer.parseInt(st.nextToken());
				int c = Integer.parseInt(st.nextToken());
				int p = Integer.parseInt(st.nextToken());

				installArea(x-1, y-1, c, p, i);	// 충전 범위 설정
			}

			sum = 0;
			start();
			StringBuilder sb= new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(sum);
			System.out.println(sb);
		}
	}

	private static void start() {
		// 각 출발점
		x1 = 0; y1= 0;
		x2 = 9; y2= 9;

		// 초기 위치부터 충전 가능
		for(int i=0; i<=M; ++i) {
			move(i);
		}

	}

	private static void move(int n) {
		x1 += dr[user1[n]];
		y1 += dc[user1[n]];
		x2 += dr[user2[n]];
		y2 += dc[user2[n]];

		// 둘다 충전할 수 없으면 끝
		if(map[x1][y1].isEmpty() && map[x2][y2].isEmpty()) return;

			// A만 충전 가능한 경우
		else if(!map[x1][y1].isEmpty() && map[x2][y2].isEmpty()) {
			Collections.sort(map[x1][y1]);
			sum += map[x1][y1].get(0).p;
		}
		// B만 충전 가능한 경우
		else if(!map[x2][y2].isEmpty() && map[x1][y1].isEmpty()) {
			Collections.sort(map[x2][y2]);
			sum += map[x2][y2].get(0).p;
		}

		// 둘 다 충전 가능
		else if(!map[x1][y1].isEmpty() && !map[x2][y2].isEmpty()) {
			Collections.sort(map[x1][y1]);
			Collections.sort(map[x2][y2]);

			// 가장 큰 충전량이 겹치지 않는다면 바로 충전
			if(map[x1][y1].get(0).num != map[x2][y2].get(0).num) {
				sum += map[x1][y1].get(0).p;
				sum += map[x2][y2].get(0).p;
			}
			else {	// 가장 큰 충전량 겹치는 경우
				if(map[x1][y1].size()==1 && map[x2][y2].size()==1) {
					// 둘 다 하나만 충전가능한데 같은 영역이면 사용자 수만큼 균등 분배
					sum += map[x1][y1].get(0).p;
				}

				else if(map[x1][y1].size()==1 && map[x2][y2].size()>1) {
					sum += map[x1][y1].get(0).p;
					sum += map[x2][y2].get(1).p;
				}
				else if(map[x1][y1].size()>1 && map[x2][y2].size()==1) {
					sum += map[x1][y1].get(1).p;
					sum += map[x2][y2].get(0).p;
				}
				else {
					// A, B 둘중에서 두번째로 큰 충전량을 먼저 알아야함
					int p = 0;
					p = Math.max(p, map[x1][y1].get(0).p+map[x2][y2].get(1).p);
					p = Math.max(p, map[x1][y1].get(1).p+map[x2][y2].get(0).p);
					sum += p;
				}
			}
		}
	}

	private static void installArea(int x, int y, int c, int p, int num) {

		boolean[][] visited= new boolean[10][10];
		Queue<Pos> q = new LinkedList<>();
		q.offer(new Pos(x, y, 0));
		visited[x][y] = true;
		map[x][y].add(new Battery(num, p));

		while(!q.isEmpty()) {
			Pos now = q.poll();
			// c 범위까지 가면 끝
			if(now.n == c) continue;

			for(int i=1; i<=4; ++i) {
				int nx = now.x+dr[i];
				int ny = now.y+dc[i];

				if(!isIn(nx, ny) || visited[nx][ny]) continue;

				map[nx][ny].add(new Battery(num, p));
				q.offer(new Pos(nx, ny, now.n+1));
				visited[nx][ny] = true;
			}
		}
	}

	private static boolean isIn(int x, int y) {
		return 0<=x&&x<10 && 0<=y&&y<10;
	}
}
