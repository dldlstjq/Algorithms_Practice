/**************************************************************
    Problem: 1733
    User: 
    Language: Java
    Result: Success
    Time:387 ms
    Memory:17780 kb
    
처음엔 풀었다 하고 좋아했는데 런타임 에러가 났다.
보니까 애초에 인덱스가 1~19였기 때문에 실제 배열을 좀 더 크게 잡아줘야 했다.
그것도 모르고 그냥 했다가 되겠지 했다.
또 생각지 못한 케이스가 있었는데 6개 이상 돌이 있을 때 중간 부터 시작하면 5개가 되어
조건을 만족하는 것으로 나왔다.
그래서 돌이 5개를 만족할 때 시작, 끝 돌 양 옆으로 같은 색 돌이 없으면 이긴 것으로 조건을 바꾸니 정답을 받았다.
****************************************************************/
 
 
import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;
 
public class Main {
 
    static int [][]board= new int[21][21];
    static boolean [][] visited = new boolean[21][21];
    static int[] dy = {-1,-1,0,1,1,1,0,-1}; // 8가지 방향
    static int[] dx = {0,1,1,1,0,-1,-1,-1};
    static int start_r = 0, start_c = 0;        // 이긴 시작 좌표 저장
    static boolean isFinish= false;         // 끝났는지 여부
     
    static void check(int y, int x, int color, int cnt, int dir) {
        // 개수가 5개이면서 그 방향 다음 좌표와 시작점 반대 방향에 돌이 없을때 즉, 6개 이상이 아닐때
        if(cnt == 5 && board[y + dy[dir]][x + dx[dir]] != color
                 && board[start_r+dy[(dir+4)%8]][start_c+dx[(dir+4)%8]] != color) {
            isFinish=true;  // 승부가 끝났다고 표시
             
            // 방향에 따라 시작좌표나 끝 좌표를 출력한다.
            // 우상, 우, 우하는 시작 좌표
            if(dir == 3 || dir == 2 || dir == 1) {
                System.out.println(color);      // 색깔과 좌표 
                System.out.printf("%d %d%n", start_r, start_c);
            }
             
            // 맨 윗 방향으로 이동할 경우 가장 마지막 돌 좌표
            else if(dir == 0){
                System.out.println(color);      // 색깔과 좌표 
                System.out.printf("%d %d%n", y, x);
            }
            // 맨 아랫 방향은 시작 좌표
            else if(dir == 4){
                System.out.println(color);      // 색깔과 좌표 
                System.out.printf("%d %d%n", start_r, start_c);
            }
             
            // 좌상, 좌, 좌하는 마지막 좌표
            else if(dir == 5 || dir == 6 || dir == 7) {
                System.out.println(color);      // 색깔과 좌표 
                System.out.printf("%d %d%n", y, x);
            }
         
            return;
        }
         
        int r = y + dy[dir];
        int c = x + dx[dir];
             
        // 경계 아웃이거나 색이 다르면 끝
        if(!(1<=r&&r<20 && 1<=c&&c<20 ) || board[r][c] != color)
            return;
             
        check(r,c, color, cnt+1, dir);
    }
     
    public static void main(String[] args) throws IOException {
        // TODO Auto-generated method stub
 
        Scanner sc = new Scanner(System.in);
        // 구현하세요.
         
        for(int i=1; i<=19; ++i) 
            for(int j=1; j<=19; ++j) 
                board[i][j] = sc.nextInt();
             
         
        outer: for(int i=1; i<=19; ++i) {
            for(int j=1; j<=19; ++j) {
                // 0인 곳은 패스
                if(board[i][j] == 0)
                    continue;
                 
                // 시작 좌표 저장
                start_r=i;  start_c=j;
                visited[i][j] = true;
                // 8방향 탐색
                for(int k=0; k<8; ++k) {
                    int ny = i + dy[k];
                    int nx = j + dx[k];
                         
                    // 경계 아웃이거나 색이 다르거나 이미 검사한 돌이면 다른 방향 탐색
                    if(!(1<=ny&&ny<20 && 1<=nx&&nx<20 ) || board[ny][nx] != board[i][j] ||
                            visited[ny][nx] == true)
                        continue;
                         
                     
                    // 다음 좌표와 돌 색깔, 돌 개수, 방향을 넣어준다.
                    // (i,j) 에서 1번, (ny, nx)에서 1번 더 검사했기 때문에 갯수는 2개를 넣어준다.
                    check(ny,nx, board[i][j], 2, k);
                     
                    // 만약 끝났다면 outer 탈출
                    // 동시에 이기는 경우나 이긴 곳이 두 군데 이상인 경우가 없기 때문에 하나를 만족하면 종료
                    if(isFinish)
                        break outer;
                }
            }
             
        }
        // 승부가 결정되지 않았으면 0
        if(!isFinish)
            System.out.println(0);
         
         
    }
}