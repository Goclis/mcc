main:
addu $t0, $zero, $sp
sw $ra, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

addiu $v0, $zero, 1
subu $sp, $sp, $v0

addiu $v0, $zero, 1
subu $sp, $sp, $v0

addiu $v0, $zero, 1
subu $sp, $sp, $v0

while_branch_0:
addiu $v0, $zero, 1
beq $v0, $zero, while_branch_0_end
srlv $v1, $zero, $zero

ori $v0, $zero, FF10H
lui $v1, 0000H
addu $v0, $v0, $v1
lw $v0, 0H($v0)

sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

addiu $v0, $zero, 1
subu $v0, $t0, $v0

lw $v1, 1H($sp)
addiu $sp, $sp, 1

sw $v1, 0H($v0)
addu $v0, $zero, $v1

addiu $v0, $zero, 1
subu $v0, $t0, $v0
lw $v0, 0H($v0)

sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

addiu $v0, $zero, 1

lw $v1, 1H($sp)
addiu $sp, $sp, 1

and $v0, $v1, $v0

sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

addiu $v0, $zero, 2
subu $v0, $t0, $v0

lw $v1, 1H($sp)
addiu $sp, $sp, 1

// a = i & 1
sw $v1, 0H($v0)
addu $v0, $zero, $v1

addiu $v0, $zero, 1
subu $v0, $t0, $v0
lw $v0, 0H($v0)

sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

addiu $v0, $zero, 2

lw $v1, 1H($sp)
addiu $sp, $sp, 1

and $v0, $v1, $v0

sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

addiu $v0, $zero, 3
subu $v0, $t0, $v0

lw $v1, 1H($sp)
addiu $sp, $sp, 1

// b = i & 2
sw $v1, 0H($v0)
addu $v0, $zero, $v1

// 这里需要好好考虑！！！！！
addiu $v0, $zero, 0

sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

addiu $v0, $zero, 3
subu $v0, $t0, $v0
lw $v0, 0H($v0)

lw $v1, 1H($sp)
addiu $sp, $sp, 1

// 0 == b
beq $v0, $v1, branch_2
srlv $v1, $zero, $zero
addiu $v0, $zero, 0
j branch_2_end
srlv $v1, $zero, $zero
branch_2:
addiu $v0, $zero, 1
branch_2_end:

// 根据0 == b的结果判断是否快速跳转
beq $v0, $zero, branch_3
srlv $v1, $zero, $zero

sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

addiu $v0, $zero, 0

sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

// a
addiu $v0, $zero, 2
subu $v0, $t0, $v0
lw $v0, 0H($v0)

lw $v1, 1H($sp)
addiu $sp, $sp, 1

// 0 == a
beq $v0, $v1, branch_4
srlv $v1, $zero, $zero
addiu $v0, $zero, 0
j branch_4_end
srlv $v1, $zero, $zero
branch_4:
addiu $v0, $zero, 1
branch_4_end:

// 加载0==b的结果
lw $v1, 1H($sp)
addiu $sp, $sp, 1
and $v0, $v1, $v0
sltu $v0, $zero, $v0

// 第一个if_block
branch_3:
beq $v0, $zero, if_branch_1_false
srlv $v1, $zero, $zero

addiu $v0, $zero, 1
subu $v0, $t0, $v0
lw $v0, 0H($v0)
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
ori $v0, $zero, FF00H
lui $v1, 0000H
addu $v0, $v0, $v1
lw $v1, 1H($sp)
addiu $sp, $sp, 1
sw $v1, 0H($v0)
addu $v0, $zero, $v1
addiu $v0, $zero, 1
subu $v0, $t0, $v0
lw $v0, 0H($v0)
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
ori $v0, $zero, FF08H
lui $v1, 0000H
addu $v0, $v0, $v1
lw $v1, 1H($sp)
addiu $sp, $sp, 1
sw $v1, 0H($v0)
addu $v0, $zero, $v1
j if_branch_1_end
srlv $v1, $zero, $zero

// 第二个if_block
if_branch_1_false:

addiu $v0, $zero, 2
subu $v0, $t0, $v0
lw $v0, 0H($v0)

sltu $v0, $zero, $v0

