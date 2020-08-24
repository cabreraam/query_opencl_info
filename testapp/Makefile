#General Makefile for OpenCL CPU / GPU

ifeq ($(VERBOSE),1)
ECHO := 
else
ECHO := @
endif

TARGET := query 

# Directories.
HOST_DIR := .
TARGET_DIR := .
#INC_DIRS := host/inc ../common/inc ../extlibs/inc 
INC_COMPILE := $(foreach DIR,$(INC_DIRS),-I$(DIR))
CXXFLAGS += $(INC_COMPILE)

# All include files.
INC_DIRS := ../ ../inc
INC_COMPILE := $(foreach DIR, $(INC_DIRS), -I$(DIR))
ifeq ($(FPGA),1)
	AOCL_COMPILE_CONFIG=$(shell aocl compile-config)
	INC_COMPILE += $(AOCL_COMPILE_CONFIG)
endif
CXXFLAGS+=$(INC_COMPILE)
CXXFLAGS+=$(INC_COMPILE)

# listing inc files isn't really necessary
INC_FILES := $(foreach DIR, $(INC_DIRS), $(wildcard $(DIR)/*.h))

# Source files.

SRC_DIR := .
SRC_FILES := main.cpp 
$(info SRC_FILES=$(SRC_FILES))

OBJ_DIR := obj
OBJ_FILES := $(subst $(SRC_DIR)/,,$(SRC_FILES))
OBJ_FILES := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(OBJ_FILES))

# Libraries
LIB_DIRS := ../lib
LIB_DIRS_COMPILE := $(foreach DIR, $(LIB_DIRS), -L$(DIR))
ifeq ($(FPGA), 1)
	AOCL_LINK_CONFIG=$(shell aocl link-config)
	LIB_DIRS_COMPILE += $(AOCL_LINK_CONFIG)
endif
$(info LIB_DIR_COMPILE=$(LIB_DIRS_COMPILE))

LIBS_LOC := ../lib
LIBS_LOC := $(foreach PATH,$(LIBS_LOC),-L$(PATH)) 
$(info LIBS_LOC=$(LIBS_LOC))
CXXFLAGS += $(LIBS_LOC)
#LIBS := OpenCL query_opencl_info
#LIBS_COMPILE := $(foreach LIB,$(LIBS),-l$(LIB)) 
#$(info LIBS_COMPILE=$(LIBS_COMPILE))

# Compiler.
CXX := g++

# Compilation flags
ifeq ($(DEBUG),1)
CXXFLAGS += -g 
else
CXXFLAGS += -O2 
endif
CXXFLAGS += -Wall

# Make it all!
all : $(TARGET_DIR)/$(TARGET)

# Host executable target.
$(info LIBS=$(LIBS))
$(TARGET_DIR)/$(TARGET): $(OBJ_FILES) $(INC_FILES)
	@[ -d $(TARGET_DIR) ] || mkdir $(TARGET_DIR)
	$(ECHO)$(CXX) $(CXXFLAGS) -fPIC $(foreach D,$(INC_DIRS),-I$D) \
			$(OBJ_FILES) \
			-o $(TARGET_DIR)/$(TARGET) \
			$(LIB_DIRS_COMPILE) -lquery_opencl_info \
			-Wl,-rpath,../lib -Wl,-rpath,/opt/intelFPGA/18.0/hld/board/nalla_pcie/linux64/lib

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo $<
	$(ECHO)[ -d $(OBJ_DIR) ] || mkdir $(OBJ_DIR)
	$(ECHO)$(CXX) $(CXXFLAGS) -o $@ -c $< 

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	@echo $<
	$(ECHO)[ -d $(OBJ_DIR) ] || mkdir $(OBJ_DIR)
	$(ECHO)$(CXX) $(CXXFLAGS) -o $@ -c $< $(LIB_DIRS_COMPILE)


.PHONY : all clean
clean :
	$(ECHO)rm -f $(TARGET_DIR)/$(TARGET)
	$(ECHO)rm -f $(OBJ_FILES)
