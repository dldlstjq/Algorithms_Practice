/*
얼핏보면 복잡해보이지만 조건만 잘 설정하면 쉬운것 같다.
옛날에는 벽에 튕겨나올 때 방향을 일일이 조건문으로 나눠서 설정한걸로 기억하는데 각 방향에 닿았을때 바뀌는 방향으로 한번에 저장했다.
웜홀은 6~10번 각각만들어 두개 좌표를 저장했는데 이것도 배열로 선언해서 저장하면 코드를 줄일 수 있을 것 같다.

 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Solution {

	static class Warmhole{
		int r; int c;
		Warmhole(int r, int c){
			this.r=r;
			this.c=c;
		}
	}

	static int N;
	static int[][] map;
	static int ret;

	static int dr[]= {-1,0,1,0};
	static int dc[]= {0,1,0,-1};

	static int one[]= {2,3,1,0};
	static int two[]= {1,3,0,2};
	static int three[]= {3,2,0,1};
	static int four[]= {2,0,3,1};

	static List<Warmhole> six;
	static List<Warmhole> seven;
	static List<Warmhole> eight;
	static List<Warmhole> nine;
	static List<Warmhole> ten;


	public static void main(String[] args) throws IOException {
		//System.setIn(new FileInputStream("sample_input.txt"));

		BufferedReader br = new BufferedReader(new InputStreamReader((System.in)));
		int T = Integer.parseInt(br.readLine());


		for(int test_case = 1; test_case <= T; test_case++)
		{
			N = Integer.parseInt(br.readLine());

			map=new int[N][N];
			six = new ArrayList<>();
			seven = new ArrayList<>();
			eight = new ArrayList<>();
			nine = new ArrayList<>();
			ten = new ArrayList<>();
			for(int i=0; i<N; ++i) {
				StringTokenizer st=new StringTokenizer(br.readLine());
				for(int j=0; j<N; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
					if( map[i][j]==6) six.add(new Warmhole(i, j));
					else if( map[i][j]==7) seven.add(new Warmhole(i, j));
					else if( map[i][j]==8) eight.add(new Warmhole(i, j));
					else if( map[i][j]==9) nine.add(new Warmhole(i, j));
					else if( map[i][j]==10) ten.add(new Warmhole(i, j));
				}


			}

			ret= 0;
			for(int i=0; i<N; ++i) {
				for(int j=0; j<N; ++j) {
					if(map[i][j] == -1) continue;
					else if(1<=map[i][j] && map[i][j]<=10) continue;
					for(int k=0; k<4; ++k)
						start(i, j, k);
				}
			}


			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(ret);
			System.out.println(sb);
		}
	}

	private static void start(int r, int c, int dir) {
		int sr=r;
		int sc=c;
		int cnt = 0;
		while(true) {
			r += dr[dir];
			c += dc[dir];

			// 범위를 벗어나거나 5번 블록
			if(!isIn(r, c) || map[r][c]==5) {
				dir = (dir+2)%4;	// 방향 반대
				cnt++;
				continue;
			}

			// 블랙홀은 종료
			else if(map[r][c] == -1) break;

				// 출발 위치로 돌아오면 종료
			else if(r==sr && c==sc) break;

			else if(map[r][c] == 1) {
				dir = one[dir];
				cnt++;
			}
			else if(map[r][c] == 2) {
				dir = two[dir];
				cnt++;
			}
			else if(map[r][c] == 3) {
				dir = three[dir];
				cnt++;
			}
			else if(map[r][c] == 4) {
				dir = four[dir];
				cnt++;
			}

			// 웜홀
			else if(map[r][c] == 6) {
				if(r==six.get(0).r && c==six.get(0).c) {
					r = six.get(1).r;
					c = six.get(1).c;
				}
				else {
					r = six.get(0).r;
					c = six.get(0).c;
				}
			}
			else if(map[r][c] == 7) {
				if(r==seven.get(0).r && c==seven.get(0).c) {
					r = seven.get(1).r;
					c = seven.get(1).c;
				}
				else {
					r = seven.get(0).r;
					c = seven.get(0).c;
				}
			}
			else if(map[r][c] == 8) {
				if(r==eight.get(0).r && c==eight.get(0).c) {
					r = eight.get(1).r;
					c = eight.get(1).c;
				}
				else {
					r = eight.get(0).r;
					c = eight.get(0).c;
				}
			}
			else if(map[r][c] == 9) {
				if(r==nine.get(0).r && c==nine.get(0).c) {
					r = nine.get(1).r;
					c = nine.get(1).c;
				}
				else {
					r = nine.get(0).r;
					c = nine.get(0).c;
				}
			}
			else if(map[r][c] == 10) {
				if(r==ten.get(0).r && c==ten.get(0).c) {
					r = ten.get(1).r;
					c = ten.get(1).c;
				}
				else {
					r = ten.get(0).r;
					c = ten.get(0).c;
				}
			}

		}

		ret = Math.max(ret, cnt);
	}

	private static boolean isIn(int r, int c) {
		return 0<=r&&r<N && 0<=c&&c<N;
	}


}
