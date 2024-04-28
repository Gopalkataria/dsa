// Test Case 1: Empty list
// Expected Output: NULL
Node* test_case1 = NULL;
Node* sorted_list1 = mergesortll(test_case1);
printf("Sorted List 1: ");
printList(sorted_list1);
printf("\n");

// Test Case 2: List with a single element
// Expected Output: 5
Node* test_case2 = createNode(5);
Node* sorted_list2 = mergesortll(test_case2);
printf("Sorted List 2: ");
printList(sorted_list2);
printf("\n");

// Test Case 3: List with multiple elements in ascending order
// Expected Output: 1 -> 2 -> 3 -> 4 -> 5
Node* test_case3 = createNode(1);
append(&test_case3, 2);
append(&test_case3, 3);
append(&test_case3, 4);
append(&test_case3, 5);
Node* sorted_list3 = mergesortll(test_case3);
printf("Sorted List 3: ");
printList(sorted_list3);
printf("\n");

// Test Case 4: List with multiple elements in descending order
// Expected Output: 5 -> 4 -> 3 -> 2 -> 1
Node* test_case4 = createNode(5);
append(&test_case4, 4);
append(&test_case4, 3);
append(&test_case4, 2);
append(&test_case4, 1);
Node* sorted_list4 = mergesortll(test_case4);
printf("Sorted List 4: ");
printList(sorted_list4);
printf("\n");

// Test Case 5: List with multiple elements in random order
// Expected Output: -10 -> 0 -> 5 -> 10 -> 15 -> 20
Node* test_case5 = createNode(0);
append(&test_case5, 10);
append(&test_case5, -10);
append(&test_case5, 20);
append(&test_case5, 5);
append(&test_case5, 15);
Node* sorted_list5 = mergesortll(test_case5);
printf("Sorted List 5: ");
printList(sorted_list5);
printf("\n");