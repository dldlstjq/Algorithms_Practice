/*
순열을 이용한 문제이다.
비트마스킹을 이용한 풀이, nextpermutation을 이용한 풀이가 있다.
np를 썼을 때가 훨씬 빠르다.
np: 794ms
비트마스킹: 3880ms
*/


// np 풀이
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

class Solution
{
   static boolean []num;
	static int []gyuyoung = new int[9];
	static int []inyoung = new int[9];
	static int card;
	static int win, lose;
	
	static void calcScore() {
		int gyu_score = 0;	// 규영이 총점
		int in_score = 0;	// 인영이 총점
		// 카드 숫자가 더 높은 쪽이 점수를 다 가져감
		for(int i=0; i<9; ++i) {
			if(gyuyoung[i] > inyoung[i])
				gyu_score += gyuyoung[i] + inyoung[i];

			else if(gyuyoung[i] < inyoung[i])
				in_score +=  gyuyoung[i] + inyoung[i];
		}
		// 규영이가 이기면 win, 지면 lose
		if(gyu_score > in_score)
			win++;
		else if(gyu_score < in_score)
			lose++;
	}
	
    
	public static void main(String args[]) throws Exception
	{
        BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		
		for(int test_case = 1; test_case <= T; test_case++)
		{
			// 카드, 승패 횟수, 인영이 카드 배열 초기화
			card = win = lose = 0;
			num = new boolean[19];
			
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			for(int i=0; i<9; ++i) {
				gyuyoung[i] = Integer.parseInt(st.nextToken());
				num[gyuyoung[i]] = true;
			}
			
			int j=0;
			for(int i=1; i<=18; ++i) {
				if(!num[i])
					inyoung[j++] = i;
			}
		
			Arrays.sort(inyoung);
			do {
				calcScore();
			}while(np(inyoung));
				
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case + " ").append(win).append(' ').append(lose);
			System.out.println(sb);
		}
	}
    // np 함수
	static boolean np(int numbers[]) {
		int N = numbers.length;
		
		int i = N-1;
		while(i>0 && numbers[i-1]>=numbers[i])
			--i;
		
		if(i == 0)
			return false;
		
		int j= N-1;
		while(numbers[i-1]>=numbers[j])
			--j;
		
		swap(numbers, i-1, j);
		
		int k = N-1;
		while(i<k)
			swap(numbers, i++, k--);
		
		return true;
	}

	private static void swap(int[] numbers, int i, int j) {
		int tmp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = tmp;
	}
}



// 비트 마스킹 순열
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

class Solution
{
    static int []gyuyoung = new int[9];
	static int []inyoung = new int[9];
	static int card;
	// 비트로 안 풀면 따로 18길이 배열 생성해서 체크해야함
	static int win, lose;
	
	static void calcScore() {
		int gyu_score = 0;	// 규영이 총점
		int in_score = 0;	// 인영이 총점
		// 카드 숫자가 더 높은 쪽이 점수를 다 가져감
		for(int i=0; i<9; ++i) {
			if(gyuyoung[i] > inyoung[i])
				gyu_score += gyuyoung[i] + inyoung[i];

			else if(gyuyoung[i] < inyoung[i])
				in_score +=  gyuyoung[i] + inyoung[i];
		}
		// 규영이가 이기면 win, 지면 lose
		if(gyu_score > in_score)
			win++;
		else if(gyu_score < in_score)
			lose++;
	}
	
	private static void permutation(int cnt, int flag) {
		if(cnt == 9 ) {
			// 점수 확인
			calcScore();
			return;
		}
		
		for(int i=1; i<=18; ++i) {
			if((flag & 1<<i) != 0) continue;
			inyoung[cnt] = i;
			permutation(cnt+1, flag|1<<i);
		}
	}
    
	public static void main(String args[]) throws Exception
	{
		BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		for(int test_case = 1; test_case <= T; test_case++)
		{
			// 카드, 승패 횟수, 인영이 카드 배열 초기화
			card = win = lose = 0;
			
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			for(int i=0; i<9; ++i) {
				gyuyoung[i] = Integer.parseInt(st.nextToken());
				card |= 1<<gyuyoung[i];	// 9장 카드의 해당 비트를 켠다.
			}
			
			permutation(0, card);
				
			StringBuilder sb = new StringBuilder();
			sb.append("#"+test_case + " ").append(win).append(' ').append(lose);
			System.out.println(sb);
		}
	}
}

