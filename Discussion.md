# Discussion

## Solutions Considered

1. **Line-by-Line Scan**

   - Implementation is simple.

   - Takes O(n) time in worst case (where n is number of lines in 1 TB). 

   - Very large files could be problematic.

2. **Binary Search**

   - Utilizes the fact that the data is sorted chronologically.

   - Locates the target day’s start and end in O(log N) file seeks.

   - There is considerably less work for just one date search.

## Final Solution Summary

- For illustration purposes, the naive approach I show is line by line in `extract_logs.cpp`.

- In operating procedures, or for a 1 TB file, it’s best practice to build an index or conduct a binary search to eliminate non-relevant data.

## Steps to Run

1. Unzip the log file (test_logs.zip -> test_logs.txt).

2. Use g++ to compile the program with the command g++ -o extract_logs extract_logs.cpp -O2.

3. Execute the program with ./extract_logs YYYY-MM-DD.

4. The system will store the output in the folder output with the filename output_YYYY-MM-DD.txt.

