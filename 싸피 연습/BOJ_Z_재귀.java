import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Z_재귀 {
	static int p = 0;
	static int r;
	static int c;

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		int N = Integer.parseInt(st.nextToken());
		r = Integer.parseInt(st.nextToken());
		c = Integer.parseInt(st.nextToken());
		visit(0, 0, N);
	}

	static void visit(int row, int col, int cnt) {
		if (cnt == 0) {
			if (row == r && col == c) {
				System.out.println(p);
				return;
			}
			p++;
			return;
		}
		//가만있기
		if (r < row + (int) Math.pow(2, cnt - 1) && c < col + (int) Math.pow(2, cnt - 1)) {
			visit(row, col, cnt - 1);
			return;
		}
		//오른쪽네모로 넘어가기
		if (r < row + (int) Math.pow(2, cnt - 1) && c >= col + (int) Math.pow(2, cnt - 1)) {
			p+= (int)(Math.pow(2, cnt - 1)*Math.pow(2, cnt - 1))*1;
			visit(row, col + (int) Math.pow(2, cnt - 1), cnt - 1);
			return;
		}
		//아래네모로 넘어가기
		if (r >= row + (int) Math.pow(2, cnt - 1) && c < col + (int) Math.pow(2, cnt - 1)) {
			p+= (int)(Math.pow(2, cnt - 1)*Math.pow(2, cnt - 1))*2;
			visit(row + (int) Math.pow(2, cnt - 1), col, cnt - 1);
			return;
		}
		//오른아래네모로 넘어가기
		if (r >= row + (int) Math.pow(2, cnt - 1) && c >= col + (int) Math.pow(2, cnt - 1)) {
			p+= (int)(Math.pow(2, cnt - 1)*Math.pow(2, cnt - 1))*3;
			visit(row + (int) Math.pow(2, cnt - 1), col + (int) Math.pow(2, cnt - 1), cnt - 1);
			return;
		}
	}
}