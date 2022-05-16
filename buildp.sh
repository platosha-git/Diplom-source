g++ \
-I/usr/include/postgresql/ \
pool/main.cpp pool/pgbackend.cpp pool/pgconnection.cpp \
-lpq -pthread
