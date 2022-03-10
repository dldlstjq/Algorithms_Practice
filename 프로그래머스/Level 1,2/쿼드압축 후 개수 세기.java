/*
전형적인 분할정복 문제
백준에서 비슷한 문제를 풀어봤는데 과연 오랜만에 풀면 풀 수 있을까 했는데 다행히 풀긴 풀었다.
4등분 해서 숫자가 일정한지 확인해서 일정하면 카운트, 아니면 다시 반으로 쪼개 들어간다.
for문에서 범위 설정할 때 전체크키가 r+len이 되어야 하는걸 설정하지 않으면 제대로 된 답이 안나온다.
*/

class Solution {
    //static int len;
    static int zero;
    static int one;
    static int[][] map;
    
    public int[] solution(int[][] arr) {
        int[] answer = {};
        answer = new int[2];
        
        int len = arr.length;
        map = new int[len][len];
        for(int i=0; i<len; ++i)
            map[i] = arr[i].clone();
        
        solve(0, 0, len);
        
        answer[0] = zero;
        answer[1] = one;
        return answer;
    }
    
    static void solve(int r, int c, int len){
        boolean flag = true;
        int mini_zero = 0;
        int mini_one = 0;
        outer:
        for(int i=r; i<r+len; ++i){
            for(int j=c; j<c+len; ++j){
                if(map[i][j] == 0) mini_zero++;
                else mini_one++;
                
                if(mini_zero>0 && mini_one>0){
                    flag = false;
                    break outer;
                }  
            }
        }
        
        if(flag) {
            if(mini_zero == len*len) zero++;
            else one++;
            return;
        }
        
        if(!flag) solve(r, c, len/2);
        if(!flag) solve(r, c+len/2, len/2);
        if(!flag) solve(r+len/2, c, len/2);
        if(!flag) solve(r+len/2, c+len/2, len/2);
        
    }
}