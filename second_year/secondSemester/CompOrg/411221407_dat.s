# Fibonacci Sequence Generator with Memory I/O
# Input: n (first location in data segment)
# Output: Fibonacci sequence stored from second location in data segment

.text
.globl main

main:
    # Load n from first data location
    la $t0, n
    lw $t0, 0($t0)      # $t0 = n
    
    # Check if n <= 0
    blez $t0, exit
    
    # Initialize pointers and values
    la $t5, sequence    # output pointer
    li $t1, 0           # F(0) = 0
    li $t2, 1           # F(1) = 1
    
    # Store F(0)
    sw $t1, 0($t5)
    addi $t5, $t5, 4
    
    # If n == 1, exit
    li $t3, 1
    beq $t0, $t3, exit
    
    # Store F(1)
    sw $t2, 0($t5)
    addi $t5, $t5, 4
    
    # Loop to generate and store remaining numbers
    li $t3, 2           # counter = 2
loop:
    bge $t3, $t0, exit   # if counter >= n, exit
    
    # Calculate next Fibonacci number
    add $t4, $t1, $t2   # F(n) = F(n-1) + F(n-2)
    
    # Store current number
    sw $t4, 0($t5)
    addi $t5, $t5, 4
    
    # Update registers for next iteration
    move $t1, $t2       # F(n-2) = F(n-1)
    move $t2, $t4       # F(n-1) = F(n)
    addi $t3, $t3, 1    # increment counter
    
    j loop

exit:
    li $v0, 10
    syscall

.data
n: .word 10             # input value (can be changed)
sequence: .space 160    # space for 40 numbers (4 bytes each)
