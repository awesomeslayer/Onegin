onegin: ./source/onegin.c ./source/onegin_func.c ./source/onegin_func.h
	g++ -o $@ $^

%.o:%.c
	g++ -c -o $@ $<