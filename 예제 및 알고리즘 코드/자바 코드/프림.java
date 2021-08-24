/*
또 다른 MST 중 프림 알고리즘이다.
크루스칼은 정렬시간이 추가로 있어 시간이 좀 더 걸리지만 프림은 크루스칼보다 시간적 이점이 있다고 했다.
크루스칼 보다는 조금 어려운데 그래도 알고 있으면 나쁠건 없다.
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class MSTPrimTest {

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(in.readLine());
		int[][] adjMatrix = new int[N][N];
		boolean[] visited = new boolean[N];
		int[] minEdge = new int[N];
		
		StringTokenizer st = null;
		for (int i = 0; i < N; i++) {
			st = new StringTokenizer(in.readLine(), " ");
			for (int j = 0; j < N; j++) {
				adjMatrix[i][j] = Integer.parseInt(st.nextToken());
			}
			minEdge[i] = Integer.MAX_VALUE;
		}
		
		int result=0; // 최소신장트리 비용
		minEdge[0] = 0; // 임의의 시작점 0의 간선비용을 0으로 세팅
		
		for (int i = 0; i < N; i++) {
			// 1. 신장트리에 포함되지 않은 정점 중 최소간선비용의 정점 찾기
			int min = Integer.MAX_VALUE;
			int minVertex = -1; // 최소간선비용의 정점번호
			for (int j = 0; j < N; j++) {
				if(!visited[j] && min>minEdge[j]) {
					min = minEdge[j];
					minVertex = j;
				}
			}
			
			visited[minVertex] = true; // 신장트리에 포함시킴
			result += min;  // 간선비용 누적
			
			// 2. 선택된 정점 기준으로 신장트리에 연결되지 않은 타 정점과의 간선 비용 최소로 업데이트
			for (int j = 0; j < N; j++) {
				if(!visited[j] &&  adjMatrix[minVertex][j] != 0 && minEdge[j]> adjMatrix[minVertex][j]) {
					minEdge[j] = adjMatrix[minVertex][j];
				}
			}
		}
		
		System.out.println(result);
	}

}
