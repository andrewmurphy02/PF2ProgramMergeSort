//------------------------------------------------------------------
// Purpose:     This program demonstrates two sorting algorithms.
// Author:      John Gauch and added on by Andrew Murphy
//------------------------------------------------------------------
#include <iostream>
#include <fstream>
using namespace std;
#include <stdlib.h>
#include "timer.h"

//------------------------------------------------------------------
// Check to see if data is sorted correctly
//------------------------------------------------------------------
bool data_sorted(int data[], int count)
{
   // Put specified count of random numbers into data array
   for (int index = 1; index < count; index++)
      if (data[index-1] > data[index])
         return false;
   return true;
}

//------------------------------------------------------------------
// Initialize data array with random values
//------------------------------------------------------------------
void create_random_data(int data[], int count, int range)
{
   // Put random data values into array
   for (int index = 0; index < count; index++)
      data[index] = rand() % range;
}

//------------------------------------------------------------------
// Read input file to initialize data array
//------------------------------------------------------------------
void read_data(string name, int data[], int &count, int &range)
{
   // Open input file
   ifstream din;
   din.open(name.c_str());
   if (din.fail())
      cout << "Error: could not open input file\n";

   // Read the data
   range = 0;
   din >> count;
   for (int i = 0; i < count; i++)
   {
      din >> data[i];
      if (data[i] > range)
	 range = data[i];
   }

   // Close the file
   din.close();
   range++;
}

//------------------------------------------------------------------
// Write data array to output file
//------------------------------------------------------------------
void write_data(string name, int data[], int count)
{
   // Open output file
   ofstream dout;
   dout.open(name.c_str());
   if (dout.fail())
      cout << "Error: could not open output file\n";

   // Write the data
   dout << count;
   for (int i = 0; i < count; i++)
   {
      if (i % 20 == 0)
	 dout << endl;
      dout << data[i] << " ";
   }

   // Close the file 
   dout.close();
}

//------------------------------------------------------------------
// Merge sort implementation with copy array
//------------------------------------------------------------------
void classic_mergesort(int data[], int copy[], int low, int high)
{
   // Check terminating condition
   int range = high - low + 1;
   if (range > 1)
   {
      // Divide the array and sort both halves
      int mid = (low + high) / 2;
      classic_mergesort(data, copy, low, mid);
      classic_mergesort(data, copy, mid + 1, high);

      // Initialize array indices
      int index1 = low;
      int index2 = mid + 1;
      int index = 0;

      // Merge smallest data elements into copy array
      while (index1 <= mid && index2 <= high)
      {
	 if (data[index1] > data[index2]) // This line makes it reverse by flipping '<'
	    copy[index++] = data[index1++];
	 else
	    copy[index++] = data[index2++];
      }

      // Copy any remaining entries from the first half
      while (index1 <= mid)
	 copy[index++] = data[index1++];

      // Copy any remaining entries from the second half
      while (index2 <= high)
	 copy[index++] = data[index2++];

      // Copy data back from the temporary array
      for (index = 0; index < range; index++)
	 data[low + index] = copy[index];
   }
}

//------------------------------------------------------------------
// Mergesort implementation without copy array
// Best case O(NlogN) - random data
// Worst case O(NlogN) - random data
// Average case O(NlogN) - random data
//------------------------------------------------------------------
void merge_sort(int data[], int low, int high)
{
   // Check terminating condition
   int range = high - low + 1;
   if (range > 1)
   {
      // Allocate memory and call classic_mergesort
      int *copy = new int[range];
      classic_mergesort(data, copy, low, high);
      delete[]copy;
   }
}

