# Semaphores and Shared Memory

## Description  

The main program starts by creating a shared memory segment, where it also attaches the other programs to the same shared memory segment. Then, it creates 4 sets of 2 semaphores (8 in total), initializing them to 0.

Subsequently, the remaining processes are created, each assigned an id starting from 0 to 4. The corresponding programs are then executed.  
- `sem_child` contains the code for P1 and P2. Flag 1 corresponds to P1, and it is our first execution with id = 0. P1 is responsible for writing and reading data until the TERM message is received, at which point the processes terminate.  
- The second execution is in the `enc` program. This program contains the code for `enc1` and `enc2`. With id = 1, it corresponds to `enc1`, and with id = 3, it corresponds to `enc2`. Their function is to encode the message using an MD5 function and verify if it has been correctly transmitted.  
- The third execution happens in the `chan` program, which handles the channel with id = 2. Depending on the probability provided by the user, the message might get "spoiled" by inserting `x` at random positions.  
- Finally, with id = 4, P2 is executed, which is responsible for reading the message.

The programs can transfer messages from left to right and vice versa until the TERM termination message is given to P1, signaling the end of the program. Semaphores are used to "sleep" and "wake up" processes to facilitate message transfer.

---

## Assignment 1: Operating Systems 2020
**Stevis Charalampos-Antonius**  
**ID: 1115201600278**

---

## Contents of the Assignment

- **Folder `code`** containing the following:
    - `Makefile`
    - `chan.c`
    - `enc.c`
    - `main.c`
    - `read_write.c`
    - `sem_child.c`
    - `shared_memory.c`
    - `enc.h`
    - `read_write.h`
    - `shared_memory.h`
    - `README.md`

---

## How to Run the Program

1. **Building the Program:**  
   Using the provided `Makefile`, compile the program with the following command:

   ` make all `
This will create the executable files and the .o object files for the source code.

This will create the executable files and the .o object files for the source code.

2. **Running the Program:**  
   In the first terminal, run the `exe` program with the probability you want (in decimal form from 0 to 1), for example, `0.5`:
   `   ./exe 1 0.5`

This will start the program and it will wait for someone to write. It will also print the id of the shared memory segment it has attached to. The second argument (e.g., 1) indicates that this program will write first, meaning it is P1.

3. **Running Additional Processes:**
In a second terminal, run the sem_child program with the id printed by the previous exe execution:
`./sem_child <id> 0 4`

The first argument is the id that the child process will attach to.  
The second argument (`0`) indicates that this process will write second (meaning it is **P2**).  
The third argument (`4`) is the id of the specific process (explained below).

---

## Functionality of the Program

The main program creates and attaches multiple processes to a common **shared memory** segment. It creates 4 sets of semaphores, initializing them to 0. Then, the following processes are created:

- **P1 (id = 0):** Responsible for writing and reading data until the TERM message is received, after which it terminates.
- **Enc1 (id = 1):** Encodes the message using the MD5 function and checks whether the message was sent correctly.
- **Enc2 (id = 3):** Verifies that the message was sent correctly.
- **Chan (id = 2):** Introduces random errors into the message (adding `x` characters) based on the probability given by the user.

The processes transfer messages using semaphores, which cause the processes to "sleep" and "wake up" as needed for message passing.

The process flow can move messages from left to right and vice versa until the TERM termination message is given to P1, at which point the program stops. The semaphores ensure synchronization between the processes during the message transfer.

---

## Limitations of the Program

- If the message is corrupted during transfer, the program does not attempt to correct it. The message is received incorrectly.
- The program does not terminate after the first message.
- The program does not delete the shared memory segment after the program finishes.
