#ifndef SORT_H
#define SORT_H

/* Sort.h
 * Holds the information for the Recursive Sorts used in this
 * project - Merge and Quick.
 */

// Includes files.
#include <iostream>
using namespace std;

class Sort 
{
    public:
        // QuickSort()
        // Sorts the information in arr by the way of quicksort.
        static void quicksort(int *arr, int size)
        {
            quicksort(arr, 0, size-1);
        }

        // MergeSort()
        // Sorts the information in arr by the way of mergesort.
        static void mergesort(int *arr, int size)
        {
            mergesort(arr, 0, size-1);
        }
        
        // Print()
        // Prints an array of information of length size.
        static void print(int *arr, int size) 
        {
            // Prints all information inside of arr.
            cout << "ARRAY: ";
            for(int i = 0; i < size; i++) 
                cout << arr[i] << " ";
            cout << endl;
        }

    private:
        // QuickSort()
        // Helper function to do the quick sort operation.
        static void quicksort(int *arr, int left, int right)
        {
            // If we have something to sort, then do so.
            if(left < right) 
            {
                // Calculate the pivot
                int pivot = partitionLists(arr, left, right);
                
                // Divide the list at the pivot point.
                quicksort(arr, left, pivot - 1);
                quicksort(arr, pivot + 1, right);
            }
        }
        
        // partitionLists()
        // Helper function to do the quick sort operation.
        static int partitionLists(int *arr, int left, int right) 
        {
            // Get the pivot (right value)
            int pivot = arr[right], i = left - 1;
            
            // Go through the entire list from left to right.
            for(int j = left; j <= right - 1; j++)
            {
                // See if we need to swap sides.
                if(arr[j] <= pivot) 
                {
                    i++;
                    swap(arr[i], arr[j]);
                }
            }
            
            // Swap the pivot in the right place.
            swap(arr[i+1], arr[right]);
            
            // Return the location of the pivot.
            return i+1;
        }
        
        // Swap()
        // Used to swap two values together.
        static void swap(int &first, int &second) 
        {
            int temp = first;
            first = second;
            second = temp;
        }
        
        // MergeSort()
        // Helper function to do mergesort operations.
        static void mergesort(int *arr, int left, int right)
        {
            // If we have a list to sort.
            if(left < right) 
            {
                // Calculate the midpoint of the array.
                int mid = (left + right) / 2;
                
                // Divide the list into 2.
                mergesort(arr, left, mid);
                mergesort(arr, mid+1, right);
                
                // Merge the lists at the end.
                mergeLists(arr, left, mid, right);
            }
        }
        
        // mergeLists()
        // Helper function to do merge two smaller sets together.
        static void mergeLists(int *arr, int left, int mid, int right) 
        {
            // Calculate the left and right sublists.
            int i, j, k, n1 = mid - left + 1, n2 = right - mid;
            int Left[n1], Right[n2];
            
            // Create the left and right sublists.
            for(i = 0; i < n1; i++)
                Left[i] = arr[left + i];
            for(j = 0; j < n2; j++)
                Right[j] = arr[mid + j + 1];
            
            // Start initial pointers.
            i = j = 0;
            k = left;
            
            // While there are elements to be sorted on either side
            // Then put them into array in right locations.
            while(i < n1 && j < n2) 
            {
                // If left goes first, then it goes in.
                // Otherwise put right in first.
                if(Left[i] <= Right[j])
                {
                    arr[k] = Left[i];
                    i++;
                }
                else 
                {
                    arr[k] = Right[j];
                    j++;
                }
                k++;
            }
            
            // If there are elements in left that still need to be
            // processed, then put them in.
            while(i < n1) 
            {
                arr[k] = Left[i];
                i++;
                k++;
            }
            
            // If there are elements in right that still need to be
            // processed, then put them in.
            while(j < n2) 
            {
                arr[k] = Right[j];
                j++;
                k++;
            }
        }
};

#endif /* SORT_H */