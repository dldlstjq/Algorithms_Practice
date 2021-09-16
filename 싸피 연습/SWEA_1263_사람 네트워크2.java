/*
플로이드-와샬 알고리즘을 사용하는 문제이다.
각 정점간 최단거리를 구할 때 사용하는데 코드 자체는 3중 for문을 돌리면 돼서 그렇게 어렵진 않다.
하지만 경유지와 출발지, 도착지를 헷갈리는 순간 어렵게 되고 이해를 못하면 응용문제가 나왔을 때 코드 수정이 쉽지 않을 것 같다.
반드시 손으로 그리면서 원리를 알아야 기억하기도, 응용하기도 쉬울 것 같다.

이 문제에서도 자기자신으로의 노드 연결은 없기 때문에 최종 값을 구할 때 자기 자신 연결은 빼야 답이 나온다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {
	
	
	public static void main(String[] args) throws Exception {
		//System.setIn(new FileInputStream("input.txt"));
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T;
		T= Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());
			int N = Integer.parseInt(st.nextToken());
			
			int[][] adj = new int[N][N];
			int INF = 987654321;
			
			for(int i=0; i<N; ++i) {
				for(int j=0; j<N; ++j) {
					adj[i][j] = Integer.parseInt(st.nextToken());
					if(adj[i][j] == 0)
						adj[i][j] = INF;
				}
			}
			
			// 경 출 도
			for(int k=0; k<N; ++k) {
				for(int i=0; i<N; ++i) {
					for(int j=0; j<N; ++j) {
						adj[i][j] = Math.min(adj[i][j], adj[i][k]+adj[k][j]);
					}
				}
			}
			
			int min = Integer.MAX_VALUE;
			// 가장 짧은 합 구함
			for(int i=0; i<N; ++i) {
				int sum = 0;
				for(int j=0; j<N; ++j) {
					if(i == j)
						continue;
					sum += adj[i][j];
				}
				min = Math.min(min, sum);
			}
			
			StringBuilder sb= new StringBuilder();
			sb.append("#"+test_case+" "+ min);
			System.out.println(sb);
		}
	}
}

