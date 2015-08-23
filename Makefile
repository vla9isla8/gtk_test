All: main
	
main: main.o
	gcc main.o `pkg-config --libs gtk+-3.0` -o main -lpthread -lcurses

main.o: main.c
	gcc `pkg-config --cflags gtk+-3.0` -c main.c 

clean:
	rm -rf *.o main
	
install: All
	mkdir -p /usr/local/bin/timer_custom
	cp  main /usr/local/bin/timer_custom/main
	cp  icon.png  /usr/local/bin/timer_custom/icon.png
	cp timer.desktop /usr/share/applications/timer.desktop

uninstall: 
	rm -rf /usr/local/bin/timer_custom
	rm /usr/share/applications/timer.desktop
