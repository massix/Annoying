//
//  main.cpp
//  Annoying
//
//  Created by Massimo Gengarelli on 20/2/12.
//

#include <iostream>
#include <vector>
#include <unistd.h>
#include <signal.h>
#include <cstdio>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string>
#include <cstring>

#include "move.h"
#include "rock.h"
#include "paper.h"
#include "scissor.h"
#include "lizard.h"
#include "spock.h"

typedef std::vector<move*> move_vector;

unsigned int hands = 0;
unsigned long int *plays = 0;


bool crossed = true;

#ifndef __APPLE__
#include <stdlib.h>
#include <time.h>
#define arc4random() rand()
#endif

void usage (const char *prgname);
void infinite_circle (unsigned int useconds);

void usage (const char *prgname) {
	printf ("Usage: %s --plays <num> [arguments]\n"
			"    --plays <num>    - number of plays\n"
			"    --usage|--help   - prints this and exit\n"
			"    --straight       - don't cross the arrays\n"
			"    --crossed        - cross the arrays [default]\n", prgname);
}

void infinite_circle (unsigned int useconds) {
	if (useconds <= 0)
		useconds = 500000;
	while (true) {
		usleep(useconds);
		printf("/\b");
		fflush(stdout);
		usleep(useconds);
		printf("-\b");
		fflush(stdout);
		usleep(useconds);
		printf("\\\b");
		fflush(stdout);
		usleep(useconds);
		printf("|\b");
		fflush(stdout);
		usleep(useconds);
		printf("/\b");
		fflush(stdout);
		usleep(useconds);
		printf("-\b");
		fflush(stdout);
		usleep(useconds);
		printf("\\\b");
		fflush(stdout);
		usleep(useconds);
		printf("|\b");
		fflush(stdout);
	}

}

int main (int argc, const char * argv[])
{	
#ifndef __APPLE__
	srand(time(0));
#endif

	move_vector player;
	move_vector cpu;
	
	// Parse arguments
	int c = 1;
	while (c < argc) {
		if (strcmp(argv[c], "--plays") == 0) {
			if (++c >= argc) {
				fprintf(stderr, "--plays requires an int");
				return -1;
			}
			else hands = atoi(argv[c]);
		}
		
		if (strcmp(argv[c], "--usage") == 0) {
			usage(argv[0]);
			return 0;
		}
		
		if (strcmp(argv[c], "--help") == 0) {
			usage(argv[0]);
			return 0;
		}
		
		if (strcmp(argv[c], "--straight") == 0) 
			crossed = false;
		
		
		if (strcmp(argv[c], "--crossed") == 0) 
			crossed = true;
		
		c++;
	}
	
	if (hands == 0) {
		usage(argv[0]);
		return -1;
	}
	
	// Set up shared memory
	int shmid = shmget(IPC_PRIVATE, sizeof(unsigned int), 0660 | IPC_CREAT);
	if (shmid == -1) {
		perror("shmget()");
		fflush(stderr);
		return -1;
	}
	
	plays = (unsigned long int *) shmat(shmid, 0, 0);
	if (plays == (void *)-1) {
		perror("shmat()");
		fflush (stderr);
		return -1;
	}
	

	
	std::cout << "Playing " << hands << (crossed? " crossed " : " straight ") << "hands." << std::endl;
	
	pid_t child = fork ();
	switch (child) {
		case 0:
			printf("Creating the hands |\b");
			fflush(stdout);
			infinite_circle(250000);
			break;
		default:
			for (unsigned int i = 0; i < hands; i++) {
				switch (arc4random() % 5) {
					case 0: player.push_back(new rock()); break;
					case 1: player.push_back(new scissor()); break;
					case 2: player.push_back(new paper()); break;
					case 3: player.push_back(new spock()); break;
					case 4: player.push_back(new lizard()); break;
				}
			}
			
			for (unsigned int i = 0; i < hands; i++) {
				switch (arc4random() % 5) {
					case 0: cpu.push_back(new rock()); break;
					case 1: cpu.push_back(new scissor()); break;
					case 2: cpu.push_back(new paper()); break;
					case 3: cpu.push_back(new spock()); break;
					case 4: cpu.push_back(new lizard()); break;
				}
			}
			
			kill(child, 9);
			std::cout << std::endl;
			break;
		case -1:
			return -1;
			break;
	}
	

	child = fork ();	
	switch (child) {
		case 0:
			printf("Calculating --> ");
			fflush(stdout);
			while (true) {
				long double thands = (crossed? (hands*hands) : hands);
				
				usleep(50000);
				printf("%05.2Lf%%\b\b\b\b\b\b", ((long double)*plays / thands) * 100.0);
				fflush(stdout);
			}
			break;
			
		default:
		{
			unsigned long long int draws = 0;
			unsigned long long int playerw = 0;
			unsigned long long int cpuw = 0;
			
			if (crossed) {
				for (move_vector::iterator ite = player.begin(); ite != player.end(); ++ite) {
					for (move_vector::iterator ite_cpu = cpu.begin(); ite_cpu != cpu.end(); ++ite_cpu) {
						if ((**ite_cpu) == (**ite)) 
							draws++;
						
						else if ((**ite_cpu) > (**ite)) 
							cpuw++;
						
						else 
							playerw++;
						
						(*plays)++;
					}
				}
			}
			else {
				for (unsigned long int i = 0; i < hands; i++) {
					if (*(player[i]) == *(cpu[i])) 
						draws++;
					
					else if (*(player[i]) > *(cpu[i]))
						cpuw++;
					
					else 
						playerw++;
					
					(*plays)++;
				}
			}
			
			kill (child, 9);
			std::cout << std::endl;
			std::cout << "\n\n---- RESULTS ----" << std::endl;
			std::cout << "Player won " << playerw << " hands." << std::endl;
			std::cout << "CPU    won " << cpuw << " hands." << std::endl;
			std::cout << "Draws      " << draws << " hands." << std::endl;
			std::cout << "Hands done " << playerw + cpuw + draws << " ." << std::endl;
	
			long double thands = (crossed? (hands*hands) : hands);
			printf("\n\n---- STATISTICS ----\n"
				   "Player won %0.2Lf%% games \n"
				   "CPU    won %0.2Lf%% games \n"
				   "A total of %0.2Lf%% games were a draw \n",
				   ((long double)playerw / thands) * 100.0,
				   ((long double)cpuw / thands) * 100.0,
				   ((long double)draws / thands) * 100.0);
			

			break;
		}
		case -1:
			return -1;
			break;
	}
	
	// Free the shared memory
	int e = shmdt(plays);
	if (e == -1)
		perror("shmdt()");
	
	e = shmctl(shmid, IPC_RMID, 0);
	if (e == -1)
		perror("shmctl()");
	
	// Free the arrays
	child = fork();
	switch (child) {
		case 0:
			printf("\n\nFreeing memory |\b");
			fflush(stdout);
			infinite_circle(250000);
			break;
			
		default:
			for (move_vector::iterator ite = player.begin(); ite != player.end(); ++ite)
				delete (*ite);
			
			for (move_vector::iterator ite = cpu.begin(); ite != cpu.end(); ++ite)
				delete (*ite);
			
			kill (child, 9);
			std::cout << std::endl;
			break;
	}
	return 0;
}
