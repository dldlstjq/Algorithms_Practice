/*
구현하는데 실수가 조금 많았다.
경사로를 놓을 때 경사로 길이 확인에서 틀렸고 이미 경사로를 놓은 위치에는 놓을 수 없다는걸 간과했다.
그걸 알고나니 무난하게 구현할 수 있었다.
결국 실수를 얼마나 줄이고 하느냐가 관건이다.
배열을 하나 더 선언해서 인덱스만 바꿔주면 함수 하나로도 구현 가능하다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
	
	static int N, L;
	static int [][]map;
	static int [][]map2;
	
	static int check(int [][] arr) {
		boolean [][]isRoad = new boolean[N][N];	// 경사로 있는지 여부
		int ret=0;
		for(int i=0; i<N; ++i) {
			int cnt=0;
			outer:
			for(int j=0; j<N-1; ++j) {
				// 차이가 2 이상이면 실패
				if(Math.abs(arr[i][j] - arr[i][j+1])>=2)
					break;
				
				// 같은 높이면 패스
				if(arr[i][j] == arr[i][j+1]) {
					cnt++;
					continue;
				}
				
				// 다음 이동할 길이 더 크다.
				if(arr[i][j] < arr[i][j+1] && arr[i][j+1]-arr[i][j] == 1) {
					if(j-(L-1)<0/* || map[i][j-L-1] != map[i][j]*/)
						break;
					for(int k = j; k>=j-(L-1); --k) {
						if(arr[i][j] != arr[i][k] || isRoad[i][k]) 
							break outer;
						else
							isRoad[i][k] = true;
					}
					cnt++;
				}
				
				// 다음 이동할 길이 더 작다.
				else if(arr[i][j] > arr[i][j+1] && arr[i][j]-arr[i][j+1] == 1) {
					if(j+L>=N /*|| map[i][j+L] != map[i][j+1]*/)
						break;
					for(int k = j+1; k<=j+L; ++k)
						if(arr[i][j+1] != arr[i][k] || isRoad[i][k]) 
							break outer;
						else
							isRoad[i][k] = true;
					cnt++;
				}
				
			}
			if(cnt == N-1)
				ret++;
		}
		
		return ret;
	}

	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		L = Integer.parseInt(st.nextToken());
		
		map = new int[N][N];
		map2 = new int[N][N];
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<N; ++j) {
				map[i][j] = Integer.parseInt(st.nextToken());
				map2[j][i] = map[i][j]; 
			}
		}
		
		int a= check(map);
		int b= check(map2);
		System.out.println(a+b);
	}

}