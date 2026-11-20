# CSA02 – C Programming: Assignment 5

**Modular, Memory-Aware and Persistent Program Engineering (CO5)**

## Student & Environment Details

* **Student Name:** Kaushick V S

* **Register Number:** 1912260163

* **Course Code & Name:** CSA02 – C Programming

* **Case Study:** District Blood Bank Network

* **Compiler & Version:** GCC (TDM-GCC 4.9.2 / MinGW GCC, Dev-C++ default C89/C99 compatible)

  *(Run `gcc --version` in Command Prompt to verify the exact patch version installed on your machine.)*

## Repository Structure

```
CSA02-1912260163-Assignment5/
├── README.md
├── Task_A1/
│   └── Task_A1_Functional_Decomposition.docx
├── Task_A2/
│   └── Task_A2_Design_With_Recursion.docx
├── Task_A3/
│   └── Task_A3_Design_With_Pointers.docx
├── Task_A4/
│   └── Task_A4_Dynamic_Memory_Design.docx
├── Task_A5/
│   └── Task_A5_File_Storage_Design.docx
├── Task_B1/
│   └── task_b1.c
├── Task_B2/
│   └── task_b2.c
├── Task_B3/
│   └── task_b3.c
└── Task_B4/
    └── task_b4.c

```

## Compilation Commands

All Part B C programs are written to compile cleanly with standard `gcc` (including Dev-C++ default mode as well as `-std=c99` / `-std=c11`):

* **Task B1 (Instrumented Recursion):**

  ```
  gcc -Wall -Wextra task_b1.c -o task_b1.exe
  
  ```

* **Task B2 (Adversarial Inputs & CLI Validation):**

  ```
  gcc -Wall -Wextra task_b2.c -o task_b2.exe
  
  ```

* **Task B3 (Binary `fseek` In-Place Update & File Benchmarking):**

  ```
  gcc -Wall -Wextra task_b3.c -o task_b3.exe
  
  ```

* **Task B4 (Dynamic Growable `DonorList`):**

  ```
  gcc -Wall -Wextra task_b4.c -o task_b4.exe
  
  ```

*(Note: If running on Linux/WSL/MSYS2 with AddressSanitizer enabled, append `-g -fsanitize=address` to check heap bounds and leaks.)*

## Steps to Execute Each Program

### 1. Task B1 (`task_b1.exe`)

1. Open Command Prompt in the `Task_B1` directory.

2. Run the default validation and call-count scaling test:

   ```
   task_b1.exe
   
   ```

3. *(Optional)* Test stack overflow depth for linear recursion vs. iterative execution:

   ```
   task_b1.exe s 300000
   task_b1.exe i 10000000
   
   ```

### 2. Task B2 (`task_b2.exe`)

1. Open Command Prompt in the `Task_B2` directory (or pass arguments via **Execute → Parameters...** in Dev-C++).

2. Execute the adversarial test cases:

   ```
   task_b2.exe
   task_b2.exe find O+
   task_b2.exe find Z+
   task_b2.exe issue A- 2
   task_b2.exe issue A- -5
   task_b2.exe filetest missing_donors.txt r
   task_b2.exe nametest
   task_b2.exe memtest
   
   ```

### 3. Task B3 (`task_b3.exe`)

1. Open Command Prompt in the `Task_B3` directory.

2. Execute the binary `fseek` in-place update program:

   ```
   task_b3.exe
   
   ```

### 4. Task B4 (`task_b4.exe`)

1. Open Command Prompt in the `Task_B4` directory.

2. Execute the geometric-doubling dynamic array program:

   ```
   task_b4.exe
   
   ```

## Summary of Results

### Part A – Design & Pseudocode

* **Task A1 (Functional Decomposition):** Divided the District Blood Bank system into 9 single-responsibility functions with a structure chart, `const`-correct pointer/value interfaces, and two designs (output pointers vs. return struct) for returning multiple summary values.

* **Task A2 (Design with Recursion):** Designed recursive pseudocode for `DigitalRoot` and divide-and-conquer `PowerFast`, traced deepest call stacks, derived recurrences ($T(n) = O(n)$ vs. $O(\log n)$), and compared recursion against loops and the $O(1)$ congruence formula.

* **Task A3 (Design with Pointers):** Illustrated pointer arithmetic (`p + 3`, `*(p + 3)`, `p[3]`, `*p++`) with memory diagrams, designed a safe pointer-returning minimum-stock search, and specified `argc`/`argv` CLI validation.

* **Task A4 (Dynamic Memory Design):** Designed a geometrically doubling `DonorList` using a temporary pointer with `realloc()` to prevent pointer loss on failure, and analyzed memory leaks, dangling pointers, and double frees.

* **Task A5 (File Storage Design):** Justified human-readable CSV text storage for variable-length donor records and fixed-size binary records for `O(1)` in-place `fseek`/`fread`/`fwrite` stock updates.

### Part B – Implementation & Experimental Investigation

* **Task B1:** Verified `power_linear(2, 30)` completes in **31 calls** ($n + 1$) while `power_fast(2, 30)` completes in **6 calls** ($\lfloor \log_2 n \rfloor + 2$). Removing memoization (`power_fast(base, exp/2) * power_fast(base, exp/2)`) degrades call count back to $O(n)$, and deep linear recursion triggers a stack overflow whereas iteration runs in $O(1)$ stack space.

* **Task B2:** Demonstrated safe bounded input truncation using `fgets()` + input buffer flushing, graceful system error reporting via `perror()` on missing files, strict `argc`/`argv` and `strtol()` validation, and leak-free heap cleanup (`free(ptr); ptr = NULL;`).

* **Task B3:** Confirmed `update_units()` updates record `3` (`4:8` $\rightarrow$ `4:20`) in place using `fseek()` while safely failing on out-of-bounds record `9` without corrupting existing records (`1:40 2:25 3:12 4:20 5:30`).

* **Task B4:** Verified geometric capacity doubling (`0 -> 2 -> 4 -> 8`) as 5 donors are appended to `DonorList`, preserving existing pointers safely on `realloc()` and freeing all heap memory prior to exit.