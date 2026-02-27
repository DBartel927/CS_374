# Reservation System

## Building

`make` to build. Produces executable `reservations`
`make clean` removes build artifacts

## Files

`reservations.c` Main program and thread-safe seat logic
`Makefile` Builds the project
`README.md` Project documentation, and what you are currently reading

## Data Structures

`int *seat_taken` Dynamic array representing seats where 0 = free and 1 = taken/reserved
`int seat_taken_count` Tracks total number of reserved seats
`pthread_mutex_t seat_lock` Mutex protecting shared seat data

## Functions

`main` Initializes data, launches broker threads, and waits for threads to complete
`seat_broker()` Performs random reserve/free transactions and verifies seat consistency
`reserve_seat(int n)` Reserves seat n if free, updates `seat_taken_count`, protected by a mutex
`free_seat(int n)` Frees seat n if reserved, updates `seat_taken_count`, protected by a mutex
`verify_seat_count()` Confirms array matches global counter

## Notes

Each broker is its own thread
All shared data is protected by a mutex
Very large broker counts may cause system slowdown