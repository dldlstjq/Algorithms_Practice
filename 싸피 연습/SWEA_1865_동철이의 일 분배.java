/*
일을 완료할 수 있는 확률의 최대값을 구하는 문제이다.
가장 처음 든 생각은 순열로 모든 경우의 수를 구한 다음 시간을 줄이는 방법을 생각하는 것이었다.
N이 최대 15이므로 모든 경우의 수를 구하면 시간초과가 나고 시간을 줄여야 하는데 그 방법이 생각나지 않았다.
그리디로 해서 가장 확률이 높은 것부터 차례대로 하면 어떨까 생각했지만 제대로 된 답이 안나왔다.
결국 다른 사람 풀이를 보고 힌트를 얻었는데 백트래킹을 하여 안되는 건 미리 걸러내는 것이었다.
확률이므로 곱하는 수는 1을 넘지 않고 현재 최대값보다 작다면 아무리 곱해도 더 커질 수 없기 때문에 현재 확률이 최대값보다 같거나 작으면 가지치기하면 된다.

백트래킹 방법이 생각이 안나서 풀이를 잘 몰랐는데 다시 알고리즘 문제를 풀면서 감을 빨리 익혀나가야겠다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {
	
	static int N;
	static int prob[][];
	static double ret;
	
	public static void main(String[] args) throws Exception {
		
		//System.setIn(new FileInputStream("input.txt"));
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		
		int T = Integer.parseInt(br.readLine());
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			N = Integer.parseInt(br.readLine());
			
			prob = new int[N][N];
			
			StringTokenizer st = null;
			for(int i=0; i<N; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<N; ++j)
					prob[i][j] = Integer.parseInt(st.nextToken());
			}
			
			ret=0;
			perm(0, 0, 1);
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case+" "+String.format("%.6f", ret*100));
			System.out.println(sb.toString());
		}
	}

	private static void perm(int idx, int flag, double sum) {
		if(idx == N) {
			ret = Math.max(ret, sum);
			return;
		}
		// 백트래킹. 확률은 1보다 작기 때문에 곱해봤자 더 커질 수는 없다.
		if(sum <= ret) return;
		
		for(int i=0; i<N; ++i) {
			if((flag&1<<i) != 0) continue;
			perm(idx+1, flag|1<<i, sum*(prob[idx][i]*0.01));
		}
	}
}
