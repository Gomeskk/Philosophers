# Philosophers - 42 Project

## Introduction

The **Philosophers** project at 42 introduces students to concurrent programming using threads and synchronization mechanisms in C. The goal is to solve the classic **Dining Philosophers problem**, a well-known problem in computer science that demonstrates **deadlock, race conditions, and resource synchronization**.

## Concept

The project requires implementing a simulation where philosophers sit around a table and attempt to eat using shared forks. The key challenges include:

  - **Thread management** using ```pthread```.

  - **Mutex synchronization** to avoid race conditions.

  - **Avoiding deadlocks** using proper resource allocation strategies.

  - **Handling starvation** to ensure all philosophers get to eat.

Each philosopher must follow this cycle:

**take forks → eat → put down forks → sleep → think → repeat**.

Key constraints:

  - A philosopher **must have two forks** to eat.

  - Philosophers should avoid **deadlocks** and **resource starvation**.

  - The program must use **mutexes** and **threads** for synchronization.

## Mandatory Requirements

Your program must:

  - Create **N philosophers**, each represented as a thread.

  - Use **mutexes** to ensure that forks are picked up and released safely.

  - Prevent **race conditions** when philosophers access shared resources.

  - Ensure the simulation stops when:

    - A philosopher does not eat within the given time limit.

    - The simulation reaches its defined execution time (if applicable).

### Input Arguments:

Your program should take the following arguments:

```console
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```console
./philo 5 800 200 200 7
```

  - ```5``` → Number of philosophers.

  - ```800``` → Time (in ms) before a philosopher dies if they don’t eat.

  - ```200``` → Time (in ms) a philosopher takes to eat.

  - ```200``` → Time (in ms) a philosopher takes to sleep.

  - ```7``` → Number of times all the philosophers need to eat before terminating the program.

## Implementation Details

### Threads and Mutexes

  - Each philosopher is represented as a **separate thread**.

  - A **mutex** is used to lock the forks to prevent simultaneous access by multiple threads.

  - A **global mutex** is often used to protect shared resources like printing or checking if a philosopher has died.

### Synchronization Mechanisms

  - **Mutex locks** prevent race conditions when philosophers pick up or put down forks.

  - **Precise timing** is needed to ensure accurate simulation, typically using ```gettimeofday()``` or ```usleep()```.

  - **Avoiding deadlocks** can be done using even/odd philosopher ordering or a hierarchy strategy.

### Fork Handling Strategies

  - **Odd/even approach:** Philosophers with even IDs pick up the right fork first, while those with odd IDs pick up the left fork first.

  - **Waiter approach:** Introduce a controller that grants permission before a philosopher picks up a fork.

## Bonus Features

For the **philo_bonus** program:

  - Implement the solution using **processes and semaphores** (```sem_t```).

  - Use **message queues** for proper inter-process communication.

### Compilation and Usage

To compile the program, run:

```console
make
```

To execute:

```console
./philo 5 800 200 200
```

To clean up object files:

```console
make clean
```

## Common Pitfalls

  - $\color{crimson}{\textbf{Race Conditions}}$ → Ensure proper mutex locking to avoid inconsistent states.

  - $\color{crimson}{\textbf{Deadlocks}}$ → Make sure that all philosophers don’t block each other indefinitely.

  - $\color{crimson}{\textbf{Starvation}}$ → Balance fork acquisition so that all philosophers get a chance to eat.

  - $\color{crimson}{\textbf{Incorrect Timing}}$ → Use precise timing functions to match expected behavior.

  - $\color{crimson}{\textbf{Overuse of usleep()}}$ → Avoid using long sleeps that cause delays in checking critical conditions.

## Conclusion

The $\color{RoyalBlue}{\textbf{Philosophers}}$ project is an excellent exercise in $\color{RoyalBlue}{\textbf{multithreading, synchronization, and concurrency control}}$. It provides practical experience in $\color{RoyalBlue}{\textbf{avoiding deadlocks, managing shared resources, and optimizing thread performance}}$, essential skills for real-world systems programming.

