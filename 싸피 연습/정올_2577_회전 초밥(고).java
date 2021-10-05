/*
슬라이딩 윈도우를 활용한 문제이다.
처음에 시간복잡도를 잘못계산해 2중 for문으로 해결 가능한 줄 알았는데
N이 3백만, k가 3만이어서 전체 90억의 연산을 해야 한다.
도저히 알고리즘을 모르겠어서 쳐보니까 슬라이딩 윈도우를 활용해야 한다.
처음에 k개에서 시작해 하나씩 빼고 넣으며 이동하면 한번만 돌고도 전체를 구할 수 있다.
이렇게 또 하나 알아간다.
*/ 
 
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;
  
  
public class Main {
      
    static int N, d, k, c;
    static int[] plate; //  초밥 접시
    static int[] sushi; // 초밥 종류
  
      
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
          
        N = Integer.parseInt(st.nextToken());
        d = Integer.parseInt(st.nextToken());
        k = Integer.parseInt(st.nextToken());
        c = Integer.parseInt(st.nextToken());
          
        plate = new int[N];
        sushi = new int[d+1];
          
          
        for(int i=0; i<N; ++i) 
            plate[i] = Integer.parseInt(br.readLine());
          
        int ans = 0, cnt = 0;   // 최종 정답, 초밥 종류
        Queue<Integer> q = new LinkedList<>();
        for(int i=0; i<k; ++i) {
            q.offer(plate[i]);  // 앞에서부터 k개를 큐에 저장
            if(sushi[plate[i]] == 0) // 아직 먹지 않은 종류의 초밥이면 카운트
                cnt++;
                  
            sushi[plate[i]]++;  // 먹은 초밥 카운트    
        }
        // 쿠폰 종류를 먹지 않은 경우
        if(sushi[c] == 0)
            ans = Math.max(ans, cnt+1);
        // 쿠폰 종류를 먹은 경우
        else
            ans = Math.max(ans, cnt);
//      ans = Math.max(ans, cnt);   // 0~k-1번까지 먹은 초밥 종류 수
          
          
        for(int i=0; i<N-1; ++i) {
            sushi[q.poll()]--;  // 맨 앞에 초밥을 뺀다.
            if(sushi[plate[i]] == 0)    // 큐에 해당 초밥이 없으면 초밥 종류 감소
                cnt--;
              
            q.offer(plate[(i+k)%N]); // 다음 초밥을 큐에 저장
              
            if(sushi[plate[(i+k)%N]] == 0) // 아직 먹지 않은 종류의 초밥이면 카운트
                cnt++;
            sushi[plate[(i+k)%N]]++;
              
            // 쿠폰 종류를 먹지 않은 경우
            if(sushi[c] == 0)
                ans = Math.max(ans, cnt+1);
            // 쿠폰 종류를 먹은 경우
            else
                ans = Math.max(ans, cnt);
        }
          
        System.out.println(ans);
    }
}