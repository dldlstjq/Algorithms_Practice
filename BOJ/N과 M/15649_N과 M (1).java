/*
조합을 사용하는 문제 같다.
잊을만하면 계속 풀어서 순열, 조합은 확실히 마스터 해야된다.
StringBuilder를 이용하는 거랑 System.out.print 이용에 속도차이가 엄청 난다.

StringBuilder: 272~280ms
System.out.print: 1900ms~2200ms

 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {

	static int N, M;
	static int arr[];
	static StringBuilder sb = new StringBuilder();

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;

		st = new StringTokenizer(br.readLine());

		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());

		arr = new int[M];

		solve(0, 0);
		System.out.println(sb);

	}
	private static void solve(int idx, int visited) {
		if(idx == M) {
			for(int i=0; i<M; ++i)
				sb.append(arr[i]).append(" ");
			sb.append("\n");
			return;
		}

		for(int i=1; i<=N; ++i) {
			if((visited&(1<<i)) !=0) continue;
			arr[idx] = i;
			solve(idx+1, visited|(1<<i));
		}
	}
}