# Simple Library to Query OpenCL 1.0 device info

## Instructions
On ExCL PCIe node:

Issue

`make FPGA=1`

This should create `lib/libquery_opencl_info.so` in the top-level dirctory.

Now navigate to the testapp directory and build the application using:

`cd testapp`

`make FPGA=1`

Then run `query` and you should get a (messy) rundown of some OpenCL 1.0 device info.
