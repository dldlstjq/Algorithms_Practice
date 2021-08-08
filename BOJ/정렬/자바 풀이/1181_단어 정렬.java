/*
Comparator를 구현하면 되는건데 String의 경우 자체적으로 compareTo라는 API가 있어 그걸 갖다 쓰면 된다.
compareTo는 사전순으로 정렬하도록 만들어 준다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.StringTokenizer;


public class Main {
	
	// Comparator를 익명객체로 구현
	// Comparator 인터페이스의 compare 함수를 재정의
	// 원래는 두 원소 중 첫번째가 두번째보다 작으면 음수, 같으면 0, 두번째가 더 크면 양수를 리턴한다.
	// 단순히 뺄셈 연산을 하면 경우를 안 나눠도 되지만 언더, 오버플로우 문제가 발생할 수 있기에 뺄셈은 주의해야 한다.
	static Comparator<String> comp = new Comparator<String>(){
		@Override
		public int compare(String e1, String e2) {
			if(e1.length() == e2.length())
				return e1.compareTo(e2);	// 사전 순 정렬
			else
				return e1.length() - e2.length();
		}
	};

	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		int N = Integer.parseInt(br.readLine());
		
		String arr[] = new String[N];
		for(int i=0; i<N; ++i) 
			arr[i] = br.readLine();


		// 1. Comparator 객체를 직접 만든다.
		Arrays.sort(arr, comp);
		
		// 2. 람다식 사용
		Arrays.sort(arr, new Comparator<String>() {
			@Override
			public int compare(String e1, String e2) {
				if(e1.length() == e2.length())
					return e1.compareTo(e2);	// 사전 순 정렬
				else
					return e1.length() - e2.length();
			}
		});
		
		// 3. 2의 람다식을 더 간단하게
		Arrays.sort(arr, (e1, e2) -> {
			if(e1.length() == e2.length())
				return e1.compareTo(e2);	// 사전 순 정렬
			else
				return e1.length() - e2.length();
		});
		
		
		
		StringBuilder sb = new StringBuilder();
		sb.append(arr[0]).append('\n');
		for(int i=1; i<N; ++i) {
			if(!arr[i].equals(arr[i-1]))
				sb.append(arr[i]).append('\n');
		}
			
		System.out.println(sb);
		
		
	}

}