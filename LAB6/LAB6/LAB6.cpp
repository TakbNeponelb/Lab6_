#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "LAB6.h"
#include <locale.h>
#pragma warning(disable: 4996)
//------------------------------------------------------------

/*4. �������� ������ : � ���������� ������� ������� : ����� ������, ����� �����������, ����� ����������,
����� �����������, ����� � ����, ���� ������.������� ������ : ������, ��������� �� ������ � ����� - ���������,
����� ����������� ������� � 7.00 �� 9.00.��������� : ����� ����������� : ������ 0 - 59, ���� 0 - 23. �������� �������
����������� � ���������� ����� ������� �� ���������� ����.*/


struct STrain {
	int number;
	struct {
		int HourDepart, MinuteDepart;
	} Time;
	struct {
		char CityArrive[30], CityDepart[30];
	}City;
	int cost;
	char travel_time;
};
// ---------�������� ����� ������, �� � ���������
//---------------� ������� �������� � Win1251
char* ANSIUpperCase(char* s, char* S) {
	S = strcpy(S, s);
	char* ch = S;
	while (*ch) {
		if (*ch >= 'a' && *ch <= 'z' || *ch >= '�' && *ch <= '�') *ch = *ch - 32;
		if (*ch == '�') *ch = '�';
		ch++;
	}
	return S;
}
//----------������ �����: �������� ��������� �� ����������
void CreateBinaryFile(int argc, char* argv[]) {
	if (argc < 3) {
		printf("���� ����������\nPress any key");
		_getch();
		return;
	}
	FILE* ft = fopen(argv[2], "rt");
	if (ft == NULL) {
		printf("Error: �� ������� ������� ���� � ��������� ������� %s\n", argv[2]);
		printf("Press any key "); _getch();
		return;
	}
	FILE* fb = fopen(argv[1], "wb");
	if (fb == NULL) {
		fclose(ft);
		printf("Error: �� ������� ������� �������� ���� %s\n", argv[1]);
		printf("Press any key"); _getch();
		return;
	}
	STrain Train{};
	int kol = 0, nw = 1;
	char s[3],st[3];

	while (nw) {

		fscanf(ft, "%10s", &Train.number); 

		if (/*strcmp(Train.number, "**") == 0 ||*/ feof(ft)) break;

		char Cities[30];
		char* n;  

		fgets(Cities, 30, ft); 
		fflush(ft); 
		n = strchr(Cities, '\n'); if (n) Cities[n - Cities] = '\0';    
		Train.City.CityDepart[30] = Cities[30];

		fgets(&Cities[30], 30, ft); // stdin � ����������� ��������� ���� (����������), ����� ������ ���
		fflush(ft);  // ���� ������ ���� �������, ������� ������� �� ������, � ���� ������:
		n = strchr(Cities, '\n'); if (n) Cities[n - Cities] = '\0';    // �����������

		Train.City.CityArrive[30] = Cities[30];
		fgets(&Cities[30], 30, ft); // stdin � ����������� ��������� ���� (����������), ����� ������ ���
		fflush(ft);  // ���� ������ ���� �������, ������� ������� �� ������, � ���� ������:
		n = strchr(Cities, '\n'); if (n) Cities[n - Cities] = '\0';    // �����������

		fscanf(ft, "%2s:%2s", &s, &st);
		Train.Time.HourDepart = atoi(s); Train.Time.MinuteDepart = atoi(st);
		
		fscanf(ft, "%5s", Train.travel_time);
		Train.cost = atoi(s);
		nw = fwrite(&Train, sizeof(Train), 1, fb);
		kol++;


	}
	if (nw != 1) printf("Error: ������ ��� ������");
	fclose(ft);
	fclose(fb);
	printf("������ �������� ���� �� %d ������� �� %d ����\n", kol, sizeof(Train));
	printf("Press any key to continue");
	_getch();
	return;
}
//-------------- ������ �����: ����� � �������� ����� ----
void FindIVAN(int argc, char* argv[]) {
	if (argc < 2) {
		printf("���� ����������\nPress any key");
		_getch();
		return;
	}
	FILE* fb = fopen(argv[1], "rb");
	if (fb == NULL) {
		printf("Error: �� ������� ������� �������� \
���� %s\n", argv[1]);
		printf("Press ENTER");
		_getch();
		return;
	}
	STrain Train;
	char SUp[60];
	int kol = 0, nr = 1;
	while (nr) {
		nr = fread(&Train, sizeof(Train), 1, fb);
		if (nr > 0) {
			if ((((Train.Time.HourDepart > 7) && (Train.Time.MinuteDepart > 0)) || ((Train.Time.HourDepart < 9) && (Train.Time.MinuteDepart < 59))) &&
				((strcmp(ANSIUpperCase(Train.City.CityDepart, SUp), "������") == 0) && (strcmp(ANSIUpperCase(Train.City.CityArrive, SUp), "�����-���������") == 0)) )
			{
				printf("������ %10s\t %30s\t %30s\t %2s:%2s\n", Train.number, Train.City.CityDepart, Train.City.CityArrive, Train.Time.HourDepart, Train.Time.MinuteDepart);
					kol++;
			}
		}
			
	}
	if (kol == 0)
		printf("������, ��������������� �������,�� �������\n");
	else
		printf("����� �������: %d\n", kol);
	fclose(fb);
	printf("Press any key to continue");
	_getch();
	return;
}
//-------������ �����: ������������� � �������� ����� ----
void CorrectFile(int argc, char* argv[]) {
	if (argc < 2) {
		printf("���� ����������\nPress any key");
		_getch();
		return;
	}
	FILE* fb = fopen(argv[1], "rb+");
	if (fb == NULL) {
		printf("Error: �� ������� ������� �������� ���� %s\n",
			argv[1]);
		printf("Press ENTER");
		_getch();
		return;
	}
	STrain Train;
	int kol = 0, nr = 1, nw = 1, flag;
	nr = fread(&Train, sizeof(Train), 1, fb);
	while (nr == 1 && nw == 1) {
		printf("������� ������:\n");
		printf("%10s\t%30s\t%30s\t%2d:%2d\t%5s\t%10s\n", Train.number, Train.City.CityDepart, Train.City.CityArrive, 
			Train.Time.HourDepart, Train.Time.MinuteDepart,Train.travel_time, Train.cost);
		flag = 0;
		if ((Train.Time.HourDepart < 0) && (Train.Time.HourDepart > 23)) { Train.Time.HourDepart = 0; flag = 1; }
		if ((Train.Time.MinuteDepart < 0) && (Train.Time.MinuteDepart > 59)) { Train.Time.MinuteDepart = 0; flag = 1; }
		if (flag) {
			kol++;
			fseek(fb, 0 - sizeof(Train), SEEK_CUR);
			nw = fwrite(&Train, sizeof(Train), 1, fb);
			fseek(fb, 0, SEEK_CUR);
			printf("������� �������������:\n");
			printf("%10s%30s\t%30s\t%2d:%2d\t%5s\t%10s\n", Train.number, Train.City.CityDepart, Train.City.CityArrive,
				Train.Time.HourDepart, Train.Time.MinuteDepart,  Train.travel_time,Train.cost);
		}
		nr = fread(&Train, sizeof(Train), 1, fb);
	}
	if (kol == 0)
		printf("�� ����� �������������\n");
	else
		printf("����� �������������: %d\n", kol);
	fclose(fb);
	printf("Press any key to continue");
	_getch();
	return;
}