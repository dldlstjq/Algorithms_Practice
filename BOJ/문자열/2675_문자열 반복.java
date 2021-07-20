/*
문제자체는 어렵지 않다. 입력받을 때 어떻게 입력받을 것이며
파싱을 어떻게 하는지 잘 알아두면 좋을 것 같다.
*/
// stringtokenizer를 사용
import java.io.*;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(bf.readLine());
		
		for(int i=0; i<t; ++i) {
			StringTokenizer st = new StringTokenizer(bf.readLine(), " ");
			int R = Integer.parseInt(st.nextToken());
			String S = st.nextToken();
			
			String ret = "";
			for(int j=0; j < S.length(); ++j) {
				for(int k=0; k < R; ++k) {
					ret += S.charAt(j);
				}
				
			}
			System.out.println(ret);
		}
	}
}


//////////////////////////////////////////////////
// split 사용
import java.io.*;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
	
		int t = Integer.parseInt(bf.readLine());
		
		
		for(int i=0; i<t; ++i) {
			String[] str = bf.readLine().split(" ");
			
			int R = Integer.parseInt(str[0]);
			String S = str[1];
			
			for(int j=0; j < S.length(); ++j) {
				for(int k=0; k < R; ++k) {
					System.out.print(S.charAt(j));
				}
				
			}
			System.out.println();
		}
		
	}
}



//////////////////////////////////////
// 스캐너 사용
// next()를 사용해야 한다. nextLine() 으로 입력받으면 입력 과정에서 공백까지 읽어버리기 때// 문이다.
import java.util.Scanner;
public class Main {
 
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
		int T = in.nextInt();
		for(int i = 0; i < T; i++) {
	
			int R = in.nextInt();
			String S = in.next();	// nextLine() 을 쓰면 error!
			
			for(int j = 0; j < S.length(); j++) {           
				for(int k = 0; k < R; k++) {	// R 만큼 반복 출력
					System.out.print(S.charAt(j));
				}
			}
            
			System.out.println();
		}
	}
}