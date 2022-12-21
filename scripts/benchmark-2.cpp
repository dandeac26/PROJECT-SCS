// #ifndef _WIN64

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <iostream>
#include <chrono>


// #ifdef WIN32

// extern "C" void stress_cpu(int operations);
// extern "C" int cpu_brand(char brand[]);

// #else // else go ahead and use the Linux compiler and hope that it does not try to optimize this code

void stress_cpu(int operations)
{
#define M1 asm("addl $1, %eax\nxorl $1, %eax\n");
#define M2 M1 M1 M1 M1 M1
#define M3 M2 M2 M2 M2 M2
#define M4 M3 M3 M3 M3 M3
#define M5 M4 M4 M4 M4 M4
#define M6 M5 M5 M5 M5 M5

	asm("movl $1, %eax\n");
	for (int i = 0; i < operations; i++)
	{
		M6
		M6
	}
}

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

// #endif

// #ifdef WIN32

// #include <windows.h>
// #define pthread_t DWORD
// #define pthread_create(THREAD_ID_PTR, ATTR, ROUTINE, PARAMS) CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ROUTINE,(void*)(PARAMS),0,THREAD_ID_PTR)
// #define sleep(ms) Sleep(ms)

// #else // Linux

#include <pthread.h>
#include <unistd.h>

//#endif

const int MAX_THREADS = std::thread::hardware_concurrency();
const int OPERATIONS = 10000000;
int threads_active;

void* thread(void*)
{
	stress_cpu(OPERATIONS);
	threads_active--;
	return NULL;
}

#define SCORE(THREAD_COUNT) (unsigned int)(10000000ULL / (end_ms - start_ms) * THREAD_COUNT)

int main(int argc, char** argv)
{
// #ifdef WIN32
// 	char brand[48 + 16];
// 	brand[48] = 0;
// 	if (cpu_brand(brand)) // retrieve the processor brand -- this requires assembly code
// 	{
// 		std::cout << "CPU: " << brand << std::endl;
// 	}
// #else
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
// #endif
	unsigned long long start_ms, end_ms;

	if (MAX_THREADS > 1)
	{
		std::cout << "testing multi-core performance with " << MAX_THREADS << " threads" << std::endl;
		start_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); // start milliseconds
		threads_active = 0;
		for (int i = 1; i < MAX_THREADS; i++)
		{
			threads_active++;
			pthread_t tid;
			pthread_create(&tid, NULL, thread, NULL); // create one thread here
		}
		stress_cpu(OPERATIONS); // run the cpu stress on the main thread
		while (threads_active)
			sleep(1); // sleep one millisecond
		end_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); // end milliseconds
		std::cout << "multi-core score: " << SCORE(MAX_THREADS) << std::endl;
	}

	start_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "testing single-core performance" << std::endl;
	stress_cpu(OPERATIONS);
	end_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "single-core score: " << SCORE(1) << std::endl << std::endl << "Ctrl+C to end program" << std::endl;

	std::cin.get();

	return 0;
}

//#endif