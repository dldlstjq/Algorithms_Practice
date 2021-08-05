/*
문제 자체 이해는 쉬웠다.
그냥 단순하게 접근해서 2중 for문으로 풀었더니 예상하듯이 시간초과를 받았다.
그럼 어떻게 접근해야하나 싶었는데 거꾸로 계산을 한다는 것을 보고 스택을 사용하기로 했다.
본인보다 크거나 같은 탑이 있으면 그 탑이 신호를 받고 본인보다 작은 탑은 팝해서 날리면 됐다.
팝을 할 때 이대로 날려도 되는건가 싶었지만 어차피 현재 탑보다 작으면 현재 탑에서 다 걸리기 때문에 날려줘도 상관없었다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main {

	public static void main(String[] args) throws Exception{

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		int arr[] = new int[N];
		int ret[] = new int[N];	// 정답 저장
		HashMap<Integer, Integer> hMap = new HashMap<Integer, Integer>();
		
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		for(int i=0; i<N; ++i) {
			arr[i] = Integer.parseInt(st.nextToken());
			hMap.put(arr[i], i+1);	// 값과 인덱스를 쌍으로 저장
		}
		Stack<Integer> stack = new Stack<Integer>();
		for(int i=0; i<N; ++i) {
			// 스택이 있거나 높이가 작으면 계속 뺌
			while(!stack.isEmpty() && stack.peek() < arr[i])
				stack.pop();
			// 비었으면 자신보다 큰 탑이 없다
			if(stack.isEmpty())
				ret[i] = 0;
			// 자신보다 크거나 같으면 해당 탑의 인덱스를 저장
			else if(stack.peek()>=arr[i]) 
				ret[i] = hMap.get(stack.peek());
			// 자기자신 푸시
			stack.push(arr[i]);
		}
		
		StringBuilder sb = new StringBuilder();
		for(int num: ret)
			sb.append(num+" ");
		System.out.println(sb);
		
	}
}