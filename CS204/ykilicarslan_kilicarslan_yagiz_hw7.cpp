#include <iostream>
#include <thread>
#include <mutex>
#include <time.h>
#include <random>
#include <chrono>
#include "HW7DynIntQueue.h"
#include <ctime>  
#include <iomanip>
using namespace std;

// # of fillers and packers can be changed seemlessly using this global constant integers
const int FILLER_NUM = 2;
const int PACKER_NUM = 2;

// counters are referance variables for keeping the total count of boxes for two fillers and two packers
// they can also be global variables like this only need to delete the ref() part in thread initialization
//int counter1 = 0;
//int counter2 = 0;

// dynamicIntegerQueues are global since we want to access them by multiple threads
// also mutex's are used by multiple threads
HW7DynIntQueue q_fill;
HW7DynIntQueue q_pack;
mutex fillMutex;
mutex packMutex;
mutex coutMutex;

// for getting random integer bw min-max values
int random_range(const int & min, const int & max) {
	static mt19937 generator(time(0)); 
	uniform_int_distribution<int> distribution(min, max); 
	return distribution(generator); 
}

// for getting momentary time 
void getTime(){
	time_t tt = chrono::system_clock::to_time_t 
                (chrono::system_clock::now()); 
	tm *ptm = new tm; 
	localtime_s(ptm, &tt); 
	cout << put_time(ptm,"%X") << endl;
}


/* PRODUCER THREAD FUNCTION***************
starting with boxNum = 1, generate given total_number of boxes 
->when enqueueing new box to filling queue to filler to fill,
use mutex to prevent any confliction 
->use coutMutex to prevent any output confusion 
->use sleep to simulate 
*******************************************/
void produce(int total_box_count, int min, int max){
	int boxNum = 1;
	while(boxNum <= total_box_count){
		fillMutex.lock();
		q_fill.enqueue(boxNum);
		fillMutex.unlock();
			
		coutMutex.lock();		
		cout << "Producer has enqueued a new box " << boxNum << " to filling queue "
			<< "(filling queue size is " <<  q_fill.getCurrentSize() << "): "; getTime();
		coutMutex.unlock();

		this_thread::sleep_for(chrono::seconds(random_range(min, max)));

		boxNum++;
	}
}

/*FILLER THREAD FUNCTION******************
while fillingQueue is not empty dequeue the currentBox
and enqueue it to the packaging queue
-> use 2 mutex for filling queue and packaging queue 
-> referance variable counter1 keeps track of the # of boxes filled 
so that multiple workers using the same thread function won't create problems
-> even though filling queue is empty always unlock the fillingMutex in the else part
-> simulate filling work by sleep part
******************************************/
void fill(int total_box_count, int min, int max, int fillerNum, int & counter1){	
	int currentBox;
	while (counter1 < total_box_count){	
		fillMutex.lock();
		if (!q_fill.isEmpty()){
			q_fill.dequeue(currentBox);
			counter1++;
			fillMutex.unlock();
			
			coutMutex.lock();
			cout << "Filler " << fillerNum+1 << " started filling the box " << currentBox
				<< " (filling queue size is " << q_fill.getCurrentSize() << "): "; getTime();
			coutMutex.unlock();

			this_thread::sleep_for(chrono::seconds(random_range(min, max)));

			coutMutex.lock();
			cout << "Filler " << fillerNum+1  << " finished filling the box " << currentBox
				<< ": "; getTime();
			coutMutex.unlock();
			
			
			packMutex.lock();
			q_pack.enqueue(currentBox);
			packMutex.unlock();

			coutMutex.lock();			
			cout << "Filler " << fillerNum+1 << " put box " << currentBox 
				<< " into packaging queue (packaging queue size is " 
				<< q_pack.getCurrentSize() << "): " << ": "; getTime();
			coutMutex.unlock();

			this_thread::sleep_for(chrono::seconds(random_range(min, max)));
		}
		else{
			fillMutex.unlock();
		}
	}
}

/*PACKAGING THREAD FUNCTION**************
while packaging queue is not empty dequeue currentBox to package it
-> similar to filling thread function, use mutex for packageMutex to prevent confusion
-> referance variable counter2 keeps track of the # of boxes packaged 
so that multiple workers using the same thread function won't create problems
-> always unlock the mutex in the else part 
****************************************/
void pack(int total_box_count ,int min, int max, int packerNum, int & counter2){
	int currentBox;
	while (counter2 < total_box_count){
		packMutex.lock();	
		if(!q_pack.isEmpty()){	
			q_pack.dequeue(currentBox);
			counter2++;
			packMutex.unlock();

			coutMutex.lock();
			cout << "Packager " << packerNum+1 << " started packaging the box " << currentBox
				<< " (packaging queue size is " << q_pack.getCurrentSize() << "): "; getTime();
			coutMutex.unlock();

			this_thread::sleep_for(chrono::seconds(random_range(min, max)));

			coutMutex.lock();
			cout << "Packager " << packerNum+1 << " finished packaging the box " << currentBox
				<< ": "; getTime();
			coutMutex.unlock();
		}
		else{
			packMutex.unlock();
		}
	}
}




int main(){

// TIME RANGE INPUTS ----------------------
// Take entries for #ofItems, Min-Max waiting time for each worker
	int min_production, max_production, total_box_count;
	cout << "Please enter the total number of items: "; 
	cin >> total_box_count;
	cout << "Please enter the min-max waiting time range of producer: " << endl;
	cout << "Min: "; 
	cin >> min_production;
	cout << "Max: "; 
	cin >> max_production;

	int min_filling_time, max_filling_time;
	cout << "Please enter the min-max waiting time range of filler workers: " << endl;
	cout << "Min: "; 
	cin >> min_filling_time;
	cout << "Max: "; 
	cin >> max_filling_time;

	int min_packaging_time, max_packaging_time;
	cout << "Please enter the min-max waiting time range of packager workers: " << endl;
	cout << "Min: "; 
	cin >> min_packaging_time;
	cout << "Max: "; 
	cin >> max_packaging_time;
	

// SIMULATION START TIME -------------------
	cout << "Simulation starts ";
	getTime();


// INITIALIZATION OF THREADS ---------------
	int i; // for multiple workers
	// for keeping track of boxes when there are multiple workers doing the same job
	int counter1 = 0; 
	int counter2 = 0;

	thread producer(&produce, total_box_count, min_production, max_production);

// use ref() to keep the communication bw multiple threads using same thread function
	thread filler[FILLER_NUM];
	for (i = 0; i < FILLER_NUM; i++){
		filler[i] = thread(&fill, total_box_count, min_filling_time, max_filling_time, i, ref(counter1));
	}

	thread packer[PACKER_NUM];
	for (i = 0; i < PACKER_NUM; i++){
		packer[i] = thread(&pack, total_box_count, min_packaging_time, max_packaging_time,i,ref(counter2));
	}

// after threads are done, return to the main thread using .join()
	producer.join();
	for (i = 0; i < FILLER_NUM; i++){
		filler[i].join();
	}	
	for (i = 0; i < PACKER_NUM; i++){
		packer[i].join();
	}

	cout << "End of the simulation ends: "; getTime();
	return 0;
}