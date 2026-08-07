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

Comparing C and x86-64 we can obviously see that Assembly has a faster average execution time. One thing to note is that C had more modifications done to it to make it faster and more precise.
But in this case making it more precise did not help as much as we had though. C was never even close to the time of Assembly. While it may seem like both had similar performance that is actually not true, 
Assembly in each case was roughly twice as fast as C. This highlights just how much time Assembly can save. Overall their average execution times vary quite a bit and it shows
how much faster assembly can be. The only time the gap between C and Assembly shortened was in the 2^26 test which does not really say much about C but we can see assembly struggling a bit more
with the increase in size. 

Unfortunately as well we could not run it in 2^28. It took too long and would sometimes just not work. So we had to settle for 26 instead.

