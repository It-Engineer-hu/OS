#!/bin/sh

# Function to create the AddressBook file
create(){
    touch addressbook.txt
    echo "AddressBook created!"
}

# Function to insert new entry
insert(){
    echo "Enter Name: "
    read name
    
    echo "Enter Address: "
    read address
    
    echo "Enter Phone No: "
    read phoneNo
    
    echo "Enter email id: "
    read email 
    
    echo "$name $address $phoneNo $email" >> addressbook.txt
    echo "Entry added!"
}

# Function to view all entries in AddressBook
view(){
    echo "======================# AddressBook #========================="
    echo "Name   Address   Phone   Email"
    cat addressbook.txt
}

# Function to modify an existing entry
modify(){
    echo "Enter the name which you want to modify: "
    read name

    # Check if the name exists in the addressbook
    if ! grep -q "^$name " addressbook.txt; then
        echo "No such entry found for $name."
        return
    fi

    # Remove the old entry (by name)
    grep -v "^$name " addressbook.txt > addressbook1.txt
    mv addressbook1.txt addressbook.txt

    # Now ask for new details
    echo "Enter new Name: "
    read new_name
    
    echo "Enter new Address: "
    read address
    
    echo "Enter new Phone No: "
    read phoneNo
    
    echo "Enter new Email: "
    read email
    
    # Add the modified entry to the addressbook
    echo "$new_name $address $phoneNo $email" >> addressbook.txt
    echo "$new_name has been modified."
}

# Function to delete an entry
delete(){
    echo "Enter the name which you want to delete: "
    read name

    # Check if the name exists
    if ! grep -q "^$name " addressbook.txt; then
        echo "No such entry found for $name."
        return
    fi

    # Remove the entry
    grep -v "^$name " addressbook.txt > addressbook1.txt
    mv addressbook1.txt addressbook.txt

    echo "$name has been deleted."
}

# Main program loop
n=0
while [ $n -ne 6 ]
do 
    echo ""
    echo "Select choice:"
    echo ""
    echo "Create => 1 "
    echo "Insert => 2"
    echo "View => 3"
    echo "Modify => 4"
    echo "Delete => 5"
    echo "Exit => 6"
    read ch
    
    case $ch in
        "1") create;;
        "2") insert;;
        "3") view;;
        "4") modify;;
        "5") delete;;
        "6") exit;;
        *) echo "Invalid option. Please try again.";;
    esac
done