//------------------------------------------------------------------
// Purpose:     Three way merge sort implementation
// Author:      Andrew Murphy
//------------------------------------------------------------------
void threeway_merge(int data[], int copy[], int low, int high)
{
   // Check terminating condition
   int length = high - low;
   if (length > 1)
   {
      // Divide the array and sort each third
      int mid1 = low + (length / 3);
      int mid2 = (mid1 + (length / 3)) + 1;
      threeway_merge(data, copy, low, mid1);
      threeway_merge(data, copy, mid1, mid2);
      threeway_merge(data, copy, mid2, high);
      
      // Initialize array indices
      int pos1 = low;
      int pos2 = mid1;
      int pos3 = mid2;
      int pos = 0;

      // Merge smallest data elements into copy array
      while (pos1 < mid1 && pos2 < mid2 && pos3 < high)
      {
      // 1 > 2
      if (data[pos1] >= data[pos2]) // Flips the '<' to reverse
      {
      if (data[pos1] >= data[pos3]) // Flips the '<' to reverse
	  {     
      copy[pos++] = data[pos1++];
      }   
      else
      {     
	  copy[pos++] = data[pos3++];
      }    
	  } 
      // 2 > 3
      else 
      {
      if (data[pos2] >= data[pos3]) // Flips the '<' to reverse
      {    
      copy[pos++] = data[pos2++];
      }   
      else
      {    
      copy[pos++] = data[pos3++];
      }
      }   
      }
      
        // Puts reversed data elements into copy 
        // array checking 1 and 2
        while((pos2 < mid2) && (pos1 < mid1))
        {
        if(data[pos1] > data[pos2]) // Flips the '<' to reverse
        {
        copy[pos++] = data[pos1++];
        }
        else
        {
        copy[pos++] = data[pos2++];
        }
        }
        // Puts reversed data elements into copy 
        // array checking 3 and 1
        while((pos3 < high) && (pos1 < mid1))
        {
        if(data[pos1] > data[pos3]) // Flips the '<' to reverse
        {
        copy[pos++] = data[pos1++];
        }
        else
        {
        copy[pos++] = data[pos3++];
        }
        }
        // Puts reversed data elements into copy 
        // array checking 3 and 2
        while((pos3 < high) && (pos2 < mid2))
        {
        if(data[pos2] > data[pos3]) // Flips the '<' to reverse
        {
        copy[pos++] = data[pos2++];
        }
        else
        {
        copy[pos++] = data[pos3++];
        }
        }
        
      // Copy any remaining entries from the first third
      while (pos1 < mid1)
	 copy[pos++] = data[pos1++];
     
      // Copy any remaining entries from the second third
      while (pos2 < mid2)
	 copy[pos++] = data[pos2++];

      // Copy any remaining entries from the third third
      while (pos3 < high)
	 copy[pos++] = data[pos3++];

      // Copy data back from the temporary array
      for (pos = 0; pos < length; pos++)
	 data[low + pos] = copy[pos];
   }
}

//------------------------------------------------------------------
// Mergesort implementation without copy array
// Best case O(NlogN) - random data
// Worst case O(NlogN) - random data
// Average case O(NlogN) - random data
//------------------------------------------------------------------
void merge_test(int data[], int low, int high)
{
   // Check terminating condition
   int range = high - low + 1;
   if (range > 1)
   {
      // Allocate memory and call threeway_mergesort
      int *copy = new int[range];
      threeway_merge(data, copy, low, high);
      delete[]copy;
   }
}

//------------------------------------------------------------------
// main program to test sorting functions
//------------------------------------------------------------------
int main()
{
   const int MAX_COUNT = 1000000;
   const int MAX_RANGE = 1000000;
   int data[MAX_COUNT];
   cout << "---------------------------------\n";
   cout << "Welcome to Andrew's Merge Sorter!\n";
   cout << "---------------------------------\n";
   // Prompt user for sort parameters
   cout << "Enter number of data values [1.." << MAX_COUNT << "]:";
   int count;
   cin >> count;
   if (count > MAX_COUNT)
      count = MAX_COUNT;

   cout << "Enter range of data values [1.." << MAX_RANGE << "]:";
   int range;
   cin >> range;
   if (range > MAX_RANGE)
      range = MAX_RANGE;

   // Print input data menu
   cout << "Select initial data:\n"
      << "  r - random data\n";
   char choice;
   cin >> choice;
   
   // Create input data
   if (choice == 'r') 
      create_random_data(data, count, range);
   write_data("sort.in", data, count);

   // Print sorting method menu
   cout << "Select sorting method:\n"
      << "  c - use classic merge sort\n"
      << "  m - use three way merge sort\n"
      << "  e - exit the program\n";
   // Perform requested sort
   cin >> choice;
   Timer t;
   t.start_timer();
   switch (choice)
   {
   case 'c': // Classic merge sort
      merge_sort(data, 0, count - 1);
      break;
   case 'm': // Three way merge sort
      merge_test(data, 0, count);
      break;
   case 'e': // Exit the program
      return 0;
      break;
   }
   t.end_timer();
   cout << "CPU time = " << t.elapsed_cpu() << " sec\n";
   
   // Write output file
   write_data("sort.out", data, count);
}