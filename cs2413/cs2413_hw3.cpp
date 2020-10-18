// CS 2413 Homework 3
// Author: Matthew Carroll
// Date: 10/17/2020
// Sort an input of integers in descending order by bubble or merge+selection sort.
// Implemented using in place methods where possible

#include <iostream>
#include <vector>

void swap(std::vector<int>* List, int a, int b) {
    //Swap the elements of the vector at given indexes a and b
    int temp = List->at(a);
    List->at(a) = List->at(b);
    List->at(b) = temp;
}

void BubbleUp(std::vector<int>* List, int sorted) {
    //sorted denotes which pass the function is on, how many elements are already sorted
    for (int i = 0; i < (List->size() - (1 + sorted)); i++) {
        if (List->at(i) < List->at(i + 1)) {
            swap(List, i, i + 1);
        }
    }
}

int GetIndexofMin(std::vector<int>* List, int start_index) { //Get the index of the smallest value from the List, starting at the start index
    int indexof_min = start_index;
    for (int i = start_index; i < List->size(); i++) {
        if (List->at(i) < List->at(indexof_min)) indexof_min = i;
    }
    return indexof_min;
}

void SelectionSort(std::vector<int>* List) { //Makes the list sorted ascending
    for (int i = 0; i < List->size(); i++) {
        swap(List, i, GetIndexofMin(List, i));
    }
}

void Merge(std::vector<int>* a, std::vector<int>* b, std::vector<int>* output) {

    while ((a->size() != 0) && (b->size() != 0)) { //While the sublists still have elements
        if (a->back() > b->back()) {               //Push the larger of the two back elements into the output.
            output->push_back(a->back());
            a->pop_back();
        }
        else {
            output->push_back(b->back());
            b->pop_back();
        }
    }

    for (int i = a->size(); i > 0; i--) { //Push the remaining elements into the output
        output->push_back(a->back());
        a->pop_back();
    }
    for (int i = b->size(); i > 0; i--) {
        output->push_back(b->back());
        b->pop_back();
    }
}

int main() {
    
    //INPUT the task and input all the values in the unsorted list
    int Task;
    std::cin >> Task;
    int input;
    std::vector<int> List;

    while (std::cin >> input) {
        List.push_back(input);
    }

    //SORTING
    if (Task == 0) { //If the task is to bubble sort

        for (int i = 0; i < List.size(); i++) { //Keep bubbling up until you get to the end of the array
            BubbleUp(&List, i);
        }

    } else if (Task == 1) {

        std::vector<int> Split[2]; //Array storing each half of the List as vectors

        int half = List.size() / 2;
        for (int i = 0; i < half; i++) { //Split the List into two smaller lists by pushing each element
            Split[0].push_back(List.at(i));
            Split[1].push_back(List.at(i + half));
        }

        SelectionSort(&Split[0]);
        SelectionSort(&Split[1]);

        List.clear();
        Merge(&Split[0], &Split[1], &List);
    }


    //OUTPUT each element in order
    for (int i = 0; i < List.size(); i++) {
        std::cout << List.at(i) << " ";
    }
}