#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <thread>
//#include <ctime>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

std::mutex mtx;
//std::shared_mutex shrd_mtx;
std::condition_variable_any cv;
std::chrono::milliseconds mSeconds(1000);

//int g_readerRetryCount = 0;
//int g_writerReaderCount = 0;
bool g_writer_active = false;

const size_t g_bufferSize = 300;
std::streamsize g_bytesRead;
char g_buffer[g_bufferSize];

bool g_isBufferEmpty = true;
bool g_isReadComplete = false;




//std::string logFile = "logFile.txt";

void checkFileStatus(std::fstream& file) {
	if (!file.good()) {
		if (file.fail()) {
			//throw std::runtime_error("File operation failed due to a format issue.");
			throw;
		}
		else if (file.bad()) {
			throw std::runtime_error("File operation failed due to a severe error.");
		}
	}
}

void logInfo(const std::string& a_logData) {
	//return;
	std::fstream logFile("logFile.txt", std::ios::app);
	time_t timestamp = time(NULL);
	std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string l_logData = a_logData + " - " + std::to_string(current_time) + "\n";
	logFile << l_logData;
	logFile.close();
}

std::string threadIdToString(const std::thread::id& id) {
	std::ostringstream oss;
	oss << id;
	return oss.str();
}





void producer(std::fstream& a_fileOutput) {
	//std::cout << "Producer start writing... " << std::endl;
	logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer is waiting for lock - LINE NO - " + std::to_string(__LINE__));

	while (1) {
		std::unique_lock<std::mutex> writeLock(mtx);
		//logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer acquired the lock and waiting - LINE NO - " + std::to_string(__LINE__));

		cv.wait(writeLock, [] { return !g_isBufferEmpty; });
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer acquired the lock and started - LINE NO - " + std::to_string(__LINE__));

		//g_writer_active = true;
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer set the ACTIVE WRITER TO TRUE and started writing - LINE NO - " + std::to_string(__LINE__));

		a_fileOutput.write(g_buffer, g_bytesRead);
		try {
			checkFileStatus(a_fileOutput);
			logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer finished writing the current buffer - LINE NO - " + std::to_string(__LINE__));
		}
		catch (const std::exception e) {
			logInfo(threadIdToString(std::this_thread::get_id()) + e.what() + " - LINE NO - " + std::to_string(__LINE__));
			std::cerr << e.what();
		}
		std::cout << "Producer: " << g_buffer << std::endl;
		//g_writer_active = false;
		memset(g_buffer, 0, g_bytesRead);
		g_isBufferEmpty = true;
		std::cout << "Producer: " << g_bytesRead << std::endl;

		g_bytesRead = 0;
		std::this_thread::sleep_for(mSeconds * 0.1);
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer released the lock - LINE NO - " + std::to_string(__LINE__));
		if (g_isReadComplete) {
			a_fileOutput.close();
			break;
		}
		cv.notify_one();
		//std::this_thread::sleep_for(std::chrono::seconds(2));
	}

	logInfo(threadIdToString(std::this_thread::get_id()) + " - Producer finished writing - LINE NO - " + std::to_string(__LINE__));
}

void consumer(std::fstream& a_fileInput) {
	logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer is waiting for lock - LINE NO - " + std::to_string(__LINE__));
	int g_readerRetryCount = 0;

	while (g_readerRetryCount < 5) {
		std::unique_lock<std::mutex> readLock(mtx);
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer acquired the lock and waiting - LINE NO - " + std::to_string(__LINE__));

		//cv.wait(readLock, [] { return (!g_writer_active && g_isBufferEmpty) ? true : false; });
		cv.wait(readLock, [] { return (g_isBufferEmpty) ? true : false; });
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer acquired the lock and started - LINE NO - " + std::to_string(__LINE__));

		if (!a_fileInput.eof()) {
			a_fileInput.read(g_buffer, g_bufferSize);
			g_bytesRead = a_fileInput.gcount();
		}
		try {
			//checkFileStatus(a_fileInput);
			logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer filled the buffer after reading - LINE NO - " + std::to_string(__LINE__));
		}

		catch (const std::exception e) {
			logInfo(threadIdToString(std::this_thread::get_id()) + e.what() + " - LINE NO - " + std::to_string(__LINE__));
			std::cerr << e.what();
		}


		std::cout << "Consumer: " << g_bytesRead << std::endl;

		if (g_bytesRead > 0) {
			g_isBufferEmpty = false;
			//std::cout << g_buffer;
			//std::this_thread::sleep_for(mSeconds);
			logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer set the BUFFER VALUE to FALSE - LINE NO - " + std::to_string(__LINE__));
		}
		else {
			std::this_thread::sleep_for(mSeconds * 5);
			g_readerRetryCount++;
		}

		//std::cout << std::this_thread::get_id() << " finished reading..." << std::endl;
			//std::this_thread::sleep_for(std::chrono::seconds(1));

		cv.notify_one();
	}
	logInfo(threadIdToString(std::this_thread::get_id()) + " - Consumer finished reading... - LINE NO - " + std::to_string(__LINE__));
	g_isReadComplete = true;
}

//std::ifstream openInputFile(filePath) {
//	return fileIN;
//}

int main() {
	std::string l_srcPath = "../../SHARED_MUTEX.md";
	std::string l_destPath = "../../sharedMutex.md";

	std::fstream l_fileIN(l_srcPath, std::ios::in);
	if (!l_fileIN) {
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Can't open file at location: " + l_srcPath + " LINE NO - " + std::to_string(__LINE__));
		std::cerr << "File path : " << l_srcPath << std::endl;
		std::perror("File open error");
		return 0;
	}

	std::cout << "File successfully opened.." << l_srcPath << std::endl;
	logInfo(threadIdToString(std::this_thread::get_id()) + " - File opened at location: " + l_srcPath + " LINE NO - " + std::to_string(__LINE__));


	std::fstream l_fileOUT(l_destPath, std::ios::in | std::ios::out | std::ios::trunc);
	if (!l_fileOUT) {
		logInfo(threadIdToString(std::this_thread::get_id()) + " - Can't open file at location: " + l_destPath + " LINE NO - " + std::to_string(__LINE__));
		std::cerr << "File path: " << l_destPath << std::endl;
		std::perror("File open error");
		return 0;
	}
	std::cout << "File successfully opened.." << l_destPath << std::endl;
	logInfo(threadIdToString(std::this_thread::get_id()) + " - File opened at location: " + l_destPath + " LINE NO - " + std::to_string(__LINE__));

	std::thread l_writer1(producer, std::ref(l_fileOUT));
	std::thread l_reader1(consumer, std::ref(l_fileIN));
	//std::thread l_reader2(consumer, std::ref(l_fileIN));

	l_reader1.join();
	l_fileIN.close();
	//l_reader2.join();
	l_writer1.join();

	l_fileOUT.close();
	return 0;
}