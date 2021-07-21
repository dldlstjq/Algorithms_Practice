/*
입력받은 단어를 전부 대문자로 바꿔서 풀었다.
최댓값이 같은 알파벳이 여러개일 경우는 flag를 써서 구했다.
스캐너로 입력 받는다면 input.next()를 사용한다.
*/
import java.io.*;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int[] alpha = new int[26];
		String word = br.readLine();
		word = word.toUpperCase();	// 일단 대문자로 변환
		
		// 알파벳 체크
		for(int i=0; i < word.length(); ++i) 
			alpha[word.charAt(i) - 'A']++;
		
		int ret = 0, idx = 0;
		boolean flag = true;
		for(int i=0; i < 26; ++i) {
			// 최댓값 고름. 최댓값이 있으면 flag=true
			if(alpha[i]> ret) {
				ret = alpha[i];
				idx = i;
				flag = true;
			}
			// 만약 현재 최댓값과 해당 알파벳 사용이 같다면 flag=false
			else if(alpha[i] == ret)
				flag= false;
				
		}
		
		if(flag)
			System.out.println((char)(idx + 'A'));
		else
			System.out.println("?");
	}
}


///////////////////////////////////////
//스캐너 풀이
import java.util.Scanner;
 
public class Main {
 
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
 
		int[] arr = new int[26]; // 영문자의 개수는 26개임
		String s = in.next();
 
		for (int i = 0; i < s.length(); i++){
 
			if ('A' <= s.charAt(i) && s.charAt(i) <= 'Z') { // 대문자 범위
				arr[s.charAt(i) - 'A']++;	// 해당 인덱스의 값 1 증가
			}
    
			else {	// 소문자 범위
				arr[s.charAt(i) - 'a']++;
			}
		}
 
 
		int max = -1;
		char ch = '?';
 
		for (int i = 0; i < 26; i++) {
			if (arr[i] > max) {
				max = arr[i];
				ch = (char) (i + 65); // 대문자로 출력해야하므로 65를 더해준다.
			}
			else if (arr[i] == max) {
				ch = '?';
			}
		}
 
		System.out.print(ch);
	}
 
}