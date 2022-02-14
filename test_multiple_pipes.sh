#! /bin/sh
make DEBUG=1 bonus=1 re

# Test 1: checking if even handling 1 pipe works
./pipex Makefile "cat" "grep main" outfile.txt
< Makefile cat | grep main > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "1:	\033[32m[YOU ARE AMAZING]\033[0m"
else
    echo -e "1:	\033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

rm outfile.txt outfile2.txt

#Test 2: checking 2 pipes

./pipex Makefile "cat" "grep SRCS" "grep main" outfile.txt
< Makefile cat | grep SRCS | grep main > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "2:	\033[32m[YOU ARE AMAZING]\033[0m"
else
    echo -e "2:	\033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

rm outfile.txt outfile2.txt

#Test 3: checking 3 pipes

./pipex Makefile "cat" "grep SRCS" "grep main" "grep c" outfile.txt
< Makefile cat | grep SRCS | grep main | grep c > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "3:	\033[32m[YOU ARE AMAZING]\033[0m"
else
    echo -e "3:	\033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

rm outfile.txt outfile2.txt