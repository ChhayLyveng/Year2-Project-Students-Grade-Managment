# Student Grade Management System 

A robust C++ CLI application developed for a Year 2 project. This system manages student records, academic performance, and GPA calculations using a **Doubly Linked List** for efficient data handling and **File I/O** for permanent data storage.

## Key Features

* **Data Structure**: Utilizes a custom Doubly Linked List (`struct Element`) to allow bidirectional traversal and efficient deletion of records.
* **Dual-Year Logic**: Specialized course lists and credit weights for Year 1 (25 credits) and Year 2 (20 credits).
* **Dynamic CRUD Operations**: 
    * **Create**: Add new students with validation.
    * **Read**: Search by ID or display filtered lists by academic year.
    * **Update**: Modify specific fields (Name, Age, Scores, etc.) for existing records.
    * **Delete**: Remove students from the linked list by ID.
* **GPA Ranking**: Built-in sorting algorithm to rank students from highest to lowest GPA based on their year.
* **Persistence**: Automatically reads from and writes to `students_year1.csv` and `students_year2.csv` to ensure data is not lost between sessions.
* **User Interface**: Color-coded terminal output using ANSI escape sequences for a professional look and feel.

## Technical Overview

### Data Structure: Doubly Linked List
The project uses a pointer-based linked list where each node (`Element`) contains a `student` object and pointers to both the `next` and `previous` elements. This allows for $O(1)$ insertions at the tail and efficient deletions.



### GPA Calculation Logic
The system calculates the average score based on specific course credits:

$$Average = \frac{\sum (Score_i \times Credit_i)}{Total Credits}$$

* **Year 1**: Weighted across 10 courses
* **Year 2**: Weighted across 8 courses 

## File Structure

* `main.cpp`: The entry point containing the menu loop and user interaction logic.
* `function.h`: The core engine containing structure definitions, memory management, and file handling.
* `*.csv`: Database files used to store student records persistently.

## Getting Started

### Prerequisites
* A C++ compiler (GCC/G++ recommended).
* A terminal that supports ANSI colors (standard on Linux/macOS; use Windows Terminal for PC).

## Sample Menu

1. Add student information
2. Display students information
3. Input student scores by ID
4. Delete student by ID
5. Search students by ID
6. Sort students by GPA
7. Save all records to files
8. Update student based on ID 
9. Exit

