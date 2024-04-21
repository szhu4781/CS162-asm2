CC=g++
EXE_FILE=program_2

all: $(EXE_FILE)

$(EXE_FILE): run_catalog.o catalog.h catalog.o 
	$(CC) run_catalog.o catalog.o -o $(EXE_FILE)

run_catalog.o: run_catalog.cpp
	$(CC) -g -c run_catalog.cpp

catalog.o: catalog.cpp catalog.h
	$(CC) -g -c catalog.cpp

clean:
	rm -f *.o $(EXE_FILE)
