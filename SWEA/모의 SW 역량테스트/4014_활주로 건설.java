/*
비교적 빠른 시간내에 풀 수 있었다.
아무래도 몇 번 풀어봤던 기억이 있어 어떻게 조건을 설정해야 하는지 알 수 있어 그런 것 같다.
기본 배열을 저장하고 행, 열을 바꿔서 저장한느 배열을 따로 만든뒤에 둘 다 계산했다.

경사로의 경우 자기보다 클 때, 작을 때 나눠서 조건을 검사했고 경사로 끝만 범위에 들어오는지, 다른 경사로가 이미 있는지, 같은 높이인지 검사해줬다.
처음에 케이스 7번만 틀려서 틀린 부분을 찾아봤고 높이가 2이상이면 안되는 조건을 빼먹었다.
제출하니 49개만 맞았다고 했는데 자기보다 큰 걸 만났을 때만 높이 2이상임을 검사했다.
자기보다 높이가 작을때도 2이상인지 검사 했어야 했는데 그걸 빼먹었다.
절대값을 이용해서 계산해주니 정답을 받을 수 있었다.
 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {

	static int N, X;
	static int[][] map;
	static int[][] colMap;
	static int ret;

	static boolean[] isPath;
	static boolean[] isPath1;

	public static void main(String[] args) throws IOException {
		//System.setIn(new FileInputStream("sample_input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int T = Integer.parseInt(br.readLine());


		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st= new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			X = Integer.parseInt(st.nextToken());

			map = new int[N][N];
			colMap = new int[N][N];
			for(int i=0; i<N; ++i) {
				st= new StringTokenizer(br.readLine());
				for(int j=0; j<N; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
					colMap[j][i] = map[i][j];
				}
			}

			ret=0;
			start();

			StringBuilder sb=  new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(ret);
			System.out.println(sb);

		}
	}

	private static void start() {
		for(int i=0; i<N; ++i) {
			isPath = new boolean[N];
			if(isPossible(i))
				ret++;

			isPath1 = new boolean[N];
			if(isRowPossible(i))
				ret++;
		}
	}

	private static boolean isRowPossible(int i) {
		for(int j=0; j<N-1; ++j) {
			if(colMap[i][j] == colMap[i][j+1]) continue;

				// 높이가 1보다 크면 안됨
			else if(Math.abs(colMap[i][j]-colMap[i][j+1])>=2) return false;

			else if(colMap[i][j] < colMap[i][j+1]) {
				// 경사로 마지막이 범위를 벗어나거나 이미 다른 경사로 설치되어 있다면 불가
				if(j-(X-1) <0 || isPath1[j-(X-1)]) return false;

					// 현재 높이와 경사로 마지막 높이가 맞지 않으면 불가
				else if(colMap[i][j-(X-1)] != colMap[i][j]) return false;

				else {	// 그 외의 경우는 설치 가능
					for(int k=j; k>=j-(X-1); --k)
						isPath1[k] = true;
				}
			}
			else if(colMap[i][j] > colMap[i][j+1]) {
				// 경사로 마지막이 범위를 벗어나거나 이미 다른 경사로 설치되어 있다면 불가
				if(j+X >=N || isPath1[j+X]) return false;

					// 설치할 첫번째 높이와 경사로 마지막 높이가 맞지 않으면 불가
				else if(colMap[i][j+X] != colMap[i][j+1]) return false;

				else {	// 그 외의 경우는 설치 가능
					for(int k=j+1; k<=j+X; ++k)
						isPath1[k] = true;
				}
			}
		}
		return true;
	}

	private static boolean isPossible(int i) {
		for(int j=0; j<N-1; ++j) {
			if(map[i][j] == map[i][j+1]) continue;

				// 높이가 1보다 크면 안됨
			else if(Math.abs(map[i][j]-map[i][j+1])>=2) return false;
			else if(map[i][j] < map[i][j+1]) {
				// 경사로 마지막이 범위를 벗어나거나 이미 다른 경사로 설치되어 있다면 불가
				if(j-(X-1) <0 || isPath[j-(X-1)]) return false;

					// 현재 높이와 경사로 마지막 높이가 맞지 않으면 불가
				else if(map[i][j-(X-1)] != map[i][j]) return false;

				else {	// 그 외의 경우는 설치 가능
					for(int k=j; k>=j-(X-1); --k)
						isPath[k] = true;
				}
			}
			else if(map[i][j] > map[i][j+1]) {
				// 경사로 마지막이 범위를 벗어나거나 이미 다른 경사로 설치되어 있다면 불가
				if(j+X >=N || isPath[j+X]) return false;

					// 설치할 첫번째 높이와 경사로 마지막 높이가 맞지 않으면 불가
				else if(map[i][j+X] != map[i][j+1]) return false;

				else {	// 그 외의 경우는 설치 가능
					for(int k=j+1; k<=j+X; ++k)
						isPath[k] = true;
				}
			}
		}
		return true;
	}
}
