/*
싸피에서 배열 돌리기라는 문제를 풀어봤었는데 다시 보니까 또 생각이 안났다.
배열을 돌리면서 최솟값을 구하면 되는데 복습을 해야겠다는 생각을 많이 했다.
새로운 문제를 계속 풀어나가는게 좋을지, 복습을 하는게 좋을지 이게 또 관건인 것 같다.
*/

class Solution {
    
    static int dr[] = {1,0,-1,0};
    static int dc[] = {0,1,0,-1};
    
    static int[] answer;
    static int idx;
    
    public void rotate(int[][] arr, int x1, int y1,int x2, int y2){
        int tmp = arr[x1][y1];
        int min_num = Integer.MAX_VALUE;
        
        min_num = Math.min(min_num, tmp);
        int r = x1;
        int c = y1;
        int dir = 0;
        while(dir<4){
            // 다음 좌표
			int nr = r+dr[dir];
			int nc = c+dc[dir];
				
			// 경계 내에 있다면?
			if(x1<=nr && nr<=x2 && y1<=nc && nc<=y2) {
				// 다음 값을 현재 위치에 넣어주기
				arr[r][c] = arr[nr][nc];
                
                min_num = Math.min(min_num, arr[nr][nc]);
					
				// 다음 위치로 이동
				r = nr;
				c = nc;
			}
			// 경계 밖에 있다면?
			else {
				dir++;
			}
        }
        arr[x1][y1+1] = tmp;
        
        answer[idx++] = min_num;
    }
    
    public int[] solution(int rows, int columns, int[][] queries) {
        
        answer = new int[queries.length];
        
        int[][] arr = new int[rows+1][columns+1];
        
        for(int i=1; i<=rows; ++i){
            for(int j=1; j<=columns; ++j){
                arr[i][j] = ((i-1) * columns + j);
            } 
        }
        
        
        for(int i=0; i<queries.length; ++i){
            int x1 = queries[i][0];
            int y1 = queries[i][1];
            int x2 = queries[i][2];
            int y2 = queries[i][3];    
            
            rotate(arr, x1, y1, x2, y2);
        }

        return answer;
    }
}