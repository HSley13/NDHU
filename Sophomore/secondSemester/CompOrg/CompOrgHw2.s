# Homework 2: Selection Sort in MIPS Assembly
# Description: Reads integers from console until 0 is entered,
#              sorts them using Selection Sort, and prints the result.

.text
.globl main

main:
    # Read numbers until 0 is entered
    la $s0, array       # Load array address
    li $s1, 0           # Initialize counter (n)

read_loop:
    li $v0, 5           # Read integer
    syscall
    
    beqz $v0, end_read  # If input == 0, stop reading
    sw $v0, 0($s0)       # Store number in array
    addi $s0, $s0, 4     # Move to next array position
    addi $s1, $s1, 1     # Increment counter (n++)
    j read_loop

end_read:
    # Call selection_sort procedure
    la $a0, array        # $a0 = array address
    move $a1, $s1        # $a1 = n (number of elements)
    jal selection_sort   # Call sorting function

    # Print sorted array
    la $t0, array        # Load array address
    li $t1, 0            # Initialize loop counter (i = 0)

print_loop:
    bge $t1, $s1, exit   # If i >= n, exit
    
    lw $a0, 0($t0)       # Load array[i]
    li $v0, 1            # Print integer
    syscall
    
    addi $t0, $t0, 4     # Move to next element
    addi $t1, $t1, 1     # i++
    
    # Print space (except after last element)
    blt $t1, $s1, print_space
    j print_loop

print_space:
    li $v0, 11           # Print character
    li $a0, 32            # ASCII for space
    syscall
    j print_loop

exit:
    li $v0, 10           # Exit program
    syscall

# --- Selection Sort Procedure ---
# Arguments: $a0 = array address, $a1 = n
selection_sort:
    li $t0, 0           # i = 0 (outer loop counter)

outer_loop:
    addi $t1, $t0, -1   # j = i - 1 (inner loop counter)
    move $t2, $t0       # min_index = i

    # Find the minimum element in the unsorted part
    move $t3, $t0       # k = i
    inner_loop:
        bge $t3, $a1, end_inner  # If k >= n, exit loop
        
        # Compute array[k] address
        sll $t4, $t3, 2         # $t4 = k * 4
        add $t4, $a0, $t4        # $t4 = &array[k]
        lw $t5, 0($t4)           # $t5 = array[k]
        
        # Compute array[min_index] address
        sll $t6, $t2, 2          # $t6 = min_index * 4
        add $t6, $a0, $t6        # $t6 = &array[min_index]
        lw $t7, 0($t6)            # $t7 = array[min_index]
        
        # Compare array[k] and array[min_index]
        bge $t5, $t7, skip_update
        move $t2, $t3            # min_index = k
        
    skip_update:
        addi $t3, $t3, 1         # k++
        j inner_loop

    end_inner:
    # Swap array[i] and array[min_index]
    sll $t4, $t0, 2              # $t4 = i * 4
    add $t4, $a0, $t4            # $t4 = &array[i]
    lw $t5, 0($t4)               # $t5 = array[i]
    
    sll $t6, $t2, 2              # $t6 = min_index * 4
    add $t6, $a0, $t6            # $t6 = &array[min_index]
    lw $t7, 0($t6)               # $t7 = array[min_index]
    
    sw $t7, 0($t4)               # array[i] = array[min_index]
    sw $t5, 0($t6)               # array[min_index] = array[i]
    
    addi $t0, $t0, 1             # i++
    blt $t0, $a1, outer_loop     # Repeat if i < n
    
    jr $ra                       # Return to caller

.data
array: .space 400                # Space for 100 integers (4 bytes each)
