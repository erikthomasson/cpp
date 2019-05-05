

#include <vector>
#include <iostream>





void print(int arr[],int n){
    
    std::cout<<'{';

    for(int i=0; i < n; i++){
        std::cout<<arr[i]<< ", ";
    }
    std::cout<<'}'<<std::endl;    
}

void insertionSort(int arr[], int n){
    int i, j, key; 
    for (i = 1; i < n; i++){ 
        key = arr[i]; 
        j = i - 1; 
  
        /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
        while (j >= 0 && arr[j] > key) { 
            arr[j + 1] = arr[j]; 
            j--; 
        } 
        arr[j + 1] = key; 
    } 

}
