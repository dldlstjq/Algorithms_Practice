import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Z_반복문 {
   public static void main(String[] args) throws Exception {
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
      StringTokenizer st = new StringTokenizer(br.readLine(), " ");
      int N = Integer.parseInt(st.nextToken()); // 1 ≤ N ≤ 15
      int r = Integer.parseInt(st.nextToken()); // 0 ≤ r, c < 2^N
      int c = Integer.parseInt(st.nextToken());
      int rs = 0; // 해당 좌표가 포함된 사각영역의 시작좌표
      int cs = 0;
      int answer = 0;
      while(N > 0) {
         int side = 1 << (N-1); // 정사각형의 한 변 
//         Math.pow(2, N-1);
         int diff = side * side; // 정사각형
         if (r < rs+side && c < cs + side) { // 좌상
            
         } else if (r < rs+side && cs + side <= c) { // 우상
            answer += diff;
            cs += side;
         } else if (rs+side <= r && c < cs + side) { // 좌하
            answer += diff * 2;
            rs += side;
         } else if (rs+side <= r && cs + side <= c) { // 우하
            answer += diff * 3;
            rs += side; cs += side;
         } 
         N--;
      }
      System.out.println(answer);
   } // end of main
} // end of class