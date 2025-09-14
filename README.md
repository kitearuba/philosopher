# 🧠 Philosophers - Dining Simulation (42 Project)

![Philo](https://img.shields.io/badge/Philosophers-42Project-blue?style=flat-square) ![C](https://img.shields.io/badge/Language-C-green?style=flat-square) ![Threads](https://img.shields.io/badge/Concurrency-Pthreads-yellow?style=flat-square)

This project simulates the classic **Dining Philosophers Problem** using **POSIX threads and mutexes**, as part of the 42 core curriculum. The goal is to create a deadlock-free, starvation-safe system where philosophers eat, sleep, and think — using shared forks.

> ✅ This implementation is the **mandatory multithreaded version** (pthreads).  
> ❌ No bonus (processes/semaphores) included.

---

## 📑 Table of Contents

* [Introduction](#introduction)
* [Features](#features)
* [Project Structure](#project-structure)
* [Compilation](#compilation)
* [Usage](#usage)
* [How It Works](#how-it-works)
* [Design Highlights](#design-highlights)
* [Locking Strategy](#locking-strategy)
* [Improvements Over Early Versions](#improvements-over-early-versions)
* [Testing & Debugging Notes](#testing--debugging-notes)
* [Test Scenarios](#test-scenarios)
* [Advanced Testing Examples](#advanced-testing-examples)
* [ThreadSanitizer Caveat](#threadsanitizer-caveat)
* [Acknowledgments](#acknowledgments)
* [Author](#author)

---

## 🧠 Introduction

Philosophers sit around a table, each needing two forks to eat. Forks are shared — leading to potential **deadlocks** or **starvation**. The simulation must:

* Avoid deadlocks
* Track each philosopher's state
* Exit cleanly when a death or *all philosophers fed* condition occurs
* Respect strict timing (death printed ≤10ms late)

---

## ✨ Features

* 🧵 Each philosopher is a `pthread`
* 🔐 One mutex per fork
* 🕐 Custom `ft_usleep()` allows early interruption and precise timing
* 📋 Thread-safe logging via a single `print_lock`
* 🧮 **Max-meal** tracking via monitor thread and `fed_lock`
* 💬 Action logging uses a clean `enum` (`t_state`) system
* ✅ Leak-free and race-free (tested with Valgrind & sanitizers)
* ♻️ Centralized cleanup split into small functions (Norm-compliant)

---

## 📁 Project Structure

```

.
├── include/            # Header files (philo.h)
├── src/
│   ├── core/           # main.c
│   ├── init/           # init.c, safe\_atoi.c
│   ├── simulation/     # routine.c, monitor.c, fork\_handling.c, simulation\_end.c, launch.c
│   ├── utils/          # print.c, ft\_usleep.c, time.c, cleanup.c
├── Makefile
└── README.md

````

---

## 🛠 Compilation

Submission flags (Norm-only):

```make
CFLAGS = -Wall -Wextra -Werror
````

Development/testing flags:

```make
# AddressSanitizer + UndefinedBehaviorSanitizer
make asan

# ThreadSanitizer
make debug
```

---

## 🚀 Usage

```bash
./philo number_of_philos time_to_die time_to_eat time_to_sleep [max_meals]
```

Example:

```bash
./philo 5 800 200 200 7
```

---

## 🔍 How It Works

* **Threads**: one per philosopher + one monitor
* **Forks**: one mutex per fork
* **Monitor**: checks continuously for:

  * Death (`elapsed >= time_to_die`)
  * Completion (`total_fed == num_philo`)
* **Unified End Flag**: all threads respect `simulation_ended`
* **Logging**: `print_action()` suppresses all prints after end, except the single death message

---

## ⚙️ Design Highlights

* 🍽 Alternating fork order prevents deadlock
* 🧠 Philosophers immediately stop once they’ve reached `max_meals`
* 💀 Death and all-fed both funnel through **centralized control** (`end_simulation_*`)
* 🔒 Mutex discipline prevents race conditions
* 🧼 Cleanup refactored into helpers → Norm-compliant and safe against partial inits

---

## 🔒 Locking Strategy

| Purpose         | Mutex Used        |
| --------------- | ----------------- |
| Printing logs   | `print_lock`      |
| End flag        | `simulation_lock` |
| Fork access     | One per fork      |
| Meal tracking   | `fed_lock`        |
| Per-philo state | `state_lock`      |

---

## 🔄 Improvements Over Early Versions

* **Race conditions**:

  * Fixed `max_meals` over-eating with `is_fed` checks.
* **Unified termination**:

  * Death and meals use one shared end flag.
* **Print suppression**:

  * No noisy prints after simulation ends.
* **Memory cleanup**:

  * Split into multiple helper functions to satisfy the 25-line Norm rule.
* **Testing**:

  * Stable across `-O1`, `-O2`, and `-O3`.
  * Verified with ASAN, UBSAN, and TSAN.

---

## 🔬 Testing & Debugging Notes

* ✅ **Valgrind** – no leaks or invalid memory.
* ✅ **ASAN/UBSAN** – clean under heavy stress.
* ✅ **TSAN** – no data races, but see [ThreadSanitizer Caveat](#threadsanitizer-caveat).

---

## 🧪 Test Scenarios

```bash
./philo 1 800 200 200        # 1 philosopher -> dies
./philo 5 800 200 200        # Runs until Ctrl+C
./philo 5 800 200 200 5      # Stops after all eat 5 meals
./philo 4 310 200 100        # Tight timing (some deaths)
./philo 200 800 200 200      # Stress test ~200 philosophers
```

---

## 📊 Advanced Testing Examples

Verify all philosophers ate exactly N meals:

```bash
./philo 5 300 90 90 19 \
  | grep "is eating" | awk '{print $2}' | sort | uniq -c
```

---

## ⚠️ ThreadSanitizer Caveat

When testing with **TSan** at very large philosopher counts (`N=100+`), the program may terminate prematurely.
This is **not a logic error**: ThreadSanitizer inflates per-thread memory usage, and `pthread_create` can fail when too many threads are requested.

### How to defend this during evaluation

* On normal builds (no sanitizers), `N=100+` works fine.
* Under TSan, failure is due to environment limits, not race conditions.
* To demonstrate correctness:

  * Run TSan with smaller `N` (20–50) — no races are reported.
  * Or adjust stack size limit before running:

    ```bash
    ulimit -s 65536
    make fclean && make debug
    ./philo 200 800 200 200
    ```

This is a **defense-ready point**: the code is race-free, Norm-compliant, and passes official tests. TSan big-N failures are an **environment artifact**.

---

## 🙌 Acknowledgments

* 🕒 Valgrind, sanitizers, LazyPhilosophersTester
* 💡 42 peers for mutex debugging discussions
* ✨ Final version is **clear, clean, Norm-compliant, and defense-ready**

---

## 👨‍💻 Author

**Christian (chrrodri)**
GitHub: [@kitearuba](https://github.com/kitearuba)

---
