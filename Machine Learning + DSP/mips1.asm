addi $3, $0, 100 #n = 100 , loop counter
addi $1, $0, 5 # B
addi $2,$0, -6#A
addi $4, $0, 1 #initial direction of x
addi $5, $0, 1 #initial direction of y
addi $6, $0, 0 #loop counter for x 
addi $7, $0, 0 #loop counter for y 
addi $8, $0, 1 #counter for the same direction
addi $9, $0, 0x2020 #memory address for x
addi $10, $0, 0x2420 #mem address for y
addi $11, $0, 0 #initial value of x
addi $12,$0, 0 #initial value of y


loop_parta: 
addi $6, $0, 0 #loop counter for x 
addi $7,$0, 0 #loop counter for y

loop_x:
addi $3,$3,-1
add $11, $11, $4 #incrementing the value of x
sw $11, 0($9) #storing the value of x
sw $12, 0($10) 
addi $9, $9, 4 #incementing the memory address of x
addi $10, $10, 4
addi $6, $6, 1 #incrementing loop counter for x
beq $3,$0, exit
bne $6, $8, loop_x

loop_y:
addi $3,$3,-1
add $12, $12, $5 #incrementing the value of y
sw $11, 0($9) 
sw $12, 0($10) 
addi $9, $9, 4 
addi $10, $10, 4#incementing the memory address of y
addi $7, $7, 1 #incrementing loop counter for y
beq $3,$0, exit
bne $7, $8, loop_y

sub $4, $0, $4 #flip sign for x
sub $5, $0, $5 #flip sign for y
addi $8,$8,1 
bne $3, $0, loop_parta

exit:

#part b
addi $3, $0, 100 #loop counter
addi $7, $0, 0x2820 #mem address for C
addi $9, $0, 0x2020 #mem address to access the x vaules
addi $10, $0, 0x2420
addi $4, $0, 1 #classification value
addi $5, $0, -1 #classification value
addi $8, $0, 0
loop_partb:
lw $11, 0($9) #loading the value of x
lw $12, 0($10) #loading the value of y 
addi $9, $9, 4 #updating mem add for x
addi $10, $10, 4 #updating mem add for y
addi $3, $3, -1 #updating loop counter
mult $11, $1 #x[i]*a
mflo $14 #$14 = x[i]*a
mult $12, $2 # y[i]*b
mflo $15 #$15 = y[i]*b
add $6, $14, $15 # $16 = the sum
slt $8, $6, $0 #$20 = 1, if the sum is negative, else $20 = 0
bne $8, $0, neg #if the sum is negative, branch to neg block
sw $4, 0($7) #storing the classification value for the positive sum 
addi $7, $7, 4 #updating the memory address for storing the classification values
bne $3, $0, loop_partb
beq $3, $0, exit_b

neg:
sw $5, 0($7) #storing the classification value for the positive sum 
addi $7, $7, 4 #updating the memory address for storing the classification values
bne $3, $0, loop_partb
beq $3, $0, exit_b

exit_b:
#part c 

addi $1, $0, 1 # new value of a
addi $2, $0, 1 # new value of b
addi $3, $0, 100 # loop counter
addi $7, $0, 0x2820 #mem address for C
addi $9, $0, 0x2020 #mem address to access the x vaules
addi $10, $0, 0x2420 #mem address to access the y values 
addi $5, $0, 0x2000 #mem address to store the final a value
addi $6, $0, 0x2004 #mem address to store the final b value

loop_partc:
lw $11, 0($9) #loading the value of x
lw $12, 0($10) #loading the value of y 
lw $13, 0($7) #loading the value of c
addi $9, $9, 4 #updating mem add for x
addi $10, $10, 4 #updating mem add for y
addi $7, $7, 4 #updating mem add for c
addi $3, $3, -1 #updating loop counter
mult $11, $1 #x[i]*a
mflo $14 #$14 = x[i]*a
mult $12, $2 # y[i]*b
mflo $15 #$15 = y[i]*b
add $4, $14, $15 # $4 = the sum
slt $8, $4, $0 #checking if the sum result is negative or positive 
slt $14, $13, $0 #checking if the value in c is +1 or -1 
bne $14, $8, update
beq $14, $8, no_update

no_update:
add $1, $0, $1 # new value of a
add $2, $0, $2 # new value of b
bne $3, $0, loop_partc
beq $3, $0, exit_c

update:
slt $14, $13, $4 #to checking the sign of the expected result
beq $14, $0, update_by_adding #if the expected value is less(negative)
bne $14, $0, update_by_subtracting #if the expected value is more(positive)

update_by_adding:
add $1, $1, $11 #a = a+x[i]
add $2,$2, $12 #b = b + y[i]
bne $3, $0, loop_partc
beq $3, $0, exit_c

update_by_subtracting:
sub $1, $1, $11 #a = a-x[i]
sub $2,$2, $12 #b = b - y[i]
bne $3, $0, loop_partc
beq $3, $0, exit_c

exit_c:
sw $1,0($5)
sw $2,0($6)














  







