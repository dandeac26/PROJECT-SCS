#ifndef _WIN64

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <iostream>
#include <chrono>


#ifdef WIN32

 extern "C" void stress_cpu(int operations);


 #else // else go ahead and use the Linux compiler and hope that it does not try to optimize this code

void stress_cpu(int operations)
{
#define more asm("addl $1, %eax\nxorl $1, %eax\n");
#define Much_more more more more more more
#define MMuch_more Much_more Much_more Much_more Much_more Much_more
#define M4 MMuch_more MMuch_more MMuch_more MMuch_more MMuch_more
#define M5 M4 M4 M4 M4 M4
#define bunch_of_asm M5 M5 M5 M5 M5

	asm("movl $1, %eax\n");
	for (int i = 0; i < operations; i++)
	{
		bunch_of_asm
		bunch_of_asm
	}
}


#endif

#ifdef WIN32

#include <windows.h>
#define pthread_t DWORD
#define pthread_create(THREAD_ID_PTR, ATTR, ROUTINE, PARAMS) CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ROUTINE,(void*)(PARAMS),0,THREAD_ID_PTR)
#define sleep(ms) Sleep(ms)

#else // Linux

#include <pthread.h>
#include <unistd.h>

#endif

int MAX_THREADS = std::thread::hardware_concurrency();
int OPERATIONS = 1000000;
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
	if (argc > 2){
		OPERATIONS = atoi(argv[2]);
		MAX_THREADS = atoi(argv[1]);
	}
	unsigned long long start_ms, end_ms;

	if (MAX_THREADS > 1)
	{
		std::cout << "Testing multi-core performance with " << MAX_THREADS << " threads (higher == better)                     " ;//<< "\n";
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
		std::cout << "                        multi-core score: " << SCORE(MAX_THREADS);// << "\n";
	}

	start_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "                                             testing single-core performance                 " ;//<< "\n";
	stress_cpu(OPERATIONS);
	end_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << " single-core score: " << SCORE(1) ;//<< "\n";

	

	return 0;
}

#endif