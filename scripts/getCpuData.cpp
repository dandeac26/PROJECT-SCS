#ifndef _WIN64

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <iostream>
#include <chrono>


#ifdef WIN32

extern "C" int cpu_brand(char brand[]);

#else // else go ahead and use the Linux compiler and hope that it does not try to optimize this code



long long cpu_brand0()
{
	asm(
		"movl $0x80000002, %eax\n"
		"cpuid\n"
		"xchg %rbx, %rax\n"
		"shl $32, %rax\n"
		"shl $32, %rbx\n"
		"shr $32, %rbx\n"
		"add %rbx, %rax\n"
	);
}

long long cpu_brand1()
{
	asm(
		"movl $0x80000002, %eax\n"
		"cpuid\n"
		"mov %rdx, %rax\n"
		"shl $32, %rax\n"
		"shl $32, %rcx\n"
		"shr $32, %rcx\n"
		"add %rcx, %rax\n"
	);
}

long long cpu_brand2()
{
	asm(
		"movl $0x80000003, %eax\n"
		"cpuid\n"
		"xchg %rbx, %rax\n"
		"shl $32, %rax\n"
		"shl $32, %rbx\n"
		"shr $32, %rbx\n"
		"add %rbx, %rax\n"
	);
}

long long cpu_brand3()
{
	asm(
		"movl $0x80000003, %eax\n"
		"cpuid\n"
		"mov %rdx, %rax\n"
		"shl $32, %rax\n"
		"shl $32, %rcx\n"
		"shr $32, %rcx\n"
		"add %rcx, %rax\n"
	);
}

long long cpu_brand4()
{
	asm(
		"movl $0x80000004, %eax\n"
		"cpuid\n"
		"xchg %rbx, %rax\n"
		"shl $32, %rax\n"
		"shl $32, %rbx\n"
		"shr $32, %rbx\n"
		"add %rbx, %rax\n"
	);
}

long long cpu_brand5()
{
	asm(
		"movl $0x80000004, %eax\n"
		"cpuid\n"
		"mov %rdx, %rax\n"
		"shl $32, %rax\n"
		"shl $32, %rcx\n"
		"shr $32, %rcx\n"
		"add %rcx, %rax\n"
	);
}

#endif

#ifdef WIN32

#include <windows.h>

#else // Linux

#include <pthread.h>
#include <unistd.h>

#endif

int main(int argc, char** argv)
{
#ifdef WIN32
	char brand[48 + 16];
	brand[48] = 0;
	if (cpu_brand(brand)) // retrieve the processor brand -- this requires assembly code
	{
		std::cout << "CPU: " << brand << std::endl;
	}
#else
	// retrieve the processor brand -- this requires assembly code
	union
	{
		char brand[48 + 16];
		long long x[6];
	};
	brand[48] = 0;
	x[0] = cpu_brand0();
	x[1] = cpu_brand1();
	x[2] = cpu_brand2();
	x[3] = cpu_brand3();
	x[4] = cpu_brand4();
	x[5] = cpu_brand5();
	std::cout << "CPU: " << brand << std::endl;
#endif
    return 0;
}
