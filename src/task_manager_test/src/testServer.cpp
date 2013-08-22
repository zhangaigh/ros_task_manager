#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "task_manager_lib/TaskScheduler.h"
#include "task_manager_lib/DynamicTask.h"
#include "task_manager_test/TaskIdle.h"
#include "task_manager_lib/TaskWaitDefault.h"

int end = 0;

void sighdl(int n) {
	end ++;
}


using namespace task_manager_test;

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"tasks");
    ros::NodeHandle nh("~");
    TaskScheduler::debug = 1;

    boost::shared_ptr<TaskEnvironment> env(new TaskEnvironment());
	printf("\n*******************\n\nTesting task server functions\n");

	printf("Creating tasks\n");
    boost::shared_ptr<TaskDefinition> idle(new TaskIdle(env));
    boost::shared_ptr<TaskDefinition> wait(new TaskWaitDefault(env));
	printf("Creating task scheduler\n");
	TaskScheduler ts(nh, idle, 0.5);
    ts.addTask(wait);
	printf("Scanning tasks directory\n");
	ts.loadAllTasks("./lib",env);
	ts.printTaskDirectory();
	printf("Configuring tasks\n");
	ts.configureTasks();
	// don't delete tasks, because the ts took responsibility for them
	printf("Launching idle task\n");
    
	ts.startScheduler();

    ros::spin();

	return 0;
}