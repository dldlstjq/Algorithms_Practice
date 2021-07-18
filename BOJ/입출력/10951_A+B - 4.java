/* 
EOF를 연습하기에 좋은 문제 같다.
scanner와 bufferedreader 두 가지 방법을 이용한 eof 방법인데
스캐너는 hasnext()를 쓰고 br은 값이 null이면 eof로 중단한다.

스캐너: 228ms
br : 136ms
*/
import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		Scanner in=new Scanner(System.in);
		
		// 참고로 hasNextInt() 의 경우 입력값이 정수일경우 true를 반환하며 
		// 정수가 아닐경우 바로 예외를 던지며 더이상의 입력을 받지 않고 hasNextInt()에서 false를 반환하면서 반복문이 종료된다.
		while(in.hasNextInt()){
			int a=in.nextInt();
			int b=in.nextInt();
			System.out.println(a+b);
		}	
		in.close();
	}

}



/////////////////////////////////////////
// buffer
import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		StringTokenizer st;
		String str;
		
		// BufferedReader 의 경우 null 을 반환한다. 이 부분은 오히려 null 인지 아닌지만 조건문을 통해 구분해주면 되므로 쉽다.
		while((str=br.readLine()) != null) {
			st = new StringTokenizer(str, " ");
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			sb.append(a+b).append("\n");
		}
		System.out.print(sb);
		
	}

}

