#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h> 

#pragma warning(disable:4996)

#define EPSILON 0.3
#define DC_RATE 0.7
#define size 10
#define EPISODE 30000

typedef struct cell {
	double R;
	int state;
	int connected;
	double direction[4];
	struct cell* connection;
}cell;

cell map[size][size];
cell* ptr = &map[0][0];
int arr[25][4];

int init();
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

int init() {
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
<<<<<<< Updated upstream:source.c
	/*������� �� �ʱ�ȭ ����*/
<<<<<<< HEAD
	FILE* Map;
	char tmp;

	int cnt = 0;
	Map = fopen("Map.txt", "r");
	if (Map == NULL) {
		printf("initialize map failed\n");
		return -1;
	}
	tmp = fgetc(Map);
	tmp = fgetc(Map);
	tmp = fgetc(Map);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			tmp = fgetc(Map);
			if (tmp != '\n' && tmp != ' ') {
				if (tmp == 'T') {
					map[i][j].R = 0;
					for (int k = 0; k < 2; k++) {
						arr[cnt][0] = i;
						arr[cnt][1] = j;
						arr[cnt][k + 2] = fgetc(Map) - 48;
					}
					cnt++;
				}
				else if (tmp == 'w')
					map[i][j].R = -3;
				else if (tmp == 'c')
					map[i][j].R = 0;
				else if (tmp == 'g')
					map[i][j].R = 3;
				else if (tmp == 'p') {
					map[i][j].R = 0;
					map[i][j].state = 1;
				}
				else
					map[i][j].R = 0;
			}
			else
				j--;
		}
	}
	fclose(Map);
	for (int i = 0; i < 25; i++) {
		if (map[arr[i][0]][arr[i][1]].state != 1) {
			map[arr[i][0]][arr[i][1]].connection = &map[arr[i][2]][arr[i][3]];
			map[arr[i][0]][arr[i][1]].connected = 1;
			map[arr[i][2]][arr[i][3]].connected = 1;
		}
	}
=======
=======
	/*여기부터 맵 초기화 시작*/
>>>>>>> Stashed changes:소스코드/source.c
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
>>>>>>> cb05f8631b50c0b2ca25b0be02512967261938e3

}
void print() {
	system("cls");
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j].connection != NULL) {
				if (map[i][j].state == 1)
<<<<<<< Updated upstream:source.c
					printf("�� ");//���� ��ġ
				else
					printf("�� ");
			}
			else if (map[i][j].connected != 0) {
				if (map[i][j].state == 1)
					printf("�� ");//���� ��ġ
				else
					printf("�� ");
			}
			else {
				if (map[i][j].state == 1)
					printf("�� ");//���� ��ġ
				else if (map[i][j].R == -3)
					printf("�� ");//������ ���� ����
				else if (map[i][j].R == 0)
					printf("�� ");//�ܴ��� ����
				else if (map[i][j].R == 3)
					printf("�� ");//��ǥ����
=======
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
>>>>>>> Stashed changes:소스코드/source.c
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

<<<<<<< HEAD


=======
<<<<<<< Updated upstream:source.c
>>>>>>> cb05f8631b50c0b2ca25b0be02512967261938e3
int rand_way(double direction[4]) {// 0���� ũ�ų� ���� Q���� ��ȣ�� ����
=======
int rand_way(double direction[4]) {// 0보다 크거나 같은 Q값의 번호를 리턴
>>>>>>> Stashed changes:소스코드/source.c
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