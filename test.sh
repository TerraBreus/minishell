#!/bin/bash

# Clear previous results
echo "Minishell Tokenization Test Results" > results.txt
echo "==================================" >> results.txt
echo "" >> results.txt

# Test counter
test_num=1

run_test() {
    echo "Test $test_num: $1" >> results.txt
    echo "----------------" >> results.txt
    echo "$1" | ./minishell >> results.txt 2>&1
    echo "" >> results.txt
    ((test_num++))
}

# Basic commands
run_test "echo hello"
run_test "ls"
run_test "pwd"

# Quoted strings
run_test "echo \"simple quoted\""
run_test "echo 'simple single quoted'"
run_test "echo \"quote 'inside' quotes\""
run_test "echo 'quote \"inside\" single quotes'"
run_test "echo \"multiple 'nested' \\\"quotes\\\"\""
run_test "echo 'multiple \"nested\" \\'quotes\\''"

# Valid redirects
run_test "echo valid > redirect1.txt"
run_test "echo append >> redirect1.txt"
run_test "echo \"quoted\" > redirect2.txt"
run_test "echo 'quoted' >> redirect2.txt"
run_test "echo space > \"file with spaces.txt\""
run_test "echo space >> 'file with spaces.txt'"

# Invalid redirects
run_test "echo missing >"
run_test "echo missing >>"
run_test "echo double > > redirect.txt"
run_test "echo double >> >> redirect.txt"
run_test "echo redirect > |"
run_test "echo redirect >> |"
run_test "echo empty > \"\""
run_test "echo empty >> ''"
run_test "echo spaces > '  '"
run_test "echo spaces >> \"  \""

# Edge cases with quotes
run_test "echo \"\""
run_test "echo ''"
run_test "echo \"\" > empty_out"
run_test "echo '' >> empty_out"
run_test "echo > \"quoted file\""
run_test "echo >> 'quoted file'"
run_test "echo \"partial > quote\""
run_test "echo 'partial >> quote'"

# Combined cases
run_test "echo \"quoted\" > combined.txt"
run_test "echo 'quoted' >> combined.txt"
run_test "echo mix > \"mixed file.txt\""
run_test "echo mix >> 'mixed file.txt'"
run_test "echo \"multiple > redirects\" > final.txt"
run_test "echo 'multiple >> redirects' >> final.txt"

# Clean up test files
rm -f redirect1.txt redirect2.txt "file with spaces.txt" empty_out combined.txt "mixed file.txt" final.txt "quoted file"

echo "Testing complete. Results saved to results.txt"