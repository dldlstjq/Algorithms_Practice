/*
이전에 풀어봤던 문제인데 대표적으로 큐를 이용해서 풀 수 있다.
굳이 큐를 이용하지 않고 리스트로도 풀 수 있을 것 같았는데 핵심은 인덱스 조절이다.
인덱스만 잘 조절하면 단순히 삭제만 하면 되기 때문에 큐보다 시간이 훨씬 더 적게 걸린다.
큐는 k-1번째까지 계속 poll과 offer를 반복하기 때문에 시간이 좀 더 걸리는 것 같다.

큐: 668ms
리스트: 156ms
*/

// 큐 풀이
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		StringBuilder sb = new StringBuilder();
		
		int N = Integer.parseInt(st.nextToken());
		int K = Integer.parseInt(st.nextToken());
		
		Queue<Integer> q = new LinkedList<Integer>();
		
		for(int i=1; i<=N; ++i) 
			q.offer(i);
		
		sb.append('<');
		while(!q.isEmpty()) {
			int cnt = 0;
			// K번째 수를 넣기 때문에 K-1번째 수까지는 큐의 맨 뒤로.
			while(cnt < K-1) {
				int curr = q.poll();
				q.offer(curr);
				cnt++;
			}
			// 마지막 하나가 남으면 >를 붙이고 아니면 ,를 붙인다.
			if(q.size()>1)
				sb.append(q.poll()+", ");
			else
				sb.append(q.poll()).append('>');
		}
		
		System.out.println(sb);
	}
}



// 리스트 풀이
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		StringBuilder sb = new StringBuilder();
		
		int N = Integer.parseInt(st.nextToken());
		int K = Integer.parseInt(st.nextToken());
		
		ArrayList<Integer> list = new ArrayList<Integer>();
		
		for(int i=1; i<=N; ++i) 
			list.add(i);
		
		sb.append('<');
		int idx = 0;
		while(!list.isEmpty()) {
			idx = (idx+K-1)%list.size();
			sb.append(list.remove(idx)).append(", ");
		}
		sb.setLength(sb.length()-2);
		sb.append('>');
		
		System.out.println(sb);
	}
}
