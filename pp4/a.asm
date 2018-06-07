	# LCall main
	  jal main           	# jump to function
	# quit
	# here we quit
	  addi $v0, $zero, 10		# set 10 to $v0
	  syscall
  __f:
	# BeginFunc 4
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 4	# decrement sp to make space for locals/temps
	# _tmp0 = i
	  lw $t0, 4($fp)	# load i from $fp+4 into $t0
	  move $t1, $t0		# copy value
	# print _tmp0
	# here we print _tmp0
	  move $a0, $t1		# move value to $a0
	  addi $v0, $zero, 34		# set 34 to $v0
	  syscall
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
  main:
	# BeginFunc 68
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 68	# decrement sp to make space for locals/temps
	# _tmp1 = 1
	  li $t0, 1		# load constant value 1 into $t0
	# i = _tmp1
	  move $t1, $t0		# copy value
	# _tmp2 = 10
	  li $t2, 10		# load constant value 10 into $t2
	# j = _tmp2
	  move $t3, $t2		# copy value
	# (save modified registers before flow of control change)
	  sw $t0, -24($fp)	# spill _tmp1 from $t0 to $fp-24
	  sw $t1, -8($fp)	# spill i from $t1 to $fp-8
	  sw $t2, -28($fp)	# spill _tmp2 from $t2 to $fp-28
	  sw $t3, -12($fp)	# spill j from $t3 to $fp-12
  _L0:
	# _tmp3 = 0
	  li $t0, 0		# load constant value 0 into $t0
	# _tmp4 = _tmp3 < j
	  lw $t1, -12($fp)	# load j from $fp-12 into $t1
	  slt $t2, $t0, $t1	
	# IfZ _tmp4 Goto _L1
	# (save modified registers before flow of control change)
	  sw $t0, -32($fp)	# spill _tmp3 from $t0 to $fp-32
	  sw $t2, -36($fp)	# spill _tmp4 from $t2 to $fp-36
	  beqz $t2, _L1	# branch if _tmp4 is zero 
	# _tmp5 = i * j
	  lw $t0, -8($fp)	# load i from $fp-8 into $t0
	  lw $t1, -12($fp)	# load j from $fp-12 into $t1
	  mul $t2, $t0, $t1	
	# i = _tmp5
	  move $t0, $t2		# copy value
	# _tmp6 = 1
	  li $t3, 1		# load constant value 1 into $t3
	# _tmp7 = j - _tmp6
	  sub $t4, $t1, $t3	
	# j = _tmp7
	  move $t1, $t4		# copy value
	# j = j
	  move $t1, $t1		# copy value
	# Goto _L0
	# (save modified registers before flow of control change)
	  sw $t0, -8($fp)	# spill i from $t0 to $fp-8
	  sw $t1, -12($fp)	# spill j from $t1 to $fp-12
	  sw $t2, -40($fp)	# spill _tmp5 from $t2 to $fp-40
	  sw $t3, -44($fp)	# spill _tmp6 from $t3 to $fp-44
	  sw $t4, -48($fp)	# spill _tmp7 from $t4 to $fp-48
	  b _L0		# unconditional branch
  _L1:
	# PushParam i
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -8($fp)	# load i from $fp-8 into $t0
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall __f
	  jal __f            	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp8 = i
	  lw $t0, -8($fp)	# load i from $fp-8 into $t0
	  move $t1, $t0		# copy value
	# print _tmp8
	# here we print _tmp8
	  move $a0, $t1		# move value to $a0
	  addi $v0, $zero, 34		# set 34 to $v0
	  syscall
	# _tmp9 = 0
	  li $t2, 0		# load constant value 0 into $t2
	# Return _tmp9
	  move $v0, $t2		# assign return value into $v0
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
	# EndFunc
	# quit
	# here we quit
	  addi $v0, $zero, 10		# set 10 to $v0
	  syscall
