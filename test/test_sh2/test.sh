#!/bin/bash

readonly MINISHELL_PROMPT=">> "
readonly MINISHELL_EXE="minishell"
readonly MINISHELL_DIR="../../"
readonly MINISHELL_TESTCASE="test/test_sh2/"

readonly MINISHELL_PATH="${MINISHELL_DIR}${MINISHELL_EXE}"
readonly LOG_FILE_NAME="result.log"

cd ${MINISHELL_DIR}
echo ls | ./minishell
echo pwd | ./minishell
# cat test/test_sh2/test_case/test.txt | ./minishell >> result.log
# cat test/test_sh2/test_case/test.txt | ./minishell >> result.log