beq $v0, $zero, branch_6
srlv $v1, $zero, $zero

sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0

addiu $v0, $zero, 3
subu $v0, $t0, $v0
lw $v0, 0H($v0)

lw $v1, 1H($sp)
addiu $sp, $sp, 1

// !a && b
and $v0, $v1, $v0
sltu $v0, $zero, $v0

branch_6:
beq $v0, $zero, if_branch_5_false
srlv $v1, $zero, $zero

addiu $v0, $zero, 1
subu $v0, $t0, $v0
lw $v0, 0H($v0)
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
addiu $v0, $zero, 1
lw $v1, 1H($sp)
addiu $sp, $sp, 1

sub $v0, $v1, $v0

sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
ori $v0, $zero, FF00H
lui $v1, 0000H
addu $v0, $v0, $v1
lw $v1, 1H($sp)
addiu $sp, $sp, 1
sw $v1, 0H($v0)
addu $v0, $zero, $v1
addiu $v0, $zero, 1
subu $v0, $t0, $v0
lw $v0, 0H($v0)
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
addiu $v0, $zero, 1
lw $v1, 1H($sp)
addiu $sp, $sp, 1
sub $v0, $v1, $v0
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
ori $v0, $zero, FF08H
lui $v1, 0000H
addu $v0, $v0, $v1
lw $v1, 1H($sp)
addiu $sp, $sp, 1
sw $v1, 0H($v0)
addu $v0, $zero, $v1
j if_branch_5_end
srlv $v1, $zero, $zero
if_branch_5_false:
addiu $v0, $zero, 0
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
addiu $v0, $zero, 3
subu $v0, $t0, $v0
lw $v0, 0H($v0)
lw $v1, 1H($sp)
addiu $sp, $sp, 1
beq $v0, $v1, branch_8
srlv $v1, $zero, $zero
addiu $v0, $zero, 0
j branch_8_end
srlv $v1, $zero, $zero
branch_8:
addiu $v0, $zero, 1
branch_8_end:
bne $v0, $zero, branch_9
srlv $v1, $zero, $zero
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
addiu $v0, $zero, 1
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
addiu $v0, $zero, 2
subu $v0, $t0, $v0
lw $v0, 0H($v0)
lw $v1, 1H($sp)
addiu $sp, $sp, 1
beq $v0, $v1, branch_10
srlv $v1, $zero, $zero
addiu $v0, $zero, 0
j branch_10_end
srlv $v1, $zero, $zero
branch_10:
addiu $v0, $zero, 1
branch_10_end:
lw $v1, 1H($sp)
addiu $sp, $sp, 1
sltu $v0, $zero, $v0
branch_9:
beq $v0, $zero, if_branch_7_end
srlv $v1, $zero, $zero
addiu $v0, $zero, 1
subu $v0, $t0, $v0
lw $v0, 0H($v0)
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
addiu $v0, $zero, 2
lw $v1, 1H($sp)
addiu $sp, $sp, 1
mult $v1, $v0
mflo $v0
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
ori $v0, $zero, FF00H
lui $v1, 0000H
addu $v0, $v0, $v1
lw $v1, 1H($sp)
addiu $sp, $sp, 1
sw $v1, 0H($v0)
addu $v0, $zero, $v1
addiu $v0, $zero, 1
subu $v0, $t0, $v0
lw $v0, 0H($v0)
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
addiu $v0, $zero, 2
lw $v1, 1H($sp)
addiu $sp, $sp, 1
mult $v1, $v0
mflo $v0
sw $v0, 0H($sp)
addiu $v0, $zero, 1
subu $sp, $sp, $v0
ori $v0, $zero, FF08H
lui $v1, 0000H
addu $v0, $v0, $v1
lw $v1, 1H($sp)
addiu $sp, $sp, 1
sw $v1, 0H($v0)
addu $v0, $zero, $v1
if_branch_7_end:
if_branch_5_end:
if_branch_1_end:
j while_branch_0
srlv $v1, $zero, $zero
while_branch_0_end:
addiu $sp, $sp, 3
lw $ra, 1H($sp)
addiu $sp, $sp, 2
lw $t0, 0H($sp)
jr $ra
srlv $v1, $zero, $zero
