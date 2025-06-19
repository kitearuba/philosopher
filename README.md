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
- [Enum-Based Architecture](#enum-based-architecture)
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
- 📋 Logs are thread-safe and color-coded (up to 100 philosophers)
- 🧮 Max-meal detection handled via central monitor thread
- 💬 Actions are logged using clean `enum` states (`t_state`)
- ✅ All major functions return typed statuses (`t_status`)
- 🧼 Clean memory, no leaks (validated with Valgrind & sanitizers)

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
* Action logging is handled via `print_action()` which uses a clean `t_state` enum
* All major init and error-handling functions use `t_status` for explicit success/failure control

---

## ⚙️ Design Highlights

* 🍽 Fork grabbing order alternates to prevent deadlock
* 🧠 Philosophers may eat slightly beyond `max_meals` if already mid-cycle — this avoids starvation and is allowed
* 💀 Simulation end is **centralized in the monitor thread** (not in routines)
* 🧼 Memory and thread lifecycle fully controlled and leak-free
* 🔍 `safe_atoi()` is hardened to reject invalid inputs (non-digit, empty, signed, or overflow values)
* 🔒 Simulation refuses to start if any input is 0 or malformed, including the optional `[max_meals]` argument
* 🧩 `print_action()` is fully norm-compliant and uses helper functions to map states to strings and colors
* 🚦 No ternary operators, initializer arrays, or non-compliant structures — fully validated by Norminette

---

## 🧬 Enum-Based Architecture

To improve clarity, safety, and maintainability, this project uses two custom enums:

### `t_state` (Philosopher States)

```c
typedef enum e_state
{
	STATE_EATING,
	STATE_SLEEPING,
	STATE_THINKING,
	STATE_TAKEN_FORK,
	STATE_DIED
}	t_state;
```

Used throughout the simulation to represent philosopher actions. These states are:

* Logged via `print_action(philo, STATE_EATING);`
* Mapped to messages and colors using helper functions (`get_state_message()`, `get_state_color()`)
* Replace fragile string comparisons and reduce error risk

### `t_status` (Return Values)

```c
typedef enum e_status
{
	SUCCESS = 0,
	FAILURE = 1
}	t_status;
```

Used as return types for critical functions like:

* `init_simulation()`
* `parse_args()`
* `allocate_simulation_memory()`

This makes error handling clear and enforces consistent flow control.

> 🎯 The enum system improves code validation, avoids typos, and follows 42 Norms by avoiding string magic, ternaries, and array initializers in function bodies.

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
* ✅ Input parsing uses a strict custom `safe_atoi()` implementation that rejects non-numeric, negative, or malformed input — including leading signs (`+`, `-`) and overflow. The simulation will only start if all arguments are valid positive integers.

---

## ⚙️ Optional Macros

This project includes two **optional macros** in `philo.h` to control output behavior.

By **default**, they are set to:

```c
#define PHILO_COLOR_CAP     0
#define PHILO_PRINT_CAP     0
```

| Macro             | Purpose                                                             |
| ----------------- | ------------------------------------------------------------------- |
| `PHILO_COLOR_CAP` | Enables color-coded logs if `num_philo <= PHILO_COLOR_CAP`          |
| `PHILO_PRINT_CAP` | Enables a meal summary at the end if `num_philo <= PHILO_PRINT_CAP` |

> 🛠️ Evaluators can modify these macros during review if they want to see colored output or a simulation summary.
> ✅ They are **disabled by default** to ensure Deepthought compliance and clean log output.

---

## 🙌 Acknowledgments

* Thanks to 42 for teaching threads the hard way!
* Huge respect to everyone debugging mutexes at midnight
* Special thanks to Valgrind, AddressSanitizer, and custom `ft_usleep()` for keeping this clean and sharp
* Project rewritten with a focus on safety, readability, and full 42 Norm compliance using enums and strict function structure.

---

## 👨‍💻 Author

* **Christian (chrrodri)**
  GitHub: [@kitearuba](https://github.com/kitearuba)
