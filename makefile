all: app

app: main.o singleConn.o multiConn.o poolConn.o pgbackend.o pgconnection.o customConn.o iofile.o
	g++ main.o singleConn.o multiConn.o poolConn.o pgbackend.o pgconnection.o customConn.o iofile.o -o app -lpq -pthread

main.o: main.cpp
	g++ -c main.cpp

singleConn.o: singleConn.cpp
	g++ -c -I/usr/local/pgsql/include -lpq singleConn.cpp

multiConn.o: multiConn.cpp
	g++ -c -I/usr/local/pgsql/include -lpq -pthread multiConn.cpp

poolConn.o: poolConn.cpp pgbackend.cpp pgconnection.cpp
	g++ -c -I/usr/include/postgresql/ -lpq -pthread poolConn.cpp pgbackend.cpp pgconnection.cpp

customConn.o: customConn.cpp
	g++ -c -I/usr/local/pgsql/include -lpq -pthread customConn.cpp

iofile.o: iofile.cpp iofile.h
	g++ -c iofile.cpp

clean:
	rm -rf *.o app