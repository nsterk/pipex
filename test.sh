#! /bin/sh
make debug=1 re

# Test 1:
./pipex Makefile "cat" "grep srcs" outfile.txt

< Makefile cat | grep srcs > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "1:	\033[32m[YOU ARE AMAZING]\033[0m"
else
    echo -e "1:	\033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

rm outfile.txt outfile2.txt

# Test 2:
./pipex Makefile "cat -e" "grep srcs" outfile.txt

< Makefile cat -e | grep srcs > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "2:	\033[32m[OK]\033[0m"
else
    echo -e "2:	\033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

rm outfile.txt outfile2.txt

# Test 3:
./pipex Makefile "cat -e -e" "grep srcs" outfile.txt

< Makefile cat -e -e | grep srcs > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "3:	\033[32m[OK]\033[0m"
else
    echo -e "3:	\033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

rm outfile.txt outfile2.txt

# Test 4 - illegal option on first command
./pipex Makefile "cat --e -e" "grep srcs" outfile.txt

< Makefile cat --e -e | grep srcs > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "4:	\033[32m[BAM GURL]\033[0m"
else
    echo -e "4:	\033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

rm outfile.txt outfile2.txt

# Test 5 - illegal option on second command
./pipex Makefile "cat -e" "grep -0oei srcs" outfile.txt

< Makefile cat -e | grep -0oei srcs > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "5:	\033[32m[OK]\033[0m"
else
    echo -e "5:	\033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

rm outfile.txt outfile2.txt

# Test 6 - empty string for first command
./pipex Makefile "" "grep -0oei srcs" outfile.txt

< Makefile | grep -0oei srcs > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "6:	\033[32m[OK]\033[0m"
else
    echo -e "6:	\033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

rm outfile.txt outfile2.txt