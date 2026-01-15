TARGETS=recordfile getsize mymkdir myls

.PHONY: all clean

all: $(TARGETS)

recordfile: recordfile.c
	gcc -Wall -Wextra -o $@ $^

getsize: getsize.c
	gcc -Wall -Wextra -o $@ $^

mymkdir: mymkdir.c
	gcc -Wall -Wextra -o $@ $^

myls: myls.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)