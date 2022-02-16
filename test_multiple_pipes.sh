#! /bin/sh
make DEBUG=1 bonus=1 re

clear

# echo -e "Inspect test results after outcome?"

#read elaborate

#echo -e "$elaborate"

echo -e "\n\033[0;36m****************** MANDATORY PART ******************\033[0m\n"

sleep 0.2

# Test 1: checking if even handling 1 pipe works
./pipex Makefile "cat" "grep main" outfile.txt
< Makefile cat | grep main > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "1 \033[32m[OK]\033[0m"
else
    echo -e "1 \033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

rm outfile.txt outfile2.txt
sleep 0.2

#Test 2: checking 2 pipes

./pipex Makefile "cat" "grep SRCS" "grep main" outfile.txt
< Makefile cat | grep SRCS | grep main > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "2 \033[32m[OK]\033[0m"
else
    echo -e "2 \033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

rm outfile.txt outfile2.txt
sleep 0.2

#Test 3: checking 3 pipes

./pipex Makefile "cat" "grep SRCS" "grep main" "grep c" outfile.txt
< Makefile cat | grep SRCS | grep main | grep c > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "3 \033[32m[OK]\033[0m"
else
    echo -e "3 \033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

rm outfile.txt outfile2.txt
sleep 0.2

#Test 4: checking 4 pipes

./pipex Makefile "cat" "grep SRCS" "grep main" "grep c" "wc" outfile.txt
< Makefile cat | grep SRCS | grep main | grep c | wc > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "4 \033[32m[OK]\033[0m"
else
    echo -e "4 \033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

# open outfile.txt outfile2.txt
# sleep 5
rm outfile.txt outfile2.txt
sleep 0.2

#Test 5: checking 5 pipes

./pipex omgbash.txt "cat" "cat -e" "grep file" "grep user" "grep c" "wc" outfile.txt
< omgbash.txt cat | cat -e | grep file | grep user | grep c | wc > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "5 \033[32m[OK]\033[0m"
else
    echo -e "5 \033[31m[KO]\033[0m"
    diff outfile.txt outfile2.txt >> diff.txt
fi

# open outfile.txt outfile2.txt
# sleep 5
rm outfile.txt outfile2.txt
sleep 0.2