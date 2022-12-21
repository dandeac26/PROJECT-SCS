
#include <iostream>
//#include "windows.h"
#include "stdlib.h"
#include "time.h"
//#include <windows.h>
#include <fstream>

using namespace std;

ofstream g("output.out", ios_base::app);

#define rdtsc __asm __emit 0fh __asm __emit 031h 
#define cpuid __asm __emit 0fh __asm __emit 0a2h
#define CLOCKS_PER_INSTR (double)total_cycles/100
#define MY_CLOCKS_PER_SEC (2.6 * 1000000000) /// 2.6 GHz 

int main(int argc, char* argv[])
{
	unsigned cycles_high1 = 0, cycles_low1 = 0, cpuid_time = 0;
	unsigned cycles_high2 = 0, cycles_low2 = 0;
	unsigned __int64 temp_cycles1 = 0, temp_cycles2 = 0;
	__int64 total_cycles = 0;
	
	__asm {
		pushad
		CPUID
		RDTSC
		mov cycles_high1, edx
		mov cycles_low1, eax
		popad
		pushad
		CPUID
		RDTSC
		popad
		pushad
		CPUID
		RDTSC
		mov cycles_high1, edx
		mov cycles_low1, eax
		popad
		pushad
		CPUID
		RDTSC
		popad
		pushad
		CPUID
		RDTSC
		mov cycles_high1, edx
		mov cycles_low1, eax
		popad
		pushad
		CPUID
		RDTSC
		sub eax, cycles_low1
		mov cpuid_time, eax
		popad
	}
	cycles_high1 = 0;
	cycles_low1 = 0;

	//Measure the code sequence 
	__asm {
		pushad
		CPUID
		RDTSC
		mov cycles_high1, edx
		mov cycles_low1, eax
		popad
	}

	//Section of code to be measured 

	
	
	unsigned int arr[109];
   // unsigned int arr[] = { 64, 34, 25, 12, 22, 11, 90, 22, 44 ,55 };
	unsigned int n = sizeof(arr) / sizeof(arr[0]);

	unsigned int i, j;
	for (i = 0; i < 100; i++) {
		if (i > 80)
			arr[i] = i - 29;
		else
			if (i > 20)
				arr[i] = i - 10;
			else arr[i] = i;
	}

	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
	
	
	/*
	unsigned int *arr;
	arr = (unsigned int *)malloc(sizeof(unsigned int)*103); 
    //unsigned int arr2[] = { 64, 34, 25, 12, 22, 11, 90, 33, 33 ,44 };
	//arr = arr2;
	unsigned int i, j;

	for (i = 0; i < 100; i++) {
		if (i > 80)
			arr[i] = i - 29;
		else
			if (i > 20)
				arr[i] = i - 10;
			else arr[i] = i;
	}
	unsigned int n = sizeof(arr) / sizeof(arr[0]);

	
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
		}*/
	
	/*
	
	// fdiv
	float a = 2.44;
	float b = 4.55;
	
	__asm {
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
		fld a
		fld b
		fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
			fld a
			fld b
			fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
				fld a
				fld b
				fdiv
	}
		
	
	*/
/*
	__asm {
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
		mov EAX, 22
		mov EBX, 3
		MUL EBX
			mov EAX, 22
			mov EBX, 3
			MUL EBX
			mov EAX, 22
			mov EBX, 3
			MUL EBX
			mov EAX, 22
			mov EBX, 3
			MUL EBX
			mov EAX, 22
			mov EBX, 3
			MUL EBX
			mov EAX, 22
			mov EBX, 3
			MUL EBX
			mov EAX, 22
			mov EBX, 3
			MUL EBX
			mov EAX, 22
			mov EBX, 3
			MUL EBX
			mov EAX, 22
			mov EBX, 3
			MUL EBX
			mov EAX, 22
			mov EBX, 3
			MUL EBX
			mov EAX, 22
			mov EBX, 3
			MUL EBX
	}*/
/*

	float x = 20.2, y = 3005.44;
	__asm {
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
		fld x
		fld y
		fsub
			fld x
			fld y
			fsub
			fld x
			fld y
			fsub
			fld x
			fld y
			fsub
			fld x
			fld y
			fsub
			fld x
			fld y
			fsub
			fld x
			fld y
			fsub
			fld x
			fld y
			fsub
			fld x
			fld y
			fsub
			fld x
			fld y
			fsub
			fld x
			fld y
			fsub
	}*/

/*
	int x = 4, y = 45;
	for(int i = 1; i<=100; i++)
		x += y;
	*/


	__asm {
		pushad
		CPUID
		RDTSC
		mov cycles_high2, edx
		mov cycles_low2, eax
		popad
	}

	temp_cycles1 = ((unsigned __int64)cycles_high1 << 32) | cycles_low1;
	temp_cycles2 = ((unsigned __int64)cycles_high2 << 32) | cycles_low2;


	total_cycles = temp_cycles2 - temp_cycles1 - cpuid_time;
	printf("tcycle1: %u, tcycle2: %u, cpuid_time: %u\n", temp_cycles1, temp_cycles2, cpuid_time);

	double total = total_cycles;
	g << "cpuid_time: " << cpuid_time << '\n';
	g << "total cycles: " << (int)total_cycles << '\n';
	//g << "total cycles/instr: " << CLOCKS_PER_INSTR << '\n';
	g << "\Time: " << (double)total_cycles / MY_CLOCKS_PER_SEC;
	g << "\n========== Static Sort (100 u_ints) ========== \n";

	
	printf("total cycles: %d\n", (int)total_cycles);
	printf("total cycles/instr: %lf\n", CLOCKS_PER_INSTR);// (double)total_cycles/20
	printf("\Time: %lfs\n",(double) total_cycles / MY_CLOCKS_PER_SEC);

	//printf("cyclLow: %d\ncycllow2%d\nCpuid_time is %d, with total cycles: %d", cycles_low1, cycles_low1, cpuid_time, total_cycles);
}