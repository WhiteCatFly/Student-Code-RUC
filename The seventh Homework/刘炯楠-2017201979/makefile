main: main.o sent_processor.o corpus.o data_processor.o
	g++ -o main main.o sent_processor.o corpus.o data_processor.o
main.o: main.cpp sent_processor.h corpus.h data_processor.h
	g++ -c main.cpp
data_processor.o: data_processor.cpp data_processor.h corpus.h
	g++ -c data_processor.cpp
sent_processor.o: sent_processor.cpp sent_processor.h corpus.h
	g++ -c sent_processor.cpp
corpus.o: corpus.cpp corpus.h
	g++ -c corpus.cpp
clean:
	rm main main.o data_processor.o sent_processor.o corpus.o
