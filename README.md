<h1 align="center">Philosophers Dining</h1>
<p align="center">
  <img width=150 height=100 src="https://media1.tenor.com/m/z40WAPqRtecAAAAd/winnie-the-pooh-hungry.gif">
  <img width=150 height=100 src="https://media1.tenor.com/m/SHfPQLDYXqgAAAAd/winnie-the-oooh-sleep.gif">
  <img width=200 height=100 src="https://media1.tenor.com/m/1KrRCz7jr9oAAAAC/winnie-the-pooh-think-think.gif">
</p>

---

## 📚 Project Overview

The **Philosophers Dining** project is a classical concurrency problem in computer science. It simulates a scenario where several philosophers sit around a table, each alternating between thinking and eating. Between each pair of philosophers is a single fork, and a philosopher needs **both forks** (the one on the left and the one on the right) to eat.

The goal is to implement a program that simulates this behavior using **processes or threads** with mutexes to avoid **deadlocks** and **race conditions**.
---

## 🎯 Objectives

- Understand and implement synchronization mechanisms to handle resource sharing.  
- Prevent deadlocks and starvation, ensuring every philosopher can eat.  
- Use system calls and primitives for inter-process or inter-thread communication.  
- Implement timed actions and state monitoring.  
- Handle program termination and cleanup gracefully.

---

## 📝 Project Requirements
- Philosophers should be represented by threads or processes.  
- Each philosopher cycles through:  
  - **Thinking**   
  - **Taking forks (left and right)**  
  - **Eating** 
  - **Sleeping**  
- The program should output timestamps and state changes for each philosopher (e.g., "Philosopher 3 has taken a fork", "Philosopher 2 is eating").  
- Use synchronization to avoid:  
  - Deadlocks (where philosophers wait forever).  
  - Starvation (where a philosopher never gets to eat).  
- Support a specified number of philosophers as an argument.  
- Implement rules for philosophers dying if they don’t eat within a certain time.  
- Provide clean exit handling on completion or error.

---

## ⚙️ Usage

```bash
make
```

Number of Philosophers are restricted to 200 to increase the limit:
```
make re limit=[NUM]
```
# Run the program
./philo 'number_of_philosophers' 'time_to_die' 'time_to_eat' 'time_to_sleep' 'number_of_times_each_philosopher_must_eat (optional)'
