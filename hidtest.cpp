/*******************************************************
 this is some evil shit
 send help

********************************************************/

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"
#include <stdint.h>
#include <iostream>
#include <string>
#include <atomic>
#include <sstream>
#include <ctime>

// Headers needed for sleeping.
#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	int res;
	unsigned char buf[256];
	#define MAX_STR 255
	wchar_t wstr[MAX_STR];
	hid_device *handle;
	int i;

#ifdef WIN32
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
#endif

	struct hid_device_info *devs, *cur_dev;
	
	if (hid_init())
		return -1;

	handle = hid_open(0x2341, 0x003e, NULL);
	if (!handle) {
		printf("unable to open device\n");
 		return 1;
	}

	int result;
	unsigned char packet_buffer[64];
	union {
		uint8_t input[sizeof(float)];
		float output;
	}quat0;
	union {
		uint8_t input[sizeof(float)];
		float output;
	}quat1;
	union {
		uint8_t input[sizeof(float)];
		float output;
	}quat2;
	union {
		uint8_t input[sizeof(float)];
		float output;
	}quat3;

	struct pak {
		uint8_t id;
		float quat[4];
	};

	while (true) {
		result = hid_read(handle, packet_buffer, 17);
		if (result > 0) {

			pak* recv = (pak*)packet_buffer;

			quat0.input[0] = packet_buffer[1];
			quat0.input[1] = packet_buffer[2];
			quat0.input[2] = packet_buffer[3];
			quat0.input[3] = packet_buffer[4];

			//float * quat = &packet_buffer[1,2,3,4]; //this does not work because hid_read() reads the packet as unsigned char array

			std::cout << quat0.output << "\n";
			std::cout << recv->quat[0] << "," << recv->quat[1] << "," << recv->quat[2] << "," << recv->quat[3] << "," << "\n";

		}
	}
	
	hid_exit();

#ifdef WIN32
	system("pause");
#endif

	return 0;
}



