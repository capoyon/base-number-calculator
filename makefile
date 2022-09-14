base-calculator.exe: window.o parser.o base-converter.o
	g++ windows.o parser.o base-converter.o -o base-calculator.exe

windows.o: windows.cpp
	g++ -c windows.cpp

parser.o: parser.cpp
	g++ -c parser.cpp

base-converter.o: base-converter.cpp
	g++ -c base-converter.cpp

clean:
	rm *.o


