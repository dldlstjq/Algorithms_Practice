/*
보충시간 때 다시 한번 풀어봤다.
처음에 못풀었던 이유가 시작점 이전에도 돌이 있을 수 있는 경우를 생각못해서였다.
그래서 그 부분을 고려하며 하나씩 해보니까 풀 수 있었다.
*/

import java.io.BufferedReader; 
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
 
public class Main {
 
    static int board[][] = new int[20][20];
     
    // 우상, 우, 우하, 하 방향만 검사
    static int dr[] = {-1,0,1,1};
    static int dc[] = {1,1,1,0};
     
    private static boolean is_omok(int r, int c, int dir, int cnt) {
        if(cnt == 5) {
            // 맨 마지막 돌 다음에도 같은 색의 돌이 있으면 육목이라서 안됨
            int nextR = r+dr[dir];
            int nextC = c+dc[dir];
            if((1<= nextR && nextR <= 19 && 1<= nextC && nextC <= 19) && board[nextR][nextC] == board[r][c])
                return false;
            return true;
        }
         
         
        int nr = r+dr[dir];
        int nc = c+dc[dir];
 
        // 범위를 벗어나거나, 돌 색깔이 다르면 안됨
        if(!(1<=nr && nr <=19 && 1<=nc && nc <=19) || board[nr][nc] != board[r][c])
            return false;
 
        if(is_omok(nr, nc, dir, cnt+1))
            return true;
        else
            return false;
    }
     
    public static void main(String[] args) throws IOException {
        BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
         
         
        for(int i=1; i<=19; ++i) {
            StringTokenizer st= new StringTokenizer(br.readLine(), " ");
            for(int j=1; j<=19; ++j)
                board[i][j] = Integer.parseInt(st.nextToken());
        }
         
        for(int i=1; i<=19; ++i) {
            for(int j=1; j<=19; ++j) {
                if(board[i][j] ==0)
                    continue;
                // 4방향 탐색
                for(int k=0; k<4; ++k) {
                    int nr = i+dr[k];
                    int nc = j+dc[k];
                     
                    // 주어진 범위를 벗어나거나, 돌 색깔이 다르면 안됨
                    if(!(1<=nr && nr <=19 && 1<=nc && nc <=19) || board[nr][nc] != board[i][j])
                        continue;
                     
                    // 오목일 때 시작점 이전에 돌이 더 있는지 확인
                    if(is_omok(i,j,k,1)) {
                        int prevR = i-dr[k];
                        int prevC = j-dc[k];
                        // 시작점 이전에 있던 돌이 같은 색깔이면 위배
                        if((1<= prevR && prevR <= 19 && 1<= prevC && prevC <= 19) && board[prevR][prevC] == board[i][j])
                            continue;
                         
                        if(board[i][j] == 1)
                            System.out.println(1);
                        else
                            System.out.println(2);
                        System.out.println(i+" "+j);
                        System.exit(0);
                    }
                }
                 
            }
        }
         
        // 답이 나오지 않으면 0
        System.out.println(0);
         
    }
 
 
}