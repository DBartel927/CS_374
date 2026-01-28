// In this challenge, we're going to make a FIFO where we send a fixed-length message every time. This will make it easier to extract the data on the consumer side.

// What We Are Sending
// We're going to send 16-byte chunks of data. Each chunk has one byte at the beginning that has the sequence number of the message, and then the remaining bytes have the message which is a null-terminated string. (The string might be shorter than the remaining 15 bytes, but we'll send all 16 bytes every time.)

// Here's an example buffer in some C pseudocode for the second message in the sequence:

// char buf[64];

// buf[0] = 2;
// buf[1] = 'M';
// buf[2] = 'e';
// buf[3] = 's';
// buf[4] = 's';
// buf[5] = 'a';
// buf[6] = 'g';
// buf[7] = 'e';
// buf[8] = ' ';
// buf[9] = '2';
// buf[10] = '\0'; // null terminator
// buf[11] = don't care
// ...
// buf[15] = don't care
// The Producer and Consumer
// The producer will send a number of messages that is specified on the command line. It will also print out when it sends the data:

// $ ./producer 10
//   waiting for readers...
//   Sending 0 Message #0
//   Sending 1 Message #1
//   Sending 2 Message #2
//   Sending 3 Message #3
//   Sending 4 Message #4
//   Sending 5 Message #5
//   Sending 6 Message #6
//   Sending 7 Message #7
//   Sending 8 Message #8
//   Sending 9 Message #9
// (The producer should only accept counts between 1 and 255, inclusive, since those values fit in a byte.)

// Important! The producer must call sleep(1); between each write! It's in <unistd.h>. It'll slow down the run and make it more fun.

// Meanwhile, a consumer in another window (assuming there is only one), will print out the following:

// $ ./consumer
//   waiting for writers...
//   0: Message #0
//   1: Message #1
//   2: Message #2
//   3: Message #3
//   4: Message #4
//   5: Message #5
//   6: Message #6
//   7: Message #7
//   8: Message #8
//   9: Message #9
// Experiment with multiple producers and consumers. Each producer will start at count 0 when it launches.

// Hints
// You'll have a char buf[16] array to hold everything, but the first byte is the sequence number, and the remaining bytes are the message.

// You can use sprintf() to print into a buffer like this:

// char buf[16];

// buf[0] = msg_num;  // Set the message number
// sprintf(buf, "Message %d", msg_num); // Set the message
// But that sprintf() will overwrite buf[0] that you just set! You really want sprintf() to start "printing" at buf[1]. So you need to pass a pointer to &buf[1].

// sprintf(&buf[1], "Message %d", msg_num); // Set the message
// But that's klunky and non-idiomatic C. It simplifies using pointer arithmetic:

// sprintf(buf + 1, "Message %d", msg_num); // Set the message
// That's better!

// Recall that in C a[b] == *(a+b) by definition. We can do some simplification to see the &buf[1] == buf+1 equivalence:

// &buf[1] == &(*(buf+1))   by definition
//         == (buf+1)       &* cancels
//         == buf+1         remove parens

// This is the consumer program.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "my_fifo2"
#define MSG_SIZE 16

int main(void) {
    mkfifo(FIFO_NAME, 0666);

    printf("waiting for writers...\n");
    int fd = open(FIFO_NAME, O_RDONLY);

    unsigned char buf[MSG_SIZE];
    ssize_t n;

    while ((n = read(fd, buf, MSG_SIZE)) == MSG_SIZE) {
        unsigned char seq = buf[0];
        char *msg = (char *)(buf + 1);

        printf("%d: %s\n", seq, msg);
        fflush(stdout);
    }

    close(fd);
    return 0;
}