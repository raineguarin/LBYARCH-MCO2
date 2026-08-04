.code

public calculateDistanceASM

calculateDistanceASM proc
    ;   Windows x4 Calling Conventions
    ;   rcx = n
    ;   rdx = X1
    ;   r8  = X2
    ;   r9  = Y1
    ;   r10 = Y2
    ;   r11 = Z
    ;   [rsp + 40] = Y2
    ;   [rsp + 48] = Z

    test rcx, rcx           ; test n, n | check if n <= 0
    jle done                ; return if n <= 0

    ; load stack 5 and 6 arguments into the registers
    mov r10, QWORD PTR [rsp + 40] 
    mov r11, QWORD PTR [rsp + 48] 

    xor rax, rax            ; set i = 0

L1:
    movsd xmm0, QWORD PTR [r8  + rax*8]  
    subsd xmm0, QWORD PTR [rdx + rax*8]
    mulsd xmm0, xmm0

    movsd xmm1, QWORD PTR [r10 + rax*8]
    subsd xmm1, QWORD PTR [r9  + rax*8]
    mulsd xmm1, xmm1

    addsd xmm0, xmm1
    sqrtsd xmm0, xmm0

    movsd QWORD PTR [r11 + rax*8], xmm0

    inc rax
    cmp rax, rcx
    jl L1

; keep the blank new line at the end to avoid error in compilation
done:
    ret
calculateDistanceASM endp

end