programms=(BinarySearch BinaryTree Factorial LinearSearch LinkedList QuickSort TreeVisitor)
touch err_file.txt
for program in ${programms[*]}
do
	${PWD}/build/compiler/compiler irt ${PWD}/tests/PositiveSamples/${program}.java /dev/null 2> err_file.txt
        if [ -s err_file.txt ]
	then
	printf "%s.java not passed!\n" $program
	cat err_file.txt
	rm err_file.txt
	exit 1
	else
	cat err_file.txt	
	printf "%s.java passed\n" $program
	fi
done
rm err_file.txt
