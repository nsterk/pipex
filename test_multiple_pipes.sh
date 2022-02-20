#! /bin/sh

_compilation()
{
	make debug=1 bonus=1 re
}

_mandatory()
{
	echo "\n\033[0;36m****************** MANDATORY PART ******************\033[0m\n"

	sleep 0.2
	# Test 1: checking if even handling 1 pipe works
	./pipex Makefile "cat" "grep main" outfile.txt
	< Makefile cat | grep main > outfile2.txt

	if diff outfile.txt outfile2.txt;
	then
		echo "1 \033[32m[OK]\033[0m"
	else
		echo "1 \033[31m[KO]\033[0m"
		diff outfile.txt outfile2.txt >> diff.txt
	fi

	rm outfile.txt outfile2.txt
	sleep 0.2
}

_bonus()
{
	echo "\n\033[0;36m******************* BONUS PART *********************\033[0m\n"
	#Test 2: checking 2 pipes

	./pipex Makefile "cat" "grep SRCS" "grep main" outfile.txt
	< Makefile cat | grep SRCS | grep main > outfile2.txt

	if diff outfile.txt outfile2.txt;
	then
		echo "2 \033[32m[OK]\033[0m"
	else
		echo "2 \033[31m[KO]\033[0m"
		diff outfile.txt outfile2.txt >> diff.txt
	fi

	rm outfile.txt outfile2.txt
	sleep 0.2

	#Test 3: checking 3 pipes

	./pipex Makefile "cat" "grep SRCS" "grep main" "grep c" outfile.txt
	< Makefile cat | grep SRCS | grep main | grep c > outfile2.txt

	if diff outfile.txt outfile2.txt;
	then
		echo "3 \033[32m[OK]\033[0m"
	else
		echo "3 \033[31m[KO]\033[0m"
		diff outfile.txt outfile2.txt >> diff.txt
	fi

	rm outfile.txt outfile2.txt
	sleep 0.2

	#Test 4: checking 4 pipes

	./pipex Makefile "cat" "grep SRCS" "grep main" "grep c" "wc" outfile.txt
	< Makefile cat | grep SRCS | grep main | grep c | wc > outfile2.txt

	if diff outfile.txt outfile2.txt;
	then
		echo "4 \033[32m[OK]\033[0m"
	else
		echo "4 \033[31m[KO]\033[0m"
		diff outfile.txt outfile2.txt >> diff.txt
	fi

	rm outfile.txt outfile2.txt
	sleep 0.2

	#Test 5: checking 5 pipes

	./pipex omgbash.txt "cat" "cat -e" "grep file" "grep user" "grep c" "wc" outfile.txt
	< omgbash.txt cat | cat -e | grep file | grep user | grep c | wc > outfile2.txt

	if diff outfile.txt outfile2.txt;
	then
		echo "5 \033[32m[OK]\033[0m"
	else
		echo "5 \033[31m[KO]\033[0m"
		diff outfile.txt outfile2.txt >> diff.txt
	fi

	rm outfile.txt outfile2.txt
	sleep 0.2
}

_errorhandling()
{
	echo "\n\033[0;36m******************* ERROR HANDLING *********************\033[0m\n"
	echo "See error_results.txt\n"
	#Test 1: Non-existing command
	echo "******************** Test 1 ********************\n\nShell: \c" > error_results.txt && < omgbash.txt cat | noexisty > outfile2.txt >> error_results.txt 2>&1
	echo "Pipex: \c" >> error_results.txt && ./pipex omgbash.txt "cat" "noexisty" outfile.txt >> error_results.txt 2>&1
	
	rm outfile2.txt

	#Test 2: grep without argument
	echo "\n******************** Test 2 ********************\n\nShell: \c" >> error_results.txt && < omgbash.txt cat | grep > outfile2.txt >> error_results.txt 2>&1
	echo "Pipex: \c" >> error_results.txt && ./pipex omgbash.txt "cat" "grep" outfile.txt >> error_results.txt 2>&1
	rm outfile2.txt outfile.txt
}

if [ $# -eq 0 ]; then _mandatory && _bonus && _errorhandling; fi

while getopts embra ARG; do
	case $ARG in
		a)
			_mandatory && _bonus && _errorhandling
			;;
		e)
			_errorhandling
			;;
		m)
			_mandatory
			;;
		b)
			_bonus
			;;
		r)
			make DEBUG=1 bonus=1 re
			;;
	esac
done
