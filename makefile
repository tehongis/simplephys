run		: pysimplephys.so

pysimplephys.so : main.c
	python3 setup.py install
	#gcc -Wall -I /usr/include/python3.9/ -o build/pysimplephys.so -shared main.c
