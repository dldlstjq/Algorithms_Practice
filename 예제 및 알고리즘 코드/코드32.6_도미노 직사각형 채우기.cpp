const int dx[4] = { 1,-1,0,0 };
const int dy[4] = { 0,0,1,-1 };
//(y,x)가 직사각형 범위 안의 칸인지 확인한다.
bool inRange(int y, int x);
//직사각형의 정보
int H, W;
vector<string> board;
//주어진 직사각형에 도미노를 채울 수 있는지 여부를 반환한다.
bool fillDomino() {
	//각 칸을 표현하는 정점의 번호를 계산한다.
	vector<vector<int>>id(H, vector<int>(W, -1));
	//각 칸을 순회하며 번호를 매긴다.
	n = m = 0;
	for (int y = 0; y < H; ++y)
		for (int x = 0; x < W; ++x)
			if (board[y][x] != '#') {
				if ((y + x) % 2 == 0)
					id[y][x] = n++;
				else
					id[y][x] = m++;
			}
	//adj[][]를 채운다.
	memset(adj, 0, sizeof(adj));
	//A에 속한 모든 칸에 대해 인접한 칸을 검사한다.
	for(int y1=0;y1<H;++y1)
		for(int x1=0;x1<W;++x1)
			if ((y1 + x1) % 2 == 0 && board[y1][x1] != '#') {
				//(y1,x1)의 모든 인접한 칸을 검사한다.
				for (int k = 0; k < 4; ++k) {
					int y2 = y1 + dy[k], x2 = x1 + dx[k];
					//(y2,x2)가 범위 안에 있는 빈 칸이라면 두 정점을 연결한다.
					if (inRange(y2, x2) && board[y2][x2] != '#')
						adj[id[y1][x1]][id[y2][x2]] = 1;
				}
			}
	//이분 매칭의 크기가 빈 칸의 수의 절반이어야 한다.
	return bipartiteMatch() * 2 == (n + m);
}