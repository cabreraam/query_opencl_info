#include <stdio.h>
#include "query_opencl_info.h"

// ACL specific includes
//#include "AOCLUtils/aocl_utils.h"

void free_resources(cl_platform_id* platforms)
{
	if (platforms)	
		free(platforms);
}

void dump_error(const char *str, cl_int status) {
  printf("%s\n", str);
  printf("Error code: %d\n", status);
}

void all_platform_info(cl_platform_id* platform)
{

	char info_string[STRING_BUFFER_LEN];

	//CL_PLATFORM_PROFILE
	clGetPlatformInfo(*platform, CL_PLATFORM_PROFILE, STRING_BUFFER_LEN,
		&info_string, NULL); 
	fprintf(stderr, "%-32s= %s\n", "CL_PLATFORM_PROFILE", info_string);

	//CL_PLATFORM_VERSION
	clGetPlatformInfo(*platform, CL_PLATFORM_VERSION, STRING_BUFFER_LEN,
		&info_string, NULL); 
	fprintf(stderr, "%-32s= %s\n", "CL_PLATFORM_VERSION", info_string);

	//CL_PLATFORM_NAME
	clGetPlatformInfo(*platform, CL_PLATFORM_NAME, STRING_BUFFER_LEN,
		&info_string, NULL); 
	fprintf(stderr, "%-32s= %s\n", "CL_PLATFORM_NAME", info_string);

	//CL_PLATFORM_VENDOR
	clGetPlatformInfo(*platform, CL_PLATFORM_VENDOR, STRING_BUFFER_LEN,
		&info_string, NULL); 
	fprintf(stderr, "%-32s= %s\n", "CL_PLATFORM_VENDOR", info_string);

	//CL_PLATFORM_EXTENSIONS
	clGetPlatformInfo(*platform, CL_PLATFORM_EXTENSIONS, STRING_BUFFER_LEN,
		&info_string, NULL); 
	fprintf(stderr, "%-32s= %s\n", "CL_PLATFORM_EXTENSIONS", info_string);

	fprintf(stderr, "\n");

} 

