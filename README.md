---
# 🌈 Philosophers - The Dining Simulation

![Philo](https://img.shields.io/badge/Philosophers-42Project-blue?style=flat-square) ![C Programming](https://img.shields.io/badge/Language-C-green?style=flat-square) ![Threads](https://img.shields.io/badge/Concurrency-Pthreads-yellow?style=flat-square) ![42 Network](https://img.shields.io/badge/42Network-Philo-lightblue?style=flat-square)

**Philosophers** is a concurrency simulation project from the **42 School curriculum**. It challenges students to solve the classic "Dining Philosophers Problem" using **threads**, **mutexes**, and precise **timing**, while strictly adhering to the **42 Norm**.

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
- No philosopher dies unless expected.
- Simulation ends cleanly.
- Memory and thread management is 100% safe.

---

## 💡 Features

### ✅ Mandatory
- ✉ Multiple philosophers running in parallel
- 🧒 Fork sharing with mutexes
- ⏳ Accurate timing for eating, sleeping, and death
- 📅 Stop simulation when a philosopher dies
- 📊 Optional argument to stop after `N` meals per philosopher
- 💪 No data races or undefined behavior

### ✨ Bonus (Optional)
- Handling 1000+ philosophers efficiently
- Logging toggles for performance testing
- Custom test script with delays between tests

---

## 📁 Project Structure

```bash
.
├── include/            # Header files (structs, prototypes, macros)
├── src/
│   ├── core/           # main.c, simulation control
│   ├── init/           # parsing, memory setup
│   ├── routine/        # philosopher behaviors
│   ├── monitor/        # observer thread for death/meals
│   ├── utils/          # time utils, actions, printing
├── Makefile            # Norm-compliant compilation
├── test.sh             # Custom test runner
└── README.md           # This file :)
```

---

## 🔧 Installation & Compilation

```bash
git clone https://github.com/kitearuba/philo.git
cd philo
make
```

This builds the `philo` executable using `-pthread` and flags suitable for 42 evaluation.

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

### Output:
```
112 1 has taken a fork
113 1 has taken a fork
113 1 is eating
...
800 3 died
```

---

## 🕵️ How It Works (Simple Terms)

- Each philosopher is a **thread**.
- They use **mutexes** (forks) to eat.
- A **monitor thread** watches everyone:
  - If someone doesn't eat in time → they die → simulation ends.
  - If everyone eats `N` times → simulation ends.
- A shared `simulation_ended` flag tells threads when to stop.

---

## 🌐 Project Highlights

| Topic              | Description                                       |
|-------------------|---------------------------------------------------|
| Threads           | One per philosopher + one monitor                 |
| Mutexes           | One per fork + print/death/fed/sim flags          |
| Timing            | Uses `gettimeofday` and custom `usleep` wrapper   |
| Exit Logic        | Unified via `simulation_ended` flag               |
| Memory Safety     | Valgrind and ASan clean (no leaks or overflows)   |

---

## ⚖️ Test Scenarios

```bash
./philo 1 800 200 200       # Should die (only one fork)
./philo 5 800 200 200       # Should run forever
./philo 5 800 200 200 7     # Should stop cleanly after 7 meals each
./philo 4 310 200 100       # May die (tight timing)
./philo 1000 800 200 200    # Stress test, should stay stable
```

---

## 🙌 Acknowledgments

- Thanks to **42 School** for this mind-bending project.
- Cheers to **everyone struggling with deadlocks and timing bugs** — you’re not alone!
- Gratitude to **Valgrind** and **AddressSanitizer** for saving our brains.

---

## 👨‍💻 Author

- **Christian (chrrodri)**  
  GitHub: [@kitearuba](https://github.com/kitearuba)

