#!/bin/bash

# =============================
# 🚀 PHILO EDGE CASE TESTER
# =============================
# This script tests edge cases for the 42 Philosophers project.

EXEC=./philo
AUTO_MODE=false
RESULTS=()

# Optional --auto mode for non-interactive use
if [[ "$1" == "--auto" ]]; then
  AUTO_MODE=true
fi

# Color & style
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
RESET="\033[0m"
BOLD="\033[1m"

# Function to log and evaluate test cases
function test_case() {
  local description="$1"
  local command="$2"

  echo -e "${YELLOW}▶ $description${RESET}"
  eval "$command"
  local exit_code=$?

  local expected_exit=0

  # Set expected exit codes based on test description
  case "$description" in
    "Missing arguments - should print error"*) expected_exit=1 ;;
    "Invalid input - non-numeric"*) expected_exit=1 ;;
    "Negative timing - should print error"*) expected_exit=1 ;;
    "Zero philosophers - invalid input"*) expected_exit=1 ;;
    "Standard 5 philosophers"*) expected_exit=124 ;;
    "500 philosophers"*) expected_exit=124 ;;
    "1000 philosophers"*) expected_exit=124 ;;
    "Zero meals - should exit immediately"*) expected_exit=0 ;;
  esac

  local status=""
  local emoji="❌"
  if [[ $exit_code -eq $expected_exit ]]; then
    status="${GREEN}OK${RESET}"
    emoji="✅"
  else
    status="${RED}FAIL${RESET} (Exit: $exit_code, Expected: $expected_exit)"
  fi

  RESULTS+=("${emoji} ${description}${RESET}\n    🔹 ${BOLD}Command:${RESET} ${command}\n    🔸 ${BOLD}Result:${RESET} ${status}")

  echo -e "${GREEN}--- END TEST ---${RESET}"
  if ! $AUTO_MODE; then
    echo -e "\nPress ENTER to continue, or ESC to exit..."
    read -rsn1 key
    if [[ $key == $'\e' ]]; then
      echo -e "${RED}Exiting test script.${RESET}"
      exit 1
    fi
    echo ""
  fi
}

# ==========================
#        TEST CASES
# ==========================

test_case "1 Philosopher - should die after taking one fork" "$EXEC 1 800 200 200"
test_case "Standard 5 philosophers (run for 3 seconds max)" "timeout 3s $EXEC 5 800 200 200"
test_case "5 philosophers, stop after 3 meals each" "$EXEC 5 800 200 200 3"
test_case "Tight timing (4 310 200 100) - might die" "$EXEC 4 310 200 100"
test_case "Zero meals - should exit immediately" "$EXEC 5 800 200 200 0"
test_case "Missing arguments - should print error" "$EXEC"
test_case "Invalid input - non-numeric" "$EXEC 5 800 abc 200"
test_case "Negative timing - should print error" "$EXEC 5 -800 200 200"
test_case "Zero philosophers - invalid input" "$EXEC 0 800 200 200"
test_case "500 philosophers - output suppressed" "timeout 5s $EXEC 500 800 200 200"
test_case "1000 philosophers - bonus stability test" "timeout 5s $EXEC 1000 800 200 200"

# ==========================
#         SUMMARY
# ==========================
echo -e "\n${YELLOW}📋 TEST SUMMARY${RESET}"
for result in "${RESULTS[@]}"; do
  echo -e "\n$result"
done
echo -e "\n🎉 ${BOLD}${GREEN}All tests completed.${RESET}"
