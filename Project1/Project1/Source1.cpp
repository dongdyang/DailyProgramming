

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
char g[5][5];
int ansx;
int ansy;

// �����ǰ���� 'x' ȡʤ�򷵻� 1��'o' ȡʤ�򷵻� -1�����򷵻� 0  
int judge()
{
	int i, j;
	int xa = 0, xb = 0; // �ж����Խ���  
	int ya = 0, yb = 0; // �жϸ��Խ���  
	for (i = 0; i < 4; i++) {
		int ra = 0, rb = 0; // �ж���  
		int ca = 0, cb = 0; // �ж���  
		if (g[i][i] == 'x')
			xa += 1;
		else if (g[i][i] == 'o')
			xb += 1;
		if (g[i][3 - i] == 'x')
			ya += 1;
		else if (g[i][3 - i] == 'o')
			yb += 1;
		for (j = 0; j < 4; j++) {
			if (g[i][j] == 'x')
				ra += 1;
			else if (g[i][j] == 'o')
				rb += 1;
			if (g[j][i] == 'x')
				ca += 1;
			else if (g[j][i] == 'o')
				cb += 1;
		}
		if (ra == 4 || ca == 4 || xa == 4 || ya == 4)
			return 1;
		else if (rb == 4 || cb == 4 || xb == 4 || yb == 4)
			return -1;
	}
	return 0;
}

int alpha_beta(int player, int alpha, int beta)
{
	int i, j;
	int flag;
	flag = judge();
	if (flag) // �Ѿ��ֳ�ʤ��  
		return flag;
	if (player) {
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (g[i][j] == '.') {
					int val;
					g[i][j] = 'x'; // ����  
					val = alpha_beta(player ^ 1, alpha, beta);
					g[i][j] = '.'; // ����  
					if (val > alpha) {
						alpha = val;
						ansy = i;
						ansx = j;
					}
					if (alpha >= beta)
						return alpha;
				}
			}
		}
		return alpha;
	}
	else {
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (g[i][j] == '.') {
					int val;
					g[i][j] = 'o';
					val = alpha_beta(player ^ 1, alpha, beta);
					g[i][j] = '.';
					if (val < beta)
						beta = val;
					if (alpha >= beta)
						return beta;
				}
			}
		}
		return beta;
	}
}

int main()
{
	fopen("input.txt", "r", stdin);
	char od[2];
	while (scanf("%s", od), od[0] != '$') {
		int i, j;
		int alpha = -1;
		int beta = 1;
		int ans;
		int count = 0;
		for (i = 0; i < 4; i++) {
			scanf("%s", g[i]);
			for (j = 0; j < 4; j++)
				if (g[i][j] != '.')
					count++;
		}
		if (count <= 4) { // ���Ŀǰ���̵����Ӳ����� 4 ����˫�����ޱ�ʤ����  
			printf("#####\n");
			continue;
		}
		ans = alpha_beta(1, alpha, beta);
		if (ans > 0)
			printf("(%d,%d)\n", ansy, ansx);
		else
			printf("#####\n");
	}
	return 0;
}

