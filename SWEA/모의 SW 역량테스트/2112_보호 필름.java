/*
어려운 문제....
A, B 두개를 최소한으로 써서 K개 이상 통과해야 하는데 어떻게 조합해야 A,B를 적절히 할 수 있을지 생각이 안났다.

다른 사람 풀이를 보니 DFS를 써서 A를 넣고 층 증가, B를 넣어주고 층 증가 이런식으로 풀이했다.
A, B를 집어넣은 다음에는 원래 상태로 되돌려놨고 배열 전체를 되돌리는 것이 아니라 바꾼 층만 되돌린다.
그리고 A, B를 바로 넣는 것이 아니라 안넣고, A 넣고, B 넣고 이런 식으로 해야 모든 경우를 파악할 수 있다.

결정적으로 K개가 연속인지 확인하는 과정을 3중 for 문을 돌면서 했는데 시간초과가 났다.
2중 for문 돌면서 같은 숫자가 계속 나오면 카운팅 해주고 다른 숫자가 나오면 카운팅을 초기화해서 계속 가면 된다.

꼭 다시 풀어봤으면 하는 문제이다.

 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {

	static int D,W,K;
	static int[][] film, tmp;

	static int ret;

	public static void main(String[] args) throws IOException {
		//System.setIn(new FileInputStream("sample_input.txt"));

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int T = Integer.parseInt(br.readLine());

		for(int test_case = 1; test_case <= T; test_case++)
		{
			StringTokenizer st = new StringTokenizer(br.readLine());
			D = Integer.parseInt(st.nextToken());
			W = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());

			film = new int[D][W];
			tmp = new int[D][W];

			for(int i=0; i<D; ++i) {
				st = new StringTokenizer(br.readLine());
				for(int j=0; j<W; ++j) {
					film[i][j] = Integer.parseInt(st.nextToken());
					tmp[i][j] = film[i][j];
				}
			}

			ret = Integer.MAX_VALUE;
			if(testFilter()) ret = 0;
			else start(0, 0);

			StringBuilder sb = new StringBuilder();
			sb.append("#").append(test_case).append(" ").append(ret);
			System.out.println(sb);
		}
	}

	private static void start(int cnt, int layer) {
		if(cnt>=ret) return;

		if(layer==D) {
			if(testFilter())
				ret = Math.min(cnt, ret);
			return;
		}

		// 아무것도 투입 안함
		start(cnt, layer+1);

		// A 투입
		for(int i=0; i<W; ++i)
			film[layer][i] = 0;
		start(cnt+1, layer+1);

		// B 투입
		for(int i=0; i<W; ++i)
			film[layer][i] = 1;
		start(cnt+1, layer+1);

		// 원상복구
		for(int i=0; i<W; ++i)
			film[layer][i] = tmp[layer][i];
	}

	private static boolean testFilter() {
		for(int i=0; i<W; ++i) {
			boolean flag = false;
			int cnt = 1;
			int prev = film[0][i];
			for(int j=1; j<D; ++j) {
				if(prev == film[j][i]) cnt++;
				else {
					prev = film[j][i];
					cnt=1;
				}
				if(cnt==K) {
					flag = true;
					break;
				}
			}
			if(!flag) return false;
		}

		return true;
	}
}
