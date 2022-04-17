/*
청소년 상어보다는 쉬워보였는데 바로 해결하지 못했다.
자료구조를 저장하는 것 부터 쉬워보이지 않았는데 경우를 나눴다.
클래스를  상어의 번호, 냄새 k, 상어가 있는지 나타내는 isShark, 냄새만 있는지 나타내는 isSmell로 선언했다.
상어의 현재 방향은 dir 1차원 배열로 저장했으며 상어가 아웃인지 상태를 나타내는 isSharkOut 1차원 배열도 선언했다.
상어의 방향별 우선순위는 3차원으로 선언해서 상어의 번호, 방향, 방향별 우선순위를 나타내게 했다.

마지막으로 각 상어가 이동할 좌표를 저장할 movePos를 2차원으로 선언했다.

상어가 동시에 이동한다는 것을 알고 있었음에도 구현할 때 잘못 해버렸다.
만약 M=4인 상태에서 1~4번 상어가 모두 같은 좌표로 이동해야 하는 경우 1번상어 하나만 남게된다.
동시에 모든 상어가 이동하기 때문인데 처음에 구현할때 이를 간과했다.

만약 2번 상어가 이동할 좌표가 비었으면 바로 2번상어를 그 위치에 넣어주게 했는데 그렇게 되면 1번상어도 그 위치로 이동해야하는 경우 이미 상어가 있으므로 갈 수 없게 되버려서 제대로 된 결과가 나오지 않는다.
또, 빈 좌표가 없는 경우 자기 냄새가 있는 곳으로 이동해야 하는데 이것도 우선순위가 있다.
그래서 자기 냄새가 여러개 있다고 하더라도 우선순위에서 제일 처음 나오는 방향으로만 이동가능하다.
하지만 처음 나오는 방향만 저장한다는 것을 구현하지 않아 계속 우선순위 방향이 변해 답이 제대로 안나왔다.

이 문제는 동시에 모든 상어가 이동한다, 방향별 우선순위가 있다는 것을 잘 알고 구현을 제대로 해야 답이 잘 나오는 것 같다.

6%에서 틀렸습니다가 떴는데 시간이 딱 1000초일 때 상어가 1마리 이상이면 바로 반복문을 종료시키고 -1을 출력해야 통과가 된다.
*/


import java.util.*;
import java.io.*;


public class Main
{
	static class Shark{
		int num; int smell; boolean isShark; boolean isSmell;
		
		Shark(int num, int smell, boolean isShark, boolean isSmell){
			this.num= num;
			this.smell= smell;
			this.isShark= isShark;
			this.isSmell= isSmell;
		}
		
	}
	
	static int N,M,k;
	static Shark[][] map;		// 전체 상태 표현
	static int[] dir;			// 각 상어의 현재 방향
	static boolean[] isSharkOut;	// 상어가 잡아먹혔는지 여부
	static int priority[][][];	// 상어 이동방향 우선순위 저장
	
	// 위 아래 왼쪽 오른쪽
	static int dr[] = {0,-1,1,0,0};
	static int dc[] = {0,0,0,-1,1};
	
	static int[][] movePos;	// 상어가 이동할 좌표 저장
	
	static int time;	// 전체 경과 시간
	
    public static void main(String args[]) throws Exception
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
    	
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        k = Integer.parseInt(st.nextToken());
        
	     map = new Shark[N][N];
	     dir = new int[M+1];
	     isSharkOut = new boolean[M+1];
	     
	     movePos = new int[M+1][2];
	     
	     for(int i=0; i<N; ++i) {
	    	 st = new StringTokenizer(br.readLine());
	    	 for(int j=0; j<N; ++j) {
	    		 int n = Integer.parseInt(st.nextToken());
	    		 if(n == 0) map[i][j]= new Shark(0, 0, false, false);
	    		 else map[i][j]= new Shark(n, k, true, false);
	    	 }
	     }
	     
	     st = new StringTokenizer(br.readLine());
	     for(int i=1; i<=M; ++i)
	    	 dir[i] = Integer.parseInt(st.nextToken());
	     
	     // 상어 방향 우선순위
	     priority = new int[M+1][5][4];
	     for(int i=1; i<=M; ++i) {
	    	 for(int j=1; j<=4; ++j) {
	    		 st = new StringTokenizer(br.readLine());
	    		 for(int k=0; k<4; ++k)
	    			 priority[i][j][k] = Integer.parseInt(st.nextToken());
	    	 }
	     }
	     
	    
        while(true) {
        	
        	moveShark();
        	decreaseSmell();
        	time++;
        	if(onlyFirstShark()) break;
        	
        	if(time >= 1000) {
        		time = -1;
        		break;
        	}
        	
        }
        
