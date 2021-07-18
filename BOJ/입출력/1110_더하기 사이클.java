/* 
알고리즘 자체는 어렵지 않다. 입출력 연습 위해 스캐너, 버퍼 두 가지 이용

스캐너: 204ms
br : 132ms
*/

// 버퍼리더
import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		int goal = Integer.parseInt(st.nextToken());
		int cnt = 1;
		int num = goal;
		while(true) {
			if(num < 10) {
				num = num*10+num;
			}
			else {
				int a = num%10;
				int b = (num/10 + num%10) %10;
				num = 10*a+b;
			}
			
			if(num == goal)
				break;
			
			cnt++;
		}
		
		System.out.println(cnt);
		
	}

}


//////////////////////////////
// 스캐너
import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		Scanner in=new Scanner(System.in);
        
		int goal = in.nextInt();
		int cnt = 1;
		int num = goal;
		while(true) {
			if(num < 10) {
				num = num*10+num;
			}
			else {
				int a = num%10;
				int b = (num/10 + num%10) %10;
				num = 10*a+b;
			}
			
			if(num == goal)
				break;
			
			cnt++;
		}
		
		System.out.println(cnt);
		in.close();
	}

}


