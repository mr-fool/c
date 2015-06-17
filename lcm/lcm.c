#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct targs{
	int *arr;
	ssize_t size;
	int *dest;
	pthread_mutex_t *write_lock;
	pthread_t *id;
	bool final;
};

int gcd(int x, int y){
	while (x != y){
		if (x < y) {
			y -= x;
		}//end if
		else {
			x = x - y;
		}//end else
  }
  return x;
}

int lcm(int x, int y){
	return (x/gcd(x,y))*y;
}

void *work_thread(void *arg){
	struct targs *targs = (struct targs*) arg;
	if (targs->size == 1){
		*(targs->dest) = targs->arr[0];
	}//end if
	else {
		int acc = lcm(targs->arr[0], targs->arr[1]);
		int i;
		for (i = 2; i < targs->size; ++i) {
			acc = lcm(acc, targs->arr[i]);
		}
		*(targs->dest) = acc;
	}//end else
	pthread_mutex_lock(targs->write_lock);
	int i;
	if (targs->final) {
		printf("Final ");
	}//end if
	printf("Thread %lu: (", *(targs->id));
	
	--targs->size;
	for (i = 0; i < targs->size; ++i) {
		printf("%i, ", targs->arr[i]);
    }//end for 
    printf("%i)", targs->arr[i]);
    printf(" : %s%i\n", !targs->final ? "LCM = " : "", *(targs->dest));
    pthread_mutex_unlock(targs->write_lock);
    return NULL;
}

int main(int argc, char *argv[]){
	if (argc != 3){
    printf("Usage: lcm_skeleton <filename>\n");
    return -1;
  }
	FILE *nums = fopen(argv[1], "r");
	int *args = malloc(sizeof(int)*10);
	ssize_t args_size = 10;
	int i = 0;
	while (fscanf(nums, "%d", args + i++) > 0){
		if (i >= args_size){
			args_size *= 2;
			args = realloc(args, sizeof(int)*args_size);
			}//end if
	}//end while
	args_size = --i;
	args = realloc(args, sizeof(int)*args_size);
	int nthreads;
	if (sscanf(argv[2], "%d", &nthreads) <= 0) {
		exit(2);
	}//end if
	pthread_t threads[nthreads];
	int perthread = args_size/nthreads;
	perthread += nthreads*perthread != args_size;
	int result[nthreads];
	
	struct targs *targs[nthreads];
	pthread_mutex_t write_lock;
	pthread_mutex_init(&write_lock, NULL);
	for (i = 0; i < nthreads; ++i) {
		targs[i] = malloc(sizeof(struct targs));
		*targs[i] = (struct targs){args + perthread*i,
		perthread,
		result + i,
		&write_lock,
		threads + i,
		false};
		if (i == (nthreads - 1)) {
			targs[i]->size = args_size - perthread*i;
		}//end if
		pthread_create(threads + i, NULL, work_thread, targs[i]);
	}//end for
	for (i = 0; i < nthreads; ++i) {
		pthread_join(threads[i], NULL);
		free(targs[i]);
	}//end for 
	free(args);
	int final;
	struct targs final_args = {
		result, 
		nthreads, 
		&final,
		&write_lock, 
		threads, 
		true};
	pthread_create(threads, NULL, work_thread, &final_args);
	pthread_join(threads[0], NULL);
	printf("Final Least Common Multiple: %i\n", final);
	return 0;
}
