Onegin.exe: onegin.cpp	
    g++ -o $@ $^

%.o:%.c
	g++ -c -o $@ $<