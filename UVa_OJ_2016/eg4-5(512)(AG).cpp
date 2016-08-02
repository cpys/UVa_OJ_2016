//#include <stdio.h>
//#include <string.h>
//#define maxd 100
//#define BIG 10000
//int r, c, n, d[maxd][maxd], d2[maxd][maxd], ans[maxd][maxd], cols[maxd];
//
//void copy(char type, int p, int q) {
//	if (type == 'R') {
//		for (int i = 1; i <= c; i++) {
//			d[p][i] = d2[q][i];
//		}
//	}
//	else {
//		for (int i = 1; i <= r; i++) {
//			d[i][p] = d2[i][q];
//		}
//	}
//}
//
//void del(char type) {
//	memcpy(d2, d, sizeof(d));
//	int cnt = type == 'R' ? r : c, cnt2 = 0;
//	for (int i = 1; i <= cnt; i++) {
//		if (!cols[i]) copy(type, ++cnt2, i);
//	}
//	if (type == 'R') r = cnt2;
//	else c = cnt2;
//}
//
//void ins(char type) {
//	memcpy(d2, d, sizeof(d));
//	int cnt = type == 'R' ? r : c, cnt2 = 0;
//	for (int i = 1; i <= cnt; i++) {
//		if (cols[i]) copy(type, ++cnt2, 0);
//		copy(type, ++cnt2, i);
//	}
//	if (type == 'R') r = cnt2;
//	else c = cnt2;
//}
//
//int main() {
//	int r1, c1, r2, c2, q, kase = 0;
//	char cmd[10];
//	memset(d, 0, sizeof(d));
//	while (scanf("%d%d%d", &r, &c, &n) == 3 && r) {
//		int r0 = r, c0 = c;
//		for (int i = 1; i <= r; i++) {
//			for (int j = 1; j <= c; j++) {
//				d[i][j] = i * BIG + j;
//			}
//		}
//		while (n--) {
//			scanf("%s", cmd);
//			if (cmd[0] == 'E') {
//				scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
//				int t = d[r1][c1];
//				d[r1][c1] = d[r2][c2];
//				d[r2][c2] = t;
//			}
//			else {
//				int a, x;
//				scanf("%d", &a);
//				memset(cols, 0, sizeof(cols));
//				for (int i = 0; i < a; i++) {
//					scanf("%d", &x);
//					cols[x] = 1;
//				}
//				if (cmd[0] == 'D') {
//					del(cmd[1]);
//				}
//				else ins(cmd[1]);
//			}
//		}
//		memset(ans, 0, sizeof(ans));
//		for (int i = 1; i <= r; i++) {
//			for (int j = 1; j <= c; j++) {
//				ans[d[i][j] / BIG][d[i][j] % BIG] = i * BIG + j;
//			}
//		}
//		if (kase > 0) printf("\n");
//		printf("Spreadsheet #%d\n", ++kase);
//		scanf("%d", &q);
//		while (q--) {
//			scanf("%d%d", &r1, &c1);
//			printf("Cell data in (%d,%d) ", r1, c1);
//			if (ans[r1][c1] == 0) printf("GONE\n");
//			else printf("moved to (%d,%d)\n", ans[r1][c1] / BIG, ans[r1][c1] % BIG);
//		}
//	}
//	return 0;
//}

#include <cstdio>
#include <cstring>
#define maxd 10000

struct Command {
	char c[5];
	int r1, c1, r2, c2;
	int a, x[20];
} cmd[maxd];
int r, c, n;

int simulate(int& r0, int& c0) {
	for (int i = 0; i < n; i++) {
		if (cmd[i].c[0] == 'E') {
			if (cmd[i].r1 == r0 && cmd[i].c1 == c0) {
				r0 = cmd[i].r2;
				c0 = cmd[i].c2;
			}
			else if (cmd[i].r2 == r0 && cmd[i].c2 == c0) {
				r0 = cmd[i].r1;
				c0 = cmd[i].c1;
			}
		}
		else {
			int dr = 0, dc = 0;
			for (int j = 0; j < cmd[i].a; j++) {
				int x = cmd[i].x[j];
				if (cmd[i].c[0] == 'I') {
					if (cmd[i].c[1] == 'R' && x <= r0) dr++;
					if (cmd[i].c[1] == 'C' && x <= c0) dc++;
				}
				else {
					if (cmd[i].c[1] == 'R' && x == r0) return 0;
					if (cmd[i].c[1] == 'C' && x == c0) return 0;
					if (cmd[i].c[1] == 'R' && x < r0) dr--;
					if (cmd[i].c[1] == 'C' && x < c0) dc--;
				}
			}
			r0 += dr;
			c0 += dc;
		}
	}
	return 1;
}

int main() {
	int r0, c0, q, kase = 0;
	while (scanf("%d%d%d", &r, &c, &n) == 3 && r) {
		for (int i = 0; i < n; i++) {
			scanf("%s", cmd[i].c);
			if (cmd[i].c[0] == 'E') {
				scanf("%d%d%d%d", &cmd[i].r1, &cmd[i].c1, &cmd[i].r2, &cmd[i].c2);
			}
			else {
				scanf("%d", &cmd[i].a);
				for (int j = 0; j < cmd[i].a; j++) {
					scanf("%d", &cmd[i].x[j]);
				}
			}	
		}
		if (kase > 0) printf("\n");
		printf("Spreadsheet #%d\n", ++kase);

		scanf("%d", &q);
		while (q--) {
			scanf("%d%d", &r0, &c0);
			printf("Cell data in (%d,%d) ", r0, c0);
			if (!simulate(r0, c0)) printf("GONE\n");
			else printf("moved to (%d,%d)\n", r0, c0);
		}
	}
	return 0;
}