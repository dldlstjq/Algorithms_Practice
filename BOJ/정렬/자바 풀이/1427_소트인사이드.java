/*
입력을 캐릭터 배열로 받아 정렬한 후 StringBuilder의 내장 함수인 reverse를 써서 뒤집었다.
reverse는 StirngBuilder나 StringBuffer를 사용하는 것이 좋을 것 같다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		char c[] = br.readLine().toCharArray();
		Arrays.sort(c);
		
        // StringBuilder에 내장된 reverse 사용
		StringBuilder sb = new StringBuilder();
		sb.append(c);
		sb.reverse();
		System.out.println(sb);
	}

}