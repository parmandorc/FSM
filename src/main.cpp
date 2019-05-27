#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>


static bool lIsRunning = true;

void HandleInterruptSignal(int pSignalNumber)
{
	lIsRunning = false;
}

int main(int argc, const char* argv[])
{
	std::signal(SIGINT, HandleInterruptSignal);
	
	while (lIsRunning)
	{
		std::cout << "Running..." << std::endl;
		
		static const std::chrono::milliseconds waitTimeBetweenFrames(1000);
		std::this_thread::sleep_for(waitTimeBetweenFrames);
	}
	
	return 0;
}

