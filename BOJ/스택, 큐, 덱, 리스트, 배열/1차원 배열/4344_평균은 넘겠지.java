/*
버퍼에 익숙해지기 위해 많은 연습이 필요한 것 같다.
알고리즘은 어려운게 없는데 버퍼 입력이 아직 미숙하다.

스캐너: 436ms
버퍼: 176ms
*/
import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int t = Integer.parseInt(br.readLine());
		
		for(int i=0; i < t; ++i) {
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			
			int n = Integer.parseInt(st.nextToken());
			int [] arr = new int[n];    // 성적 저장
			
			double sum = 0;    // 성적 합
			
			for(int j=0; j<n; ++j) {
				arr[j] = Integer.parseInt(st.nextToken());
				sum += arr[j];
			}
			
            // 평균 넘는 비율 구함
			double avg = sum/n;
			double cnt = 0;
			
			for(int j=0; j<n; ++j) {
				if(arr[j]>avg)
					cnt++;
			}
			
			System.out.printf("%.3f%%\n", cnt/n*100);
		}
	}
}



//////////////////////////////////
// 스캐너
import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		Scanner sc = new Scanner(System.in);
		
		int t = sc.nextInt();
		
		for(int i=0; i < t; ++i) {
			
			int n = sc.nextInt();
			int [] arr = new int[n];
			
			double sum = 0;
			
			for(int j=0; j<n; ++j) {
				arr[j] = sc.nextInt();
				sum += arr[j];
			}
			
			double avg = sum/n;
			double cnt = 0;
			
			for(int j=0; j<n; ++j) {
				if(arr[j]>avg)
					cnt++;
			}
			
			System.out.printf("%.3f%%\n", cnt/n*100);
		}
	}
}