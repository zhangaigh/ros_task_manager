

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "task_manager_lib/TaskClient.h"

#define DEBUG(c) printf("Executing "#c":");res=c;printf("%d\n",res);
#define DEBUGSTATUS(c) printf("Executing "#c);

int end = 0;
void sighdl(int n) {
	end ++;
}

using namespace task_manager_lib;
int main(int argc, char * argv[])
{
    ros::init(argc,argv,"client");
    ros::NodeHandle nh("~");
	int i,res = -1;
	TaskParameters tp;
    tp.setParameter("task_duration",50.);
    tp.setParameter("task_timeout",5.);
	TaskClient::StatusMap sm;

	TaskClient client("/tasks",nh);

	printf("Task list on the server:\n");
	client.printTaskList();

	printf("Task status on the server:\n");
	client.printStatusMap();

	printf("Running task Test\n");
	DEBUG(client.startTask("Test",true,0.5,tp));
	printf("Task status on the server:\n");
	client.printStatusMap();

	printf("Sleeping 3 sec\n");
	for (i=0;i<3;i++) {
		printf("Task status on the server:\n");
		client.printStatusMap();
		sleep(1);
	}


	printf("Back to idle, by timeout\n");
	for (i=0;i<5;i++) {
		printf("Task status on the server:\n");
		client.printStatusMap();
		sleep(1);
	}
	printf("Terminating\n");
}
