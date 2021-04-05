#include <iostream>
#include <vector>
#include <utility>

template <class T>
void print_array(std::vector <T> &arr);

template <class T>
int partition(std::vector <T> &arr, int low, int high)
{
    int pivot = arr[low];
    int i = low;

    for (int j = i + 1; j <= high; j++) {
        if (arr[j] <= pivot){
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i], arr[low]);
    return i; 
}

template <class T>
void quicksort(std::vector <T> &arr, int low, int high)
{
     if (low < high){

        int pivot = partition(arr, low, high);
        quicksort(arr, low, pivot - 1);
        quicksort(arr, pivot + 1, high);
    }
}


template <class T>
void print_array(std::vector <T> &arr)
{
    for (int i = 0; i <= arr.size() - 1; i++) 
        std::cout << arr[i] << '\n';
}

int main()
{
    std::vector <int> v_int = {10, 2, 3, 4, 1, 18, 420};

    quicksort(v_int, 0, v_int.size() - 1);
    std::cout << "spam = " << v_int.size() << '\n';
    print_array(v_int); 
    return 0;
}
