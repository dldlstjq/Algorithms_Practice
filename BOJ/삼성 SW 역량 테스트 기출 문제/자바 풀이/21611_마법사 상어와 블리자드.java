/*
1시간 30분 내에 풀 수 있었는데 하나 빠트린것 때문에 2시간 가까이 걸려서 해결할 수 있었다.
구슬 파괴후 빈칸으로 하나씩 이동하는 것은 큐를 활용했다.
1. 현재 칸이 빈칸 : 해당 칸을 큐에 저장
2. 큐에 빈칸이 있고, 현재 칸이 구슬: 빈 칸에 구슬을 저장하고, 현재 칸을 빈 칸으로 만든다. 현재 칸이 빈칸이므로 큐에 저장한다.

위 2가지를 반복하며 구슬을 떙겨줬다.

이동 방향은 행렬 가운데서 달팽이 모양으로 뻗어나가는데 왼쪽, 아래, 오른족, 위 순서를 반복하고, 왼쪽과 아래, 오른쪽과 위가 같은 크기만큼 움직이고
왼쪽-아래, 오른쪽-위 이동이 특정횟수만큼 이동하면 다음에는 한 칸 더 이동한다는 것을 이용했다.

구슬 파괴도 마찬가지로 큐를 이용했다.
1. 큐가 비었거나 같은 구슬: 큐에 저장
2. 다른 구슬
	2-1. 그룹이 4개 미만이면 큐를 비워줌
	2-2. 4개 이상이면 점수 계산. 큐에 저장된 그룹을 모두 0으로 만들어서 폭파
	2-3. 2-1, 2-2 가 끝난 후 현재 위치를 큐에 저장하고 구슬 정보를 num에 저장한다. 그렇게 해야 현재위치 정보가 반영된다.

구슬 이동과 파괴는 더이상 파괴되는 구슬이 없을 때까지 반복하므로 boolean 전역변수를 이용해서 조건을 걸었다.

마지막 관문인 구슬의 변화이다.
더이상 파괴되는 구슬이 없다면 구슬이 개편되는데, 2개 그룹으로 나뉜다.
첫번째는 그룹의 구슬 개수, 두번쨰는 구슬 번호이다.
행렬 중앙인 상어위치에서 2개씩 좌표가 이어져나가서 이걸 어떻게 처리하나 고민햇는데 이것 역시 큐를 이용했다.

Pair라는 큐를 활용해서 구슬 파괴하기 전 진행방향 1번부터 Pair에 저장했다.
그리고 구슬 파괴 로직과 똑같이 같은 구슬 그룹을 구하고 다른 구슬이 나온다면 그때 저장한 구슬 개수와 구슬 번호를 Pair에서 2개 좌표를 꺼내어 저장했다.
이때, map에 바로 저장하면 상태가 달라지므로 임시 배열 tmp에 모두 바뀐 정보를 저장 후 다시 map에 카피하는 방법을 사용했다.
여기서, 구슬의 개수가 행렬 칸 보다 많다면 바로 종료해줘야한다.

결정적으로 구슬 이동과 폭파의 경우 좌표가 0,0이 되면 종료한다.
구슬 변화의 경우도 0,0이 되면 종료하지만 구슬 개수가 행렬 칸 보다 많을 경우에 종료한다는 조건이 추가된다.

여기서 0,0이 되면 tmp를 map에 카피하는 것까지는 코드를 넣어줬는데 행렬칸보다 많은 경우 종료만 하고 배열 복사를 넣어주지 않아 제대로된 정답이 안나왔다.
이걸 해결하고 나니 다행히도 정답을 받을 수 있었다.

구슬 이동, 폭파, 변화가 모두 비슷한 로직이 반복되는데 일단은 처음 푼 풀이 그대로 올리고 나중에 줄일 수 있으면 줄여봐야겠다.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
	static class Pos{
		int r; int c;
		Pos(int r, int c){
			this.r=r;
			this.c=c;
		}
	}

	static int N,M;
	static int[][] map;
	static int[][] shark;

	// 위 아래 왼쪽 오른쪽
	static int dr[]= {-1,1,0,0};
	static int dc[]= {0,0,-1,1};

	// 이동 방향. 왼쪽 아래 오른쪽 위
	static int[] mr= {0,1,0,-1};
	static int[] mc= {-1,0,1,0};

	static boolean fire;	// 폭발 여부

	static Queue<Pos> Pair;	// 구슬이 변할 때 좌표 저장

	static int ret;

	public static void main(String[] args) throws IOException {
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());

		map = new int[N][N];
		Pair = new LinkedList<>();

		shark = new int[1][2];
		shark[0][0] = (N+1)/2-1;
		shark[0][1] = (N+1)/2-1;

		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}

		for(int i=0; i<M; ++i) {
			st = new StringTokenizer(br.readLine());
			int d = Integer.parseInt(st.nextToken());
			int s = Integer.parseInt(st.nextToken());

			savePair();
			destroygusul(d, s);
//			print();

			while(true) {
				// 빈 칸으로 구슬 이동
				movegusul();
//				print();

				// 구슬 폭발
				explosion();
//				print();

				// 폭발한 곳이 있다면 다시 빈칸으로 구슬 이동
				if(!fire) break;
				fire = false;
			}

			// 구슬 변화
			changeGusul();
			Pair.clear();
//			print();
		}
		System.out.println(ret);
	}

	private static void savePair() {
		// 폭발하는 구슬은 4개 이상 연속하는 구슬이 있을 때 발생
		int r = shark[0][0];
		int c = shark[0][1];

		int flag = 1;	// 방향이 바뀌는 카운트
		int dir = 0;	// 방향
		while(true) {
			// 왼쪽, 아래는 같은 횟수만큼 이동
			while(dir<2) {
				for(int i=0; i<flag; ++i) {
					r = r+mr[dir];
					c = c+mc[dir];
					Pair.offer(new Pos(r, c));// 구슬 전체 좌표 저장

					// (0, 0)에 있는 구슬까지 옮긴 후 종료
					if(r==0 && c==0) {
						return;
					}
				}
				dir++;
			}
			flag++;	// 왼쪽, 아래 이동했다면 횟수 증가

			// 오른쪽, 위쪽은 같은 횟수만큼 이동
			while(dir<4) {
				for(int i=0; i<flag; ++i) {
					r = r+mr[dir];
					c = c+mc[dir];
					Pair.offer(new Pos(r, c));// 구슬 전체 좌표 저장
				}
				dir++;
			}
			flag++;	// 오른쪽, 위 이동했다면 횟수 증가

			dir %= 4;
		}
	}

	private static void changeGusul() {
		// 폭발하는 구슬은 4개 이상 연속하는 구슬이 있을 때 발생
		int r = shark[0][0];
		int c = shark[0][1];

		int[][] tmp = new int[N][N];
		int flag = 1;	// 방향이 바뀌는 카운트
		int dir = 0;	// 방향
		int num = 0;	// 구슬 번호
		Queue<Pos> q = new LinkedList<>();	// 빈 공간 좌표 저장
		while(true) {
			// 왼쪽, 아래는 같은 횟수만큼 이동
			while(dir<2) {
				for(int i=0; i<flag; ++i) {
					r = r+mr[dir];
					c = c+mc[dir];

					// 큐가 비었으면 현재 좌표 저장
					if(q.isEmpty() || num == map[r][c]) {
						q.offer(new Pos(r, c));
						num = map[r][c];	// 구슬 번호 저장
					}
					// 다른 구슬일 경우
					else if(num != map[r][c]) {
						// 두 개의 구슬로 변환
						// A는 구슬 개수, B는 그룹 이루고 있는 구슬 번호
						int A = q.size();
						int B = num;

						Pos first = Pair.poll();
						Pos second = Pair.poll();
						// 2개 그룹에 구슬 추가
						tmp[first.r][first.c] = A;
						tmp[second.r][second.c] = B;

						// 구슬이 칸의 수보다 많으면 남은 구슬은 사라진다
						if(Pair.isEmpty()) {
							copy(tmp);
							return;
						}

						// 큐를 비운 후 현재 좌표를 다시 저장
						q.clear();
						q.offer(new Pos(r, c));
						num = map[r][c];	// 구슬 번호 저장
					}

					// (0, 0)에 있는 구슬까지 옮긴 후 종료
					if(r==0 && c==0) {
						copy(tmp);
						return;
					}
				}
				dir++;
			}
			flag++;	// 왼쪽, 아래 이동했다면 횟수 증가

			// 오른쪽, 위쪽은 같은 횟수만큼 이동
			while(dir<4) {
				for(int i=0; i<flag; ++i) {
					r = r+mr[dir];
					c = c+mc[dir];
					// 큐가 비었으면 현재 좌표 저장
					if(q.isEmpty() || num == map[r][c]) {
						q.offer(new Pos(r, c));
						num = map[r][c];	// 구슬 번호 저장
					}
					// 다른 구슬일 경우
					else if(num != map[r][c]) {
						// 두 개의 구슬로 변환
						// A는 구슬 개수, B는 그룹 이루고 있는 구슬 번호
						int A = q.size();
						int B = num;

						Pos first = Pair.poll();
						Pos second = Pair.poll();
						// 2개 그룹에 구슬 추가
						tmp[first.r][first.c] = A;
						tmp[second.r][second.c] = B;

						// 구슬이 칸의 수보다 많으면 남은 구슬은 사라진다
						if(Pair.isEmpty()) {
							copy(tmp);
							return;
						}

						// 큐를 비운 후 현재 좌표를 다시 저장
						q.clear();
						q.offer(new Pos(r, c));
						num = map[r][c];	// 구슬 번호 저장
					}
				}
				dir++;
			}
			flag++;	// 오른쪽, 위 이동했다면 횟수 증가

			dir %= 4;
		}
	}

	private static void copy(int[][] tmp) {
		for(int i=0; i<N; ++i)
			map[i] = tmp[i].clone();

	}

	private static void explosion() {
		// 폭발하는 구슬은 4개 이상 연속하는 구슬이 있을 때 발생
		int r = shark[0][0];
		int c = shark[0][1];


		int flag = 1;	// 방향이 바뀌는 카운트
		int dir = 0;	// 방향
		int num = 0;	// 구슬 번호
		Queue<Pos> q = new LinkedList<>();	// 빈 공간 좌표 저장
		while(true) {

			// 왼쪽, 아래는 같은 횟수만큼 이동
			while(dir<2) {
				for(int i=0; i<flag; ++i) {
					r = r+mr[dir];
					c = c+mc[dir];

					// 큐가 비었으면 현재 좌표 저장
					if(q.isEmpty() || num == map[r][c]) {
						q.offer(new Pos(r, c));
						num = map[r][c];	// 구슬 번호 저장
					}
					// 다른 구슬일 경우
					else if(num != map[r][c]) {
						// 같은 구슬 그룹이 4개 미만이면 통과
						if(q.size() < 4) {
							q.clear();
						}
						else {	// 4개 이상이면 폭파
							ret += num*q.size();	// 점수
							while(!q.isEmpty()) {
								Pos now = q.poll();
								map[now.r][now.c]= 0;
								fire = true;
							}
						}

						// 큐를 비운 후 현재 좌표를 다시 저장
						q.offer(new Pos(r, c));
						num = map[r][c];	// 구슬 번호 저장
					}

					// (0, 0)에 있는 구슬까지 옮긴 후 종료
					if(r==0 && c==0) return;
				}
				dir++;
			}
			flag++;	// 왼쪽, 아래 이동했다면 횟수 증가

			// 오른쪽, 위쪽은 같은 횟수만큼 이동
			while(dir<4) {
				for(int i=0; i<flag; ++i) {
					r = r+mr[dir];
					c = c+mc[dir];
					// 큐가 비었으면 현재 좌표 저장
					if(q.isEmpty() || num == map[r][c]) {
						q.offer(new Pos(r, c));
						num = map[r][c];	// 구슬 번호 저장
					}
					// 다른 구슬일 경우
					else if(num != map[r][c]) {
						// 같은 구슬 그룹이 4개 미만이면 통과
						if(q.size() < 4) {
							q.clear();
						}
						else {	// 4개 이상이면 폭파
							ret += num*q.size();	// 점수
							while(!q.isEmpty()) {
								Pos now = q.poll();
								map[now.r][now.c]= 0;
								fire = true;
							}
						}

						// 큐를 비운 후 현재 좌표를 다시 저장
						q.offer(new Pos(r, c));
						num = map[r][c];	// 구슬 번호 저장
					}
				}
				dir++;
			}
			flag++;	// 오른쪽, 위 이동했다면 횟수 증가

			dir %= 4;
		}
	}

	private static void movegusul() {
		int r = shark[0][0];
		int c = shark[0][1];

		// 방향이 바뀌는 카운트
		int flag = 1;
		int dir = 0;	// 방향
		Queue<Pos> q = new LinkedList<>();	// 빈 공간 좌표 저장

		while(true) {

			// 왼쪽, 아래는 같은 횟수만큼 이동
			while(dir<2) {
				for(int i=0; i<flag; ++i) {
					r = r+mr[dir];
					c = c+mc[dir];
					// 이동해야 할 좌표가 있다면 그 자리로 이동하고 현재 좌표를 빈 공간으로 만듦
					if(!q.isEmpty() && map[r][c] != 0) {
						Pos now = q.poll();
						map[now.r][now.c] = map[r][c];	// 빈 공간에 구슬을 넣어준다.
						q.offer(new Pos(r, c));
						map[r][c] = 0;
					}
					// 빈 공간일 경우
					else if(map[r][c] == 0) {
						q.offer(new Pos(r, c));
					}

					// (0, 0)에 있는 구슬까지 옮긴 후 종료
					if(r==0 && c==0) return;
				}
				dir++;
			}
			flag++;	// 왼쪽, 아래 이동했다면 횟수 증가

			// 오른쪽, 위쪽은 같은 횟수만큼 이동
			while(dir<4) {
				for(int i=0; i<flag; ++i) {
					r = r+mr[dir];
					c = c+mc[dir];

					// 이동해야 할 좌표가 있고 구슬이 있다면 그 자리로 이동하고 현재 좌표를 빈 공간으로 만듦
					if(!q.isEmpty() && map[r][c] != 0) {
						Pos now = q.poll();
						map[now.r][now.c] = map[r][c];	// 빈 공간에 구슬을 넣어준다.
						q.offer(new Pos(r, c));
						map[r][c] = 0;
					}
					// 빈 공간일 경우
					else if(map[r][c] == 0) {
						q.offer(new Pos(r, c));
					}
				}
				dir++;
			}
			flag++;	// 오른쪽, 위 이동했다면 횟수 증가

			dir %= 4;
		}
	}

	private static void print() {
		for(int i=0; i<N; ++i)
			System.out.println(Arrays.toString(map[i]));
		System.out.println();
	}

	private static void destroygusul(int d, int s) {
		int sharkR = shark[0][0];
		int sharkC = shark[0][1];
		if(d==1) {
			for(int i=sharkR-s; i<sharkR; ++i)
				map[i][sharkC] = 0;

		}

		else if(d==2) {
			for(int i=sharkR+s; i>sharkR; --i)
				map[i][sharkC] = 0;

		}

		else if(d==3) {
			for(int i=sharkC-s; i<sharkC; ++i)
				map[sharkR][i] = 0;

		}

		else if(d==4) {
			for(int i=sharkC+s; i>sharkR; --i)
				map[sharkR][i] = 0;

		}
	}
}