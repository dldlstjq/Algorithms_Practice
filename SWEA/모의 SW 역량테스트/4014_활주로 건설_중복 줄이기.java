/*
중복된 코드를 조금이라도 더 줄이는 방법
 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;


public class Solution {

	static int N, X;
	static int[][] map;
	static int[][] colmap;

	static int ret;

	public static void main(String[] args) throws Exception {
//		System.setIn(new FileInputStream("sample_input.txt"));

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int T;
		T= Integer.parseInt(br.readLine());

		StringTokenizer st = null;
		StringBuilder sb = null;
		for(int test_case = 1; test_case <= T; test_case++)
		{
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			X = Integer.parseInt(st.nextToken());

			map = new int[N][N];
			colmap = new int[N][N];

			for(int i=0; i<N; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<N; ++j) {
					map[i][j] = Integer.parseInt(st.nextToken());
					colmap[j][i] = map[i][j];
				}

			}

			ret = 0;
			for(int i=0; i<N; ++i) {
				buildRoad(map[i]);
				buildRoad(colmap[i]);
			}

			sb = new StringBuilder();
			sb.append("#"+test_case+" "+ret);
			System.out.println(sb);
		}
	}

	// 경사로 지을 수 있는지 검사
	private static void buildRoad(int[] road) {
		// 높이 1, 가로 X
		boolean[] isRoad = new boolean[N];	// 이미 경사로가 지어졌는지

		for(int i=0; i<road.length-1; ++i) {
			// 높이 같으면 통과
			if(road[i] == road[i+1]) continue;
				// 높이 차이가 2 이상이면 활주로 건설 불가
			else if(road[i]+1 < road[i+1] || road[i] > road[i+1]+1) return;

			// 2 2 3 2 2 2
			if(road[i]+1 == road[i+1]) {
				// 자기보다 더 높은 활주로인 경우
				if(!makeUpRoad(i, road, isRoad))
					return;
			}

			// 3 3 3 2 1 1 
			// 3 3 3 2 2 2
			else if(road[i]-1 == road[i+1]) {
				//더 낮은 활주로
				if(!makeDownRoad(i, road, isRoad))
					return;

			}
		}

		ret++;	// 아무 문제 없으면 건설 가능
	}

	private static boolean makeUpRoad(int idx, int[] road, boolean[] isRoad) {
		//   i  
		// 2 2 3 2 2 2
		// 경사로 끝이 범위 벗어나거나 다른 경사로가 있다면 건설 불가
		if(idx-(X-1) < 0 || isRoad[idx-(X-1)]) return false;

		for(int i=idx; i>=idx-(X-1)+1; --i) {
			// 같은 높이가 아니거나 이미 경사로가 있으면 건설 불가
			if((road[i] != road[i-1]) || isRoad[i])
				return false;
			isRoad[i]= true;
		}
		isRoad[idx-(X-1)]= true;	// // i와 i-1을 비교하기 때문에 마지막 경사로까지 표시
		return true;
	}

	private static boolean makeDownRoad(int idx, int[] road, boolean[] isRoad) {
		//     i
		// 3 3 3 2 1 1 
		// 3 3 3 2 2 2
		// 경사로 끝이 범위 벗어나거나 다른 경사로가 있다면 건설 불가
		if(idx+X >= N || isRoad[idx+X]) return false;

		for(int i=idx+1; i<idx+X; ++i) {
			// 같은 높이가 아니거나 이미 경사로가 있으면 건설 불가
			if((road[i] != road[i+1]) || isRoad[i])
				return false;
			isRoad[i]= true;
		}
		isRoad[idx+X]= true;	// // i와 i+1을 비교하기 때문에 마지막 경사로까지 표시
		return true;
	}


}