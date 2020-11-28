all : fileDir make_pipes Province City Store Search

fileDir:
	@mkdir -p build
	@mkdir -p bin
	@mkdir -p namedPipe

make_pipes:
	@touch namedPipe/s
	@touch namedPipe/c
	@touch namedPipe/p


# Province : 
Province : build/ProvinceMain.o build/Province.o build/Tools.o
	@echo "Making Province executable file!"
	g++ -std=c++11 build/ProvinceMain.o build/Province.o build/Tools.o -o bin/Province
	
build/ProvinceMain.o : src/ProvinceMain.cpp src/Province.cpp src/Province.h
	g++ -std=c++11 -c src/ProvinceMain.cpp -o build/ProvinceMain.o

build/Province.o :  src/Province.cpp src/Province.h
	g++ -std=c++11 -c src/Province.cpp -o build/Province.o

# City :
City : build/CityMain.o build/City.o build/Tools.o
	@echo "Making City executable file"
	g++ -std=c++11 build/CityMain.o build/City.o build/Tools.o -o bin/City

build/CityMain.o : src/CityMain.cpp src/City.cpp src/City.h
	g++ -std=c++11 -c src/CityMain.cpp -o build/CityMain.o 

build/City.o :  src/City.cpp src/City.h
	g++ -std=c++11 -c src/City.cpp -o build/City.o

# Store :
Store : build/StoreMain.o build/Store.o build/Tools.o
	@echo "Making Store executable file"
	g++ -std=c++11 build/StoreMain.o build/Store.o build/Tools.o -o bin/Store

build/StoreMain.o : src/StoreMain.cpp src/Store.cpp src/Store.h
	g++ -std=c++11 -c src/StoreMain.cpp -o build/StoreMain.o 

build/Store.o :  src/Store.cpp src/Store.h
	g++ -std=c++11 -c src/Store.cpp -o build/Store.o

# Root :
Search :  build/Main.o build/Root.o build/Tools.o
	@echo "Linking..."

	g++ -std=c++11 build/Main.o build/Root.o build/Tools.o -o  StoreCalculator.out

build/Main.o : src/Main.cpp src/Root.h src/Root.cpp
	g++ -std=c++11 -c src/Main.cpp -o build/Main.o

build/Tools.o : src/Tools.cpp src/Tools.h
	g++ -std=c++11 -c src/Tools.cpp -o build/Tools.o

build/Root.o : src/Root.cpp src/Root.h
	g++ -std=c++11 -c src/Root.cpp -o build/Root.o

clean : 
	rm -f -r build
	rm -f -r bin
	rm -f -r namedPipe
	rm -f Search
