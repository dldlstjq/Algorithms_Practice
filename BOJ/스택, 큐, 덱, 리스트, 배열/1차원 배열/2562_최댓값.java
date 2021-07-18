/*
배열에서 최댓값을 구하는 문제이다. 스캐너, 버퍼 둘 다 이용 가능하다.
두 개 다 연습해서 어떤쪽이든 자유롭게 사용가능 하다도록 하자.

스캐너: 240ms
버퍼: 148ms
*/

import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		int [] arr= new int[9];
		
		BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
		
		for(int i=0; i<9; ++i)
			arr[i] = Integer.parseInt(bf.readLine());
		
		int max = 0;
		int idx=0;
		for(int i=0; i<9; ++i) {
			if(max<arr[i]) {
				max=arr[i];
				idx = i;
			}
		}
		
		System.out.println(max);
		System.out.println(idx+1);
	}

}


////////////////////////////////////////////
// 스캐너
import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		int [] arr= new int[9];
		
		Scanner sc = new Scanner(System.in);
		
		for(int i=0; i<9; ++i)
			arr[i] = sc.nextInt();
		
		int max = 0;
		int idx=0;
		for(int i=0; i<9; ++i) {
			if(max<arr[i]) {
				max=arr[i];
				idx = i;
			}
		}
		
		System.out.println(max);
		System.out.println(idx+1);
	}
}