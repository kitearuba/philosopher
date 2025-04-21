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

# Colors and styles
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
BLUE="\033[34m"
CYAN="\033[36m"
RESET="\033[0m"
BOLD="\033[1m"
GREEN_CHECK="${GREEN}✔${RESET}"
RED_CROSS="${RED}✘${RESET}"

# Counter
TEST_NUM=1

function test_case() {
  local description="$1"
  local command="$2"

  if ! $AUTO_MODE && [[ "$description" != *"should print error"* && "$description" != *"invalid input"* ]]; then
    echo -e "
${YELLOW}Press ENTER to continue to test: ${BOLD}$description${RESET}"
    echo -e "🔹 Command: ${BOLD}$command${RESET}"
    read -rsn1
  fi


  echo -e "${YELLOW}▶ [$TEST_NUM] $description${RESET}"
  ((TEST_NUM++))

  eval "$command"
  local exit_code=$?

  local expected_exit=0
  case "$description" in
    *"should print error"*|*"invalid input"*|*"only spaces"*|*"Empty string"*|*"abc"*) expected_exit=1 ;;
    *"should print error"*|*"invalid input"*|*"only spaces"*|*"Empty string"*) expected_exit=1 ;;
    "Standard 5 philosophers"*) expected_exit=124 ;;
    "500 philosophers"*) expected_exit=124 ;;
    "Zero meals - should exit immediately"*) expected_exit=0 ;;
  esac

  local is_expected=false
  if [[ "$description" == "1000 philosophers"* ]]; then
    [[ $exit_code -eq 0 || $exit_code -eq 124 ]] && is_expected=true
  elif [[ $exit_code -eq $expected_exit ]]; then
    is_expected=true
  fi

  local status emoji
  if $is_expected; then
    status="${GREEN}OK${RESET}"
    emoji="$GREEN_CHECK"
  else
    status="${RED}FAIL${RESET} (Exit: $exit_code, Expected: $expected_exit)"
    emoji="$RED_CROSS"
  fi

  RESULTS+=("${emoji} ${BOLD}$description${RESET}\n    🔹 ${BOLD}Command:${RESET} $command\n    🔸 ${BOLD}Result:${RESET} $status")

  echo -e "${GREEN}--- END TEST ---${RESET}"
  if ! $AUTO_MODE; then
    echo -e "\nPress ENTER to continue, or ESC to exit..."
    read -rsn1 key
    [[ $key == $'\e' ]] && echo -e "${RED}Exiting test script.${RESET}" && exit 1
    echo ""
  fi
}

# ========== VALIDATION TESTS ==========
echo -e "
${BOLD}${BLUE}🔍 Starting Validation Tests...${RESET}
"
ORIGINAL_AUTO_MODE=$AUTO_MODE
AUTO_MODE=true

test_case "Zero meals - should exit immediately" "$EXEC 5 800 200 200 0"
echo -e "
🔹 Input: 5 800 200 200 0
"
test_case "Missing arguments - should print error" "$EXEC"
echo -e "
🔹 Input: (no arguments)
"
test_case "Invalid input - non-numeric" "$EXEC 5 800 abc 200"
echo -e "
🔹 Input: 5 800 abc 200
"
test_case "Negative timing - should print error" "$EXEC 5 -800 200 200"
echo -e "
🔹 Input: 5 -800 200 200
"
test_case "Zero philosophers - invalid input" "$EXEC 0 800 200 200"
echo -e "
🔹 Input: 0 800 200 200
"
test_case "Too many arguments - should print error" "$EXEC 5 800 200 200 3 4"
echo -e "
🔹 Input: 5 800 200 200 3 4
"
test_case "Arguments with letters and digits mixed - should print error" "$EXEC 5a 800 200 200"
echo -e "
🔹 Input: 5a 800 200 200
"
test_case "Arguments with only spaces - should print error" "$EXEC '   ' 800 200 200"
echo -e "
🔹 Input: '   ' 800 200 200
"
test_case "Empty string as argument - should print error" "$EXEC '' 800 200 200"
echo -e "
🔹 Input: '' 800 200 200
"

AUTO_MODE=$ORIGINAL_AUTO_MODE

# ======= STOP AFTER VALIDATION TESTS =======
echo -e "
${BOLD}${YELLOW}Validation tests completed. Press ENTER to continue with stress tests...${RESET}"
read -rsn1

# ========== STRESS TESTS ==============
echo -e "
${BOLD}${BLUE}⚙️  Starting Stress and Runtime Tests...${RESET}
"
test_case "Standard 5 philosophers (run for 4 seconds max)" "timeout 4s $EXEC 5 800 200 200"
test_case "5 philosophers, stop after 3 meals each" "$EXEC 5 800 200 200 3"
test_case "Tight timing (4 310 200 100) - might die" "$EXEC 4 310 200 100"
test_case "500 philosophers - output suppressed" "timeout 6s $EXEC 500 800 200 200"
test_case "1000 philosophers - bonus stress test" "timeout 6s $EXEC 1000 800 200 200"
test_case "Trailing spaces after last argument - should print error" "$EXEC 5 800 200 200 3   "

# ========== VALGRIND TEST =============
echo -e "\n${BOLD}${CYAN}🔍 VALGRIND MEMORY LEAK TEST${RESET}"
echo -e "${YELLOW}⚠ Only for leak checking, not timing.${RESET}"

LEAK_OUTPUT=$(valgrind --leak-check=full --show-leak-kinds=all $EXEC 5 800 200 200 3 2>&1)
LEAK_LINE=$(echo "$LEAK_OUTPUT" | grep "definitely lost")
if echo "$LEAK_LINE" | grep -q "0 bytes in 0 blocks"; then
  LEAK_STATUS="✔ No memory leaks detected (definitely lost = 0)"
else
  LEAK_COUNT=$(echo "$LEAK_LINE" | grep -oP '\\d+(?= bytes in \\d+ blocks)')
  LEAK_STATUS="✘ Memory leak detected: $LEAK_LINE\nLeaks Detected: ${LEAK_COUNT} bytes"
  echo "$LEAK_OUTPUT"
fi

# ========== SUMMARY ====================
echo -e "\n${BOLD}${YELLOW}📋 TEST SUMMARY${RESET}"
echo -e "${BLUE}==============================================${RESET}"

PASS_COUNT=0
FAIL_COUNT=0
VALIDATION_HEADER_SHOWN=false
STRESS_HEADER_SHOWN=false
COUNT=1

for result in "${RESULTS[@]}"; do
  if echo "$result" | grep -q "should print error\|invalid input\|Zero meals"; then
    if [ "$VALIDATION_HEADER_SHOWN" = false ]; then
      echo -e "\n${BLUE}--- Input Validation Tests ---${RESET}"
      VALIDATION_HEADER_SHOWN=true
    fi
  else
    if [ "$STRESS_HEADER_SHOWN" = false ]; then
      echo -e "\n${BLUE}--- Stress & Runtime Tests ---${RESET}"
      STRESS_HEADER_SHOWN=true
    fi
  fi

  echo -e "\n[$COUNT] $result"
  ((COUNT++))
  if echo "$result" | grep -q "🔸 .*OK"; then
    ((PASS_COUNT++))
  else
    ((FAIL_COUNT++))
  fi

  sleep 0.1

done

echo -e "\n${BOLD}✅ Passed: $PASS_COUNT   ❌ Failed: $FAIL_COUNT${RESET}"
echo -e "\n${BOLD}${CYAN}🔍 Valgrind Leak Status:${RESET} $LEAK_STATUS"
echo -e "\n🎉 ${BOLD}${GREEN}All tests completed.${RESET}"
