/*
처음엔 모든 경우를 판별하는 bfs를 이용해서 최소를 구하는 방법을 생각했다.
하지만 n이 10억이어서 모든 경우는 시간초과가 나서 어떻게 해야 하나 싶었다.
순간이동이 2배로 이동하는 것에 힌트를 얻어 2씩 나누어서 가면 어떨까 생각했고
처음에는 무조건 1칸 이동한 후 2배씩 늘려가며 홀수이면 +1을 해주면 되었다.
아이디어가 잘 생각이 안났는데 반씩 줄여나간다는 생각을 해서 뿌듯했다.
*/

import java.util.*;

public class Solution {
    static int ans;
    public int solution(int n) {
        
        // 반씩 쪼개간다.
        ans = solve(n);
        return ans;
    }
    
    static int solve(int n){
        int ret = 0;
        if(n == 1)
            return 1;
        
        if(n % 2 == 0)
            return ret += solve(n/2);
        else
            return ret += solve(n/2)+1;
        
    }
}