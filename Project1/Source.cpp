#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<io.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iostream>
using namespace std;
const int limit = 100;
struct subscriber
{
	char surname[20];
	int year;
	char phoneNumber[100];
}pInfo;

void createNewFile();
void readFile();
void change();
void deletion();



//void task();
//void add(int);
//int addSubscriber();


void main() {
	int s;
	char key = NULL;

	do {
		system("cls");
		printf_s("\t---MENU---\n\
1.Create a new file\n\
2.View the file\n\
3.Correct file records\n\
4.Carry out the task\n\
5.Quit\n");

		printf_s("\nSelect option number:\n");
		scanf_s("%d", &s);
		switch (s) {
		case 1:system("cls"); createNewFile();
			break;
		case 2: readFile();
			break;
		case 3: change();
			break;
		case 4: /*task();*/
			break;
		case 5: printf_s("Do you really want to quit?y/n\n");
			do { key = _getch(); } while (key != 'n' && key != 'N' && key != 'y' && key != 'Y');
			printf_s("%c", key);
			if (key == 'y' || key == 'Y') { exit(0); };
			if (key == 'n' || key == 'N') { break; }
		default:
			printf("You are expected to enter a number from 1 to 5. Press any key to try one more time\n");
			_getch();
		}
	} while (key != 'y' && key != 'Y');
	system("pause");
}

void createNewFile()
{
	char key2 = NULL;
	char key3 = NULL;
	int n = 0;
	FILE* fp;
	subscriber* pInfo = new subscriber[limit];
	if ((fp = fopen("test.bin", "w+b")) == NULL) {
		printf("Cannot open file.\n"); exit(1);
	}
	//while (true)
	//{
	for (int i = 0; i < limit; i++) {
		/*	GOTO1:;*/
		system("cls");
		printf_s("Subscriber No.%d\n", n + 1);
		/*	while (getchar() != '\n');*/
		fflush(stdin);
		do {
			while (getchar() != '\n');

			printf_s("Enter the subscriber's surname:");
			gets_s(pInfo->surname);
		} while (strlen(pInfo->surname) == 0);
		do {
			do {
				while (getchar() != '\n');
				printf_s("Enter the subscriber's phone number:");
				gets_s(pInfo->phoneNumber);
				if (strlen(pInfo->phoneNumber) < 7) { printf_s("Phone number must be equal or more than 7 digits. Press any key to try one more time\n"); }
			} while (strlen(pInfo->phoneNumber) < 7);
			do {
				printf_s("Enter the year the telephone was installed:");
				scanf_s("%d", &pInfo->year);
				if (pInfo->year < 1950 || pInfo->year>2021) { printf_s("Enter the year from 1950 to 2021!\n"); }
			} while (pInfo->year < 1950 || pInfo->year>2021);
			fwrite(pInfo, sizeof(subscriber), limit, fp);
			printf_s("Does the subscriber have more phone numbers?[y/n]\n");
			do { key3 = _getch(); } while (key3 != 'n' && key3 != 'N' && key3 != 'y' && key3 != 'Y');
			printf_s("%c\n", key3);
			if (key3 == 'y' || key3 == 'Y') { memcpy(&pInfo->surname, &pInfo->surname, sizeof(limit)); };
		} while (key3 == 'y');
		if (key3 == 'n' || key3 == 'N')
		{
			n++;
			puts("Data added. Do you want to enter the data for one more subscriber?[y/n]");
			do { key2 = _getch(); } while (key2 != 'n' && key2 != 'N' && key2 != 'y' && key2 != 'Y');
			printf_s("%c\n", key2);
			if (key2 == 'n' || key2 == 'N') break;
		}
	}
	fclose(fp);
}


void readFile()
{
	FILE* fp;
	subscriber* pInfo = new subscriber[limit];
	if ((fp = fopen("test.bin", "rb")) == NULL) {
		printf("Cannot open file.\n"); exit(1);
	}
	while (fread(pInfo, sizeof(subscriber), limit, fp) != NULL) {

		printf("%20s | %4d | %15s\n", pInfo->surname, pInfo->year, pInfo->phoneNumber);
	}
	fclose(fp);
	_getch();


}
void task()
{}

void change() {
	int s1;
	char key1 = NULL;
	do {
		system("cls");
		printf_s("\tSUBMENU\n\
		\t1.Add a new record\n\
		\t2.Make changes\n\
		\t3.Delete a record\n\
		\t4.Return to the main menu\n");

		printf_s("\nSelect option number:\n");
		scanf_s("%d", &s1);
		switch (s1) {
		case 1: /*add();*/
			break;
		case 2:
			break;
		case 3: deletion();
			break;
		case 4: printf_s("Do you really want to return to the main menu?y/n\n");
			do { key1 = _getch(); } while (key1 != 'n' && key1 != 'N' && key1 != 'y' && key1 != 'Y');
			printf_s("%c", key1);
			if (key1 == 'y' || key1 == 'Y') {};
			if (key1 == 'n' || key1 == 'N') { break; }
		default:
			printf("You are expected to enter a number from 1 to 4\n");
		}
	} while (key1 != 'y' && key1 != 'Y');
}
void deletion()
{
	
		FILE* fp;
		subscriber* pInfo = new subscriber[limit];
		if ((fp = fopen("test.bin", "rb")) == NULL) {
			printf("Cannot open file.\n"); exit(1);
		}
		while (fread(pInfo, sizeof(subscriber), limit, fp) != NULL) {

			printf("%20s | %4d | %15s\n", pInfo->surname, pInfo->year, pInfo->phoneNumber);
		}

	int del = 0;
	printf_s("Enter the number of the entry you want to delete:");
	scanf_s("%d", &del);

	FILE* fp_temp;
	if ((fp_temp = fopen("test_t.bin", "wb")) == NULL) {
		printf("Cannot open file.\n"); exit(1);
	}
	int i = 0;
	fseek(fp, 0, SEEK_SET);
	while (fread(pInfo, sizeof(subscriber), limit, fp) != NULL) {
		if (i != del) {

			fwrite(pInfo, sizeof(subscriber), limit, fp_temp);
		}
		i++;
	}

	fclose(fp);
	fclose(fp_temp);
	remove("test.bin");
	rename("test_t.bin", "test.bin");
}
