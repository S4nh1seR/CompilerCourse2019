programms=(LC_1 TC_1a TC_2 TC_2a TC_3a TC_3a\(1\) TC_3a\(a\) TC_3\(b\) TC_4a TC_4b TC_5a TC_6a TC_7b TC_7c TC_8a TC_9a TC_9a_2 TC_11a TC_12b TC_13a TC_13b TC_13c TC_bonus1)
touch err_file.txt
fails=0
for program in ${programms[*]}
do
	${PWD}/build/compiler/compiler none ${PWD}/tests/NegativeSamples/${program}.java /dev/null 2> err_file.txt | cat >> err_file.txt
        if [ -s err_file.txt ]
	then
	printf "%s.java error detected, passed\n" $program
	printf "###########ERROR INFO################\n"
	cat err_file.txt
	printf "###################################\n"
	printf "\n"
	> err_file.txt
	else	
	printf "%s.java error not detected, not passed!\n\n" $program
	fails=1
	fi
done
rm err_file.txt
if [ $fails -eq 0 ]
then
printf "all tests are passed!\n"
else
printf "there are failed tests(\n"
exit 1
fi
