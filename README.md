**Video**

Demo vid: https://www.youtube.com/watch?v=3nrgrpw4CGA

**Specifications**

Write the kernel in (1) C program and (2) an x86-64 assembly language.  The kernel must calculate the distances between the coordinate points across two vectors.

*Required to use functional scalar SIMD registers
*Required to use functional scalar SIMD floating-point instructions

Input: Scalar variable n (integer) contains the length of the vector; Vectors X1, X2, Y1, Y2, and Z are double-precision float.

Example:

X1 -> 1.5, 4.0, 3.5, 2.0

X2 -> 3.0, 2.5, 2.5, 1.0

Y1 -> 4.0, 3.0, 3.5, 3.0

Y2 -> 2.0, 2.5, 1.0, 1.5

(answer)
Z -> 2.5, 1.58113883, 2.692582404, 1.802775638

Output: store result in vector Z.  Display the result of 1st ten elements of vector Z for all versions of kernel (i.e., C and x86-64).

**Program Output Screenshot** 

<img width="1413" height="961" alt="181b8c61-e1a2-4fd1-a2e6-e87c14ee8a32" src="https://github.com/user-attachments/assets/8a77e344-ea55-4815-b2aa-0184e34055b8" />



**Comparative Analysis** 

Comparing C and x86-64 we can obviously see that Assembly is way faster. One thing to note is that C had more modifications done to it to make it faster.
But in this case it did not help much as it was still slower. C was never even close to the time of Assembly. While it may seem like both had similar performance that is actually not true, 
Assembly in each case was roughly twice as fast as C. This highlights just how much time Assembly can save. Overall performance is good but could be even better, 
but its clear that assembly is way faster.

Unfortunately as well we could not run it in 2^28. It took too long and would sometimes just not work. So we had to settle for 26 instead. 


Note:

1.) Write a C main program to call the kernels of the C version and x86-64 assembly language.

2.) Time the kernel portion only.  

3.) For each kernel version, time the process for vector size n = {220, 224, and  230}.  If 230 is impossible, you may reduce it to the point your machine can support (i.e.,  228 or 229).

4.) You must run at least 30 times for each version to get the average execution time. 

5.) For the data, you may initialize each vector and scalar variable with the same or different random value. 

6.) You will need to check the correctness of your output.  Thus, if the C version is your "sanity check answer key," then the output of the x86-64 version has to be checked with the C version and output correspondingly (i.e., the x86-64 kernel output is correct, etc.).

7.) Output in GitHub (make sure that I can access your Github):

a.) Github readme containing the following (C and x86-64):

        i.) comparative execution time and short analysis of the performance of the kernels

       ii.) Take a screenshot of the program output with the correctness check (C).

       iii.) Take a screenshot of the program output, including the correctness check (x86-64).

       iv.) short videos (5-10mins) showing your source code, compilation, and execution of the C and x86-64 program

b.) Visual Studio project folder containing complete files (source code: C, x86-64, and all other required files) for others to load and execute your program.


