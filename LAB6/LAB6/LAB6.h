#pragma once
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#pragma warning(disable: 4996)

#ifndef MYHEADER_H
#define MYHEADER_H




char* ANSIUpperCase(char* s, char* S);

//----------������ �����: �������� ��������� �� ����������
void CreateBinaryFile(int argc, char* argv[]);

//-------------- ������ �����: ����� � �������� ����� ----
void FindIVAN(int argc, char* argv[]);

//-------������ �����: ������������� � �������� ����� ----
void CorrectFile(int argc, char* argv[]);



#endif // MYHEADER_H
