#include <thread>
#include <vector>
#include <iostream>


void sumSquares(int min, int max, unsigned long *total) {
	for (int i = min; i <= max; i++)
		(*total) += i * i;
}

int main() {
	//get n from user
	std::cout << "Compute the sum of the first n squares.\nEnter n: ";
	int n=0;
	std::cin >> n;
	if (n < 0)
		n = 0;
	//get number of threads from user
	std::cout << "\nHow many threads? ";
	int numOfThreads = 0;
	std::cin >> numOfThreads;
	if (numOfThreads > n)
		numOfThreads = n;
	else if (numOfThreads < 1)
		numOfThreads = 1;

	//--------------create threads---------------
	unsigned long total = 0;
	std::vector<std::thread> threads;
	//the range [1 ,n] is divided into a number of subsets equal to numOfThreads
	const int subsetSize = n / numOfThreads;
	const int reminder = n % numOfThreads;
	for (int i = 0, min=0, max=0; i < numOfThreads; i++) {
		min = max + 1;
		//the first threads will compute one additional square
		//to account for the reminder
		if (i < reminder)
			max = min + subsetSize;
		else
			max = min + subsetSize-1;
		threads.push_back(std::thread(sumSquares, min, max, &total));
	}
	//wait for threads to finish
	for (std::thread& thr : threads)
		thr.join();
	//--------------------------------------------

	//print result
	std::cout << "The result is: " << total;
}