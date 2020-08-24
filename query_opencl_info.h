#include "CL/opencl.h"

// ACL specific includes
#ifdef FPGA
#include "AOCLUtils/aocl_utils.h"
#endif

#define STRING_BUFFER_LEN 1024

void free_resources(cl_platform_id* platforms);

void dump_error(const char *str, cl_int status); 

void all_platform_info(cl_platform_id* platform); 

void all_device_info(cl_device_id device); 
