BINARY_DIR = build

# ----------------------------------------------------------------------------------------------------------------------

all: converter.o main.o
	g++ $(BINARY_DIR)/morze.o $(BINARY_DIR)/converter.o -o ${BINARY_DIR}/morze
.PHONY: all

main.o: build_dir
	g++ -c -Wall -lstdc++ main.cpp -o $(BINARY_DIR)/morze.o
.PHONY: main.o

converter.o: build_dir
	g++ -c -Wall -lstdc++ converter.cpp -o $(BINARY_DIR)/converter.o
.PHONY: converter.o

# ----------------------------------------------------------------------------------------------------------------------

test: clean.test all
	./run_tests.sh
.PHONY: test

clean.test:
	rm -f out-[0123456789]*.txt
.PHONU : clean.test

# ----------------------------------------------------------------------------------------------------------------------

build_dir:
	mkdir -p "$(BINARY_DIR)"
.PHONY: build_dir

clean:
	rm -rf $(BINARY_DIR)
PHONY: clean