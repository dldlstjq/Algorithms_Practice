/*
큐 2개를 이용해서 풀었다.
N이 짝수, 홀수인 경우를 나눠서 저장했고 하나씩 번갈아가며 저장한 후 출력하면 정답이 나온다.
사실 인덱스 설정만으로도 쉽게 풀리는 문제여서 큐를 사용하는 것보다 인덱스만 적절하게 조정해서 푸는게 더 좋은 풀이 같다.
입력값을 하나의 배열에다 저장하는데 인덱스를 0, 2, 4 ... 이런식으로 하나씩 저장하고
1, 3, 5 .... 이런식으로 하나씩 저장한 뒤 배열을 출력하면 끝이다.
간결하게 풀 수도 있다는 것을 느꼈다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;

public class Solution {

	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
				
		for(int test_case = 1; test_case <= T; test_case++)
		{
			int N = Integer.parseInt(br.readLine());
			
			Queue<String> q1 = new LinkedList<String>();
			Queue<String> q2 = new LinkedList<String>();
			
			List<String> ans = new LinkedList<String>();
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			for(int i=0; i<N; ++i) {
				// N이 짝수일 때는 N/2 미포함
				if(N%2 ==0 && i < N/2)
					q1.offer(st.nextToken());
				// N이 홀수일 때는 N/2 포함
				else if(N%2 == 1 && i <= N/2)
					q1.offer(st.nextToken());
				else
					q2.offer(st.nextToken());
			}
			
			// 두 개의 큐가 비어있지 않을 때 까지 반복
			while(!q1.isEmpty() || !q2.isEmpty()){
				if(!q1.isEmpty())
					ans.add(q1.poll());
				if(!q2.isEmpty())
					ans.add(q2.poll());
			}
			
			StringBuilder sb = new StringBuilder();
			sb.append("#" + test_case + " ");
			for(String n: ans)
				sb.append(n + " ");
			System.out.println(sb);
		}
	}
}

