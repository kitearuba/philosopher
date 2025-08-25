---

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

---

## 📁 Project Structure

```
.
├── include/            # Header files (philo.h)
├── src/
│   ├── core/           # main.c
│   ├── init/           # init.c, safe_atoi.c
│   ├── simulation/     # routine.c, monitor.c, fork_handling.c, simulation_end.c, launch.c
│   ├── utils/          # print.c, ft_usleep.c, time.c, cleanup.c
├── Makefile
└── README.md
```

---

## 🛠 Compilation

Submission flags (Norm-only):

```make
CFLAGS = -Wall -Wextra -Werror
```

Development/testing flags:

```make
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined -O0
# CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -O2   # ThreadSanitizer
```

This project was tested at optimization levels `-O1`, `-O2`, and `-O3` without issues.
Early debugging started at `-O0` with sanitizers, then moved to higher optimizations once stable.

---

## 🚀 Usage

```bash
./philo number_of_philos time_to_die time_to_eat time_to_sleep [max_meals]
```

Example:

```bash
./philo 5 800 200 200 7
```

> 5 philosophers, die if they don’t eat in 800ms, eat/sleep for 200ms, stop when each eats 7 times.

---

## 🔍 How It Works

* **Threads**: one per philosopher + one monitor
* **Forks**: one mutex per fork
* **Monitor**: checks continuously for:

  * Death (`elapsed >= time_to_die`)
  * Completion (`total_fed == num_philo`)
* **Unified End Flag**: all threads respect `simulation_ended` (protected by `simulation_lock`)
* **Logging**: `print_action()` suppresses all prints after end, except the single death message

---

## ⚙️ Design Highlights

* 🍽 Alternating fork order prevents deadlock
* 🧠 **New in this version:** philosophers immediately stop once they’ve reached `max_meals`, even if others are mid-action
* 💀 Death and all-fed both funnel through **one centralized control method** (`end_simulation_*`)
* 🔒 Mutex discipline prevents race conditions that were found in early drafts
* 🧼 Memory and threads cleaned up in strict reverse order of initialization

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

During development, several issues were identified and fixed:

* **Race conditions**:

  * Earlier versions allowed philosophers to eat slightly beyond `max_meals`.
  * Fixed by adding `is_fed` checks *before taking forks* and exiting the routine loop once fed.
* **Unified termination**:

  * Death and max-meals are now controlled by the same logic (`simulation_end`), instead of separate ad-hoc flags.
* **Print suppression**:

  * Previously, philosophers could still print actions after the simulation had ended.
  * Now, `print_action()` enforces a final gate: only a death message may appear after end.
* **Testing methodology**:

  * The first README only mentioned Valgrind leak checks.
  * In this version, the program has been tested with **Valgrind, AddressSanitizer, UndefinedBehaviorSanitizer, and ThreadSanitizer**.
  * ThreadSanitizer initially showed data races; additional locks and `is_fed` gating fixed them.
* **Optimization levels**:

  * Verified under `-O1`, `-O2`, and `-O3`.
  * Some earlier issues only appeared when optimizations were enabled — now stable across all.

---

## 🔬 Testing & Debugging Notes

* ✅ **Valgrind**:

  ```bash
  valgrind --leak-check=full --show-leak-kinds=all ./philo 5 800 200 200
  ```

  → No leaks, no invalid memory usage.

* ✅ **Sanitizers**:

  * `-fsanitize=address,undefined` → caught invalid frees and undefined behavior early
  * `-fsanitize=thread` → exposed hidden race conditions, now fully resolved

* 🖥️ **Home computer issue**:
  ThreadSanitizer sometimes failed with:

  ```
  FATAL: ThreadSanitizer: unexpected memory mapping
  ```

  This was solved with **ASLR disabled**:

  ```bash
  setarch "$(uname -m)" -R ./philo args...
  ```

  On 42 school machines, ThreadSanitizer runs without this workaround.

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

### Verify all philosophers ate exactly N meals

```bash
setarch "$(uname -m)" -R ./philo 5 300 90 90 19 \
  | grep "is eating" | awk '{print $2}' | sort | uniq -c
```

Sample output:

```
     19 1
     19 2
     19 3
     19 4
     19 5
```

Confirms that each philosopher ate **exactly 19 times**, with no over-eating after end.

---

## 🙌 Acknowledgments

* 🕒 Countless tests with **Valgrind, sanitizers, and setarch**
* 💡 Thanks to the 42 community for debugging mutex madness at 3 AM
* ✨ Final version focuses on **clarity, strict Norm compliance, centralized control, and defense-ready reasoning**

---

## 👨‍💻 Author

**Christian (chrrodri)**
GitHub: [@kitearuba](https://github.com/kitearuba)

---
