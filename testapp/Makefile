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
INC_DIRS := .
INC_COMPILE := $(foreach DIR,$(INC_DIRS),-I$(DIR))
CXXFLAGS += $(INC_COMPILE)

# All include files.
INC_FILES := $(foreach D,$(INC_DIRS),$(wildcard $D/*.h))
$(info INC_FILES=$(INC_FILES))

# Source files.

SRC_DIR := .
SRC_FILES := main.cpp 
$(info SRC_FILES=$(SRC_FILES))

OBJ_DIR := .obj
OBJ_FILES := $(subst $(SRC_DIR)/,,$(SRC_FILES))
OBJ_FILES := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(OBJ_FILES))

# Libraries
LIBS_LOC := .
LIBS_LOC := $(foreach PATH,$(LIBS_LOC),-L$(PATH)) 
$(info LIBS_LOC=$(LIBS_LOC))
CXXFLAGS += $(LIBS_LOC)
LIBS := OpenCL query_opencl_info
LIBS_COMPILE := $(foreach LIB,$(LIBS),-l$(LIB)) 
$(info LIBS_COMPILE=$(LIBS_COMPILE))

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
			$(LIBS_COMPILE) \
			-Wl,-rpath,.

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo $<
	$(ECHO)[ -d $(OBJ_DIR) ] || mkdir $(OBJ_DIR)
	$(ECHO)$(CXX) $(CXXFLAGS) -o $@ -c $< 

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	@echo $<
	$(ECHO)[ -d $(OBJ_DIR) ] || mkdir $(OBJ_DIR)
	$(ECHO)$(CXX) $(CXXFLAGS) -o $@ -c $< $(LIBS_COMPILE)


.PHONY : all clean
clean :
	$(ECHO)rm -f $(TARGET_DIR)/$(TARGET)
	$(ECHO)rm -f $(OBJ_FILES)
