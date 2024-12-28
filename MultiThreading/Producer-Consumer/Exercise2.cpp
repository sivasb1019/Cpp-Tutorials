/*

### **Following are some main applications of std::shared_mutex:**

	- When reading data is the primary operation and writing data is uncommon, shared mutexes offer effective parallelism.
	- Shared mutexes can be used in caching algorithms to enable simultaneous updating of the cache by one thread
	  while allowing several threads to read data that has been cached.
	- Database connection pooling allows for simultaneous reading and updating of connection information by several threads,
	  but not for simultaneous modification.

## **When to use?**
	- When you have a read-heavy workload (many readers, few writers).
	- When you need to protect a shared resource from data races.

### Use a shared mutex when you have a situation where:
	- There are many threads that need to read the shared resource concurrently.
	- There are fewer threads that need to write to the resource.
	- You want to optimize read access and ensure exclusive write access.

### **Conclusion**
	- std::shared_mutex is one of the useful mechanisms for access synchronization in multithreaded environments.
	- It works especially effectively in scenarios where the shared data is mostly read-only.
	- A shared mutex (std::shared_mutex in C++) is used when you need to manage access to a shared resource in a way that allows
	  multiple threads to read the resource concurrently but ensures exclusive access for a single thread when writing to the resource.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <ctime>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>


std::shared_mutex shrd_mtx;
std::mutex readerWriterMutex;
std::condition_variable_any cv;

int g_reader_count = 0;
int g_writer_content = 0;
bool g_writer_active = false;

const size_t g_bufferSize = 300;
char g_buffer[g_bufferSize];




//std::string logFile = "logFile.txt";

void logInfo(const std::string& a_logData) {
	std::fstream logFile("logFile.txt", std::ios::app);
	time_t timestamp = time(NULL);
	std::string l_logData = a_logData + " - " + std::string(ctime(&timestamp));
	logFile << l_logData;
	logFile.close();
}

std::string threadIdToString(const std::thread::id& id) {
	std::ostringstream oss;
	oss << id;
	return oss.str();
}

void producer(std::fstream& a_fileInput, std::fstream& a_fileOutput) {
	//std::cout << "Producer start writing... " << std::endl;
	logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer is waiting for lock - LINE NO - " + std::to_string(__LINE__));
	
	while (!a_fileInput.eof()) {
		std::unique_lock<std::shared_mutex> exclusive_lock(shrd_mtx);
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer acquired the lock and waiting - LINE NO - " + std::to_string(__LINE__));

		cv.wait(exclusive_lock, [] { return (g_reader_count == 0 || !g_writer_active) ? true : false; });
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer acquired the lock and started - LINE NO - " + std::to_string(__LINE__));

		g_writer_active = true;
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer set the ACTIVE WRITER TO TRUE and started writing - LINE NO - " + std::to_string(__LINE__));

		a_fileInput.read(g_buffer, g_bufferSize);
		a_fileOutput.write(g_buffer, a_fileInput.gcount());
		//std::cout << "Producer finished writing... " << std::endl;
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer finished writing and set the ACTIVE WRITER TO FALSE - LINE NO - " + std::to_string(__LINE__));

		g_writer_active = false;
		g_writer_content++;
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer released the lock - LINE NO - " + std::to_string(__LINE__));
		cv.notify_one();
		//std::this_thread::sleep_for(std::chrono::seconds(2));
	}

}

void consumer(std::fstream& a_fileInput) {
	logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer is waiting for lock - LINE NO - " + std::to_string(__LINE__));
	
	while(!a_fileInput.eof()) {
		std::shared_lock<std::shared_mutex> shrd_lock(shrd_mtx);
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer acquired the lock and waiting - LINE NO - " + std::to_string(__LINE__));

		cv.wait(shrd_lock, [] { return (!g_writer_active) ? true : false; });
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer acquired the lock and started - LINE NO - " + std::to_string(__LINE__));

		{
			std::lock_guard<std::mutex> readerCountlock(readerWriterMutex);
			g_reader_count++;
			logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer Increased the READER COUNT: " + std::to_string(g_reader_count) + " - LINE NO - " + std::to_string(__LINE__));
		}

		shrd_lock.unlock();
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer released the lock - LINE NO - " + std::to_string(__LINE__));

		cv.notify_all();
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer notifyied all waiting threads and started reading - " + std::to_string(__LINE__));

		a_fileInput.read(g_buffer, g_bufferSize);

		if (a_fileInput.gcount() > 0) {
			std::cout << g_buffer;
		}

		{
			std::lock_guard<std::mutex> readerCountlock(readerWriterMutex);
			g_reader_count--;
			logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer finished reading and notifyied all waiting threads - " + std::to_string(__LINE__));
		}

		//std::this_thread::sleep_for(std::chrono::seconds(1));

		cv.notify_all();
	}

}

//std::ifstream openInputFile(filePath) {
//	return fileIN;
//}

int main() {
	std::string l_srcPath = "../SHARED_MUTEX.md";
	std::string l_destPath = "./assets/sharedMutex.md";

	std::fstream l_fileIN(l_srcPath, std::ios::in);
	if (!l_fileIN) {
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Can't open file at location: " + l_srcPath + " LINE NO - " + std::to_string(__LINE__));
		std::cerr << "File path : " << l_srcPath << std::endl;
		std::perror("File open error");
		return 0;
	}

	std::cout << "File successfully opened.." << l_srcPath << std::endl;


	std::fstream l_fileOUT(l_destPath, std::ios::in | std::ios::out | std::ios::trunc);
	if (!l_fileOUT) {
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Can't open file at location: " + l_destPath + " LINE NO - " + std::to_string(__LINE__));
		std::cerr << "File path: " << l_destPath << std::endl;
		std::perror("File open error");
		return 0;
	}
	std::cout << "File successfully opened.." << l_destPath << std::endl;
	std::thread l_writer1(producer, std::ref(l_fileIN), std::ref(l_fileOUT));
	std::thread l_reader1(consumer, std::ref(l_fileOUT));
	//std::thread l_reader2(consumer, std::ref(l_fileIN));

	//l_writer1.join();
	logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer finished writing LINE NO - " + std::to_string(__LINE__));
	l_reader1.join();
	//l_reader2.join();

	l_fileIN.close();
	l_fileOUT.close();
	return 0;
}