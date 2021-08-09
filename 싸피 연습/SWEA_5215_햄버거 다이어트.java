/*
재료가 중복이 되지 않기 때문에 인덱스 조절을 하면서 칼로리가 넘지 않도록 재료를 선택하는 것으로 구현했다.
분명 맞는 로직인데 첫번째 케이스만 통과하고 그 뒤로는 통과하지 못했다.
대체 왜 안될까 싶어서 다른 사람 코드도 보고 했는데 별 차이가 없어 보였다.
혹시나 해서 출력을 살펴보니 개행을 두 번해서 형식이 안맞아 틀린거였다....
다행히 로직에는 큰 문제가 없어 좋았고 첫번째만 틀릴경우 출력을 한 번 살펴보자.

void형식, return 형식 두가지로 풀었다.
부분집합을 이용해 푸는 방법도 있다.
*/


import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main_5215_이인섭 {
	
	static int N,L;	// 재료 수, 제한 칼로리
	static int food[][];	// 점수, 칼로리
	
	// cnt: 인덱스, score: 점수, calorie: 칼로리
	static int solve1(int cnt, int score, int calorie) {
		int ans = score;
		for(int i=cnt; i<N; ++i) {
			// 칼로리가 L을 넘지 않는다면 추가하고 다음 재료 확인
			if(calorie+food[i][1] <= L)
				ans =  Math.max(ans, solve1(i+1, score+food[i][0], calorie+food[i][1]));
		}
		return ans;
	}

	// idx: 인덱스, score: 점수, calorie: 칼로리 제한
	static void solve(int idx, int score, int calorie) {
		for(int i=idx; i<N; ++i) {
			// 현재 칼로리와 해당 음식의 칼로리가 정해진 칼로리 이하 일때
			if(calorie+food[i][1] <= L)
				solve(i+1, score+food[i][0], calorie+food[i][1]);
			
		}
		ret = Math.max(ret, score);
	}
	 
	public static void main(String[] args) throws Exception{
		System.setIn(new FileInputStream("sample_input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		StringTokenizer st;
		for(int test_case = 1; test_case <= T; test_case++)
		{
			st = new StringTokenizer(br.readLine(), " ");
			N = Integer.parseInt(st.nextToken());
			L = Integer.parseInt(st.nextToken());
			
			food = new int[N][2];
			
			for(int i=0; i<N; ++i) {
				st = new StringTokenizer(br.readLine(), " ");
				food[i][0] = Integer.parseInt(st.nextToken());
				food[i][1] = Integer.parseInt(st.nextToken());
			}
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case + " " +solve1(0,0,0));
			System.out.println(sb);
		}
	}

}

