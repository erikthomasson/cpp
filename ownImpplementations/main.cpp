
#include "insertionSort.cpp"

int main(){
    int arr[] = { 12, 11, 13, 5, 6 }; 
    int n = sizeof(arr) / sizeof(arr[0]); 
  
    insertionSort(arr, n); 
    print(arr, n); 
  
    
}


