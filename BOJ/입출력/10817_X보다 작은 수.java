/* bufferreader는 한줄에 모두 읽기 때문에 for문 내부에서 읽는 것이 아니라 밖에서 입력한 후 내부에서 토큰을 잘라 주면 된다.
br, bw를 이용하는 것이 아직은 익숙하지 않은데 입출력 속도에서 많은 차이가 있기 때문에 두 가지 방법으로 모두 푸는 것을 계속 연습해야겠다.

bf,bw : 212ms
scanner : 440ms 
*/

import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	final static int MAX = 10000+1;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		int N = Integer.parseInt(st.nextToken());
		int X = Integer.parseInt(st.nextToken());
		
		st = new StringTokenizer(br.readLine(), " ");
		for(int i=0; i<N; ++i) {
			int value = Integer.parseInt(st.nextToken());
			if(value<X)
				bw.write(value + " ");
		}
		
		br.close();
		bw.flush();
		bw.close();
	}

}


// scanner 풀이
import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
	final static int MAX = 10000+1;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		int N = Integer.parseInt(st.nextToken());
		int X = Integer.parseInt(st.nextToken());
		
		st = new StringTokenizer(br.readLine(), " ");
		for(int i=0; i<N; ++i) {
			int value = Integer.parseInt(st.nextToken());
			if(value<X)
				bw.write(value + " ");
		}
		
		br.close();
		bw.flush();
		bw.close();
	}

}
