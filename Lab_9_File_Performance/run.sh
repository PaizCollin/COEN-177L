#!/bin/bash
make; 

echo
echo "----------Creating Files----------"
# cat /dev/random | head -c <bytecount>
cat /dev/random | head -c 100000 > file1.txt
cat /dev/random | head -c 1000000 > file2.txt
cat /dev/random | head -c 10000000 > file3.txt
cat /dev/random | head -c 100000000 > file4.txt

echo
echo "----------Step2----------"
for file in file1.txt file2.txt file3.txt file4.txt 
do 
    echo "Step2 $file"
    time ./step2 $file
    echo " "
done

echo "----------End Step2----------"
echo

echo "----------Step3----------"
for file in file1.txt file2.txt file3.txt file4.txt 
do 
    		for buffer in 100 1000 10000 100000
    		do
        		echo "Step3 $file $buffer"
        		time ./step3 $file $buffer
        		echo " "
    		done
done

echo "----------End Step3----------"
echo

echo "----------Step4----------"
for file in file1.txt file2.txt file3.txt file4.txt 
do 
    		for buffer in 100 1000 10000 100000
    		do
        		echo "Step4 $file $buffer"
        		time ./step4 $file $buffer
        		echo " "
    		done
done
 
echo "----------End Step4----------"
echo

echo "----------Step5----------"
for file in file1.txt file2.txt file3.txt file4.txt 
do 
    	for buffer in 100 1000 10000 100000
    	do
                for thread in 2 8 32 64
        	do
      		        echo "Step5 $file $buffer $thread"
        		time ./step5 $file $buffer $thread
        		echo " "
                done
    	done
done

 
echo "----------End Step5----------"
echo
make clean;
echo
