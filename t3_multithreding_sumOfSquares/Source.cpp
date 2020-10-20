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
	//get t from user
	std::cout << "\nHow many threads? ";
	int t = 0;
	std::cin >> t;
	if (t > n)
		t = n;

	//--------------create threads---------------
	unsigned long total = 0;
	std::vector<std::thread> threads;
	const int subdivisionSize = n / t; //each thread will compute at least subdivisioSize squares
	const int reminder = n % t;
	for (int i = 0, min=0, max=0; i < t; i++) {
		min = max + 1;
		//the first threads will compute one additional square
		//to account for the reminder
		if (i < reminder)
			max = min + subdivisionSize;
		else
			max = min + subdivisionSize-1;
		threads.push_back(std::thread(sumSquares, min, max, &total));
	}
	//wait for threads to finish
	for (std::thread& thr : threads)
		thr.join();
	//--------------------------------------------

	//print result
	std::cout << "The result is: " << total;
}