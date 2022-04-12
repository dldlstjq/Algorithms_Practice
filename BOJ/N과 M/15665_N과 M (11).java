import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {

	static int N, M;
	static int arr[];
	static int tmp[];
	static StringBuilder sb = new StringBuilder();

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;

		st = new StringTokenizer(br.readLine());

		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		arr = new int[N];
		tmp = new int[M];

		st = new StringTokenizer(br.readLine());
		for(int i=0; i<N; ++i)
			arr[i] = Integer.parseInt(st.nextToken());

		Arrays.sort(arr);
		solve(0, 0);
		System.out.println(sb);
	}

	private static void solve(int idx, int start) {
		if(idx == M) {
			for(int i=0; i<M;++i)
				sb.append(tmp[i]).append(" ");
			sb.append("\n");
			return;
		}

		int prev = -1;
		for(int i=0; i<N; ++i) {
			if(arr[i] == prev) continue;
			prev = arr[i];
			tmp[idx]=arr[i];
			solve(idx+1, i+1);
		}
	}
}