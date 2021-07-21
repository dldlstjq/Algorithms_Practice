/*
string을 뒤집으면 쉽게 풀 수 있다.
c++에서는 reverse란 api를 제공하지만 자바는 stringbuilder, stringbuffer를 써야 뒤집을 수 있다.
*/

import java.io.*;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
	
		int A = Integer.parseInt(new StringBuilder(st.nextToken()).reverse().toString());
		int B = Integer.parseInt(new StringBuilder(st.nextToken()).reverse().toString());
		
		System.out.print(A>B?A:B);
	}
}
