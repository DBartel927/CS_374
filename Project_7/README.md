# Multithreaded PPM Grayscaler

This program converts a color PPM (P6) image to grayscale using
multiple threads. The image is divided into horizontal slices, and each
thread is responsible for processing one slice.

Each thread converts its assigned pixels to grayscale and tracks the sum of red, green, and blue values.

The main thread waits for all threads to complete, computes and prints the average RGB values for the entire image, and then writes the grayscale image to disk.

## Building

Command line:

* make to build. An executable called grayscaler will be produced.
* make clean to remove the executable.

## Running

* ./grayscaler <thread_count> <input.ppm> <output.ppm>

Example:

* ./grayscaler 3 goat.ppm graygoat.ppm


Example output:

Thread 0: 0 23
Thread 1: 23 23
Thread 2: 46 25
Average R: 119
Average G: 108
Average B: 94

## Files

* grayscaler.c: Main program logic and thread implementation
* ppm.c: Provided PPM image library implementation
* ppm.h: Provided PPM image library header
* Makefile: Builds the project
* README.md: Project documentation

## Data

struct ppm

* Defined in ppm.h. Represents a PPM image.

Important fields used:
* width — image width in pixels
* height — image height in pixels
* data — raw pixel data

thread_data_t

* Structure used to pass data to and from each thread.

Contains:
* Pointer to the image
* Thread ID
* Starting row (start_y)
* Number of rows assigned (rows)
* Accumulated red, green, and blue sums
Each thread owns its own thread_data_t structure.

## Functions

main()
* Parses command line arguments
* Loads input PPM image
* Divides image into slices
* Creates threads
* Joins threads
* Computes average RGB values
* Writes grayscale image
* Frees image memory

run(void *arg)
* Executed by each thread
* Converts assigned slice to grayscale
* Accumulates RGB sums
* Returns to main thread