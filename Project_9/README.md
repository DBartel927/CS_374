# Producer Consumer Project

## Description

This program implements the producer-consumer problem using POSIX threads and semaphores. Producers generate events and place them into a shared FIFO queue. Consumers remove events from the queue and process them. Synchronization is handled using semaphores.

## Build

Run: make

## Run

./pc producers consumers events_per_producer max_buffer

Example:

./pc 2 4 5 2

## Files

pc.c – main producer/consumer implementation  
eventbuf.c – provided queue implementation  
eventbuf.h – queue interface  
Makefile – build instructions
README.md - program description and current file