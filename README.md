Thanks for the reminder! Here's the updated `README.md`, clearly stating that the implementation covers **only the mandatory part** of the project — with improvements for stability, but **not bonus features** like process-based handling or semaphores.

---

```markdown
# 🌈 Philosophers - The Dining Simulation

![Philo](https://img.shields.io/badge/Philosophers-42Project-blue?style=flat-square) ![C Programming](https://img.shields.io/badge/Language-C-green?style=flat-square) ![Threads](https://img.shields.io/badge/Concurrency-Pthreads-yellow?style=flat-square) ![42 Network](https://img.shields.io/badge/42Network-Philo-lightblue?style=flat-square)

**Philosophers** is a concurrency simulation project from the **42 School curriculum**. It challenges students to solve the classic "Dining Philosophers Problem" using **threads**, **mutexes**, and precise **timing**, while strictly adhering to the **42 Norm** and **project constraints**.

> 🧩 This implementation includes **only the mandatory part** of the project (multithreaded version with mutexes). Bonus features such as process-based concurrency or semaphores are **not** implemented here.

---

## 📚 Introduction

The project simulates a group of philosophers sitting at a table who:
1. Think  
2. Take forks  
3. Eat  
4. Sleep  
5. Repeat  

However, they must share forks, and if not synchronized correctly, they can **starve**, cause **deadlocks**, or lead to **data races**. Your job is to prevent that.

This implementation ensures:
- No philosopher dies unexpectedly
- Simulation ends cleanly when it should
- Memory and thread management is leak-free and race-free
- Consistent output even with 1000+ philosophers

> ⚠️ This project strictly forbids the use of **global variables**.

---

## 💡 Features

### ✅ Mandatory
- ✉ Multiple philosophers running in parallel (via `pthread_create`)
- 🧒 Fork sharing protected by `pthread_mutex`
- ⏳ Accurate timing using `gettimeofday()` and custom `ft_usleep`
- 📅 Simulation ends if a philosopher dies or if all eat `N` times
- 📊 Clean logging format: timestamps and philosopher ID
- 💪 No memory leaks or race conditions (validated by Valgrind & ASan)

### ⚠️ Not Included (Bonus)
- No `fork()` or `semaphores` (process-based version)
- No optional features like CLI toggles or advanced logs
- Not tested for MacOS semaphore behavior (Linux only)

---

## 📁 Project Structure

```bash
.
├── include/            # Header files (structs, prototypes, macros)
├── src/
│   ├── core/           # main.c (program entry point)
│   ├── init/           # Argument parsing, safe_atoi, memory allocation
│   ├── simulation/     # Main simulation logic: routine, monitor, simulation_end
│   ├── utils/          # Utility functions: print, time, cleanup, ft_usleep
├── Makefile            # Norm-compliant compilation
└── README.md           # This file :)
```

---

## 🔧 Installation & Compilation

```bash
git clone https://github.com/kitearuba/philo.git
cd philo
make
```

This builds the `philo` executable using `-pthread` and flags required by 42:
- `-Wall -Wextra -Werror`
- Makefile targets: `all`, `clean`, `fclean`, `re`

---

## 🚀 Usage

```bash
./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]
```

### Example:
```bash
./philo 5 800 200 200 7
```
> 5 philosophers, die if not eaten in 800ms, eat for 200ms, sleep for 200ms, simulation stops after each eats 7 times.

### Log Output:
```
113 1 has taken a fork
113 1 has taken a fork
113 1 is eating
...
800 3 died
```
> All logs follow this strict format: `timestamp_in_ms philosopher_number action`

> ⚠️ The program must log a death within **10ms** of its occurrence.

---

## 🕵️ How It Works (Simple Terms)

- Each philosopher is a **thread**
- They use **mutexes** (forks) to eat
- A **monitor thread** watches everyone:
  - If someone doesn't eat in time → they die → simulation ends
  - If everyone eats `N` times → simulation ends
- A shared `simulation_ended` flag tells threads when to stop
- A `death_print_lock` ensures the death message is printed **only once**, even under high load

---

## 🌐 Project Highlights

| Topic              | Description                                       |
|-------------------|---------------------------------------------------|
| Threads           | One per philosopher + one monitor                 |
| Mutexes           | One per fork + print/death/fed/sim flags          |
| Timing            | Uses `gettimeofday()` and custom `ft_usleep()`    |
| Exit Logic        | Controlled by `simulation_ended` flag             |
| Stability         | Handles 1000+ philosophers without crashing       |
| Memory Safety     | Valgrind and ASan clean (no leaks or overflows)   |

---

## ⚖️ Test Scenarios

```bash
./philo 1 800 200 200       # Should die (only one fork)
./philo 5 800 200 200       # Should run forever
./philo 5 800 200 200 7     # Should stop cleanly after 7 meals each
./philo 4 310 200 100       # May die (tight timing)
./philo 1000 800 200 200    # Stress test, now handled correctly
```

---

## 🙌 Acknowledgments

- Thanks to **42 School** for this mind-bending project
- Cheers to **everyone debugging timing bugs at 2AM** — you're not alone!
- Shoutout to **Valgrind**, **AddressSanitizer**, and `ft_usleep()` for keeping it clean and accurate

---

## 👨‍💻 Author

- **Christian (chrrodri)**  
  GitHub: [@kitearuba](https://github.com/kitearuba)
```

Would you like this as a downloadable `.md` file or added directly to your repo’s README?
