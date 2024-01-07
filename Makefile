CC          := gcc
EXE_DIR     := exe
EXE_FILE    := $(EXE_DIR)/main.exe

ccSRC_DIR   := src/
ccOBJ_DIR   := obj/
ccSRCS      := $(shell find $(ccSRC_DIR) -name *.c -or -name *.cpp)
ccOBJS      := $(ccSRCS:%=$(ccOBJ_DIR)%.o)
INC_DIRS := $(shell find $(ccSRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) `pkg-config --cflags --libs gtk+-3.0 epoxy`


LIB_FLAGS := -lGL -lGLU -D _DEFAULT_SOURCE
#-lglut -lGLEW 
myCCFLAGS ?= $(INC_FLAGS) -std=c11  $(LIB_FLAGS) -lOpenCL  -lm #
################################################################################

# Target rules
all: build

build: $(EXE_FILE) 

obj/%.c.o:%.c
	mkdir -p $(dir $@)
	${CC} -c $< -o $@ $(myCCFLAGS)

$(EXE_FILE):$(ccOBJS)
	mkdir -p  $(EXE_DIR)
	$(CC) -o $@ $(ccOBJS) $(LDFLAGS) $(myCCFLAGS) 


.PHONY:run
run: build
	./$(EXE_FILE)
	
.PHONY:testrun
testrun: build

.PHONY:clean
clean:
	rm -rf *.c.o *.cpp.o obj/* exe/* ${EXE_FILE} ${EXE_DIR}
	
clobber: clean
