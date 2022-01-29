/*
유저가 탐험할 수 있는 최대 던전 수를 구해야 한다.
모든 경우를 다 탐색하면 되긴 한데 시간복잡도가 될지 확인해봤다.
던전 개수가 최대 8이기 때문에 순열을 쓰면 8!이라서 시간내에 될 것 같았다.
0~n까지 순열을 구해서 하나씩 던전을 돌 때 소모 피로도를 구해 최대값을 구했다.
*/

import java.util.*;

class Solution {
    
    static int[] arr;
    static int n, answer;
    static int[][] map;
    static int all;
    
    public int solution(int k, int[][] dungeons) {

        
        n = dungeons.length;
        all = k;
        arr = new int[n];
        map = new int[n][2];
        for(int i=0; i<n; ++i)
            map[i] = dungeons[i].clone();
        
        perm(0 ,0); 
        
        return answer;
    }
    
    static void perm(int idx, int flag){
        if(idx == n){
            //System.out.println(Arrays.toString(arr));
            
            answer =  Math.max(answer, checkPirodo());
            return;
        }
        
        for(int i=0; i<n; ++i){
            if((flag & 1<<i) != 0) continue;
            arr[idx] = i;
            perm(idx+1, flag|1<<i);
            
        }
    }
    
    static int checkPirodo(){
        int cnt = 0;
        int pirodo = all;
            
        for(int i=0; i<arr.length; ++i){
            int num = arr[i];
            int need = map[num][0]; // 현재 피로도
            int waste = map[num][1];
            
            // 최소 필요 피로도 보다 작으면 cnt 리턴
            if(pirodo < need) return cnt;
            
            pirodo -= waste;
            cnt++;
        }
        return cnt;
    }
}