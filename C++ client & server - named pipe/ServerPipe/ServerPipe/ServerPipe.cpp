//// SERVER PROGRAM /////

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <time.h>
#include <string>
using namespace std;

void sendData(HANDLE pipe, BOOL result, const char data[128]){
		
	wcout << "Sending data to pipe..." << endl;

	// This call blocks until a client process reads all the data
	//const wchar_t *data = L"*** Hello Pipe World ***";	//original
	
	DWORD numBytesWritten = 0;
	result = WriteFile(
		pipe, // handle to our outbound pipe
		data, // data to send
		128 * sizeof(char), // length of data to send (bytes)
		&numBytesWritten, // will store actual amount of data sent
		NULL // not using overlapped IO
	);
	

	if (result) {
		wcout << "Number of bytes sent: " << numBytesWritten << endl;
	} else {
		wcout << "Failed to send data." << endl;
		// look up error code here using GetLastError()
	}
	//Sleep(2000);	
}

int main(int argc, const char **argv)
{
	wcout << "Creating an instance of a named pipe..." << endl;

	// Create a pipe to send data
	/*HANDLE pipe = CreateNamedPipe(
		L"\\\\.\\pipe\\my_pipe", // name of the pipe
		PIPE_ACCESS_OUTBOUND, // 1-way pipe -- send only
		PIPE_TYPE_BYTE, // send data as a byte stream
		1, // only allow 1 instance of this pipe
		0, // no outbound buffer
		0, // no inbound buffer
		0, // use default wait time
		NULL // use default security attributes
	);*/
	HANDLE pipe = CreateNamedPipe(L"\\\\.\\pipe\\my_pipe", PIPE_ACCESS_DUPLEX, \
		PIPE_WAIT | PIPE_TYPE_MESSAGE, PIPE_UNLIMITED_INSTANCES, \
		1024, 1024, 120 * 1000, NULL);

	if (pipe == NULL || pipe == INVALID_HANDLE_VALUE) {
		wcout << "Failed to create outbound pipe instance.";
		// look up error code here using GetLastError()
		system("pause");
		return 1;
	}

	wcout << "Waiting for a client to connect to the pipe..." << endl;

	// This call blocks until a client process connects to the pipe
	BOOL result = ConnectNamedPipe(pipe, NULL);
	if (!result) {
		wcout << "Failed to make connection on named pipe." << endl;
		// look up error code here using GetLastError()
		CloseHandle(pipe); // close the pipe
		system("pause");
		//return 1;
	}
	
	time_t my_time = time(NULL);
	printf("%s", ctime(&my_time));
	wcout << "Server: Hello" << endl;
	sendData(pipe,result, "Hello\n");
	Sleep(5000);
	my_time = time(NULL);

	// ctime() used to give the present time 
	printf("%s", ctime(&my_time));
	sendData(pipe, result, "Run The FPD Measurement Software\n");
	wcout << "Server: Run The FPD Measurement Software" << endl;
	Sleep(5000);
	my_time= time(NULL);

	// ctime() used to give the present time 
	printf("%s", ctime(&my_time));
	sendData(pipe, result, "Calculate The Result\n");
	wcout << "Server: Calculate The Result " << endl;
	Sleep(5000);
	// Close the pipe (automatically disconnects client too)
	sendData(pipe, result, "0");
	CloseHandle(pipe);

	wcout << "Done." << endl;
	
	system("pause");
	return 0;
}
