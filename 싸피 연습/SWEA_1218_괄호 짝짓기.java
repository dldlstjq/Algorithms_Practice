/*
전형적인 스택을 이용하는 문제라 스택으로 해결했다.
다만 ( { ) } 이런 반례는 존재하지 않았기에 해결이 가능했지 반례가 존재했다면 아래 풀이로는 불가능하다.
반례를 스택으로 풀려면 모두 꺼내서 짝이 있는지 확인하고 다시 넣어야한다.
이게 불편하다면 재귀를 이용하는 방법도 있는데 이건 한번 생각해봐야겠다.
*/


import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Stack;

public class Main_1218_이인섭 {

	public static void main(String[] args) throws Exception{

//		System.setIn(new FileInputStream("input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		
		for(int test_case = 1; test_case <= 10; test_case++)
		{
			int N = Integer.parseInt(br.readLine());
		
			char[] ch = br.readLine().toCharArray();
			HashMap<Character, Character> hMap = new HashMap<Character, Character>();
			hMap.put(')', '(');
			hMap.put('}', '{');
			hMap.put(']', '[');
			hMap.put('>', '<');
			Stack<Character> st = new Stack<Character>();
			
			for(char c: ch) {
				if(c =='(' || c== '[' || c=='{' || c=='<')
					st.push(c);
				else if(c ==')' || c== ']' || c=='}' || c=='>')
					if(!st.isEmpty() && st.peek() == hMap.get(c)) 
						st.pop();
					else
						break;	
			}
			
			if(st.isEmpty())
				System.out.printf("#%d %d%n", test_case, 1);
			else
				System.out.printf("#%d %d%n", test_case, 0);

		}
	}
}
