/*
최단 경로를 구하는 다익스트라이다.
종만북과는 다르게 일반 for문을 이용해 구하는데 우선순위 큐 보다는 시간이 조금 더 걸리는 것 같다.
두가지 방법 다 알아두자.
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;


public class DijkstraTest {

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(in.readLine().trim());
		int V = Integer.parseInt(st.nextToken()); //정점 갯수
		int start = 0;
		int end =  V-1; //도착점 인덱스
		final int INFINITY = Integer.MAX_VALUE;
		
		int[][] matrix = new int[V][V];
		int[] distance = new int[V];
		boolean[] visited = new boolean[V];
		
		for(int i=0; i<V; ++i){
			st = new StringTokenizer(in.readLine().trim(), " ");
			for(int j=0; j<V; ++j){
				matrix[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		Arrays.fill(distance, INFINITY);
		distance[start] = 0;
		
		int min=0, current=0;
		for(int i=0; i<V; ++i){
			//a단계 : 방문하지 않은 정점들 중 최소가중치의 정점 선택
			min = INFINITY;
			for(int j=0; j<V; ++j){
				if(!visited[j] && distance[j] < min){
					min = distance[j];
					current = j;
				}
			}
			visited[current] = true; // 선택 정점 방문 처리
			if(current == end){ // 선택 정점이 도착정점이면 탈출.
				break;
			}
			
			//b단계: current정점을 경유지로 하여 갈수 있는 다른 방문하지 않은 정점들에 대한 처리
			for(int c=0; c<V; ++c){
				if(!visited[c] && matrix[current][c] != 0
						&&  distance[c] > min+matrix[current][c]){
					distance[c] = min+matrix[current][c];
				}
			}
		}
		System.out.println(distance[end]);
		
	}

}
