# 🌈 Philosophers - The Dining Simulation

![Philo](https://img.shields.io/badge/Philosophers-42Project-blue?style=flat-square) ![C Programming](https://img.shields.io/badge/Language-C-green?style=flat-square) ![Threads](https://img.shields.io/badge/Concurrency-Pthreads-yellow?style=flat-square) ![42 Network](https://img.shields.io/badge/42Network-Philo-lightblue?style=flat-square)

**Philosophers** is a concurrency simulation project from the **42 School curriculum**. It challenges students to solve the classic "Dining Philosophers Problem" using **threads**, **mutexes**, and precise **timing**, while strictly adhering to the **42 Norm** and project constraints.

> 🧩 This implementation includes only the **mandatory multithreaded version** (no processes/semaphores).  
> ✅ Fully Norm-compliant, clean shutdown, and highly stable — even under tight timing and 1000+ philosophers.

---

## 📑 Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Project Structure](#project-structure)
- [Installation & Compilation](#installation--compilation)
- [Usage](#usage)
- [How It Works (Simple Terms)](#-how-it-works-simple-terms)
- [Technical Design Decisions](#️-technical-design-decisions)
- [Locking Strategy](#-locking-strategy)
- [Test Scenarios](#-test-scenarios)
- [Acknowledgments](#-acknowledgments)
- [Author](#-author)

---

## 📚 Introduction

This project simulates a group of philosophers sitting at a table who:
1. Think  
2. Take forks  
3. Eat  
4. Sleep  
5. Repeat  

However, forks are shared, and if not synchronized properly, philosophers may **starve**, **deadlock**, or cause **race conditions**. Your goal is to prevent that — with style and performance.

This implementation guarantees:
- No unexpected deaths
- Accurate max meal tracking
- Clean simulation exit and reporting
- Valgrind-clean and Norm-safe

---

## 💡 Features

### ✅ Mandatory Goals Met
- 🧵 Multithreading with `pthread_create`
- 🔐 Forks protected with `pthread_mutex`
- ⏱ Custom `ft_usleep()` for responsive sleep + interrupt
- 💀 Stops immediately on death, or after all meals are completed
- 🧼 Clean memory and thread handling

### ❌ Not Implemented (Bonus)
- No process-based version
- No CLI flags or GUI/log expansion
- Not tested with semaphores (bonus)

---

## 📁 Project Structure

```bash
.
├── include/            # Header files (structs, prototypes, macros)
├── src/
│   ├── core/           # main.c
│   ├── init/           # parse_args, safe_atoi, memory allocation
│   ├── simulation/     # routine.c, monitor.c, simulation_end.c
│   ├── utils/          # print.c, time.c, cleanup.c, ft_usleep.c
├── Makefile
└── README.md
````

---

## 🔧 Installation & Compilation

```bash
git clone https://github.com/kitearuba/philo.git
cd philo
make
```

* Flags: `-Wall -Wextra -Werror -pthread`
* Targets: `all`, `clean`, `fclean`, `re`

---

## 🚀 Usage

```bash
./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]
```

### Example:

```bash
./philo 5 800 200 200 7
```

> Run with 5 philosophers who must each eat 7 times. If one doesn't eat within 800ms, they die.

### Log Format:

```
113 1 has taken a fork
113 1 is eating
800 3 died
```

> ℹ️ Log is formatted as: `timestamp philosopher_id action`
> 🕐 Death must be printed **within 10ms** of the actual timeout.

---

## 🧠 How It Works (Simple Terms)

* Each philosopher is a **thread**
* Forks are **mutexes** shared between neighbors
* One **monitor thread** constantly checks:

  * If any philosopher starved → ends simulation
  * If all philosophers reached `max_meals` → ends simulation
* Each philosopher has a **timestamp** of their last meal
* When the `simulation_ended` flag is set, all threads stop cleanly

---

## ⚙️ Technical Design Decisions

* 🧠 Meal completion is tracked per philosopher via `is_fed` flags
* 🎯 Simulation only ends via the **monitor thread**
* ⏲️ Custom `ft_usleep` supports clean early exit checks
* ♻️ Fed philosophers **continue looping** to avoid starvation patterns
* 🧵 Fork locking is ordered to prevent deadlocks (left vs right first)
* 💬 All log output is mutex-protected for terminal cleanliness

---

## 🔒 Locking Strategy

| Purpose            | Mutex Used         |
| ------------------ | ------------------ |
| Printing messages  | `print_lock`       |
| Ending simulation  | `simulation_lock`  |
| Fork access        | One mutex per fork |
| Updating fed count | `fed_lock`         |
| Death logging      | `death_print_lock` |

---

## 🧪 Test Scenarios

```bash
./philo 1 800 200 200       # Dies (one fork)
./philo 5 800 200 200       # Runs until Ctrl+C
./philo 5 800 200 200 5     # Stops after all eat 5 times
./philo 4 310 200 100       # Likely starvation (tight timing)
./philo 1000 800 200 200    # Stress test (now stable!)
```

> ℹ️ If simulation stops after max\_meals, some philosophers may eat one extra time if they were mid-cycle — this is expected and allowed by the subject.

---

## 🙌 Acknowledgments

* Thanks to **42 School** for the mental workout
* Props to **everyone debugging segfaults at 3AM**
* 🧹 Powered by `Valgrind`, `ASan`, and C patience

---

## 👨‍💻 Author

* **Christian (chrrodri)**
  GitHub: [@kitearuba](https://github.com/kitearuba)
