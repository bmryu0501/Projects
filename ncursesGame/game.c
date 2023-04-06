#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define N 7

char map[N][N+1] = {
	"#######",
	"#     #",
	"# ##  #",
	"#    a#",
	"#^^ ###",
	"#    Y#",
	"#######",
};

int ny = 1;
int nx = 1;
int hp = 100;
int moved = 0;
int game_status = 1;

int my = 5;
int mx = 1;

char endFalgs[2][100] = {
	"GAME OVER",
	"WIN"
};

void print() {
	clear();
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			if(i == ny && j == nx) printw("@");
			else if(i == my && j == mx) printw("M");
			else printw("%c", map[i][j]);
		}
		printw("\n");
	}
	printw("HP : %d\n", hp);
	refresh();
}

int dy[4] = {0, 0, -1, 1};
int dx[4] = {-1, 1, 0, 0};

void* moveMonster() {
	while(game_status) {
		int d = rand()%4;
		my += dy[d];
		mx += dx[d];
		if(map[my][mx] == '#') {
			my -= dy[d];
			mx -= dx[d];
		}
		usleep(500 * 1000);
	}
}

void moveCharacter() {
	int ch = getch();
	if(ch == ERR) {
		ch = 0;
		moved = 0;
	}

	if(ch == KEY_LEFT) {
		nx--;
		if(map[ny][nx] == '#') nx++;
		moved = true;
	}
	if(ch == KEY_RIGHT) {
		nx++;
		if(map[ny][nx] == '#') nx--;
		moved = true;
	}
	if(ch == KEY_UP) {
		ny--;
		if(map[ny][nx] == '#') ny++;
		moved = true;
	}
	if(ch == KEY_DOWN) {
		ny++;
		if(map[ny][nx] == '#') ny--;
		moved = true;
	}
}

void endGame(int flag) {
	game_status = 0;
	usleep(500 * 1000);
	clear();
	mvprintw(6, 10, endFalgs[flag]);
	refresh();
	sleep(3);
	return;
}


int checkPosition() {
	if(!moved) return 0;
	if(ny == my && nx == mx) {
		endGame(0);
		return 1;
	}
	if(map[ny][nx] == 'Y') {
		endGame(1);
		return 1;
	}
	if(map[ny][nx] == '^') {
		hp -= 10;
		print();
		if(hp <= 0) {
			endGame(0);
			return 1;
		}
	}
	if(map[ny][nx] == 'a') {
		hp = 100;
		map[ny][nx] = ' ';
		print();
	}
	return 0;
}

int main() {
	initscr();
	curs_set(0);

	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);

	pthread_t tid;
	pthread_create(&tid, NULL, moveMonster, NULL);

	while(1) {
		print();

		if(checkPosition()) break;
		moveCharacter();

		usleep(100);
	}

	pthread_join(tid, NULL);

	getch();
	endwin();
	return 0;
}
