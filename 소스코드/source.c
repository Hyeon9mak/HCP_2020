#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h> 

#define EPSILON 0.3
#define DC_RATE 0.7
#define size 10
#define EPISODE 30000

typedef struct cell{
	double R;
	int state;
	double direction[4];
	struct cell* connection;
}cell;

cell map[size][size];
cell* ptr = &map[0][0];

void init();
void print();
void sync();

void action();
int value(double num[4]);
int rand_way(double num[4]);




int main() {
	cell* current;
	current = ptr;
	init();
	print();
	for (int i = 0; i < EPISODE; i++) {
		while (current != &map[size - 1][size - 1]) {
			srand((unsigned)time(NULL));
			sync();
			current->state = 0;

			action();
			if (ptr->connection != NULL)
				ptr = ptr->connection;
			current = ptr;
			current->state = 1;

			print();


			printf("%lf %lf %lf %lf %d", current->direction[0], current->direction[1], current->direction[2], current->direction[3], i);

			Sleep(5);
		}
		current->state = 0;
		ptr = &map[0][0];
		current = ptr;
		current->state = 1;

	}
}

void init() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			map[i][j].R = 0;
			map[i][j].connection = NULL;
			if (!i && !j) {
				map[i][j].state = 1;//0,0은 현재 위치로 설정 
			}
			else {
				map[i][j].state = 0;
			}
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == 0)
				map[i][j].direction[3] = -2;
			else if (i == size - 1)
				map[i][j].direction[2] = -2;
			if (j == 0)
				map[i][j].direction[1] = -2;
			else if (j == size - 1)
				map[i][j].direction[0] = -2;
		}
	}
	/*여기부터 맵 초기화 시작*/
	map[6][1].connection = &map[7][9];
	map[5][3].connection = &map[0][6];
	map[0][3].R = -3;
	map[8][5].R = -3;
	map[4][6].R = -3;
	map[4][2].R = -3;
	map[3][0].R = -3;
	map[7][2].R = -3;
	map[5][4].R = -3;
	map[1][7].R = -3;
	map[2][8].R = -3;
	map[8][5].R = -3;
	map[9][9].R = 3;

}
void print() {
	system("cls");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((i == 6 && j == 1) || (i == 5 && j == 3)) {
				if (map[i][j].state == 1)
					printf("● ");//현재 위치
				else
					printf("★ ");
			}
			else if ((i == 7 && j == 9) || (i == 0 && j == 6)) {
				if (map[i][j].state == 1)
					printf("● ");//현재 위치
				else
					printf("☆ ");
			}
			else {
				if (map[i][j].state == 1)
					printf("● ");//현재 위치
				else if (map[i][j].R == -3)
					printf("■ ");//깨지기 쉬운 지역
				else if (map[i][j].R == 0)
					printf("□ ");//단단한 지역
				else if (map[i][j].R == 3)
					printf("▲ ");//목표지점
			}
		}
		printf("\n");
	}
}

void sync() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (map[i][j].connection != NULL) {
				for (int k = 0; k < 4; k++)
					map[i][j].direction[k] = map[i][j].connection->direction[k];
			}
		}
	}
}

int rand_way(double direction[4]) {// 0보다 크거나 같은 Q값의 번호를 리턴
	int ret;

	srand((unsigned)time(NULL));

	while (1) {
		ret = rand() % 4;
		if (direction[ret] >= 0)
			return ret;
	}
}

int value(double direction[4]) {
	srand((unsigned)time(NULL));
	int ret;
	int cnt[4] = { 0, };

	double max = direction[0];
	for (int i = 0; i < 4; i++) {
		if (max < direction[i] && direction[i] >= 0) {
			for (int j = 0; j < i; j++)
				cnt[j] = 0;
			max = direction[i];
			cnt[i] = 1;
		}
		else if (max == direction[i]) {
			cnt[i] = 1;
		}
	}
	while (1) {
		ret = rand() % 4;
		if (cnt[ret] != 0 && direction[ret] >= -1)
			return ret;
	}
}

void action() {

	register int select;
	if (rand() < EPSILON) {
		select = rand_way(ptr->direction);
		//printf("%d\n",select);
		switch (select) {
		case 0://오른쪽
			if ((ptr + 1)->R != 0)
				ptr->direction[0] = (ptr + 1)->R;
			else
				ptr->direction[0] = DC_RATE * (ptr + 1)->direction[value((ptr + 1)->direction)];
			ptr = (ptr + 1);
			break;
		case 1://왼쪽
			if ((ptr - 1)->R != 0)
				ptr->direction[1] = (ptr - 1)->R;
			else
				ptr->direction[1] = DC_RATE * (ptr - 1)->direction[value((ptr - 1)->direction)];
			ptr = (ptr - 1);
			break;
		case 2://아래쪽
			if ((ptr + size)->R != 0)
				ptr->direction[2] = (ptr + size)->R;
			else
				ptr->direction[2] = DC_RATE * (ptr + size)->direction[value((ptr + size)->direction)];
			ptr = (ptr + size);
			break;
		case 3://윗쪽
			if ((ptr - size)->R != 0)
				ptr->direction[3] = (ptr - size)->R;
			else
				ptr->direction[3] = DC_RATE * (ptr - size)->direction[value((ptr - size)->direction)];
			ptr = (ptr - size);
			break;
		}

	}
	else {
		select = value(ptr->direction);
		//printf("%d\n", select);
		switch (select) {
		case 0://오른쪽
			if ((ptr + 1)->R != 0)
				ptr->direction[0] = (ptr + 1)->R;
			else
				ptr->direction[0] = DC_RATE * (ptr + 1)->direction[value((ptr + 1)->direction)];
			ptr = (ptr + 1);
			break;
		case 1://왼쪽
			if ((ptr - 1)->R != 0)
				ptr->direction[1] = (ptr - 1)->R;
			else
				ptr->direction[1] = DC_RATE * (ptr - 1)->direction[value((ptr - 1)->direction)];
			ptr = (ptr - 1);
			break;
		case 2://아래쪽
			if ((ptr + size)->R != 0)
				ptr->direction[2] = (ptr + size)->R;
			else
				ptr->direction[2] = DC_RATE * (ptr + size)->direction[value((ptr + size)->direction)];
			ptr = (ptr + size);
			break;
		case 3://윗쪽
			if ((ptr - size)->R != 0)
				ptr->direction[3] = (ptr - size)->R;
			else
				ptr->direction[3] = DC_RATE * (ptr - size)->direction[value((ptr - size)->direction)];
			ptr = (ptr - size);
			break;
		}
	}
}