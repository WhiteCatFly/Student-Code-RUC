objects = Main.o Disposecmd.o Reporterr.o Parser.o ReadFile.o WriteFile.o

parser : $(objects)
	g++ -std=c++11 -o parser $(objects)
	
Main.o : Main.cpp Disposecmd.h Reporterr.h Parser.h
	g++ -std=c++11 -c Main.cpp

Disposecmd.o : Disposecmd.cpp Disposecmd.h
	g++ -std=c++11 -c Disposecmd.cpp


Reporterr.o : Reporterr.cpp Reporterr.h
	g++ -std=c++11 -c Reporterr.cpp
	
Parser.o : Parser.cpp Parser.h
	g++ -std=c++11 -c Parser.cpp

ReadFile.o : ReadFile.cpp Parser.h
	g++ -std=c++11 -c ReadFile.cpp

WriteFile.o : WriteFile.cpp Parser.h
	g++ -std=c++11 -c WriteFile.cpp

.PHONY : clean
clean :
	-rm parser $(objects)
