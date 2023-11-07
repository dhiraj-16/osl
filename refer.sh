

#!/bin/bash

function create_addressbook(){
    touch "addressBook.txt"
    echo "addressBook.txt is created"
    echo "RollNo Names Address" >> "addressBook.txt"
    
    echo ""
    
}
function insert(){
    read -p "Enter the name : " name
    read -p "Enter the roll no : " roll_no
    read -p "Enter the address : " address
    echo "$roll_no, $name, $address " >> "addressBook.txt"
    echo "Recorde inserted"
    echo ""
}
function veiw_addressboook(){
    echo "The records of the address Book are as follows :"
    cat "addressBook.txt"
    echo ""

}

function deleterecord(){
    read -p "Enter the roll no to delete : " roll

    tmp_file=$(mktemp)
    grep "^.*$roll," "addressBook.txt" > "$tmp_file"
  
    if [ $? -eq 0 ];
    then
    grep -v "^.*$roll," "addressBook.txt" > "$tmp_file" && mv "$tmp_file" "addressBook.txt"

    
    echo "Record deleted successfully"
    
    else
    echo "Record not Found"
    fi
    
    echo ""
}

function search(){
    read -p "Enter the roll no to search : " roll

    tmp_file=$(mktemp)

    grep "^$roll," "addressBook.txt" > "$tmp_file"
  
    if [ $? -eq 0 ];
    then
    cat "$tmp_file"
    else
    echo "404"
    fi
    echo ""

}

function modify(){
    read -p "Enter the roll no to modify : " roll

    tmpfile=$(mktemp)

    grep "^$roll," "addressBook.txt" > "$tmpfile"

    if [ -s "$tmpfile" ];
    then
    read -p "Enter the new name of $roll : " newname
    read -p "Enter the new address of $roll : " naddress

    sed -i "s/.*$roll.*/$roll, $newname, $naddress/" "addressBook.txt"
    echo "Record modify successfully"
    else
    echo "Record not found"
    fi
    echo ""
    
}


while true;
do
echo "1) for creating address book"
echo "2) for inserting record"
echo "3) for veiw address book"
echo "4) for delete the record from address book"
echo "5) to search the record in address book"
echo "6) to modify the record in address book"

echo "7) for exit"

read choice

case "$choice" in
"1") create_addressbook;;
"2") insert;;
"3") veiw_addressboook;;
"4") deleterecord;;
"5") search;;
"6") modify;;
*) break;;

esac
done