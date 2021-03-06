; VS assembly prologue explanation

; EBP - the base pointer, the frame pointer
; ESP - the stack pointer
; When a value is pushed on the stack, the value of ESP register is decremented to the size of pushed
; value, as stack grows downwards.


012718C0 55                   push        ebp                     ; Save current frame pointer on stack
012718C1 8B EC                mov         ebp,esp                 ; Activate the new frame for callee
012718C3 81 EC C0 00 00 00    sub         esp,0C0h                ; 0C0h = 192, set ESP at the end of the frame

; Above instructions establish a new stack frame whithin the callee, while preserving the stack frame of 
; the caller. Now we can use fixed offsets relative to EBP to access passed parameters and local variables.
; EBP is fixed, but ESP is moving and is free to continue being modified

012718C9 53                   push        ebx  
012718CA 56                   push        esi  
012718CB 57                   push        edi  

; C/C++ functions shouldn't alter these three registers in this build configuration, so save them
; These are stored below our stack frame
  
012718CC 8D BD 40 FF FF FF    lea         edi,[ebp-0C0h]  

; This puts the address of the stack frame bottom (lowest address) into edi

012718D2 B9 30 00 00 00       mov         ecx,30h                  ; 30h = 0C0h/4, ‘rep stos’ will be executed 48 times
012718D7 B8 CC CC CC CC       mov         eax,0CCCCCCCCh           ; Set parameter of ‘rep stos’ instrument
012718DC F3 AB                rep stos    dword ptr es:[edi]       ; Use the value of eax (0CCCCCCCCh) to initialize stack

; ...
0127190E 5F                   pop         edi  
0127190F 5E                   pop         esi  
01271910 5B                   pop         ebx  

; Restore the values we shouldn't have altered

01271911 81 C4 C0 00 00 00    add         esp,0C0h                 ; Destroy the stack frame
01271917 3B EC                cmp         ebp,esp  
01271919 E8 36 F8 FF FF       call        __RTC_CheckEsp (01271154h)  

; More stack checking code - this sets the zero flag if the stack pointer is pointing
; where we expect it to be pointing. 
  
0127191E 8B E5                mov         esp,ebp  
01271920 5D                   pop         ebp                      ; Activate caller’s stack frame.
01271921 C3                   ret                                  ; Return to the caller


