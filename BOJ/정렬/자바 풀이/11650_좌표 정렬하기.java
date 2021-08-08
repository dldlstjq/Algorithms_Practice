/*
일반 정렬이 아닌 특수한 경우의 정렬이다.
c++과 비슷한듯 다르게 자바에도 sort 함수가 있지만 객체나 특별한 형식을 정렬할 때는 Comparable, Comparator란 인터페이스를 사용한다.
자세한건 인터넷을 참고하는게 좋고 밑의 풀이처럼 익명함수로 구현하는게 편할 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.StringTokenizer;


public class Main {

	// Comparator을 구현한 하나의 클래스를 넘겨준다고 보시면 됩니다
	// Comparator 인터페이스의 compare 함수를 재정의
	// 원래는 두 원소 중 첫번째가 두번째보다 작으면 음수, 같으면 0, 두번째가 더 크면 양수를 리턴한다.
	// 단순히 뺄셈 연산을 하면 경우를 안 나눠도 되지만 언더, 오버플로우 문제가 발생할 수 있기에 뺄셈은 주의해야 한다.
	static Comparator<int[]> comp = new Comparator<int[]>(){
		@Override
		public int compare(int[] n1, int[] n2) {
			if(n1[0] == n2[0])
				return n1[1]-n2[1];
			else
				return n1[0]-n2[0];
		}
	};

	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		int N = Integer.parseInt(br.readLine());
		
		int arr[][] = new int[N][2];
		StringTokenizer st;
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			arr[i][0] = Integer.parseInt(st.nextToken());
			arr[i][1] = Integer.parseInt(st.nextToken());
		}
		
		// 1. Comparator 객체를 직접 만든다.
		Arrays.sort(arr, comp);
		
		// 2. 람다식 사용
		Arrays.sort(arr, new Comparator<int[]>() {
			@Override
			public int compare(int[] e1, int[] e2) {
				if(e1[0] == e2[0])
					return e1[1]-e2[1];
				else
					return e1[0]-e2[1];
			}
		});
		
		// 3. 2의 람다식을 더 간단하게
		Arrays.sort(arr, (e1, e2) -> {
			if(e1[0] == e2[0])
				return e1[1] - e2[1];
			else
				return e1[0] - e2[0];
		});
		
		
		
		StringBuilder sb = new StringBuilder();
		for(int i=0; i<N; ++i)
			sb.append(arr[i][0] + " "+arr[i][1]).append('\n');
		System.out.println(sb);
		
		
	}

}