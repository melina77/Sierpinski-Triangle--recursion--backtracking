/* File Synopsis:
 * This file contains the quickSort function along with helper and testing functions. The quickSort function
 * recursively partitions a linked list into three separate lists and merges them together into a fully
 * sorted list.
 *
 * Outside help: I received advice from Shreya Pandey regarding the partition function. I was previously
 * sorting new elements into the greaterThan and lessThan lists by traversing through those lists and adding
 * the new element to the end of the lists. She advised me to add the element to the front of the list
 * instead which ultimately improved efficiency and runtime.
 */

#include "listnode.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;

ListNode* concatenate(ListNode*& lessThan, ListNode*& pivot, ListNode*& greaterThan);
void partition(ListNode*& lessThan, ListNode*& pivot, ListNode*& greaterThan);

/* Function Synopsis:
 * This function is passed a linked list by reference and recursively sorts the list by partitioning it then
 * concatenating the separate sorted lists. Nothing is returned since the ListNode is passed by reference.
 */
void quickSort(ListNode*& front) {

    if(front == nullptr || front->next == nullptr){//base case
        return;
    }

    //else: recursive case

    ListNode* less = nullptr;
    ListNode* greater = nullptr;

    partition(less,front,greater);

    quickSort(less);
    quickSort(greater);

    front = concatenate(less, front, greater);
}

/* Function Synopsis:
 * This is a helper function for the quickSort function. It operates iteratively to sort a given list of
 * numbers in ascending order. Three ListNode pointers are passed in by reference to be altered, and nothing
 * is returned. All values in the list that are less than the pivot value at the front of the list are added
 * to the lessThan list. All values greater than the pivot are added to the greaterThan list.
 */
void partition(ListNode*& lessThan, ListNode*& pivot, ListNode*& greaterThan){
    int piv = pivot->data;//original pivot value, does not get changed
    ListNode* prev = pivot;//value before cur, for sake of setting managing pointers
    ListNode* cur = pivot->next;//next in pivot, traverses through it
    ListNode* next = pivot->next->next;//value after cur in pivot, for sake of linking with prev when a node is added to another linked list

    while(cur != nullptr){
        if(cur->data < piv){
            if(lessThan!=nullptr){
                cur->next = lessThan;//concatenates the rest of the lessThan list to the cur
                lessThan = cur;//makes cur the new lessThan list
            }
            else{
                cur->next = nullptr;//so that the rest of the list doesn't get added to lessThan
                lessThan = cur;
            }
            prev->next = next;//relinks the list so that the data item taken out is no longer in the list
            cur = prev->next;
            if(cur == nullptr){
                break;
            }
            if(cur->next != nullptr){
                next = cur->next;
            }
            else{
                next = nullptr;
            }
        }

        else if(cur->data > piv){
            if(greaterThan!=nullptr){
                cur->next = greaterThan;//concatenates the rest of the greaterThan list to the cur
                greaterThan = cur;//makes cur the new greaterThan list
            }
            else{
                cur->next = nullptr;//so that the rest of the list doesn't get added to greaterThan
                greaterThan = cur;
            }
            prev->next = next;//relinks the list so that the data item taken out is no longer in the list
            cur = prev->next;
            if(cur == nullptr){
                break;
            }
            if(cur->next != nullptr){
                next = cur->next;
            }
            else{
                next = nullptr;
            }
        }

        else{//just need to rewire list if the data item is equal to pivot, it stays in the correct list
            prev = cur;
            cur = cur->next;

            if(cur != nullptr && cur->next != nullptr){
                next = cur->next;
            }
            else{
                next = nullptr;
            }
        }
    }
}



ListNode* concatenate(ListNode*& lessThan, ListNode*& pivot, ListNode*& greaterThan){
    ListNode* result = nullptr;
    if(lessThan != nullptr && greaterThan != nullptr){//if greaterThan and lessThan are both not null then pivot is also not null
        result = lessThan;//since lessThan is not null, the final linked list result will start with the first element of lessThan
        ListNode* cur = lessThan;

        while(cur->next != nullptr){
            // points to next element in linked list until end of list is reached
            cur = cur->next;
        }

        cur->next = pivot;//links smaller list to 1st elem in pivot list

        while(cur->next != nullptr){
            //gets to last element in pivot
            cur = cur->next;
        }

        cur->next = greaterThan;//links the smallest and pivot list to the greaterThan list

    }
    else if(lessThan == nullptr){//lessThan is the only nullptr
        result = pivot;//since lessThan is null, the final linked list result will start with the first element being the pivot
        ListNode* cur = pivot;

        while(cur->next != nullptr){
            //cur points to next element in linked list until end of list is reached
            cur = cur->next;
        }

        cur->next = greaterThan;//links pivot list to 1st elem in larger list
    }
    else{//greaterThan is the only nullptr
        result = lessThan; //since only greaterThan is null, the final linked list will start with the first elem in lessThan
        ListNode* cur = lessThan;

        while(cur->next != nullptr){
            //cur points to next element in linked list until end of list is reached
            cur = cur->next;
        }

        cur->next = pivot;//links smaller list to 1st elem in pivot list
    }
    return result;
}



