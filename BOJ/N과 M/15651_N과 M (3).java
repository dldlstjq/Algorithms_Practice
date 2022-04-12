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

		solve(0, 1);
		System.out.println(sb);
	}

	private static void solve(int idx, int start) {
		if(idx == M) {
			for(int i=0; i<M;++i)
				sb.append(arr[i]).append(" ");
			sb.append("\n");
			return;
		}

		for(int i=1; i<=N; ++i) {
			arr[idx]=i;
			solve(idx+1, i+1);
		}
	}
}