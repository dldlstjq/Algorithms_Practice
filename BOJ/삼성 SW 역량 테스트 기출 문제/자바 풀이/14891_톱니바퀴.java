/*
거의 다 맞게 왔는데 계속 틀리게 나와서 헤맸다.
맞닿아 있는 극을 확인해서 회전여부와 방향을 저장하는건 맞게 한것 같아
시계, 반시계 회전을 봤는데 시계방향 회전에서 인덱스 설정을 잘못했다....
너무 빨리 풀어야된다는 생각때문인지 계속 실수가 나온다.
조금만 천천히 로직을 잘 생각하면서 시도해보자.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {
	
	static int[][] arr = new int[5][8];
	
	// 시계
	static void clock(int [] b) {
		int tmp = b[7];
		for(int i=7; i>0; --i)
			b[i] = b[i-1];
		b[0] = tmp;
	}
	
	// 반시계
	static void counterClock(int [] b) {
		int tmp = b[0];
		for(int i=0; i<7; ++i)
			b[i] = b[i+1];
		b[7] = tmp;
	}
	
	static void rotate(int n, int dir) {
		int isRotate [] = new int[5];
		isRotate[n] = dir;
		// n 보다 왼쪽. n부터 시작하기 때문에 i-1번쨰의 회전방향을 저장한다.
		for(int i = n; i>1; i--) {
			// 맞닿아 있는 극이 같으면 회전 안함
			if(arr[i][6] == arr[i-1][2]) 
				break;
			isRotate[i-1] = (isRotate[i]==1) ?-1 :1;
		}
		
		// n 보다 오른쪽. n부터 시작하기 때문에 i+1번째 회전방향 저장
		for(int i= n; i<4; ++i) {
			// 맞닿아 있는 극이 같으면 회전 안함
			if(arr[i][2] == arr[i+1][6]) 
				break;
			isRotate[i+1] = (isRotate[i]==1) ?-1 :1;
		}
		
		for(int i=1; i<=4; ++i) {
			if(isRotate[i] == 1)
				clock(arr[i]);
			else if(isRotate[i] == -1)
				counterClock(arr[i]);
		}
		
	}

	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		for(int i=1; i<=4; ++i) {
			char ch[] = new char[8];
			ch = br.readLine().toCharArray();
			for(int j=0; j<8; ++j)
				arr[i][j] = ch[j]-'0';
		}
		
		int K = Integer.parseInt(br.readLine());
		for(int i=0; i<K; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			int num = Integer.parseInt(st.nextToken());
			int dir = Integer.parseInt(st.nextToken());
			
			rotate(num, dir);
		}
		
		int ret=0;
		ret += (arr[1][0]==0)?0:1;
		ret += (arr[2][0]==0)?0:2;
		ret += (arr[3][0]==0)?0:4;
		ret += (arr[4][0]==0)?0:8;
		
		System.out.println(ret);
	}

}