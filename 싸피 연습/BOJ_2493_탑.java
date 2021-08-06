/*
문제 자체 이해는 쉬웠다.
그냥 단순하게 접근해서 2중 for문으로 풀었더니 예상하듯이 시간초과를 받았다.
그럼 어떻게 접근해야하나 싶었는데 거꾸로 계산을 한다는 것을 보고 스택을 사용하기로 했다.
본인보다 크거나 같은 탑이 있으면 그 탑이 신호를 받고 본인보다 작은 탑은 팝해서 날리면 됐다.
팝을 할 때 이대로 날려도 되는건가 싶었지만 어차피 현재 탑보다 작으면 현재 탑에서 다 걸리기 때문에 날려줘도 상관없었다.


스택을 선언할 때 int 형 배열로 선언해서 인덱스와 탑 높이를 저장해도 되고 클래스를 선언해도 된다.
*/

// class를 이용한 스택 풀이
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Stack;
import java.util.StringTokenizer;

class Top{
	int height;
	int number;
	public Top(int height, int number) {
		this.height = height;
		this.number = number;
	}
}

public class Solution {
	

	public static void main(String[] args) throws Exception{

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		StringBuilder sb = new StringBuilder();
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		Stack<Top> stack = new Stack<>();
//		Stack<int[]> stack = new Stack<>();
		for(int i=1; i<=N; ++i) {
			int num = Integer.parseInt(st.nextToken());	// 현재 탑의 높이
			
			while(true) {
				// 스택이 비어있는 경우
				if(stack.isEmpty()) {
					sb.append("0");
					stack.push(new Top(i, num));	// 탑 높이와 번호 담기
					break;
				}
				
				// 스택의 top요소의 정보 받아오기
				Top top = stack.peek();
				
				// 현재 탑 높이가 top보다 높을 경우
				if(top.height < num)
					stack.pop();
				
				// 현재 탑높이가 top보다 낮은 경우
				else {
					sb.append(top.number+" ");	// 탑 번호 출력
					stack.push(new Top(i, num));	// 현재 탑정보 push
					break;
				}
			}
		}
		System.out.println(sb);
	}
}




// 첫 풀이. 해시맵으로 인덱스와 탑 높이 저장
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