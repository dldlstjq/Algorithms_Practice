/*
한참을 못풀다 겨우 해결한 문제

우선 최대 300시간 동안 움직일 수 있고 최초 분포 넓이는 50*50 이라서 못해도 300+50+300 의 크기 배열이 필요하다.
거기다 무한으로 퍼지기 때문에 범위를 벗어나는 경우도 없다.

처음 든 생각은 최대한 큰 배열을 선언해놓고 거기서 bfs를 쓰면서 퍼져나가고, tmp 임시 배열을 둬서 같은 곳에 여러개 들어오는 경우를 처리하는 방법이었다.
하지만 배열 크기가 커서 계속 copy 작업하는것은 시간을 많이 잡아먹을 것 같았고 마땅한 방법을 못찾았다.
그러다 배열 한 칸을 r*N+c로 해서 번호로 둔 뒤 번호 오름차순, 생명력 내림차순으로 정렬하는 방법을 썼다.
그렇게 되면 같은 좌표인 것들이 연속해서 붙어있게 되고 생명력이 가장 높은 것이 앞쪽으로 온다.
그래서 list.size()-1까지 i, i+1을 비교하며 다르면 넘어가고 같다면 i+1을 삭제하는 방식을 사용했다.
그렇게 되면 같은 좌표에 대해 생명력이 높은 것만 남게되고 그것들을 큐에 넣어 계속 반복하면 됐다.

중복되는 좌표의 경우 리스트를 이용하여 중복되는 것 중 우선순위 하나를 선택하는 방법이 좋은 것 같다.
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

	static class Cell{
		int r; int c; int life; int notActive; int active;

		Cell(int r, int c, int life, int notActive, int active){
			this.r=r;
			this.c=c;
			this.life=life;
			this.notActive=notActive;
			this.active=active;
		}
	}

	static class State implements Comparable<State>{
		int r; int c; int num; int life;
		State(int r, int c, int num, int life){
			this.r = r;
			this.c = c;
			this.num = num;
			this.life = life;
		}

		@Override
		public int compareTo(State o) {
			if(this.num==o.num)
				return Integer.compare(o.life, this.life);
			return Integer.compare(this.num, o.num);
		}
	}

	static int N, M, K;
	static int[][] map;

	static boolean[][] visited;
	static Queue<Cell> q;

	static int []dr= {-1,0,1,0};
	static int []dc= {0,1,0,-1};
	static int ret;

	public static void main(String[] args) throws IOException {
		//System.setIn(new FileInputStream("sample_input.txt"));

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());

			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());
			map = new int[N][M];
			visited = new boolean[850][850];
			q = new LinkedList<>();

			for(int i=0; i<N; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<M; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
					if(map[i][j] > 0) {
						visited[400+i][400+j] = true;
						q.offer(new Cell(400+i, 400+j, map[i][j], map[i][j], 0));
					}

				}
			}

			ret = 0;
			start();
			ret = q.size();


			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(ret);
			System.out.println(sb);
		}
	}



	private static void start() {
		int time = 0;
		while(!q.isEmpty()) {

			int size = q.size();
			time++;
			List<State> list = new ArrayList<>();

			for(int s=0; s<size; ++s) {
				Cell now = q.poll();

				// 비활성상태이면 감소 시켜서 0이 되는 경우 활성상태로 변경
				if(now.notActive > 0) {
					now.notActive--;
					if(now.notActive == 0) {
						now.active = now.life;
					}
					q.offer(now);
					continue;
				}

				// 활성상태인데 자기 생명력과 다르다면 이미 주변에 퍼트린 상태. 활성상태만 감소
				else if(now.active>0 && now.active != now.life) {
					now.active--;
					if(now.active == 0) {
						continue;
					}
					q.offer(now);

				}
				// 활성상태인데 생명력과 같은 경우 주변에 퍼트리기
				else if(now.active > 0 && now.active == now.life) {
					for(int i=0; i<4; ++i) {
						int nr = now.r+dr[i];
						int nc = now.c+dc[i];

						if(visited[nr][nc]) continue;

						// 동시에 같은 배열에 있으면 어떻게 처리할건지
						list.add(new State(nr, nc, nr*850+nc, now.life));
					}

					now.active--;	// 활성상태 생명 감소
					if(now.active>0)
						q.offer(now);
				}

			}

			// 같은 좌표라면 생명력이 큰 것만 살아남음
			Collections.sort(list);
			for(int i=0; i<list.size()-1; ++i) {
				if(list.get(i).r == list.get(i+1).r &&
						list.get(i).c == list.get(i+1).c) {
					list.remove(i+1);
					--i;
					continue;
				}
			}
			// 남은 세포들만 큐에 새로 저장
			for(int i=0; i<list.size(); ++i) {
				State cell = list.get(i);
				visited[cell.r][cell.c] = true;
				q.offer(new Cell(cell.r, cell.c, cell.life, cell.life, 0));
			}

			if(time == K) break;
		}
	}
}
