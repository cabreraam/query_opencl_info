#Makefile for libquery_opencl_info.so

ifneq ($(VERBOSE),)
ECHO := 
else
ECHO := @
endif

TARGET_DIR = ./lib

CXX = g++

ifeq ($(DEBUG), 1)
	CXXFLAGS += -g
else
	CXXFLAGS += -O2
endif
CXXFLAGS += -Wall 

ifeq ($(FPGA), 1)
	CXXFLAGS += -DFPGA=1
endif


LIB_DIRS :=
LIB_DIRS_COMPILE := $(foreach DIR, $(LIB_DIRS), -L$(DIR))
ifeq ($(FPGA), 1)
	AOCL_LINK_CONFIG=$(shell aocl link-config)
	LIB_DIRS_COMPILE += $(AOCL_LINK_CONFIG)
endif

#LIBS := OpenCL
LIBS :=
LIBS_COMPILE := $(foreach LIB, $(LIBS), -l$(LIB))

TARGET_LIB = libquery_opencl_info.so 

INC_DIRS := . ../common_harp/inc
INC_COMPILE := $(foreach DIR, $(INC_DIRS), -I$(DIR))
ifeq ($(FPGA),1)
	AOCL_COMPILE_CONFIG=$(shell aocl compile-config)
	INC_COMPILE += $(AOCL_COMPILE_CONFIG)
endif
CXXFLAGS+=$(INC_COMPILE)
CXXFLAGS+=$(INC_COMPILE)

# listing inc files isn't really necessary
INC_FILES := $(foreach DIR, $(INC_DIRS), $(wildcard $(DIR)/*.h))

SRC_DIR := .

#SRC_FILES := $(foreach DIR,$(SRC_DIR),$(wildcard $(DIR)/*.cpp))
SRC_FILES := $(SRC_DIR)/query_opencl_info.cpp
$(info SRC_FILES=$(SRC_FILES))
$(info SRC_DIR/SRC_FILES=$(SRC_DIR)/$(SRC_FILES))
#SRC_FILES := $(patsubst %.cpp,$(SRC_DIR)/%.cpp,$(SRC_FILES))

OBJ_DIR := obj
#OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(info OBJ_FILES=$(OBJ_FILES))


all: $(TARGET_DIR)/$(TARGET_LIB) 

$(TARGET_DIR)/$(TARGET_LIB) : $(OBJ_FILES) $(INC_FILES)
	$(ECHO)echo Include files: $(INC_FILES)
	$(ECHO)echo Include dirs: $(INC_COMPILE)
	$(ECHO)echo Source files: $(SRC_FILES)
	$(ECHO)echo Object files:  $(OBJ_FILES)
	$(ECHO)echo Library Paths: $(LIB_DIRS_COMPILE)
	$(ECHO)echo Libraries: $(LIBS_COMPILE)
	$(ECHO)echo CXXFLAGS: $(CXXFLAGS)
	$(ECHO)echo Compiling $@
	$(ECHO)[ -d $(TARGET_DIR) ] || mkdir $(TARGET_DIR)
	#build command
	$(ECHO)$(CXX) \
		$(CXXFLAGS)	\
		$(OBJ_FILES) \
		$(LIB_DIRS_COMPILE) \
		$(LIBS_COMPILE) \
		-o $(TARGET_DIR)/$(TARGET_LIB) \
		-shared

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo $< 
	@[ -d $(OBJ_DIR) ] || mkdir $(OBJ_DIR)
	$(CXX) -o $@ -c $(CXXFLAGS) -fPIC $<

$(OBJ_DIR)/ocl_template.o: $(SRC_DIR)/ocl_template.cpp
	@echo $< 
	@[ -d $(OBJ_DIR) ] || mkdir $(OBJ_DIR)
	$(CXX) -o $@ -c $(CXXFLAGS) -fPIC $< $(LIBS_COMPILE)

.PHONY : all clean

clean:
	$(ECHO)rm -rf $(TARGET_DIR)/$(TARGET_LIB)
	$(ECHO)rm -rf $(OBJ_DIR)/*