/* * * * * * Test Code Below This Point * * * * * */

/*
 * We have provided this utility function as a convenience. This
 * function traverses the linked list represented by the provided
 * front pointer and prints out the data stored in the list along
 * the way in a convenient format. You may find it to be helpful to
 * use this function as a debugging aid.
 */
void printList(ListNode* front) {
    cout << "{";
    for (ListNode *cur = front; cur != nullptr; cur = cur->next) {
        cout << cur->data;
        if (cur->next != nullptr){
            cout << ", ";
        }
    }
    cout << "}" << endl;
}

/*
 * This utility function deallocates the memory for all the nodes in a
 * given linked list. It can be used to recycle the memory allocated
 * during a test case and avoid memory leaks.
 */
void deallocateList(ListNode* front) {
    /* TODO: Implement this function. */
    //psuedo-code: two pointers - one to prev and one to cur, when cur->next is nullptr (end of linked list), deallocate cur and make prev the new cur and keep going down the list deallocating every cur along the way
    if(front != nullptr){
        ListNode* prev = front;
        ListNode* cur = front->next;
        if(cur!=nullptr){
            while(cur->next != nullptr){//get to the last element, delete all previous along the way
                delete[] prev;
                prev = cur;
                cur = cur->next;
                //delete[] prev;
            }
            delete[] prev;
            delete[] cur;//delete last element
        }
        else{//only 1 elem in list
            delete[] prev;
        }
    }
}

/*
 * This utility function is given a vector of values and constructs
 * an equivalent linked list containing the same values in the same order.
 * It can be used to construct a linked list to use as an input to
 * a function being tested.
 */
ListNode* createList(Vector<int> values){
    ListNode * next = nullptr;
    ListNode * cur = new ListNode(values[values.size()-1],next);//will always be front of linked list
    for(int i = values.size()-2; i>-1; i--){
        next = new ListNode(values[i], cur);
        cur = next;
    }
    return cur;
}

/*
 * This utility function compares a linked list and a vector for
 * equivalence and returns true if both contain the same values in the
 * same order. It can be used to confirm a linked list's contents match
 * the expected.
 */
bool areEquivalent(ListNode* front, Vector<int> v){
    /* TODO: Implement this function. */
    ListNode* cur = front;
    ListNode * next = nullptr;
    for(int i = 0; i<v.size(); i++){
        if(cur == nullptr){
            return false;
        }
        next = cur->next;
        if(v[i] != cur->data){
            return false;
        }
        cur = next;
    }
    //if it gets to this point, all values in the vector and linked list have been the same
    if(cur!= nullptr){
        return false;
    }

    return true;
}

STUDENT_TEST("Testing the partition function, simple input"){
    Vector<int> values = {4,7,3,9,2};
    Vector<int> expectLT = {2,3};
    Vector<int> expectP = {4};
    Vector<int> expectGT = {9,7};

    ListNode* lessThan = nullptr;
    ListNode* greaterThan = nullptr;
    ListNode* vals = createList(values);

    partition(lessThan,vals,greaterThan);

    EXPECT(areEquivalent(lessThan,expectLT));
    EXPECT(areEquivalent(vals,expectP));
    EXPECT(areEquivalent(greaterThan,expectGT));

    deallocateList(lessThan);
    deallocateList(vals);
    deallocateList(greaterThan);
}

STUDENT_TEST("Time linked list quicksort (500000)") {
    int startSize = 500000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v(n);
        ListNode* list = nullptr;
        for (int i = n-1; i >= 0; i--) {
            list = new ListNode(v[i], list);
        }

        TIME_OPERATION(n, quickSort(list));

        deallocateList(list);
    }
}



STUDENT_TEST("Testing the concatenate function"){
    Vector<int> valuesExpected = {2,3,4,7,9};
    Vector<int> LT = {2,3};
    Vector<int> P = {4};
    Vector<int> GT = {7,9};

    ListNode* lessThan = createList(LT);
    ListNode* greaterThan = createList(GT);
    ListNode* pivot = createList(P);
    ListNode* final = concatenate(lessThan, pivot, greaterThan);

    EXPECT(areEquivalent(final,valuesExpected));

    deallocateList(lessThan);

}

