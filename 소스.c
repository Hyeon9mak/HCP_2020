#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h> 

#pragma warning(disable:4996)

#define EPSILON 0.1
#define DC_RATE 0.7
#define size 10
#define EPISODE 30000

typedef struct cell{
	double R;
	int state;
	int color;
	int connected;
	double direction[4];
	struct cell* connection;
}cell;

cell map[size][size];
cell* ptr = &map[0][0];
int arr[25][4];

int init(FILE* Map);
void print();
void sync();

void action();
int value(double num[4]);
int rand_way(double num[4]);




int main() {
	cell* current;
	
	FILE* Map;
	
	current = ptr;
	Map = fopen("Map.txt", "r");

	if (Map == NULL) {
		printf("initialize map failed\n");
		return -1;
	}
	init(Map);
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
			if (!(i % 1000) && i != 0){
				print();
				printf("%lf %lf %lf %lf %d\r", current->direction[0], current->direction[1], current->direction[2], current->direction[3], i);
				Sleep(50);
			}
			
		}
		current->state = 0;
		ptr = &map[0][0];
		current = ptr;
		current->state = 1;

	}
}

int init(FILE* Map) {
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
	int cnt = 0;
	char tmp;
	tmp = fgetc(Map);
	tmp = fgetc(Map);
	tmp = fgetc(Map);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			tmp = fgetc(Map);
			if (tmp != '\n' && tmp != ' ') {
				if (tmp == 'T') {//T는 지름길 입구,s는 지름길 출구
					map[i][j].R = 0;
					for (int k = 0; k < 2; k++) {
						arr[cnt][0] = i;
						arr[cnt][1] = j;
						arr[cnt][k + 2] = fgetc(Map) - 48;
					}
					cnt++;
				}
				else if (tmp == 'w')//w 는 지나가면 위험한 곳
					map[i][j].R = -3;
				else if (tmp == 'c')//c 는 지나가도 괜찮은 곳
					map[i][j].R = 0;
				else if (tmp == 'g')//g 는 목표 지점
					map[i][j].R = 3;
				else if (tmp == 'p') {//p는 현재 위치
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
			map[arr[i][0]][arr[i][1]].color = i;
			map[arr[i][2]][arr[i][3]].color = i;
		}
	}

}
void print() {
	COORD pos = { 0, 0 };
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j].connection != NULL) {
				if (map[i][j].state == 1)
					printf("● ");//현재 위치
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(map[i][j].color + 5)/2 );
					printf("★ ");//지름길 입구 , 들어가는 곳과 나오는 곳 구분을 위해 색 지정
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}
			}
			else if (map[i][j].connected != 0) {
				if (map[i][j].state == 1)
					printf("● ");//현재 위치
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (map[i][j].color + 5)/2);
					printf("☆ ");//지름길 입구 , 들어가는 곳과 나오는 곳 구분을 위해 색 지정
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}
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



int rand_way(double direction[4]) {// 0보다 크거나 같은 Q 값의 방향을 랜덤으로 선택
	int ret;

	srand((unsigned)time(NULL));

	while (1) {
		ret = rand() % 4;
		if (direction[ret] >= 0)
			return ret;
	}
}

int value(double direction[4]) {//가장 큰 Q 값을 선택, 중복이 있을경우 랜덤으로 선택
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

void action() {//행동 함수
	srand((unsigned)time(NULL));
	register int select;//속도 향상을 위해 레지스터 변수를 사용 
	double n = rand();
	n /= 32767;//랜덤값을 1~0 으로 생성
	if (n< EPSILON) {//랜덤 행동의 확률
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