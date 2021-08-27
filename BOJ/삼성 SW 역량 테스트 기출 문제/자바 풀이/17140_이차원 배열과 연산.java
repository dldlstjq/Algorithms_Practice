/*
문제를 제대로 안 읽고 이해도 제대로 안돼면 어떻게 되는지 보여주는 문제인 것 같다.
처음엔 쉽네 했다가 장장 2~3시간 걸려 겨우 해결했다.
행, 열 크기에 따라 계산하는 건 이해했다.
다만 처음에는 3x3 배열부터 시작하기 때문에 크기를 3x3으로 잡아줬는데 r,c 값이 3을 넘어가버릴 때 예외를 처리해줘야 했는데 안해서 런타임 에러가 났다.
여기까진 괜찮았는데 문제를 잘못 이해해서 배열 연산 후 행, 열 크기를 r,c 값으로 잡아줘서 또 런타임 에러가 났다.
r, c값이 연산한 후에 행, 열 값보다 작을 수도 있기 때문에 범위를 벗어나서 값을 지정하려 하는 것 때문에 그랬고, 열 계산 시 배열 사이즈를 잡을 때 행 크기를 size로 잡아줘야 한다.

애초에 배열을 최대사이즈로 선언해놓고 하는 것도 나쁘진 않을 것 같다.
그렇게 되면 매번 초기화해줘야 하는 번거로움은 있을 것 같다.

잘못된 문제 이해, 인덱스 설정 에러로 인해 생각보다 많은 시간을 잡아먹었다.
문제를 꼼꼼하게 읽고 배열 인덱스 설정을 잘하자.
빨리보단 정확히가 더 중요하다. 
빠르고 정확하면 제일 좋지만 그게 안되기 때문에 정확하게 푸는 걸 목표로 하자.
괜히 틀리면 디버깅하기 어렵기 때문에 더 시간을 잡아먹는다.
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;


public class Main {
	
	static class Num implements Comparable<Num>{
		int num, cnt;

		public Num(int num, int cnt) {
			super();
			this.num = num;
			this.cnt = cnt;
		}

		@Override
		public int compareTo(Num o) {
			if(this.cnt == o.cnt)
				return Integer.compare(this.num, o.num);
			return Integer.compare(this.cnt, o.cnt);
		}
		
		
	}
	
	static int r,c,k;	// 행, 열, 수
	static int[][] arr;
	static int sec;
	
	// R 연산
	private static void calc_R(int r_len, int c_len) {
		ArrayList<ArrayList<Num>> list = new ArrayList<>();
		
		// 배열에 있는 원소 카운트해서 쌍으로 list에 저장
		for(int i=0; i < r_len; ++i) {
			ArrayList<Num> tmp = new ArrayList<>();
			int[] freq = new int[101];	// 나올 수 있는 수는 1~100
			for(int j=0; j<c_len; ++j) 
				if(arr[i][j] != 0)
					freq[arr[i][j]]++;
			
			tmp = addList(freq);
			
			// 정렬 후 저장
			Collections.sort(tmp);
			list.add(tmp);
		}
		
		// 크기가 가장 큰 행 찾는다.
		int size=0;
		for(int i=0; i<list.size(); ++i) 
			size = Math.max(size, list.get(i).size());
		
		size *=2;	// 숫자, 등장 두 개이므로 *2
		
		// 배열 열 크기 초기화
		// 행 또는 열의 크기가 100을 넘어가는 경우에는 처음 100개를 제외한 나머지는 버린다.
		if(size>100) 
			size = 100;
		
		// 배열 크기를 파라미터에 있는 크기로 맞춰야 한다. 절대 r,c 값에 맞추지 말 것!!
		// 이것땜에 한참을 고생했다...
		arr = new int[r_len][size];	
		
		for(int i=0; i<arr.length; ++i) {
			int idx=0;
			for(int j=0; j<arr[i].length; j+=2) {
				// list에 들어있는 행 크기만큼만 숫자와 등장횟수를 넣어준다.
				if(i < list.size() && idx < list.get(i).size()) {
					arr[i][j] = list.get(i).get(idx).num;
					arr[i][j+1] = list.get(i).get(idx++).cnt;
				}
			}
		}
	}
	
	// C 연산
	private static void calc_C(int r_len, int c_len) {
		ArrayList<ArrayList<Num>> list = new ArrayList<>();

		// 배열에 있는 원소 카운트해서 쌍으로 list에 저장
		for(int i=0; i<c_len; ++i) {
			ArrayList<Num> tmp = new ArrayList<>();
			int[] freq = new int[101];	// 나올 수 있는 수는 1~100
			for(int j=0; j<r_len; ++j) 
				freq[arr[j][i]]++;

			tmp = addList(freq);	// 숫자 카운팅

			// 정렬 후 저장
			Collections.sort(tmp);
			list.add(tmp);
		}

		// 크기가 가장 큰 행 찾는다.
		int size=0;
		for(int i=0; i<list.size(); ++i) 
			size = Math.max(size, list.get(i).size());

		size *= 2;
		
		// 배열 크기 초기화
		// 행 또는 열의 크기가 100을 넘어가는 경우에는 처음 100개를 제외한 나머지는 버린다.
		if(size>100) 
			size = 100;
		
		arr = new int[size][c_len];	// size가 행 크기여야 한다. 이거 잘못 잡아서 틀림....

		for(int i=0; i<arr[0].length; ++i) {
			int idx=0;
			for(int j=0; j<arr.length; j+=2) {
				// list에 들어있는 행 크기만큼만 숫자와 등장횟수를 넣어준다.
				if(i < list.size() && idx < list.get(i).size()) {
					arr[j][i] = list.get(i).get(idx).num;
					arr[j+1][i] = list.get(i).get(idx++).cnt;
				}
			}
		}
	}
	
	// 숫자 카운팅
	static ArrayList<Num> addList(int[] a) {
		ArrayList<Num> tmp = new ArrayList<>();
		for(int j=1; j<=100; ++j) 
			if(a[j] != 0)
				tmp.add(new Num(j, a[j]));
		
		return tmp;
	}
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		r = Integer.parseInt(st.nextToken());
		c = Integer.parseInt(st.nextToken());
		k = Integer.parseInt(st.nextToken());
		
		arr=  new int[3][3];	// 처음엔 3*3 배열로 시작
		
		for(int i=0;i<3; ++i) {
			st = new StringTokenizer(br.readLine(), " ");
			for(int j=0; j<3; ++j) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		

		while(true) {
			int r_len=arr.length;
			int c_len=arr[0].length;
			
			// 100초가 넘어가면 안됨.
			if(sec>100)
				break;
						
			// 인덱스0부터 배열을 잡았기 때문에 r-1,c-1로 한다.
			// r-1, c-1이 배열 범위 안에 있고 값이 k일 경우 종료
			// r, c에 맞춰서 배열 크기를 만들면 안된다!!!
			else if(r-1 < r_len && c-1<c_len && arr[r-1][c-1] == k)
				break;
			
			if(r_len >= c_len)
				calc_R(r_len, c_len);
			else
				calc_C(r_len, c_len);
			sec++;
		}
		
		if(sec<=100)
			System.out.println(sec);
		else
			System.out.println(-1);
	}
	
}