STUDENT_TEST("Simple input for quickSort"){
    /* Initialize vector to sequence of values */
    Vector<int> values = {1, 2, 3, 4};
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);

    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}

STUDENT_TEST("Complicated input for quickSort"){
    Vector<int> values = {77, 3, -5, 61, 434, 60, 77, 76, 21, 33, -890, 46};
    ListNode* list = createList(values);

    quickSort(list);
    values.sort();
    EXPECT(areEquivalent(list, values));
    deallocateList(list);
}

STUDENT_TEST("All same number input for quickSort"){
    Vector<int> values = {3, 3, 3, 3};
    ListNode* list = createList(values);

    quickSort(list);
    values.sort();
    EXPECT(areEquivalent(list, values));
    deallocateList(list);
}

STUDENT_TEST("No smaller than list quickSort call"){
    Vector<int> values = {1, 56, 234, 9958};
    ListNode* list = createList(values);

    quickSort(list);
    values.sort();
    EXPECT(areEquivalent(list, values));
    deallocateList(list);
}

STUDENT_TEST("No greater than list quickSort call"){
    Vector<int> values = {1, 2, 3, 4};
    ListNode* list = createList(values);

    quickSort(list);
    values.sort();
    EXPECT(areEquivalent(list, values));
    deallocateList(list);
}

STUDENT_TEST("All negative inputs quickSort call"){
    Vector<int> values = {-19, -256, -3, -469};
    ListNode* list = createList(values);

    quickSort(list);
    values.sort();
    EXPECT(areEquivalent(list, values));
    deallocateList(list);
}

STUDENT_TEST("Reverse order sorted inputs quicksort call"){
    Vector<int> values = {-1, -25, -37, -46};
    ListNode* list = createList(values);

    quickSort(list);
    values.sort();
    EXPECT(areEquivalent(list, values));
    deallocateList(list);
}

STUDENT_TEST("Single number input quickSort call"){
    Vector<int> values = {-1};
    ListNode* list = createList(values);

    quickSort(list);
    values.sort();
    EXPECT(areEquivalent(list, values));
    deallocateList(list);
}

STUDENT_TEST("Time linked list concatenate (500000)") {//to confirm that runtime is O(N)
    int startSize = 500000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v(n);
        ListNode* list = nullptr;
        ListNode* less = nullptr;
        ListNode* greater = nullptr;

        for (int i = n-1; i >= 0; i--) {
            list = new ListNode(v[i], list);
        }

        partition(less,list,greater);
        TIME_OPERATION(n, concatenate(less, list, greater));

        deallocateList(list);
    }
}

STUDENT_TEST("Time linked list partition (500000)") {//to confirm that runtime is O(N)
    int startSize = 500000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v(n);
        ListNode* list = nullptr;
        ListNode* less = nullptr;
        ListNode* greater = nullptr;

        for (int i = n-1; i >= 0; i--) {
            v[i] = randomInteger(-10000, 10000);
            list = new ListNode(v[i], list);
        }

        TIME_OPERATION(n, partition(less, list, greater));

        deallocateList(list);
        deallocateList(less);
        deallocateList(greater);
    }
}



STUDENT_TEST("Time linked list worst case quicksort (1000)") {
    int startSize = 1000;

        Vector<int> v;
        ListNode* list = nullptr;

        for (int i = startSize-1; i >= 0; i--) {
            v.add(i);
        }

        list = createList(v);
        TIME_OPERATION(startSize, quickSort(list));
        deallocateList(list);
}

STUDENT_TEST("Time linked list worst case quicksort (2000)") {
    int startSize = 2000;

        Vector<int> v;
        ListNode* list = nullptr;

        for (int i = startSize-1; i >= 0; i--) {
            v.add(i);
        }

        list = createList(v);
        TIME_OPERATION(startSize, quickSort(list));
        deallocateList(list);
}

STUDENT_TEST("Time linked list worst case quicksort (4000)") {
    int startSize = 4000;

        Vector<int> v;
        ListNode* list = nullptr;

        for (int i = startSize-1; i >= 0; i--) {
            v.add(i);
        }

        list = createList(v);
        TIME_OPERATION(startSize, quickSort(list));
        deallocateList(list);
}

STUDENT_TEST("Time linked list worst case quicksort (800)") {
    int startSize = 8000;

        Vector<int> v;
        ListNode* list = nullptr;

        for (int i = startSize-1; i >= 0; i--) {
            v.add(i);
        }

        list = createList(v);
        TIME_OPERATION(startSize, quickSort(list));
        deallocateList(list);
}



