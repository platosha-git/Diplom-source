g++ \
-I/usr/include/postgresql/ \
-o pool.out pool/main.cpp pool/pgbackend.cpp pool/pgconnection.cpp \
-lpq -pthread
