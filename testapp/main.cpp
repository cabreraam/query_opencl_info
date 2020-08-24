#include "query_opencl_info.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	cl_int status;
	cl_uint num_platforms;
	cl_uint* num_devices_array; 

	cl_platform_id* platforms;
	cl_device_id** devices;

	// GOAL: To get device ID
	// need platform(s)
	// query for num_platforms to figure out how much space to alloc 
	std::cout << "what's with this bottom statement?" << std::endl;
	status = clGetPlatformIDs(0, NULL, &num_platforms);
	std::cout << "fin" << std::endl;
	if (status != CL_SUCCESS)
	{
		dump_error("Failed to get number of platforms (clGetPlatformIDs)", status);
		free_resources(NULL);
		return 1;
	}
	else
		printf("num_platforms = %u\n", num_platforms);

	// alloc space for all platforms
	platforms = (cl_platform_id *) 
		malloc(sizeof(cl_platform_id) * num_platforms);

	status = clGetPlatformIDs(num_platforms, platforms, NULL);
	if (status != CL_SUCCESS)
	{
		dump_error("Failed to get platforms (clGetPlatformIDs)", status);
		free_resources(NULL);
		return 1;
	}
	else
		printf("Successfully enumerated %u platforms.\n", num_platforms);

// TODO: refactor from here to MARKER. could be under 1 main for loop

	// malloc a bucket for each platform so we know how many device counts to
	// record
	// tells us the number of devices that are available for each platform 
	num_devices_array = (cl_uint*) malloc(sizeof(cl_uint) * num_platforms);

	//for each platform, grab the device IDs
	for (int i = 0; i < num_platforms; ++i)
	{
		clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ACCELERATOR, 0, NULL,
			&num_devices_array[i]); 	
		if (status != CL_SUCCESS) 
		{
			dump_error("Failed clGetDeviceIDs.", status);
			free_resources(platforms);
			free(num_devices_array);
			return 1;
		}
		else
			printf("Platform %d has %u supported devices\n", i, num_devices_array[i]);
	}

	// malloc buckets for each platform's devices
	devices = (cl_device_id**) malloc(sizeof(cl_device_id*) * num_platforms);
	for (int i = 0; i < num_platforms; ++i)
	{
		// malloc buckets for platform "i"s devices
		devices[i] = (cl_device_id*) malloc(sizeof(cl_device_id) *
			num_devices_array[i]);	

		// grab the device ids for platform i's devices
		clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, num_devices_array[i],
			devices[i], NULL); 

	}	

// MARKER 

	// print ALL of the info!
	for (int i = 0; i < num_platforms; ++i)
	{
		
		fprintf(stderr, "========================================================");
		fprintf(stderr, "========================\n\n");

		printf("Platform %d\n\n", i);

		all_platform_info(&platforms[i]);

		for (int j = 0; j < num_devices_array[i] ;++j)
		{
			printf("\tDevice[%d][%d]\n\n", i, j);
			all_device_info(devices[i][j]);
		}

		fprintf(stderr, "========================================================");
		fprintf(stderr, "========================\n\n");
	}

	// for each platform, query for number of devices	

	free_resources(platforms);

	return 0;
}
