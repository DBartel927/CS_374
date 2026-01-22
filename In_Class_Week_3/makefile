TARGETS=fork fork2 tokenize tokenize2 tokenize3 tokenize4

.PHONY: all clean

all: $(TARGETS)

fork: fork.c
	gcc -Wall -Wextra -o $@ $^

fork2: fork2.c
	gcc -Wall -Wextra -o $@ $^

tokenize: tokenize.c
	gcc -Wall -Wextra -o $@ $^ 

tokenize2: tokenize2.c
	gcc -Wall -Wextra -o $@ $^

tokenize3: tokenize3.c
	gcc -Wall -Wextra -o $@ $^

tokenize4: tokenize4.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)