//TODO: Get all of the parameters associated with clGetDeviceInfo
//https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/clGetDeviceInfo.html
void all_device_info(cl_device_id device)
{
	char info_string[STRING_BUFFER_LEN];
	cl_uint info_uint;
	cl_bool info_bool;
	cl_bool info_ulong;
	size_t  info_size_t;
	cl_platform_id info_dev;

	clGetDeviceInfo(device, CL_DEVICE_NAME, STRING_BUFFER_LEN, &info_string,
		NULL);
	fprintf(stderr, "\t%-32s= %s\n", "CL_DEVICE_NAME", info_string);

	clGetDeviceInfo(device, CL_DEVICE_ADDRESS_BITS, sizeof(cl_uint), &info_uint, 
		NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_ADDRESS_BITS", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_AVAILABLE, sizeof(cl_bool), &info_bool, 
		NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_AVAILABLE", info_bool);

	clGetDeviceInfo(device, CL_DEVICE_COMPILER_AVAILABLE, sizeof(cl_bool), 
		&info_bool, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_COMPILER_AVAILABLE", info_bool);

	clGetDeviceInfo(device, CL_DEVICE_ENDIAN_LITTLE, sizeof(cl_bool), 
		&info_bool, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_ENDIAN_LITTLE", info_bool);

	clGetDeviceInfo(device, CL_DEVICE_ERROR_CORRECTION_SUPPORT, sizeof(cl_bool), 
		&info_bool, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_ERROR_CORRECTION_SUPPORT", info_bool);

	clGetDeviceInfo(device, CL_DEVICE_EXECUTION_CAPABILITIES,
		sizeof(cl_device_exec_capabilities), &info_bool, NULL);
	fprintf(stderr, "\t%-32s= %u", "CL_DEVICE_EXECUTION_CAPABILITIES", info_bool);
	fprintf(stderr, " <---- represents a 2 bit bitfield; refer to docs to ");
	fprintf(stderr, "interpret\n");

	clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, STRING_BUFFER_LEN, &info_string,
		NULL);
	fprintf(stderr, "\t%-32s= %s\n", "CL_DEVICE_EXTENSIONS", info_string);

	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(cl_ulong), 
		&info_ulong, NULL);
	fprintf(stderr, "\t%-32s= %u Bytes\n", "CL_DEVICE_GLOBAL_MEM_CACHE_SIZE", 
		info_ulong);

	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,
		sizeof(cl_device_mem_cache_type), &info_bool, NULL);
	fprintf(stderr, "\t%-32s= %u", "CL_DEVICE_GLOBAL_MEM_CACHE_TYPE", info_bool);
	fprintf(stderr, " <---- possible values are 0, 1, 2; refer to docs to ");
	fprintf(stderr, "interpret\n");

	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), 
		&info_ulong, NULL);
	fprintf(stderr, "\t%-32s= %u Bytes\n", "CL_DEVICE_GLOBAL_MEM_SIZE", info_ulong);

	clGetDeviceInfo(device, CL_DEVICE_DOUBLE_FP_CONFIG,
		sizeof(cl_device_fp_config), &info_bool, NULL);
	fprintf(stderr, "\t%-32s= %u", "CL_DEVICE_DOUBLE_FP_CONFIG", info_bool);
	fprintf(stderr, " <---- represents a 6 bit bitfield; refer to docs to ");
	fprintf(stderr, "interpret\n");

	clGetDeviceInfo(device, CL_DEVICE_SINGLE_FP_CONFIG,
		sizeof(cl_device_fp_config), &info_bool, NULL);
	fprintf(stderr, "\t%-32s= %u", "CL_DEVICE_SINGLE_FP_CONFIG", info_bool);
	fprintf(stderr, " <---- represents a 6 bit bitfield; refer to docs to ");
	fprintf(stderr, "interpret\n");

	clGetDeviceInfo(device, CL_DEVICE_HALF_FP_CONFIG,
		sizeof(cl_device_fp_config), &info_bool, NULL);
	fprintf(stderr, "\t%-32s= %u", "CL_DEVICE_HALF_FP_CONFIG", info_bool);
	fprintf(stderr, " <---- represents a 6 bit bitfield; refer to docs to ");
	fprintf(stderr, "interpret\n");

	clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, sizeof(cl_bool), &info_bool,
		NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_ERROR_CORRECTION_SUPPORT", info_bool);

	clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizeof(size_t),
		&info_size_t, NULL);
	fprintf(stderr, "\t%-32s= %zd\n", "CL_DEVICE_IMAGE2D_MAX_HEIGHT", info_size_t);

	clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_WIDTH, sizeof(size_t),
		&info_size_t, NULL);
	fprintf(stderr, "\t%-32s= %zd\n", "CL_DEVICE_IMAGE2D_MAX_WIDTH", info_size_t);

	clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_DEPTH, sizeof(size_t),
		&info_size_t, NULL);
	fprintf(stderr, "\t%-32s= %zd\n", "CL_DEVICE_IMAGE3D_MAX_DEPTH", info_size_t);

	clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_HEIGHT, sizeof(size_t),
		&info_size_t, NULL);
	fprintf(stderr, "\t%-32s= %zd\n", "CL_DEVICE_IMAGE3D_MAX_HEIGHT", info_size_t);

	clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_WIDTH, sizeof(size_t),
		&info_size_t, NULL);
	fprintf(stderr, "\t%-32s= %zd\n", "CL_DEVICE_IMAGE3D_MAX_WIDTH", info_size_t);

	clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), 
		&info_ulong, NULL);
	fprintf(stderr, "\t%-32s= %u Bytes\n", "CL_DEVICE_LOCAL_MEM_SIZE", info_ulong);

	clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_TYPE,
		sizeof(cl_device_local_mem_type), &info_bool, NULL);
	fprintf(stderr, "\t%-32s= %u", "cl_device_local_mem_type", info_bool);
	fprintf(stderr, " <---- possible values are 0 (global) or 1 (local); refer ");
	fprintf(stderr, "to docs to interpret\n");

	clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u MHz\n", "CL_DEVICE_MAX_CLOCK_FREQUENCY", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_MAX_COMPUTE_UNITS", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_ARGS, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_MAX_CONSTANT_ARGS", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(cl_ulong), 
		&info_ulong, NULL);
	fprintf(stderr, "\t%-32s= %u Bytes\n", "CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE", 
		info_ulong);

	clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), 
		&info_ulong, NULL);
	fprintf(stderr, "\t%-32s= %u Bytes\n", "CL_DEVICE_MAX_MEM_ALLOC_SIZE", 
		info_ulong);

	clGetDeviceInfo(device, CL_DEVICE_MAX_PARAMETER_SIZE, sizeof(size_t),
		&info_size_t, NULL);
	fprintf(stderr, "\t%-32s= %zd Bytes\n", "CL_DEVICE_MAX_PARAMETER_SIZE", 
		info_size_t);

	clGetDeviceInfo(device, CL_DEVICE_MAX_READ_IMAGE_ARGS, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_MAX_READ_IMAGE_ARGS", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_MAX_SAMPLERS, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_MAX_SAMPLERS", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t),
		&info_size_t, NULL);
	fprintf(stderr, "\t%-32s= %zd\n", "CL_DEVICE_MAX_WORK_GROUP_SIZE", info_size_t);

	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS", info_uint);

	size_t* info_size_t_arr = (size_t*) malloc(sizeof(size_t) * info_uint);

	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, 
		sizeof(size_t) * info_uint, info_size_t_arr, NULL);
	fprintf(stderr, "\t%-32s= (%zd, %zd, %zd)\n", "CL_DEVICE_MAX_WORK_ITEM_SIZES", 
		info_size_t_arr[0], info_size_t_arr[1], info_size_t_arr[2]);
	free(info_size_t_arr);

	clGetDeviceInfo(device, CL_DEVICE_MAX_WRITE_IMAGE_ARGS, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_MAX_WRITE_IMAGE_ARGS", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_MEM_BASE_ADDR_ALIGN, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u bits\n", "CL_DEVICE_MEM_BASE_ADDR_ALIGN", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u Bytes\n", "CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_NAME, STRING_BUFFER_LEN, &info_string,
		NULL);
	fprintf(stderr, "\t%-32s= %s\n", "CL_DEVICE_NAME", info_string);

	/*clGetDeviceInfo(device, CL_DEVICE_PLATFORM, sizeof(cl_platform_id),
		&info_plat, NULL);
	fprintf(stderr, "\t%-32s= %p\n", "CL_DEVICE_PLATFORM", info_plat);*/

	clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_PROFILE, STRING_BUFFER_LEN, &info_string,
		NULL);
	fprintf(stderr, "\t%-32s= %s\n", "CL_DEVICE_PROFILE", info_string);

	clGetDeviceInfo(device, CL_DEVICE_PROFILING_TIMER_RESOLUTION, sizeof(size_t),
		&info_size_t, NULL);
	fprintf(stderr, "\t%-32s= %zd ns\n", "CL_DEVICE_PROFILING_TIMER_RESOLUTION", 
		info_size_t);

	clGetDeviceInfo(device, CL_DEVICE_QUEUE_PROPERTIES,
		sizeof(cl_command_queue_properties), &info_bool, NULL);
	fprintf(stderr, "\t%-32s= %u", "CL_DEVICE_QUEUE_PROPERTIES", info_bool);
	fprintf(stderr, " <---- represents a 2 bit bitfield; refer to docs to ");
	fprintf(stderr, "interpret\n");

	clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(cl_device_type), &info_dev, NULL);
	fprintf(stderr, "\t%-32s= %p", "CL_DEVICE_TYPE", info_dev);
	fprintf(stderr, " <---- {0, 1, 2, 3, 4} are possible vals; ");
	fprintf(stderr, "refer to docs to interpret\n");

	clGetDeviceInfo(device, CL_DEVICE_VENDOR_ID, sizeof(cl_uint), 
		&info_uint, NULL);
	fprintf(stderr, "\t%-32s= %u\n", "CL_DEVICE_VENDOR_ID", info_uint);

	clGetDeviceInfo(device, CL_DEVICE_VERSION, STRING_BUFFER_LEN, &info_string,
		NULL);
	fprintf(stderr, "\t%-32s= %s\n", "CL_DEVICE_VERSION", info_string);

	clGetDeviceInfo(device, CL_DRIVER_VERSION, STRING_BUFFER_LEN, &info_string,
		NULL);
	fprintf(stderr, "\t%-32s= %s\n", "CL_DRIVER_VERSION", info_string);

	fprintf(stderr, "\n");
} 
