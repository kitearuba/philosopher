#!/bin/bash

# =============================
# 🚀 PHILO EDGE CASE TESTER
# =============================
# This script tests all major edge cases and bonus scenarios
# for your 42 Philosophers project. Use it after compiling.

EXEC=./philo

# Colors for output
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
RESET="\033[0m"

function test_case() {
  echo -e "${YELLOW}▶ $1${RESET}"
  eval "$2"
  echo -e "${GREEN}--- END TEST ---${RESET}"
  echo -e "\nPress ENTER to continue, or ESC to exit..."
  read -rsn1 key
  if [[ $key == $'\e' ]]; then
    echo -e "${RED}Exiting test script.${RESET}"
    exit 1
  fi
  echo ""
}

# 1. ✅ One Philosopher (must die)
test_case "1 Philosopher - should die after taking one fork" "$EXEC 1 800 200 200"

# 2. ✅ Standard test (run for 3s only)
test_case "Standard 5 philosophers (run for 3 seconds max)" "timeout 3s $EXEC 5 800 200 200"

# 3. ✅ With Meal Limit
test_case "5 philosophers, stop after 3 meals each" "$EXEC 5 800 200 200 3"

# 4. ✅ Tight timing, should test precision
test_case "Tight timing (4 310 200 100) - might die" "$EXEC 4 310 200 100"

# 5. ✅ Zero meal limit, must exit instantly
test_case "Zero meals - should exit immediately" "$EXEC 5 800 200 200 0"

# 6. ❌ Missing arguments
test_case "Missing arguments - should print error" "$EXEC"

# 7. ❌ Invalid argument (non-numeric)
test_case "Invalid input - non-numeric" "$EXEC 5 800 abc 200"

# 8. ❌ Negative input
test_case "Negative timing - should print error" "$EXEC 5 -800 200 200"

# 9. 🔥 High philosopher count (stress test, capped output)
test_case "500 philosophers - output suppressed" "timeout 5s $EXEC 500 800 200 200"

# 10. 🔥 Ultra stress test (bonus level)
test_case "1000 philosophers - bonus stability test" "timeout 5s $EXEC 1000 800 200 200"

echo -e "${GREEN}✅ All tests completed.${RESET}"
