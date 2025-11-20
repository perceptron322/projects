all:
	$(MAKE) -C mySimpleComputer
	$(MAKE) -C myTerm
	$(MAKE) -C myBigChars
	$(MAKE) -C myReadKey
	$(MAKE) -C console

clean:
	$(MAKE) -C ./mySimpleComputer clean
	$(MAKE) -C ./myTerm clean
	$(MAKE) -C ./myBigChars clean
	$(MAKE) -C ./myReadKey clean
	$(MAKE) -C ./console clean 

run : console/main.exe all
	./console/main.exe

rebuild: clean all
