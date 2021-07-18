/*
버퍼를 이용할 경우 하나의 숫자는 바로 parse 해도 되지만 여러 값이 동시에입력이 되면
stringtoken으로 공백을 분리해야 값이 잘 들어간다.
확실히 스캐너와 버퍼 두 개 입력을 사용하고 있는데 버퍼가 더 빠른 것을 확인할 수 있다.


스캐너: 412ms
버퍼: 128ms
*/

import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		// 숫자 하나만 입력할 경우 바로 파싱 가능
		int N = Integer.parseInt(br.readLine());
		double [] arr = new double[N];
		
		// 여러 개 입력할 경우 토큰으로 잘라줘야 함.
		StringTokenizer st = new StringTokenizer(br.readLine()," ");
		
		double max = 0;
		for(int i=0; i<N; ++i) {
			arr[i] = Double.parseDouble(st.nextToken());
			if(arr[i] > max)
				max=arr[i];
		}
		
		double sum=0;
		for(int i=0; i<N; ++i) 
			sum += arr[i]/max*100;
		
		System.out.println(sum/N);
		
	}

}


///////////////////////////
// 스캐너
import java.io.*;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		double [] arr = new double[N];
		
		
		double max = 0;
		for(int i=0; i<N; ++i) {
			arr[i] = sc.nextDouble();
			if(arr[i] > max)
				max=arr[i];
		}
		
		double sum=0;
		for(int i=0; i<N; ++i) 
			sum += arr[i]/max*100;
		
		System.out.println(sum/N);
	}
}