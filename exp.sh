#!/bin/bash

# This is a simple tester for pipex.

# Colours
RED="\033[0;31m"
GREEN="\033[0;32m"
NC="\033[0m"

# Program input
if [[ "$1" == "bonus" ]]; then
	bonus="1"
else
	bonus="0"
fi

# Exit variables
exit_status_bash="0"
exit_status_yours="0"

# Check for pipex executable
if [[ -f pipex_debug ]]; then
	pipex="./pipex_debug"
elif [[ -f pipex ]]; then
	pipex="./pipex"
else
	echo "No pipex executable found."
	exit 1
fi

echo "Running $pipex"

# Input file name
file_in="/tmp/file_in"

# Create input file
cat << EOF > $file_in
hoi
hoi
EOF

existing_out_bash="existing_out_bash"
existing_out_yours="existing_out_yours"

cat << EOF > $existing_out_bash
1
2
3
4
5
6
7
8
9
9
9
9
9
EOF

cat << EOF > $existing_out_yours
1
2
3
4
5
6
7
8
9
9
9
9
9
EOF

# $1: input file
# $2: cmd1
# $3: cmd2
# $4: output file
run_pipex()
{
	"$pipex" "$1" "$2" "$3" "$4"
	exit_status_yours="$?"
}

# $1 whole command to execute
run_bash()
{
	if [[ "$(uname)" == "Linux" ]]; then
		bash -c "$1"
	else
		zsh -c "$1"
	fi

	exit_status_bash="$?"
}

# $1: exit_status_bash
# $2: exit_status_yours 
# $3: file_out_bash
# $4: file_out_yours
compare_outputs()
{
	# Compare exit status
	if [[ ("$1" == "0" && "$2" == "0") || ("$1" != "0" && "$2" != "0") ]]; then
		echo -e "${GREEN}SUCCES${NC}: Exit codes correct (yours="$2" | bash="$1")"
	else
		echo -e "${RED}ERROR${NC}: Exit codes differ (yours="$2" | bash="$1")"
	fi

	# Compare output files
	diff "$3" "$4" > /dev/null 2>&1
	if [[ "$?" == "0" ]]; then
		echo -e "${GREEN}SUCCES${NC}: Output files the same."
	else
		echo -e "${RED}ERROR${NC}: Output files differ."
	fi

	# # Delete created files
	# if [[ -f "$3" && -f "$4" ]]; then
	# 	rm -f "$3" "$4"
	# fi

	echo ""
}

# Test 35: Multiple cat commands to existing outfile
echo "Test 35: Multiple cat cmomands"
run_bash "< $file_in cat -e | cat -e  > $existing_out_bash"
run_pipex "$file_in" "cat -e" "cat -e" "$existing_out_yours"
compare_outputs "$exit_status_bash" "$exit_status_yours" "existing_out_bash" "existing_out_yours"
