#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sys/shm.h>
#include <sys/stat.h>

using namespace std;

int fib(int val);
void do_fib(int val);
void do_sort(unsigned int val);

int main(int argc, const char * argv[])
{
    
    if ( argc < 2 ) {
        cout << "An integer argument is required." << endl;
        exit(EXIT_FAILURE);
    }
    
    pid_t childpid;
    int fd[2];
    
    unsigned long intargsize = (strlen(argv[1])+1);
    
    char readbuffer[intargsize];
    
    pipe(fd);
    childpid = fork();
    
    if ( childpid >= 0 ) // Fork was successful.
    {
        
        if ( childpid == 0 ) // If we're in the child.
        {
            
            close(fd[1]); // Close the output side of the pipe.
            
            cout << "[Child] Fibonacci Process Started." << endl;
            
            read(fd[0], readbuffer, sizeof(readbuffer)); // Read the data.
            
            do_fib(atoi(readbuffer)); // perform the fib on the data.
            
            cout << "[Child] Fibonacci Process Exited." << endl;
            
            exit(EXIT_SUCCESS);
            
        }
        else // We're in the parent.
        {
            
            cout << "[Parent] Sending the input number to child." << endl;
            close(fd[0]); // Close the input side of the pipe.
            write(fd[1], argv[1], intargsize);
            
            pid_t secondchildpid;
            
            // Establish shared memory.
            int segment_id;
            
            int * shared_integer;
            int * shared_flag;
            int * shared_terminate;
            
            segment_id = shmget(IPC_PRIVATE, (sizeof(int)*3), S_IRUSR | S_IWUSR);
            
            // Attach the shared memory segment
            shared_integer = (int *) shmat(segment_id, NULL, 0);
            shared_flag = shared_integer + 1;
            shared_terminate = shared_integer + 2;
            
            // Set defaults.
            *shared_terminate = 0;
            *shared_flag = 0;
            *shared_integer = 0;
            
            secondchildpid = fork();
            
            if( secondchildpid >= 0 ) // Fork was successful.
            {
                
                if( secondchildpid == 0 ) // If we're in the child
                {
                    
                    cout << "[Child] Quick Sort Process Started." << endl;
                    
                    while ( *shared_terminate == 0 )
                    {
                        
                        if( *shared_flag == 1 )
                        {
                            
                            if( *shared_integer == 0 )
                            {
                                cout << "[Child] Quick Sort cannot be performed on an array of size 0." << endl;
                            }
                            else
                            {
                                
                                do_sort((unsigned int)(* shared_integer));
                                
                            }
                            
                            *shared_flag = 0;
                            
                        }
                        
                    }
                    
                    cout << "[Child] Quick Sort Process Ended." << endl;
                    
                    // terminate shared memory
                    //shmdt(shared_terminate);
                    //shmdt(shared_flag);
                    //shmdt(shared_integer);
                    //shmctl(segment_id, IPC_RMID, NULL);
                    
                    exit(EXIT_SUCCESS);
                    
                }
                else // we're in the parent.
                {
                    
                    while(1)
                    {
                        
                        int ask_int;
                        
                        cout << "Enter a positive integer or -1 to end: ";
                        
                        cin >> ask_int;
                        
                        if ( ask_int < 0 ) break;
                        
                        // while the shared_flag is not 0
                        do
                        {
                            
                            if ( *shared_flag == 0 )
                            {
                                *shared_flag = 1;
                                *shared_integer = ask_int;
                                break;
                            }
                            
                        } while(1);
                        
                    }
                    
                    cout << "[Parent] Main Process Exits." << endl;
                    
                    // terminate child.
                    *shared_terminate = 1;
                    
		    shmdt(shared_terminate);
                    shmdt(shared_flag);
                    shmdt(shared_integer);
                    shmctl(segment_id, IPC_RMID, NULL);

                    exit(EXIT_SUCCESS);
                }
                
            }
            else // Fork was not successful.
            {
                perror("ERROR: Call to fork failed. Program will now terminate.");
                exit(EXIT_FAILURE);
            }
            
            exit(EXIT_SUCCESS);
            
        }
        
    }
    else // Fork was unsuccessful.
    {
        perror("ERROR: Call to fork failed. Program will terminate.");
        exit(EXIT_FAILURE);
    }
    
}

void do_fib(int val)
{
    
    if ( val < 0 ) val*=-1;
    
    cout << "[Child] Input Number: " << val << endl;
    cout << "[Child] Fibonacci Number f(" << val << ") is " << fib(val) << endl;
    
}

int fib(int val)
{
    
    if( val == 0 ) return 0;
    
    if( val == 1 ) return 1;

    return fib((val-1)) + fib((val-2));
    
}

void quick_sort(int numbers[], int left, int right);

void do_sort(unsigned int val)
{
    
    int numbers[val];
    
    cout << "[Child] Random Numbers Received: ";
    
    for( unsigned int i = 0; i < val; i++ )
    {
        
        int rvalue = ( rand() % 100 + 1 );
        cout << rvalue << " ";
        numbers[i] = rvalue;
        
    }
    
    cout << endl;
    
    cout << "[Child] Sorted Sequence: ";
    
    quick_sort(numbers, 0, (val-1));
    
    for( unsigned int i = 0; i < val; i++ )
    {
        cout << numbers[i] << " ";
    }
    
    cout << endl;
    
}

void quick_sort(int numbers[], int left, int right)
{
    int pivot, l_hold, r_hold;
    
    l_hold = left;
    r_hold = right;
    pivot = numbers[left];
    while (left < right)
    {
        while ((numbers[right] >= pivot) && (left < right))
            right--;
        if (left != right)
        {
            numbers[left] = numbers[right];
            left++;
        }
        while ((numbers[left] <= pivot) && (left < right))
            left++;
        if (left != right)
        {
            numbers[right] = numbers[left];
            right--;
        }
    }
    numbers[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot)
        quick_sort(numbers, left, pivot-1);
    if (right > pivot)
        quick_sort(numbers, pivot+1, right);
}
