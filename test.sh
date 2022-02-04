#! /bin/sh
make re

./pipex Makefile "cat" "grep srcs" outfile.txt

< Makefile cat | grep srcs > outfile2.txt

if diff outfile.txt outfile2.txt;
then
    echo -e "\033[32mSUCCESS, YOU ROCK, AND YOUR CAT IS THE CUTEST IN THE WORLD\033[0m"
    rm outfile.txt outfile2.txt
else
    echo "jammerrrrrr"
    diff outfile.txt outfile2.txt > diff.txt
    rm outfile.txt outfile2.txt
fi