PROVIDED_TEST("This tests some of the testing helper functions you are recommended to implement."){
    /* Creates a small test list containing the values 1->2->3. */
    ListNode* testList = nullptr;
    testList = new ListNode(3, testList);
    testList = new ListNode(2, testList);
    testList = new ListNode(1, testList);

    /* Test equality comparison function. */
    EXPECT(areEquivalent(testList, {1, 2, 3}));
    EXPECT(!areEquivalent(testList, {1, 2}));
    EXPECT(!areEquivalent(testList, {1, 2, 3, 4}));
    EXPECT(!areEquivalent(testList, {1, 3, 2}));

    /* Test create list function. */
    ListNode* studentList = createList({1, 2, 3, 4});
    printList(studentList);
    ListNode* cur = studentList;
    for (int i = 1; i <= 4; i++){
        EXPECT(cur != nullptr);
        EXPECT_EQUAL(cur->data, i);
        cur = cur->next;
    }

    /* Test deallocate list functions. There should be no memory leaks from this test. */
    deallocateList(studentList);
    deallocateList(testList);
}

/*
 * The provided test case demonstrates a comparsion between the same
 * algorithm (quicksort) operating on a linked list versus a vector.
 */
PROVIDED_TEST("Time linked list quicksort vs vector quicksort") {
    int startSize = 5000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v(n);
        ListNode* list = nullptr;

        /* Create linked list and vector with the same random sequence. */
        for (int i = n-1; i >= 0; i--) {
            v[i] = randomInteger(-10000, 10000);
            list = new ListNode(v[i], list);
        }

        /* NOTE: This test does not check correctness of the linked list sort
         * function. It only times the two operations to compare relative speed. */
        TIME_OPERATION(n, quickSort(list));
        TIME_OPERATION(n, v.sort());        /* Standard vector sort operation is backed
                                               with quicksort algorithm. */

        deallocateList(list);
    }
}

STUDENT_TEST("Making sure that deallocateList function works properly"){
    int startSize = 10000000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        ListNode* list = nullptr;

        /* Create linked list with random sequence. */
        for (int i = n-1; i >= 0; i--) {
            list = new ListNode(50, list);
        }

        deallocateList(list);
    }
}

STUDENT_TEST("Testing the partition function"){
    Vector<int> vals = {6,3,6,6,7,2,1,6,777,2,2,4,145,-13};
    Vector<int> lessExpected = {-13,4,2,2,1,2,3};
    Vector<int> greaterExpected = {145,777,7};
    Vector<int> pivExpected = {6,6,6,6};

    ListNode * valsList = createList(vals);
    ListNode * less = nullptr;
    ListNode * greater = nullptr;

    partition(less,valsList, greater);
    EXPECT(areEquivalent(less, lessExpected));
    EXPECT(areEquivalent(greater, greaterExpected));
    EXPECT(areEquivalent(valsList, pivExpected));

    cout<<"done"<<endl;
    deallocateList(valsList);
    deallocateList(less);
    deallocateList(greater);
}

STUDENT_TEST("Testing the createList function"){
    Vector<int> vals = {1,2,3,4,7};
    ListNode * valsList = createList(vals);
    ListNode* cur = valsList;
    ListNode * next = nullptr;

    for(int i = 0; i<vals.size(); i++){
        if(cur == nullptr){
            error("The linked list is shorter than the vector");
        }
        next = cur->next;
        if(vals[i] != cur->data){
            error("A value in the vector and the linked list do not match.");
        }
        cur = next;
    }
    //if it gets to this point, all values in the vector and linked list have been the same
    if(cur!= nullptr){
        error("The linked list is longer than the vector");
    }

    deallocateList(valsList);

}

STUDENT_TEST("Testing areEquivalent"){
    Vector<int> vals = {1,2,3,4,7};
    ListNode * valsList = createList(vals);
    EXPECT_EQUAL(areEquivalent(valsList, vals), true);

    Vector<int> notSameVals = {5,3,2,6,3};//same size vector, but different values
    Vector<int> slightlyOffVals = {1,2,3,4,5};//same size vector, last item is different
    Vector<int> veryDiffVals = {7,7,7,73,4,3,7};//different size vector and different values

    EXPECT_EQUAL(areEquivalent(valsList, notSameVals), false);
    EXPECT_EQUAL(areEquivalent(valsList, slightlyOffVals), false);
    EXPECT_EQUAL(areEquivalent(valsList, veryDiffVals), false);

    deallocateList(valsList);

}
