# philosophers

- threads (of the same process) run in a shared memory space
	... the execution of the smallest sequence of programmed instructions ...
	... The thread has a program counter that keeps track of which instruc­tion to execute next. It has registers ...
	... threads are the entities scheduled for execution on the CPU ...
- processes run in separate memory spaces
	... Program in execution ...
	... A process has an address space containing program text and data, as well as other resources ...
	... Processes are used to group resources together ...

---

int gettimeofday(struct timeval *tv, struct timezone *tz);

struct timeval {
	time_t      tv_sec;     /* seconds */
	suseconds_t tv_usec;    /* microseconds */
};

time_t 		> long
suseconds_t > long
---
int usleep(useconds_t usec);
	#include <unistd.h>

	usleep - suspend execution for microsecond intervals

	1 ms = 10^3 us

	return: 0 | -1 + errno
	parameter:
		useconds_t > unsigned int
---

# pthread family 
	#include <pthread.h>
	Compile and link with -pthread.

int pthread_create(	pthread_t *thread,
					const pthread_attr_t *attr,
                    void *(*start_routine) (void *),
					void *arg);

	create a new thread

	notes:
		A  thread  may either be joinable or detached
		joignable : joinable, then another thread can call pthread_join(3) to wait for the thread to terminate and fetch its exit status
		When a detached thread terminates, its resources are automatically released back to the system: it is not possible to join with the thread in order to obtain its exit status
		By default, a new thread is created in a joinable state, unless attr was set to create the thread in a detached state (using pthread_attr_set‐detachstate(3)

	return:
		0 | error number
	parameters:
		If attr is NULL, then the thread is created with default attributes

---

int pthread_detach(pthread_t thread);

	The pthread_detach() function marks the thread identified by thread as detached.  When a detached thread terminates, its resources are automatically released back to the system without the need for another thread to join with the terminated thread
	pthread_detach(pthread_self());

	return:
		0 | error number

---

int pthread_join(pthread_t thread, void **retval);

	function waits for the thread specified by thread to terminate. 
	If that thread has already terminated, then pthread_join() returns immediately.
	The thread specified by thread must be joinable.

	return:
		0 | error number
	parameter:
		if retval is not NULL, then pthread_join() copies the exit status of the target thread

---

int pthread_mutex_init(	pthread_mutex_t *restrict mutex,
           				const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	init:
	If attr is NULL, the default mutex attributes are used

	return:
		0 | error number

---

# semaphores

`#include <semaphore.h>`

```
int sem_open(char *SEM_NAME, flags O_CREAT, access rights 0777, int value);
int sem_post(sem_t *sem); // increment
int sem_wait(sem_t *sem); // decrement, block if zero
int sem_unlink(char *SEM_NAME);
int sem_close(sem_t *sem);
```

----

# process

```
kill
exit
```
```
#include <unistd.h>
pid_t fork(void);
```
if fail : -1
0 = parent
< 0 new child process
```
#include <sys/types.h>
#include <sys/wait.h>
pid_t waitpid(pid_t pid, int *wstatus, int options);
```
pid  	< -1 	: any child process with gr ID = pid
		-1		: any child process
		0		: meaning wait for any child process whose process group ID is equal to that of the calling process
		> 0		: wait forthe this child process

options		WTERMSIG: returns the number of the signal that caused the child process to terminate
			WSTOPSIG: returns the number of the signal which caused the child to stop.
			...
