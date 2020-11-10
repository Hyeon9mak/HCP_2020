#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h> 

#define EPSILON 0.1
#define DC_RATE 0.5
#define size 10
#define EPISODE 30000

typedef struct {
	double R;
	int state;
	double direction[4];
}cell;

cell map[size][size];
cell* ptr = &map[0][0];

void init();
void print();

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
			srand(unsigned(time(NULL)));
			current->state = 0;
			action();
			current = ptr;
			current->state = 1;

			print();
			printf("%lf %lf %lf %lf %d", current->direction[0], current->direction[1], current->direction[2], current->direction[3], i);

			Sleep(10);
		}
		current->state = 0;
		ptr = &map[0][0];
		current = ptr;
	}
}

void init() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			map[i][j].R = 0;
			if (!i && !j) {
				map[i][j].state = 1;//0,0�� ���� ��ġ�� ���� 
			}
			else {
				map[i][j].R = 0;
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
	/*������� �� �ʱ�ȭ ����*/
	map[9][8].R = -3;
	map[8][7].R = -3;
	map[7][6].R = -3;
	map[6][5].R = -3;
	map[5][4].R = -3;
	map[4][3].R = -3;
	map[3][2].R = -3;
	map[2][1].R = -3;
	map[9][9].R = 3;

}
void print() {
	system("cls");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (map[i][j].state == 1)
				printf("�� ");//���� ��ġ
			else if (map[i][j].R == -3)
				printf("�� ");//������ ���� ����
			else if (map[i][j].R == 0)
				printf("�� ");//�ܴ��� ����
			else
				printf("�� ");//��ǥ����
		}
		printf("\n");
	}
}

int rand_way(double num[4]) {// 0���� ũ�ų� ���� Q���� ��ȣ�� ����
	int ret;

	srand(unsigned(time(NULL)));

	for (;;)
	{
		ret = rand() % 4;
		if (num[ret] >= -1)
			return ret;
	}
}

int value(double direction[4]) {

	int ret;
	int cnt[4] = { 0, };

	double max = direction[0];
	for (int i = 0; i < 4; i++) {
		if (max < direction[i]) {
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
		case 0://������
			if ((ptr + 1)->R != 0)
				ptr->direction[0] = (ptr + 1)->R;
			else
				ptr->direction[0] = DC_RATE * (ptr + 1)->direction[value((ptr + 1)->direction)];
			ptr = (ptr + 1);
			break;
		case 1://����
			if ((ptr - 1)->R != 0)
				ptr->direction[1] = (ptr - 1)->R;
			else
				ptr->direction[1] = DC_RATE * (ptr - 1)->direction[value((ptr - 1)->direction)];
			ptr = (ptr - 1);
			break;
		case 2://�Ʒ���
			if ((ptr + size)->R != 0)
				ptr->direction[2] = (ptr + size)->R;
			else
				ptr->direction[2] = DC_RATE * (ptr + size)->direction[value((ptr + size)->direction)];
			ptr = (ptr + size);
			break;
		case 3://����
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
		case 0://������
			if ((ptr + 1)->R != 0)
				ptr->direction[0] = (ptr + 1)->R;
			else
				ptr->direction[0] = DC_RATE * (ptr + 1)->direction[value((ptr + 1)->direction)];
			ptr = (ptr + 1);
			break;
		case 1://����
			if ((ptr - 1)->R != 0)
				ptr->direction[1] = (ptr - 1)->R;
			else
				ptr->direction[1] = DC_RATE * (ptr - 1)->direction[value((ptr - 1)->direction)];
			ptr = (ptr - 1);
			break;
		case 2://�Ʒ���
			if ((ptr + size)->R != 0)
				ptr->direction[2] = (ptr + 1 + size)->R;
			else
				ptr->direction[2] = DC_RATE * (ptr + size)->direction[value((ptr + size)->direction)];
			ptr = (ptr + size);
			break;
		case 3://����
			if ((ptr - size)->R != 0)
				ptr->direction[3] = (ptr - size)->R;
			else
				ptr->direction[3] = DC_RATE * (ptr - size)->direction[value((ptr - size)->direction)];
			ptr = (ptr - size);
			break;
		}
	}
}
