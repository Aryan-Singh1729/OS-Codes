#!/bin/bash

file="addressbook.txt"

while true
do
    echo " "
    echo "===== ADDRESS BOOK ====="
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"

    read -p "Enter your choice: " choice

    case $choice in

    1)
        touch "$file"
        echo "Address Book Created"
        ;;

    2)
        cat "$file"
        ;;

    3)
        read -p "Enter Name: " name
        read -p "Enter Phone: " phone
        echo "$name $phone" >> "$file"
        echo "Record Inserted"
        ;;

    4)
        read -p "Enter Name to Delete: " name
        sed -i "/^$name /d" "$file"
        echo "Record Deleted"
        ;;

    5)
        read -p "Enter Name to Modify: " name
        sed -i "/^$name /d" "$file"

        read -p "Enter New Name: " newname
        read -p "Enter New Phone: " newphone

        echo "$newname $newphone" >> "$file"
        echo "Record Modified"
        ;;

    6)
        echo "Exiting..."
        exit
        ;;

    *)
        echo "Invalid Choice"
        ;;
    esac

done






# 1. Complete Explanation of Address Book Shell Program: The Address Book program is written in Bash Shell Script and is used to create, view, insert, delete, and modify contact records stored in a text file. The program starts with #!/bin/bash, which is called the shebang and tells the operating system to execute the script using the Bash shell. The statement file="addressbook.txt" declares a variable named file that stores the name of the text file where all contact records will be saved. The while true statement creates an infinite loop so that the menu is displayed repeatedly until the user chooses to exit. The do keyword indicates the beginning of the loop body, while done marks its end. The echo command is used to display the Address Book menu containing six options: Create Address Book, View Address Book, Insert Record, Delete Record, Modify Record, and Exit. The statement read -p "Enter your choice: " choice takes input from the user and stores it in the variable choice. Here, read accepts user input, -p displays a prompt, and choice stores the selected option. The case $choice in statement works similarly to a switch statement in C or C++ and executes different commands depending on the user's selection. The symbol $ is used to access the value stored in a variable. In Option 1 (Create Address Book), the command touch "$file" creates a new text file named addressbook.txt if it does not already exist. If the file already exists, its contents are preserved. In Option 2 (View Address Book), the command cat "$file" displays all the records stored inside the address book file. In Option 3 (Insert Record), the statements read -p "Enter Name: " name and read -p "Enter Phone: " phone take the contact name and phone number from the user. The command echo "$name $phone" >> "$file" stores the entered information in the address book file. The >> operator is called the append operator, which adds new data at the end of a file without removing existing records. In Option 4 (Delete Record), the program asks the user to enter the name of the contact to delete. The command sed -i "/^$name /d" "$file" removes matching records from the file. Here, sed stands for Stream Editor and is used to search, edit, or delete text. The -i option modifies the original file directly, /pattern/ identifies the text pattern to match, ^ represents the beginning of a line, and d means delete. The space after $name helps match the complete name field rather than just a prefix. In Option 5 (Modify Record), the program first asks for the name of the contact to modify. The sed -i command deletes the old record, after which the program accepts a new name and phone number using read. The command echo "$newname $newphone" >> "$file" appends the updated record to the address book. Thus, modification is performed by deleting the old record and inserting the updated record. In Option 6 (Exit), the exit command terminates the shell script and stops the infinite loop. The ;; symbol marks the end of each case option, while esac marks the end of the entire case statement. The *) option is the default case and displays an error message when the user enters an invalid choice. This program demonstrates basic shell programming concepts such as variables, loops, conditional selection, user input, file handling, and text processing. The records are stored permanently in addressbook.txt until they are modified or deleted. One limitation of this simple program is that names should be unique and should not contain special characters interpreted by sed, because deleting or modifying a matching name can affect multiple records. Also, the address book file should be created before performing other operations. To execute the program, save it as addressbook.sh, give it execution permission using chmod +x addressbook.sh, and run it using ./addressbook.sh.

# 2. Explanation of 20 Important Shell Commands (Excluding Commands Used in the Address Book Program): (1) pwd (Print Working Directory): Displays the complete path of the directory in which the user is currently working. For example, pwd may display /home/user/Documents. (2) ls (List): Displays the names of files and directories present in the current directory. For example, ls lists visible files, ls -l displays detailed information including file permissions, ownership, size, and modification date, and ls -a displays hidden files as well. (3) cd (Change Directory): Changes the current working directory. For example, cd Documents opens the Documents directory, cd .. moves one directory backward to the parent directory, and cd /home/user moves to the specified directory. (4) mkdir (Make Directory): Creates a new directory or folder. For example, mkdir college creates a directory named college, while mkdir -p college/os/practical creates the complete directory structure if the intermediate directories do not exist. (5) rmdir (Remove Directory): Deletes an empty directory. For example, rmdir college removes the college directory only if it contains no files or subdirectories. (6) cp (Copy): Copies files or directories from one location to another. For example, cp file1.txt file2.txt creates a copy of file1.txt named file2.txt, while cp -r folder1 folder2 copies a directory and its contents recursively. (7) mv (Move): Moves files or directories from one location to another and can also rename them. For example, mv old.txt new.txt renames a file, while mv file.txt Documents/ moves it into the Documents directory. (8) rm (Remove): Deletes files or directories. For example, rm file.txt deletes a file, while rm -r folder recursively deletes a directory and its contents. Deleted files are generally not moved to the Recycle Bin, so this command must be used carefully. (9) grep (Global Regular Expression Print): Searches for lines containing a specific word or pattern inside a file. For example, grep "Ashish" students.txt displays all lines containing Ashish, while grep -i "ashish" students.txt performs a case-insensitive search. (10) wc (Word Count): Counts the number of lines, words, and bytes in a file. For example, wc file.txt displays all three counts, wc -l file.txt counts lines, wc -w file.txt counts words, and wc -c file.txt counts bytes. (11) head: Displays the first 10 lines of a file by default. For example, head students.txt displays the first 10 lines, while head -n 5 students.txt displays only the first five lines. (12) tail: Displays the last 10 lines of a file by default. For example, tail students.txt displays the last 10 lines, while tail -n 5 students.txt displays the last five lines. The command tail -f logfile.txt continuously displays newly added lines, making it useful for monitoring log files. (13) sort: Arranges the lines of a file in a particular order. For example, sort names.txt sorts lines alphabetically, sort -r names.txt sorts them in reverse order, and sort -n numbers.txt sorts numerical values in ascending order. (14) uniq (Unique): Removes or identifies consecutive duplicate lines in text. For example, uniq names.txt removes adjacent duplicate lines, while uniq -c names.txt displays the number of consecutive occurrences. To remove duplicate lines that may appear anywhere in a file, sort names.txt | uniq can be used. (15) find: Searches for files and directories based on their names, types, sizes, or other conditions. For example, find . -name "data.txt" searches for data.txt in the current directory and all its subdirectories. The dot (.) represents the current directory. (16) clear: Clears the visible terminal screen to provide a clean working area. For example, entering clear removes previously displayed output from the current terminal view without deleting any actual files. (17) date: Displays the current system