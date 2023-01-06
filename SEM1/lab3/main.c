#include <stdio.h>
#include <stdlib.h>
#include "holylib.h"
#include "cases.h"

double *arrayInput() {
    double value, mean;
    int menu, placeHolder, index, len, n;
    int loop = 0;
	int reallen = 1;
	int error = 0;
	int newEl, el = 0;
	double *data = (double *)malloc(sizeof(double));
	double *newData;
	while (1){
			printf("%d --- %d\n", el, reallen);
		if (error == 1) {
		    break;
		}
		printf("Меню:\n");
		printf("  1 - инициализировать массив\n  2 - вставить элемент в массив\n  3 - удалить элемент из массива\n  4 - обработать массив (инд. задание)\n  5 - вывести массив\n  Все остальное, кроме символов - завершить программу\n");\
		error = inputInt(&menu);
		if (error) {
		    printf("Программа закончена\n");
		    free(data);
		    free(newData);
			break;
		}
		printf("\n");
        switch (menu) {
		    case 1:
				error = menuInput(&loop, &el, &data, &reallen);
				break;
		    case 2:
				error = menuInsert(&loop, &reallen, &el, &data);
				break;
		    case 3:
				error = menuRemove(&loop, &el, &reallen, &data);
				break;
			case 4:
				newData = menuTask(&loop, &el, &reallen, &data, &newEl);
				break;
			case 5:
				if (loop == 0) {
				    printf("Выводить то нечего! Попробуйте снова позже, когда будет что выводить\n\n");
					break;
				}
				int choice;
				printf("Какой из массивов хотите вывести?\n 1 - изнчачальный\n 2 - новый старый\n");
				error = inputInt(&choice);
				if (error) {
				    printf("Программа закончена\n)");
				}
				switch (choice) {
				     case 1:
						printArrayDouble(data, el);
						printf("=====================================================\n");
						break;
				     case 2:
						printArrayDouble(newData, newEl);
						printf("=====================================================\n");
						break;
				     deafault:
						printf("Ни я ни вы не создавали столько массивов... Попробуйте снова\n");
						break;
				}
				break;
			default:
		        printf("Программа закончена :)\n");
				free(data);
				free(newData);
				error = 1;
				break;
		}
	}
    return data;
}

int main() {
   double *data;
   data = arrayInput();
   return 0;
}
