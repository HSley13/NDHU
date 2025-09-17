# Fibonacci Sequence Generator with Console I/O
# Input: n (from console)
# Output: Fibonacci sequence printed to console (one number per line)

.text
.globl main

main:
    # Prompt for input
    li $v0, 4
    la $a0, prompt
    syscall

    # Read integer n (n < 40)
    li $v0, 5
    syscall
    move $t0, $v0        # $t0 = n
    
    # Check if n <= 0
    blez $t0, exit
    
    # Initialize Fibonacci sequence
    li $t1, 0           # F(0) = 0
    li $t2, 1           # F(1) = 1
    
    # Print F(0)
    move $a0, $t1
    li $v0, 1
    syscall
    li $v0, 11          # print newline
    li $a0, 10
    syscall
    
    # If n == 1, exit
    li $t3, 1
    beq $t0, $t3, exit
    
    # Print F(1)
    move $a0, $t2
    li $v0, 1
    syscall
    li $v0, 11          # print newline
    li $a0, 10
    syscall
    
    # Loop to generate and print remaining numbers
    li $t3, 2           # counter = 2
loop:
    bge $t3, $t0, exit   # if counter >= n, exit
    
    # Calculate next Fibonacci number
    add $t4, $t1, $t2   # F(n) = F(n-1) + F(n-2)
    
    # Print current number
    move $a0, $t4
    li $v0, 1
    syscall
    li $v0, 11          # print newline
    li $a0, 10
    syscall
    
    # Update registers for next iteration
    move $t1, $t2       # F(n-2) = F(n-1)
    move $t2, $t4       # F(n-1) = F(n)
    addi $t3, $t3, 1    # increment counter
    
    j loop

exit:
    li $v0, 10
    syscall

.data
