/*
스택을 이용해 후위표기식을 만든뒤 계산하는 식이다.
후위표기식을 어떻게 사용하고 계산하는지만 안다면 쉽게 풀리는 문제이다.
자료구조 시간에 스택을 직접 만들어 계산한 것이 잠깐 생각났다.
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Stack;

public class Main_SWEA_1223_계산기2 {
	
	static char expression[];	// 초기 문자열 저장
	static ArrayList<Character> numbers = new ArrayList<>();	// 후위표기식 저장
	
	private static int calc_postfix() {
		Stack<Integer> stack = new Stack<>();	// 연산자 저장
		for(char ch: numbers) {
			// 숫자일 경우 스택에 푸시
			if('0' <= ch && ch <='9') 
				stack.push(ch-'0');
			else {
				// 연산자일 경우 스택에 있는 두 숫자를 연산한 뒤 다시 스택에 푸시
				int a = stack.pop();
				int b = stack.pop();
				if(ch == '+')
					stack.push(a+b);
				else
					stack.push(a*b);
			}
		}
		return stack.pop();
	}
	
	private static void make_postfix() {
		Stack<Character> stack = new Stack<>();	// 연산자 저장
		for(char ch: expression) {
			// 숫자이면 numbers에 푸시
			if('0' <= ch && ch <='9')
				numbers.add(ch);
			// 연산자이면 +냐 *냐에 따라 다름
			else {
				// 스택이 비었으면 연산자를 op에 푸시
				if(stack.empty())
					stack.push(ch);
				// 스택탑에 +가 있는 상태에서 *연산자가 들어오면 *를 스택에 푸시
				else if(ch =='*' && stack.peek() == '+')
					stack.push(ch);
				// 나머지는 스택 탑에서 numbers로 넣어준 후 ch를 스택에 푸시
				else {
					numbers.add(stack.pop());
					stack.push(ch);
				}
			}
		}
		
		// 남아있는 연산자 후위표기식에 추가
		while(!stack.empty())
			numbers.add(stack.pop());
	}
	
	
	public static void main(String[] args) throws Exception{
		System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		for(int test_case = 1; test_case <= 10; test_case++)
		{
			int n = Integer.parseInt(br.readLine());
			
			// expression, numbers 초기화
			expression = new char[n];
			expression = br.readLine().toCharArray();
			numbers.clear();
			
			// 후위표기식 만들어 계산
			int sum = 0;
			make_postfix();
			sum = calc_postfix();
			
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case+" "+sum);
			System.out.println(sb);
		}
	}

}
