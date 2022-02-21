#include <stdint.h>
#include <unistd.h>

typedef enum	boolean_e {
	false,
	true
}		boolean_t;

void		bprint(char board[9][9]) {
	char	print[90];
	uint8_t	x;
	uint8_t	y;
	
	y = 0;
	while (y < 9) {
		x = 0;
		while (x < 9) {
			print[(y * 9 + y) + x] = board[y][x];
			x++;
		}
		print[y * 9 + y + 9] = '\n';
		y++;
	}
	write(1, print, 90);
}

boolean_t	valid(register char board[9][9], register uint8_t x, register uint8_t y) {
	register uint8_t	X;
	register uint8_t	Y;
	register char		c;
	
	c = board[y][x];
	if (0 != x && board[y][0] == c) return false;
	if (0 != y && board[0][x] == c) return false;
	if (1 != x && board[y][1] == c) return false;
	if (1 != y && board[1][x] == c) return false;
	if (2 != x && board[y][2] == c) return false;
	if (2 != y && board[2][x] == c) return false;
	if (3 != x && board[y][3] == c) return false;
	if (3 != y && board[3][x] == c) return false;
	if (4 != x && board[y][4] == c) return false;
	if (4 != y && board[4][x] == c) return false;
	if (5 != x && board[y][5] == c) return false;
	if (5 != y && board[5][x] == c) return false;
	if (6 != x && board[y][6] == c) return false;
	if (6 != y && board[6][x] == c) return false;
	if (7 != x && board[y][7] == c) return false;
	if (7 != y && board[7][x] == c) return false;
	if (8 != x && board[y][8] == c) return false;
	if (8 != y && board[8][x] == c) return false;
	Y = y / 3 * 3;
	X = x / 3 * 3;
	if (!(Y == y && X == x) && board[Y][X] == c) return false;
	if (!(Y + 1 == y && X == x) && board[Y + 1][X] == c) return false;
	if (!(Y + 2 == y && X == x) && board[Y + 2][X] == c) return false;
	if (!(Y == y && X + 1 == x) && board[Y][X + 1] == c) return false;
	if (!(Y + 1 == y && X + 1 == x) && board[Y + 1][X + 1] == c) return false;
	if (!(Y + 2 == y && X + 1 == x) && board[Y + 2][X + 1] == c) return false;
	if (!(Y == y && X + 2 == x) && board[Y][X + 2] == c) return false;
	if (!(Y + 1 == y && X + 2 == x) && board[Y + 1][X + 2] == c) return false;
	if (!(Y + 2 == y && X + 2 == x) && board[Y + 2][X + 2] == c) return false;
	return true;
}

boolean_t	solve(register char board[9][9], register uint8_t x, register uint8_t y) {
	while (y < 9) {
		while (x < 9) {
			if (board[y][x] == '0') {
				while (board[y][x] < '9') {
					board[y][x]++;
					if (valid(board, x, y) && solve(board, x + 1, y)) return true;
				}
				board[y][x] = '0';
				return false;
			}
			x++;
		}
		x = 0;
		y++;
	}
	return true;
}

void		sudoku(register char **argv) {
	register uint8_t	y;
	register uint8_t	x;
	register char		board[9][9];
	
	y = 0;
	while (y < 9) {
		x = 0;
		while (argv[y][x] != '\0') {
			if (x >= 9 || argv[y][x] < '0' || argv[y][x] > '9') return;
			board[y][x] = argv[y][x];
			x++;
		}
		if (x < 9) return;
		y++;
	}
	while (y > 0) {
		y--;
		while (x > 0) {
			x--;
			if (board[y][x] != '0' && !valid(board, x, y)) return;
		}
		x = 9;
	}
	if (solve(board, 0, 0)) bprint(board);
}

int		main(int argc, char **argv) {
	if (argc == 10) sudoku(argv + 1);
	return 0;
}
