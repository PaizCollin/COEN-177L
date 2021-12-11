#Name: Collin Paiz
#Date: 22 September 2021
#Title: Lab 1 - Basic Shell Programming
#Description: This program checks how many users are logged on. If the current user is "cpaiz", the program proceeds, else it exits. The program then  calculates the area of a circle based on the user's inputted radius. The program displays the area and asks the user if the would like to calculate the area of another circle. 

#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "cpaiz" ]
then
        echo "Now you can proceed!"
else
        echo "Check who logged in!"
        exit 1 
fi
response="Yes"
while [ $response != "No" ]
do
   echo "Enter radius of circle: "
   read radius
   area=`echo $radius \* $radius \* 3.1415 | bc`
   echo "The area of the circle is $area"
   echo "Would you like to repeat for another circle [Yes/No]?"
        read response
done

