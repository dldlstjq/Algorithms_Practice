/*
쉬워보였는데 간과한게 있어 제법 오래 걸렸다.
배열 회전의 경우 테두리를 하나씩 옮기는 방식을 썼다. 가장 큰 테두리를 회전시키고 그 다음 안의 배열을 회전시키는 방식이었다.
이것 말고도 가장 위의 행이 가장 오른쪽 열로 이동하는 것도 가능하기 때문에 더 쉬운 방법으로 하면 좋을 것 같다.
테두리를 재귀방식으로 하나씩 옮기는 것은 한 번 줄어들 때 2칸씩 줄어들어야 하는데 잘못된 방법이어서 틀렸다.
또 2^0이 되어 아예 회전을 하지 않을 떄는 rotate 하지 않아야 된다는 조건이 필요해서 조금 비효율적인 것 같긴 하다.

두 번째로 인접한 곳의 얼음이 없는 것이 2개 이상이면 1이 감소하는 부분이다.
얼음이 동시에 감소하기 때문에 원래 배열에서 하나씩 검사해서 감소를 시켜버리면 인접한 얼음에도 영향을 미친다.
따라서 인접 얼음이 3개미만인 것들을 모아 한번에 처리해야 한다.
arr배열에서 만족하지 않으면 tmp 배열을 하나씩 감소시킨 후 다시 복사해서 그 값을 가져왔다.
아니면 리스트를 활용해서 조건에 만족하지 않는 좌표를 모아서 한꺼번에 빼줘도 될 것 같다.

동시에 감소하는 것을 고려하지 않아 제법 시간이 걸렸다.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {

	static class Pair{
		int r; int c;
		Pair(int r, int c){
			this.r=r;
			this.c=c;
		}
	}

	static int N, Q;
	static int[][] arr;
	static int[][] tmp;
	static boolean[][] visited;

	static int dr[]= {-1,0,1,0};
	static int dc[]= {0,1,0,-1};

	static int len;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		N = Integer.parseInt(st.nextToken());
		Q = Integer.parseInt(st.nextToken());

		len = 1<<N;
		arr = new int[len][len];
		visited= new boolean[len][len];

		for(int i=0; i<len; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<len; ++j) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}

		st = new StringTokenizer(br.readLine());
		for(int i=0; i<Q; ++i) {
			int L = Integer.parseInt(st.nextToken());
			solve(L);
		}

		System.out.println(getIce());
		System.out.println(calcIceArea());

	}

	private static int calcIceArea() {
		int sum = 0;
		for(int i=0; i<len; ++i) {
			for(int j=0; j<len; ++j) {
				if(visited[i][j] || arr[i][j]==0) continue;
				sum = Math.max(sum, getIceArea(i, j));
			}
		}
		return sum;
	}

	private static int getIceArea(int r, int c) {
		int area = 1;
		Queue<Pair> q = new LinkedList();
		q.offer(new Pair(r, c));
		visited[r][c] = true;

		while(!q.isEmpty()) {
			Pair now = q.poll();

			for(int i=0; i<4; ++i) {
				int nr= now.r+dr[i];
				int nc = now.c+dc[i];

				// 범위 벗어나거나 얼음이 없으면 카운트
				if(!(0<=nr&&nr<len && 0<=nc&&nc<len)
						|| arr[nr][nc]==0 || visited[nr][nc]) continue;

				q.offer(new Pair(nr, nc));
				visited[nr][nc] = true;
				area++;
			}
		}
		return area;
	}

	private static int getIce() {
		int sum=0;
		for(int i=0; i<len; ++i)
			for(int j=0; j<len; ++j)
				sum += arr[i][j];
		return sum;
	}

	private static void solve(int l) {
		int num = 1<<l;
		tmp = new int[len][len];

		// 회전한 경우에만 복사
		if(num != 1) {
			for(int i=0; i<len; i+=num) {
				for(int j=0; j<len; j+=num) {
					rotate(i, j, num);
				}
			}
			copy();
		}
		else {    // num=1이어서 회전하지 않으면 얼음 녹이기 위해 arr를 tmp에 복사
			for(int i=0; i<len; ++i)
				tmp[i] = arr[i].clone();
		}

		fireIce();    // 얼음 녹이기
	}

	private static void fireIce() {
		for(int i=0; i<len; ++i) {
			for(int j=0; j<len; ++j) {
				if(arr[i][j] == 0) continue;
				check(i, j);
			}
		}
		copy();
	}

	private static void check(int r, int c) {
		int cnt= 0;
		for(int i=0; i<4; ++i) {
			int nr= r+dr[i];
			int nc = c+dc[i];

			// 범위 벗어나거나 얼음이 없으면 카운트
			if(!(0<=nr&&nr<len && 0<=nc&&nc<len) || arr[nr][nc]==0) cnt++;
		}

		// arr에 바로 빼주게 되면 전체 결과에 영향을 미치게 된다. 
		if(cnt>=2) tmp[r][c]-=1;
	}

	private static void rotate(int r, int c, int n) {

		if(n == 0) return;

		int row = r;
		// 맨 위는 맨 오른쪽으로
		for(int i=c; i<c+n; ++i)
			tmp[row++][c+n-1] = arr[r][i];

		int col = c+n-1;
		// 맨 오른쪽은 맨 아래로
		for(int i=r; i<r+n; ++i)
			tmp[r+n-1][col--] = arr[i][c+n-1];


		// 아래는 왼쪽으로
		row = r;
		for(int i=c; i<c+n; ++i)
			tmp[row++][c] = arr[r+n-1][i];

		// 왼쪽은 위로
		col = c+n-1;
		for(int i=r; i<r+n; ++i)
			tmp[r][col--] = arr[i][c];

		// 2칸씩 줄어든다.
		rotate(r+1, c+1, n-2);
	}

	private static void copy() {
		for(int i=0; i<len; ++i)
			arr[i] = tmp[i].clone();
	}
}