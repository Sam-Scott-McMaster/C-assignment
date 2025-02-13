#!/bin/bash
#
# A simple framework for regression testing the convert script
#
# Returns the number of failed test cases.
#
# Format of a test:
#     test 'command' 'input file name' 'expected output file name' 'expected std error file name'
#
# Some example test cases are given. You should add more test cases.
#
# CAUTION: Uses temporary files named test_err.txt and test_out.txt
# 
# Sam Scott, McMaster University, 2024
#
declare -i tc=0
declare -i fails=0

############################################
# Run a single test. Runs a given command 
# to check the return value, stdout, and stderr
#
# GLOBALS: tc, fails
# PARAMS: $1 = command
#         $2 = input file name
#         $3 = expected std output file name
#         $4 = expected std error file name
#
# Assumes return value should be 0 if the
# std error file is empty. Otherwise it 
# should be 1.
#
# OUTPUTS: A pass/fail report showing the
# difference between expected and actual
# output on a failure (diff command)
############################################
test() {
    tc=tc+1

    local COMMAND=$1
    local INP=$2
    local EX_OUT=$3
    local EX_ERR=$4 

    EX_RET=1
    if [[ $(cat $EX_ERR) = "" ]]; then
        EX_RET=0
    fi
    $COMMAND < $INP > test_out.txt 2> test_err.txt
    RET=$?
    if [[ $RET != $EX_RET ]]; then
        echo "TC $tc Failed"
        echo "Returned $RET"
        echo "-----------"
        fails=$fails+1
        return
    fi
    DIFF=$(diff test_out.txt $EX_OUT)
    if [[ $DIFF != '' ]]; then
        echo "TC $tc Failed Standard Output"
        echo "$DIFF"
        echo "-----------"
        fails=$fails+1
        return
    fi
    DIFF=$(diff test_err.txt $EX_ERR)
    if [[ $DIFF != '' ]]; then
        echo "TC $tc Failed Standard Error"
        echo "$DIFF"
        echo "-----------"
        fails=$fails+1
        return
    fi

    echo "TC $tc Passed"
}


test './ctest' 'inp1.txt' 'ex_out1.txt' 'empty.txt'
test './ctest -b 2' 'inp2.txt' 'ex_out2.txt' 'empty.txt'
test './ctest -a' 'empty.txt' 'empty.txt' 'usage.txt'
test './ctest --help' 'empty.txt' 'new.txt' 'empty.txt'
test './ctest -b 10' 'inp_base10.txt' 'ex_out_base10.txt' 'empty.txt'
test './ctest -b 16' 'inp_base16.txt' 'ex_out_base16.txt' 'empty.txt'
test './ctest -b 1' 'empty.txt' 'empty.txt' 'usage_invalid_base.txt'
test './ctest -b 10' 'inp_non_integer.txt' 'empty.txt' 'ex_err_non_integer.txt'
test './ctest -b 10' 'inp_negative_base10.txt' 'ex_out_negative_base10.txt' 'empty.txt'
test './ctest -b' 'empty.txt' 'empty.txt' 'usage_no_base.txt'
test './ctest -b 10 -r 5 10' 'empty.txt' 'ex_out_range_base10.txt' 'empty.txt'
test './ctest -b 10 -r' 'empty.txt' 'empty.txt' 'usage_no_range.txt'

# clean up
rm -f test_err.txt test_out.txt

# return code
exit $fails
