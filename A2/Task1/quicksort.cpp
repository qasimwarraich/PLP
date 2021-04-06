#include <iostream>
#include <vector>
#include <string>

template <class T>
void print_array(std::vector <T> &arr);

template <class T>
int partition(std::vector <T> &arr, int low, int high)
{
    auto pivot = arr[low];
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



int main()
{
    std::vector <int> v_int = {10, 2, 3, 4, 1, 18, 420, 300, 4000, 3, 1, 8};
    quicksort(v_int, 0, v_int.size() - 1);
    print_array(v_int); 


    std::vector <double> v_dbl = {10.1, 2.2, 3.3, 4.2, 1.3, 1.8, 44.2, 300.1, 400.0, 3.34, 11.0, 8.1};
    quicksort(v_dbl, 0, v_dbl.size() - 1);
    print_array(v_dbl);

    std::vector <char> v_char = {'x', 'a', 'd', 'p'};
    quicksort(v_char, 0, v_char.size() - 1);
    print_array(v_char);

    std::vector <std::string> v_str = {"Bjarne", "What", "ahy", "Have", "You", "Done", "Damn", "Don't"};
    quicksort(v_str, 0, v_str.size() - 1);
    print_array(v_str);
    return 0;
}



template <class T>
void print_array(std::vector <T> &arr)
{
    std::cout << "Vector of type --> " << typeid(arr[0]).name() << '\n';
    for (int i = 0; i <= (int)arr.size() - 1; i++) 
       std::cout << arr[i] << ' ';
    std::cout << '\n';
}


