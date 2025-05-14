# 🧠 Philosophers - Dining Simulation (42 Project)

![Philo](https://img.shields.io/badge/Philosophers-42Project-blue?style=flat-square) ![C](https://img.shields.io/badge/Language-C-green?style=flat-square) ![Threads](https://img.shields.io/badge/Concurrency-Pthreads-yellow?style=flat-square)

This project simulates the famous **Dining Philosophers Problem** using **POSIX threads and mutexes**, as part of the 42 core curriculum. The goal is to create a deadlock-free, starvation-safe system where philosophers eat, sleep, and think — using shared forks.

> ✅ This implementation is focused on the **mandatory multithreaded version**.  
> ❌ No bonus (processes/semaphores) included.

---

## 📑 Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Project Structure](#project-structure)
- [Compilation](#compilation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Design Highlights](#design-highlights)
- [Locking Strategy](#locking-strategy)
- [Test Scenarios](#test-scenarios)
- [Testing Notes](#testing-notes)
- [Optional Macros](#optional-macros)
- [Acknowledgments](#acknowledgments)
- [Author](#author)

---

## 🧠 Introduction

Philosophers sit around a table, each needing two forks to eat. But forks are shared — leading to potential **deadlocks** or **starvation**. Your job is to design a simulation that:

- Avoids deadlocks  
- Tracks each philosopher's status  
- Exits cleanly when a death or max-meal condition occurs  
- Respects tight timing constraints (death must print within 10ms)

---

## ✨ Features

- 🧵 Multithreaded philosophers via `pthread_create`
- 🔐 Forks are protected with individual mutexes
- 🕐 `ft_usleep` offers responsive sleep and early exit
- 🧮 Max-meal detection handled via central monitor
- 🧼 Clean memory, no leaks (validated with Valgrind & sanitizers)
- 📋 Logs are thread-safe and color-coded (up to 100 philosophers)
- 🛠️ Optional macros allow toggling log verbosity

---

## 📁 Project Structure

```bash
.
├── include/            # Header files (philo.h)
├── src/
│   ├── core/           # main.c
│   ├── init/           # init.c, safe_atoi.c
│   ├── simulation/     # routine.c, monitor.c, fork_handling.c, simulation_end.c
│   ├── utils/          # print.c, ft_usleep.c, time.c, cleanup.c
├── Makefile
└── README.md
````

---

## 🛠 Compilation

Use only the Norm-compliant flags for submission:

```make
CFLAGS = -Wall -Wextra -Werror
```

During development, you can optionally enable:

```make
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined -O0
```

> These flags enable AddressSanitizer and debugging (recommended for development only).

---

## 🚀 Usage

```bash
./philo number_of_philos time_to_die time_to_eat time_to_sleep [max_meals]
```

### Example:

```bash
./philo 5 800 200 200 7
```

> 5 philosophers, die if they don't eat in 800ms, eat/sleep for 200ms, simulation ends after each eats 7 times.

**Log Output:**

```
113 1 has taken a fork  
113 1 is eating  
...
800 3 died
```

---

## 🔍 How It Works

* Each philosopher is a thread
* Each fork is a mutex
* A monitor thread checks:

  * Has anyone starved? → Ends simulation
  * Has everyone eaten enough? → Ends simulation
* All threads use a shared, mutex-protected `simulation_ended` flag
* Death messages are printed exactly once, on time

---

## ⚙️ Design Highlights

* 🍽 Fork grabbing order alternates to prevent deadlock
* 🧠 Philosophers may eat slightly beyond `max_meals` if already mid-cycle — this avoids starvation and is allowed
* 💀 Simulation end is **centralized in the monitor thread** (not in routines)
* 🧼 Memory and thread lifecycle fully controlled and leak-free

---

## 🔒 Locking Strategy

| Purpose         | Mutex Used         |
| --------------- | ------------------ |
| Printing logs   | `print_lock`       |
| Shared sim flag | `simulation_lock`  |
| Fork access     | One mutex per fork |
| Meal tracking   | `fed_lock`         |
| Death message   | `death_print_lock` |

---

## 🧪 Test Scenarios

```bash
./philo 1 800 200 200       # Dies (one fork)
./philo 5 800 200 200       # Runs until Ctrl+C
./philo 5 800 200 200 5     # Stops after all eat 5 times
./philo 4 310 200 100       # Risky (tight timing)
./philo 200 800 200 200     # Stable limit (~200 philosophers)
./philo 500 800 200 200     # May work, not always reliable
./philo 1000 800 200 200    # Not recommended (timing issues)
```

> ⚠️ **Note:** Logs show accurate behavior even in tight timing. Philosophers are not forcefully blocked from re-eating after max meals to reduce starvation risk.

---

## 🔬 Testing Notes

* ✅ Used `valgrind --leak-check=full --show-leak-kinds=all` to validate all memory operations
* ✅ Also tested with `-fsanitize=address,undefined` and `-g` for early bug detection
* 🚫 Did **not** use `valgrind` for performance testing, as it introduces major delays and false starvation
* ✅ Input parsing includes a check to **strip trailing whitespace and malformed input** to prevent leaks or logic errors

---

## ⚙️ Optional Macros

This project includes two macros to limit output verbosity based on philosopher count:

```c
#define PHILO_COLOR_CAP  100
#define PHILO_PRINT_CAP  100
```

| Macro             | Purpose                                                  |
| ----------------- | -------------------------------------------------------- |
| `PHILO_COLOR_CAP` | Disables colored output if `num_philo > PHILO_COLOR_CAP` |
| `PHILO_PRINT_CAP` | Skips meal summary if `num_philo > PHILO_PRINT_CAP`      |

These are defined in `philo.h` and can be adjusted manually to fit your screen/logging preferences.

---

## 🙌 Acknowledgments

* Thanks to 42 for teaching threads the hard way!
* Huge respect to everyone debugging mutexes at midnight
* Special thanks to Valgrind, AddressSanitizer, and custom `ft_usleep()` for keeping this clean and sharp

---

## 👨‍💻 Author

* **Christian (chrrodri)**
  GitHub: [@kitearuba](https://github.com/kitearuba)
