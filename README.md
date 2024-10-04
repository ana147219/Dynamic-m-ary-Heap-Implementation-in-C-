# Dynamic m-ary Heap Implementation in C++

## Project Description
This project implements a **dynamic m-ary heap** in C++. A dynamic heap is a data structure that efficiently supports insertion, deletion, and search operations. The **m-ary heap** generalizes the binary heap by allowing each node to have more than two children, based on the value of `m`.

The project provides flexible functionality for different values of `m`, enabling advanced operations such as:
- Dynamic insertion of elements
- Removal of the root element
- Key modification within the heap
- Dynamic resizing and reordering of elements
- Merging of two heaps into one
- Conversion of a binary or m-ary heap to another heap with a new `m` value

## Features
- **Insert Elements**: Dynamically inserts elements into the heap while maintaining the heap's structure.
- **Remove Elements**: Removes the root element and reorders the heap accordingly.
- **Key Change**: Allows a node's key to be updated, with the heap adjusting to maintain order.
- **Heap Merge**: Supports the merging of two heaps into one new heap.
- **Convert Heap**: Converts an m-ary heap to a different heap with a new value of `m`.

## Code Overview
- **Insert Function**: Dynamically adds a node into the heap, ensuring that the heap properties are preserved.
- **Remove Function**: Removes the minimum (or root) element from the heap and reorders remaining elements.
- **Change Key**: Modifies a specific key and adjusts the heap to ensure all elements are in proper order.
- **Union of Heaps**: Merges two separate heaps into a single heap with all elements correctly ordered.
- **Conversion**: Converts the heap from one `m` value to another while preserving the heap structure.

## Technologies Used
- **C++**: The entire project is implemented in C++ using object-oriented principles.
- **Data Structures**: The project makes extensive use of dynamic arrays, tree structures, and pointer manipulation.

## How to Run
1. **Clone the repository**:
    ```bash
    git clone https://github.com/ana147219/Dynamic-m-ary-Heap-Implementation-in-Cpp.git
    ```
2. **Compile the program**:
    ```bash
    g++ -o heap main.cpp heap.cpp
    ```
3. **Run the program**:
    ```bash
    ./heap
    ```

## Future Improvements
- **Graphical Interface**: Add a visualization to illustrate how the heap reorders elements dynamically.
- **Optimized Performance**: Implement lazy propagation to improve the time complexity of key changes and heap merges.

## Conclusion
The **Dynamic m-ary Heap** project demonstrates the flexibility of heap-based data structures and their dynamic nature. This implementation provides the foundation for further exploration into efficient data handling using heaps in various scenarios.

