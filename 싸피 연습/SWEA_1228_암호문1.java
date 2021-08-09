/*
되게 쉬운데 입력처리를 잘못해서, 문제 이해를 잘못해서 시간이 걸렸다.
x 위치 부터 y개 숫자를 계속해서 삽입하기 때문에 배열 크기가 늘어날 수가 있다.
그래서 배열로 고정크기를 사용하는게 아니라 리스트를 써서 늘어나게 해야 한다.
입력 처리도 I는 그냥 비워주고 그 뒤로 숫자를 하나씩 받아오면 쉽게 풀리는 문제이다.
예상치 못한 데에서 시간이 많이 걸리는데 이런 건 좀 보완해야겠다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

/*
   사용하는 클래스명이 Solution 이어야 하므로, 가급적 Solution.java 를 사용할 것을 권장합니다.
   이러한 상황에서도 동일하게 java Solution 명령으로 프로그램을 수행해볼 수 있습니다.
 */
class Solution
{
	public static void main(String args[]) throws Exception
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		for(int test_case = 1; test_case <= 10; test_case++)
		{
			ArrayList<Integer> list = new ArrayList<Integer>();
			int N = Integer.parseInt(br.readLine());

			
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			for(int i=0; i<N; ++i) 
				list.add(Integer.parseInt(st.nextToken()));
			
				
			int order = Integer.parseInt(br.readLine());
			st = new StringTokenizer(br.readLine(), " ");
			
			for(int i=0; i<order; ++i) {
				String str = st.nextToken();
				int x = Integer.parseInt(st.nextToken());
				int y = Integer.parseInt(st.nextToken());
				
				for(int j=0; j<y; ++j) 
					list.add(x++, Integer.parseInt(st.nextToken()));
			}
		
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case + " ");
			for(int i=0; i<10; ++i)
				sb.append(list.get(i)+ " ");
			sb.setLength(sb.length()-1);
			System.out.println(sb);
			
		}
	}
}
