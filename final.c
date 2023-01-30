
//CPU Manager
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<sys/time.h>
#include<sys/resource.h>

int processes(){//Processes (Option 2)
	int option;
	system("clear");
	printf("Welcome to process management section\nPlease select from the following\n");
	printf("\t\t1: To kill a process\n\t\t2: To change priority of a process \n\t\t3: To pause a process \n\t\t4: To continue a process\n_\b");
	scanf("%d",&option);
	return option;

}
int main(){
	// Variables Declaration
	char *order[100];
	int choice;
	int prio;
	int caseOption;
	int prevPrio;
	int defaultOption;
	pid_t pid;
    	char op;
	// Welcome Screen

	system("clear");
	HELLO:
	printf("Hello! Welcome to our program. This program will assist you with simple commands \nto be written on Linux terminal. ");
	printf("\nPlease enter your option:\n");
        printf("Press: \n \t 1:To see the current status of the CPU(You'll need to press q to get out)");
        printf("\n \t 2:To manage currently running processes. \n");
	printf("\t 3:To show currently running zombie processes. \n--\b\b");

	scanf("%d",&choice);
	switch(choice){
	// Option 1
	case 1:
	//printf("Hint: Press q to quit");
	system("glances");
	scanf("%c",&op);
	if(op=='q'){
	goto HELLO;
	}



	break;
	//Option 2
	case 2:
	processes();

	if(processes()==1){
	system("clear");
	system("ps -eo cmd,pid,%cpu,%mem --sort=+%cpu");
	printf("\nEnter the process id from the PID column in the above list\n");
	scanf("%d",&pid);
	kill(pid,SIGKILL);
	}
	else if(processes()==2){
	system("clear");
	system("ps -eo cmd,pid,%cpu,%mem,priority --sort=+%cpu");
	printf("\nEnter the process id from the PID column in the above list\n------\b\b\b\b\b\b");
	scanf("%d",&pid);

	prevPrio=getpriority(PRIO_PROCESS,pid);
	printf("Previous priority: %d\n", prevPrio);
	printf("Now enter the new priority you want for the process\n(\t\t1:High \t\t2:Very High \n\t\t3:Normal \n\t\t4:Low \t\t5:Very low \n)\n--\b\b");
	scanf("%d",&prio);
	if(prio==1){
	sprintf(order, "renice %d %d", -14, pid);
	system(order);
	}
	else if(prio==2){
	sprintf(order, "renice %d %d", -18, pid);
	system(order);}
	else if(prio==3){
	sprintf(order, "renice %d %d", -1, pid);
	system(order);}
	else if(prio==4){
	sprintf(order, "renice %d %d", 13, pid);
	system(order);}
	else if(prio==5){
	sprintf(order, "renice %d %d", 19, pid);
	system(order);}
	else
	printf("Invalid option.");
	//goto HELLO;
	}

	else if(processes()==3){
	system("clear");
	system("ps -eo cmd,pid,%cpu,%mem,priority --sort=+%cpu");
	printf("\nEnter the process id from the PID column in the above list\n------\b\b\b\b\b\b");
	scanf("%d",&pid);
	sprintf(order, "kill -STOP %d", pid);
	system(order);
	//signal(pid,SIGSTOP);
		}
	else if(processes()==4){
	system("clear");
	system("ps -eo cmd,pid,%cpu,%mem,priority --sort=+%cpu");
	printf("\nEnter the process id from the PID column in the above list\n------\b\b\b\b\b\b");
	scanf("%d",&pid);
	sprintf(order, "kill -CONT %d", pid);
	system(order);
	//signal(pid,SIGCONT);
		}
	break;
	case 3:

	system("ps axo stat,ppid,pid,comm | grep -w defunct");
	printf("Do you want to kill the zombie processes(s)? (Y/n)");
	scanf("%s",&op);

	if(op=='Y' || op=='y'){
	printf("Enter the process ID of the zombie process");
	scanf("%d", &pid);
	kill(pid,SIGKILL);
	system("ps axo stat,ppid,pid,comm | grep -w defunct");
	goto HELLO;
	}
	else if(op=='N' || op=='n'){
	goto HELLO;
	}
	break;
	//Default action
	default:
	printf("Invalid choice, going to home...");
	goto HELLO;

}

}
