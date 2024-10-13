hasse : hasse.o ezdib.o 
	gcc -o hasse hasse.o ezdib.o -lm

hasse.o : hasse.c 
	gcc -c -o hasse.o hasse.c 

ezdib.o : ezdib.c
	gcc -c -o ezdib.o ezdib.c 

clean:
	rm *.o *.bmp hasse