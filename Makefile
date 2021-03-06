CC      := gcc
CCFLAGS := 
LDFLAGS := -lpthread -lm -lrt

#SRC_DIRS ?= ./

TARGETS:= system_calls_tracker
MAINS  := $(addsuffix .o, $(TARGETS) )
OBJ    := $(MAINS)
#DEPS   :=

.PHONY: all clean

all: clean $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJ)

$(OBJ): %.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGETS): % : $(filter-out $(MAINS), $(OBJ)) %.o
	$(CC) -o $@ $(LIBS) $^ $(CCFLAGS) $(LDFLAGS)