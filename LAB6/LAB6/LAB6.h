#pragma once
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#pragma warning(disable: 4996)

#ifndef MYHEADER_H
#define MYHEADER_H




char* ANSIUpperCase(char* s, char* S);

//----------первая часть: создание двоичного из текстового
void CreateBinaryFile(int argc, char* argv[]);

//-------------- вторая часть: поиск в двоичном файле ----
void FindIVAN(int argc, char* argv[]);

//-------третья часть: корректировка в двоичном файле ----
void CorrectFile(int argc, char* argv[]);



#endif // MYHEADER_H
