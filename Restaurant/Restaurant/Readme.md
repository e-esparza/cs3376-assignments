This assignment mimics the configuration and activities happen at a typical restaurant. Input is provided in 2 files: config.txt and activity.txt. Configuration file contains how many tables, table - waiter relationship & full menu list. Activity file mimics the actual activities that happen in restaurant. After setting up the necessary objects using the configuration file, you can read the activity file and process them. You should not use vector or any other template in this assignment.
 
We will use the following classes to complete this assignment. You can access the latest version of these files & data files at ~nxs048000/3376-hw4 in Linux. Feel free to add more variables if needed. Avoid making drastic changes to existing variables. You need to implement all the .cpp files including class implementation and overall application functionality.
 
Table : status, # of max seats, # of guests, order, waiter
menu_item: item_code, name, price
Menu : list of menu items
Order : a list of menu items ordered at a table
Waiter: waiter's data and list of tables (s)he controls.
 
 
Sample configuration file (config.txt)
 
Tables: table #, max seats
1 2        
2 4
3 2
4 2
5 2
6 4
7 6
8 10
9 2
10 4
11 4
12 4
13 4
14 2
15 2
16 2
17 2
18 2
 
Waiters: first name followed by table list
John 1 2 5 9 11 15            
Maria 3 4 6 7 17 18
Mike 8 10 12 13 14 26
 
Menu:     listing of the full menu: item code, name, price
A1 Bruschetta 5.29
A2 Caprese_Flatbread 6.10
A3 Artichoke-Spinach_Dip 3.99
A4 Lasagna_Fritta 4.99
A5 Mozzarella_Fonduta 5.99
E1 Lasagna_Classico 6.99
E2 Capellini_Pomodoro 7.99
E3 Eggplant_Parmigiana 8.99
E4 Fettuccine_Alfredo 7.49
E5 Tour_of_Italy 14.99
D1 Tiramisu 2.99
D2 Zeppoli 2.49
D3 Dolcini 3.49
S1 Soda 1.99
S2 Bella_Limonata 0.99
S3 Berry_Acqua_Fresca 2.88
 
Sample activity file (comments are not part of the file):
 
T1 P2   // Party of 2 is assigned to Table 1
T2 P4
T4 P2
T1 O A1 A1 E1 E2   // Party at table 1 orders these items
T8 P10
T1 S // Food arrives at table 1
T3 P2
T1 C // T1 gets the check, pays and leaves & table is cleaned too.
T5 P2
T1 P1 // Party of 1 is assigned to table 1
...
In addition to processing these commands, when a table is closed, display the check as well. Include table #, waiter name, # of customers in the party, name and price of each ordered item and the total. No need to worry about tax or tips.
 
Error checking:
- Do not allow orders from table with no party assigned to it.
- Do not allow assigning new party to a table when another party is already there.
- Do not allow assigning new party to a table for which waiter has not been assigned.
- Do not allow check-out from empty table or a table in which all items have not been served.
- Do not allow delivery of food to an empty table!
- Do not assign any party to table with no waiter assignment.
- Reject any request that does not match with sample formats.
 
Since we are using lot of dynamic memory in this assignment, we will use a tool called valgrind to ensure that there are no memory leaks. If the executable file for Assignment 4 is hw4, we can run the following command. After hw4 ends, valgrind will display a summary.
valgrind hw4
 
Unlike Java, there is no bult-in String Tokenizer in C++. I have included a few files in ~nxs048000/3376-hw4 directory (Tokenizer.h, Tokenizer.cpp and testTokenizer.cpp) that provide Tokenizer functionality. This can be helpful to read and process the input lines from the files.
I have also included a very simple program (simpleTokenizer.cpp) that reads a file line by line and tokenizes each line (tokens are space separated). 
 
When you are ready to submit your source files, test your program using valgrind tool to find and fix any memory leaks. 