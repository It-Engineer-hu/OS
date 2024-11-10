#!/bin/sh

create(){
	touch addresbook.txt
	echo "AddressBook created!"
}

insert(){
	echo "Enter Name: "
	read name
	
	echo "Enter Address: "
	read address
	
	echo "Enter Phone No: "
	read phoneNo
	
	echo "Enter email id: "
	read email 
	
	echo "$name $address $phoneNo $email " >> addresbook.txt
}


veiw(){
	echo "======================# AddressBook #========================= "
	echo "Name   Address   Phone   Email"
	cat addresbook.txt
}


modify(){
	echo "Enter the name which you want to modify: "
	read name 
	
	grep -v " $name " addresbook.txt > addresbook1.txt
	cp addresbook1.txt addresbook.txt
	rm addresbook1.txt
	
	echo "Enter Name: "
	read name
	
	echo "Enter Address: "
	read address
	
	echo "Enter Phone No: "
	read phoneNo
	
	echo "Enter email id: "
	read email 
	
	echo "$name $address $phoneNo $email ">> addresbook.txt
}


delete(){
	echo "Enter the name which you want to delete"
	read name 
	
	grep -v " $name " addresbook.txt > addresbook1.txt
	cp addresbook1.txt addresbook.txt
	rm addresbook1.txt
}

n=0
while [ $n -ne 6 ]
do 
	echo ""
	echo "Select choice "
	echo ""
	echo "Create => 1 "
	echo "Insert => 2"
	echo "Veiw => 3"
	echo "Modify => 4"
	echo "Delete => 5"
	echo "Exit => 6"
	read ch
	
	case $ch in
		"1") create;;
		"2")insert;;
		"3")veiw;;
		"4")modify;;
		"5")delete;;
		"6")exit;;
	esac
done