        System.out.println(time);
         
    }
    
    private static boolean onlyFirstShark() {
    	for(int i=0; i<N; ++i) {
	    	 for(int j=0; j<N; ++j) {
	    		 if(!map[i][j].isShark) continue;
	    		 else if(map[i][j].isShark && map[i][j].num != 1) return false;
	    	 }
	    }
    	return true;
    }
    
   private static void decreaseSmell() {
	   for(int i=0; i<N; ++i) {
	    	 for(int j=0; j<N; ++j) {
	    		 if(map[i][j].isShark || !map[i][j].isSmell) continue;
	    		 map[i][j].smell--;
	    		 if(map[i][j].smell == 0) map[i][j] = new Shark(0, 0, false, false);
	    	 }
	    }
	}

   private static void moveShark() {
	   for(int i=0; i<N; ++i) {
	    	 for(int j=0; j<N; ++j) {
	    		 if(!map[i][j].isShark) continue;
	    		 spreadSmell(i, j);	// 냄새 뿌리기
	    	 }
	    }
	   
	   // 1~M번 상어 이동할 방향을 한꺼번에 검사
		for(int i=1; i<=M; ++i) {
			
			int nr = movePos[i][0];
			int nc = movePos[i][1];
			
			// 잡아먹힌 상어는 패스
			if(isSharkOut[i]) continue;
			
			// 빈 칸이거나 자기 냄새면 현재 상어 이동
			if(!map[nr][nc].isShark || (map[nr][nc].isSmell && map[nr][nc].num == i))
				map[nr][nc] = new Shark(i, k, true, false);
			
			// 기존에 다른 상어가 있는 경우
			else {
				// 현재 상어가 더 작다면 기존에 있는 상어 아웃
				if(map[nr][nc].num > i) {
					isSharkOut[map[nr][nc].num]=true;
					map[nr][nc] = new Shark(i, k, true, false);
				}
				else	// 기존 상어가 크면 현재 상어가 아웃
					isSharkOut[i]=true;
			}
		}
	}

	private static void spreadSmell(int r, int c) {
		int num = map[r][c].num;
		
		// 현재 위치는 냄새만 남는다.
		map[r][c].isShark = false;
		map[r][c].isSmell = true;
		boolean isMove = false;	// 이동 여부
		int selfSmellDir = 0;	// 자기 냄새 방향
		
		// 이동하는 방향 정하기
		for(int i=0; i<4; ++i) {
			
			int directory = priority[num][dir[num]][i];
			int nr = r+dr[directory];
			int nc = c+dc[directory];
			
			// 범위 아웃
			if(!(0<=nr&&nr<N && 0<=nc&&nc<N)) continue;
			
			// 아직 자기 냄새 방향을 저장하지 않은 상태에서 자기 냄새가 있는 곳을 일단 저장
			// 우선순위가 높은 순서가 먼저 저장이되면 더이상 새로운 방향으로 값을 갱신하면 안됨!!!
			if(selfSmellDir == 0 && map[nr][nc].isSmell && map[nr][nc].num == num) {
				selfSmellDir = directory;
			}
			
			/*
			 * 동시에 이동하기 때문에 빈 칸이라고 먼저 상어를 집어넣으면 안된다.
			 * 이동할 좌표를 따로 저장 후 한번에 이동해야 값이 제대로 나오는 것 같다.
			 * 
			 */
			// 빈 공간이면 상어 이동
			if(!map[nr][nc].isShark && !map[nr][nc].isSmell) {
				isMove = true;
				dir[num] = directory;	// 방향이 바뀜
				movePos[num][0] = nr;	// 이동 방향 저장
				movePos[num][1] = nc;
				break;
			}
		}
		
		
		// 이동 못했다면 자기 냄새가 있는 방향으로 이동한다.
		if(!isMove) {
			if(selfSmellDir != 0) {
				int nr = r+dr[selfSmellDir];
				int nc = c+dc[selfSmellDir];
				dir[num] = selfSmellDir;	// 방향이 바뀜
				movePos[num][0] = nr;	// 이동 방향 저장
				movePos[num][1] = nc;
			}
		}
	}
}