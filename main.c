/*
 * thread
 *
 *  Created on: Apr 15, 2023
 *      Author: Sahithi Mangalapalli
 */

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
int num = 0;
int even = 0;
pthread_cond_t signalEven = PTHREAD_COND_INITIALIZER;
pthread_cond_t signalOdd = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock;
void printEven(){

    //lock
    pthread_mutex_lock(&lock);
    //releases lock while sleeping
    while(!even){
        printf("even is waiting \n");
        pthread_cond_wait(&signalOdd, &lock);
    }
    even =0;
    num = num+1;
    printf("P1 : %d\n", num);
    
    pthread_cond_signal(&signalEven);
    pthread_mutex_unlock(&lock);
}
void printOdd(){
    //lock
    pthread_mutex_lock(&lock);
    //releases lock while sleeping
    while(even){
        printf("odd is waiting \n");
        pthread_cond_wait(&signalEven, &lock);
    }
    even =1;
    num = num+1;
    printf("P2 : %d\n",num );
    
    pthread_cond_signal(&signalOdd);
    pthread_mutex_unlock(&lock);
}

int main(int argc, int* argv){

	pthread_t odd, even;
	printf("Welcome to the world of numbers\n");
	pthread_create(&odd,NULL,printEven,NULL);
	pthread_create(&even,NULL,printOdd, NULL);
	while(1){
	    printEven();
	    printOdd();
	}
	pthread_join(odd,NULL);
	pthread_join(even, NULL);
	printf("end");
}
