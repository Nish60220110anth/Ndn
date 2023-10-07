GPPCONFIG=$(pkg-config --cflags --libs libndn-cxx);
g++ -std=c++17 -o ./scratch/a.out ./scratch/code1.cpp $GPPCONFIG;
/usr/local/bin/nfd-start && ./scratch/a.out;
echo script finished;