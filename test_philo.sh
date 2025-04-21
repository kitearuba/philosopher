#!/bin/bash

# ==============================================================
# PHILO EDGE CASE TESTER
# Author: chrrodri (42 Barcelona)
# GitHub: https://github.com/kitearuba
# ==============================================================

EXEC=./philo
AUTO_MODE=false
RESULTS=()

if [[ "$1" == "--auto" ]]; then
  AUTO_MODE=true
fi

# Colors and symbols
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
BLUE="\033[34m"
RESET="\033[0m"
BOLD="\033[1m"
GREEN_CHECK="${GREEN}✔${RESET}"
RED_CROSS="${RED}✘${RESET}"

function test_case() {
  local description="$1"
  local command="$2"

  echo -e "${YELLOW}▶ $description${RESET}"
  eval "$command"
  local exit_code=$?

  local expected_exit=0
  case "$description" in
    "Missing arguments - should print error"*) expected_exit=1 ;;
    "Invalid input - non-numeric"*) expected_exit=1 ;;
    "Negative timing - should print error"*) expected_exit=1 ;;
    "Zero philosophers - invalid input"*) expected_exit=1 ;;
    "Standard 5 philosophers"*) expected_exit=124 ;;
    "500 philosophers"*) expected_exit=124 ;;
    "Zero meals - should exit immediately"*) expected_exit=0 ;;
  esac

  local is_expected=false
  if [[ "$description" == "1000 philosophers"* ]]; then
    if [[ $exit_code -eq 0 || $exit_code -eq 124 ]]; then
      is_expected=true
    fi
  elif [[ $exit_code -eq $expected_exit ]]; then
    is_expected=true
  fi

  local status=""
  local emoji="$RED_CROSS"
  if $is_expected; then
    status="${GREEN}OK${RESET}"
    emoji="$GREEN_CHECK"
  else
    status="${RED}FAIL${RESET} (Exit: $exit_code, Expected: $expected_exit)"
  fi

  RESULTS+=("${emoji} ${BOLD}${description}${RESET}\n    🔹 ${BOLD}Command:${RESET} ${command}\n    🔸 ${BOLD}Result:${RESET} ${status}")

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
#   VALIDATION TEST CASES
# ==========================
ORIGINAL_AUTO_MODE=$AUTO_MODE
AUTO_MODE=true

test_case "Zero meals - should exit immediately" "$EXEC 5 800 200 200 0"
test_case "Missing arguments - should print error" "$EXEC"
test_case "Invalid input - non-numeric" "$EXEC 5 800 abc 200"
test_case "Negative timing - should print error" "$EXEC 5 -800 200 200"
test_case "Zero philosophers - invalid input" "$EXEC 0 800 200 200"

AUTO_MODE=$ORIGINAL_AUTO_MODE

# ==========================
#   STRESS TEST CASES
# ==========================
test_case "Standard 5 philosophers (run for 4 seconds max)" "timeout 4s $EXEC 5 800 200 200"
test_case "5 philosophers, stop after 3 meals each" "$EXEC 5 800 200 200 3"
test_case "Tight timing (4 310 200 100) - might die" "$EXEC 4 310 200 100"
test_case "500 philosophers - output suppressed" "timeout 6s $EXEC 500 800 200 200"
test_case "1000 philosophers - bonus stress test" "timeout 6s $EXEC 1000 800 200 200"

# ==========================
#   VALGRIND TEST
# ==========================
echo -e "\n${BOLD}${BLUE}🔍 VALGRIND MEMORY LEAK TEST${RESET}"
LEAK_OUTPUT=$(valgrind --leak-check=full --show-leak-kinds=all $EXEC 5 800 200 200 3 2>&1)
LEAK_LINE=$(echo "$LEAK_OUTPUT" | grep "definitely lost")
if echo "$LEAK_LINE" | grep -q "0 bytes in 0 blocks"; then
  LEAK_STATUS="✔ No memory leaks detected (definitely lost = 0)"
else
  LEAK_COUNT=$(echo "$LEAK_LINE" | grep -oP '\d+(?= bytes in \d+ blocks)')
  LEAK_STATUS="✘ Memory leak detected: $LEAK_LINE\nLeaks Detected: $LEAK_COUNT bytes"
fi
echo "$LEAK_STATUS"
echo "$LEAK_OUTPUT"

# ==========================
#   TRAILING SPACES TEST
# ==========================
test_case "Trailing spaces after last argument - should print error" "$EXEC 5 800 200 200 3   "

# ==========================
#         SUMMARY
# ==========================
echo -e "\n${BOLD}${YELLOW}📋 TEST SUMMARY${RESET}"
echo -e "${BLUE}==============================================${RESET}"
PASS_COUNT=0
FAIL_COUNT=0
for result in "${RESULTS[@]}"; do
  echo -e "\n$result"
  if echo "$result" | grep -q "Result: OK"; then
    ((PASS_COUNT++))
  else
    ((FAIL_COUNT++))
  fi
done

echo -e "\n${BOLD}✅ Passed: $PASS_COUNT   ❌ Failed: $FAIL_COUNT${RESET}"
echo -e "\n${BOLD}${BLUE}🔍 Valgrind Leak Status:${RESET} (see above)"
echo -e "\n🎉 ${BOLD}${GREEN}All tests completed.${RESET}"
