BINARY_DIR = build

# ----------------------------------------------------------------------------------------------------------------------

all: clean executor.o main.o
	g++ -pthread $(BINARY_DIR)/calc.o $(BINARY_DIR)/executor.o -o ${BINARY_DIR}/calc
.PHONY: all

main.o: build_dir
	g++ -c -Wall --std=c++20 -lstdc++fs  main.cpp -o $(BINARY_DIR)/calc.o
.PHONY: main.o

executor.o: build_dir
	g++ -c -Wall -lstdc++ executor.cpp -o $(BINARY_DIR)/executor.o
.PHONY: executor.o

# ----------------------------------------------------------------------------------------------------------------------

test: clean.test all
	./run_tests.sh
.PHONY: test

clean.test:
	rm -f out.txt
.PHONU : clean.test

# ----------------------------------------------------------------------------------------------------------------------

build_dir:
	mkdir -p "$(BINARY_DIR)"
.PHONY: build_dir

clean:
	rm -rf $(BINARY_DIR)
PHONY: clean