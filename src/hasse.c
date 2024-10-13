#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "ezdib.h"

#define MAXSIZE 100

typedef struct Lecture {

	char lectureName[MAXSIZE];
	struct Lecture* links[MAXSIZE];
	int outgoing, incoming;
	int x, y;
	//bool isEnqueue;

} Lecture;


int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("Usage: hasse <input_file>\n");
		return 1;
	}

	char* input = argv[1];
	

	Lecture initArr[MAXSIZE];
	Lecture clonedArr[MAXSIZE];
	//Lecture queue[MAXSIZE];
	//Lecture sortedarr[MAXSIZE];

	char buff[MAXSIZE];

	int cntLectureName = 0;
	//int front = 0, rear = 0;
	//int cntSortedArray = 0;
	int addx1 = 0, addx2 = 0, addx3 = 0;
	
	FILE *fp;
	fp = fopen(input, "r");

	
	for (int i = 0; i < MAXSIZE; i++) {
		initArr[i].outgoing = 0;
	}

	while (1) {

		int a = 0, b = 0;
		bool isNew = true;
		buff[0] = 0;
		fscanf(fp, "%s", buff);

		if (buff[0] == 0) {
			break;
		}

		for (int i = 0; i < cntLectureName; i++) {
			if (strcmp(initArr[i].lectureName, buff) == 0) {
				a = i;
				isNew = false;
				break;
			}
		}

		if (isNew) {
			a = cntLectureName++;
			strcpy(initArr[a].lectureName, buff);
		}

		isNew = true;

		fscanf(fp, "%s", buff);
		for (int i = 0; i < cntLectureName; i++) {
			if (strcmp(initArr[i].lectureName, buff) == 0) {
				b = i;
				isNew = false;
				break;
			}
		}

		if (isNew) {
			b = cntLectureName++;
			strcpy(initArr[b].lectureName, buff);
		}

		if (a != b) {
			initArr[a].links[initArr[a].outgoing++] = &initArr[b];
			initArr[b].incoming++;
		}

	}

	fclose(fp);

	for (int i = 0; i < cntLectureName; i++) {
		clonedArr[i] = initArr[i];
	}

	

	// while (true) {

	// 	for (int i = 0; i < cntLectureName; i++) {
	// 		if (initArr[i].incoming == 0 && !initArr[i].isEnqueue) {
	// 			queue[rear++] = initArr[i];
	// 			initArr[i].isEnqueue = true;

	// 		}
	// 	}

	// 	sortedarr[cntSortedArray++] = queue[front];

	// 	for (int i = 0; i < queue[front].outgoing; i++) {
	// 		queue[front].links[i]->incoming--;
	// 	}

	// 	front++;

	// 	if (front == rear) {
	// 		break;
	// 	}

	// }

	for (int i = 0; i < cntLectureName; i++) {

		if (clonedArr[i].incoming == 0) {
			clonedArr[i].y = 0;
		}
	}

	HEZDIMAGE hDib = ezd_create( 640, -480, 24, 0);
	ezd_fill( hDib, 0x606060 );
	HEZDFONT hFont = ezd_load_font( EZD_FONT_TYPE_MEDIUM, 0, 0 );

	

	for (int i = 0; i < cntLectureName; i++) {
		clonedArr[i].y = clonedArr[i].incoming;
	}

	

	int addx[MAXSIZE] = {0};

	for (int i = 0; i < cntLectureName; i++) {
		for (int j = 0; j < 100; j++) {
			if (clonedArr[i].y == j) {
				clonedArr[i].x = addx[j];
				addx[j] += 150;
			}
		}
		
		
	}

	for (int i = 0; i < cntLectureName; i++) {
		clonedArr[i].x = clonedArr[i].x+50;
		clonedArr[i].y = 300-100*clonedArr[i].y;

	}

	for (int i = 0; i < cntLectureName; i++) {
		ezd_set_pixel(hDib, clonedArr[i].x, clonedArr[i].y, 0xffffff);
		ezd_text( hDib, hFont, clonedArr[i].lectureName, -1, clonedArr[i].x, clonedArr[i].y-20, 0xffffff );

	}

	for (int i = 0; i < cntLectureName; i++) {
		for (int j = 0; j < clonedArr[i].outgoing; j++) {
			for (int k = 0; k < cntLectureName; k++) {
				if (strcmp(clonedArr[i].links[j]->lectureName, clonedArr[k].lectureName) == 0) {
					if ( abs(clonedArr[k].incoming - clonedArr[i].incoming) == 1) {
						ezd_line( hDib, clonedArr[i].x, clonedArr[i].y, clonedArr[k].x, clonedArr[k].y, 0xffffff );
					}

				}
			}
		}
	}

	ezd_save( hDib, strcat(input, ".bmp"));
	

	return 0;

}
