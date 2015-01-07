main:
addu $t0, $zero, $sp
sw $ra, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

// i
addiu $v0, $zero, 1
subu $sp, $sp, $v0

// arr[100]
addiu $v0, $zero, 100
subu $sp, $sp, $v0

// t
addiu $v0, $zero, 1
subu $sp, $sp, $v0

// 0
addiu $v0, $zero, 0

// Push(0)
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

// Get addr(t)
addiu $v0, $zero, 102
subu $v0, $t0, $v0

// lw 0
lw $v1, 1H($sp)
addiu $sp, $sp, 1

// t = 0
sw $v1, 0H($v0)
addu $v0, $zero, $v1

// first while
while_branch_0:

// Get t
addiu $v0, $zero, 102
subu $v0, $t0, $v0
lw $v0, 0H($v0)

// Push(t)
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

// 100
addiu $v0, $zero, 100

// lw t
lw $v1, 1H($sp)
addiu $sp, $sp, 1

// t < 100
slt $v0, $v1, $v0

// while (false or true)
beq $v0, $zero, while_branch_0_end
srlv $v1, $zero, $zero

// Get t
addiu $v0, $zero, 102
subu $v0, $t0, $v0
lw $v0, 0H($v0)

// Push(t)
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

// Get addr(arr)
addiu $v0, $zero, 101
subu $v0, $t0, $v0

// Save addr(arr)
sw $v0, 0H($sp)
addiu $v1, $zero, 1
subu $sp, $sp, $v1

// Get t
addiu $v0, $zero, 102
subu $v0, $t0, $v0
lw $v0, 0H($v0)

// Get addr(arr)
lw $v1, 1H($sp)
addiu $sp, $sp, 1

// addr(arr[t])
add $v0, $v0, $v1

// Get t
lw $v1, 1H($sp)
addiu $sp, $sp, 1

// arr[t] = t
sw $v1, 0H($v0)
addu $v0, $zero, $v1

// Get t
addiu $v0, $zero, 102
subu $v0, $t0, $v0
lw $v0, 0H($v0)

// Save t
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

// 1
addiu $v0, $zero, 1

// Get t
lw $v1, 1H($sp)
addiu $sp, $sp, 1

// t + 1
add $v0, $v1, $v0

// Save t + 1
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

// Get addr(t)
addiu $v0, $zero, 102
subu $v0, $t0, $v0

// Get t+1
lw $v1, 1H($sp)
addiu $sp, $sp, 1

// t = t+1
sw $v1, 0H($v0)
addu $v0, $zero, $v1


j while_branch_0
srlv $v1, $zero, $zero


while_branch_0_end:

// While 2
while_branch_1:
addiu $v0, $zero, 1
beq $v0, $zero, while_branch_1_end
srlv $v1, $zero, $zero

// $v0 = 0000FF10H
ori $v0, $zero, FF10H
lui $v1, 0000H
addu $v0, $v0, $v1

// Port access
lw $v0, 0H($v0)

// Save $0xFF10
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

// Get addr(i)
addiu $v0, $zero, 1
subu $v0, $t0, $v0

// $0xFF10
lw $v1, 1H($sp)
addiu $sp, $sp, 1

// i = $0xFF10
sw $v1, 0H($v0)
addu $v0, $zero, $v1

// addr(arr)
addiu $v0, $zero, 101
subu $v0, $t0, $v0

// Save
sw $v0, 0H($sp)
addiu $v1, $zero, 1
subu $sp, $sp, $v1

// Get i
addiu $v0, $zero, 1
subu $v0, $t0, $v0
lw $v0, 0H($v0)

// Get addr(arr)
lw $v1, 1H($sp)
addiu $sp, $sp, 1

// arr[i]
add $v0, $v0, $v1
lw $v0, 0H($v0)

// Save arr[i]
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

// 0xFF00
ori $v0, $zero, FF00H
lui $v1, 0000H
addu $v0, $v0, $v1

// Get arr[i]
lw $v1, 1H($sp)
addiu $sp, $sp, 1

// $0xFF00 = arr[i]
sw $v1, 0H($v0)
addu $v0, $zero, $v1


j while_branch_1
srlv $v1, $zero, $zero

while_branch_1_end:

// return
addiu $v0, $zero, 0
addiu $sp, $sp, 102
lw $ra, 1H($sp)
addiu $sp, $sp, 2
lw $t0, 0H($sp)
jr $ra
srlv $v1, $zero, $zero
