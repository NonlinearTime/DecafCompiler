	# standard Decaf preamble 
	  .text
	  .align 2
	  .globl main
  main:
	# BeginFunc 60
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 60	# decrement sp to make space for locals/temps
	# _tmp0 = 1
	  li $t0, 1		# load constant value 1 into $t0
	# i = _tmp0
	  move $t1, $t0		# copy value
	# _tmp1 = 10
	  li $t2, 10		# load constant value 10 into $t2
	# j = _tmp1
	  move $t3, $t2		# copy value
	# (save modified registers before flow of control change)
	  sw $t0, -24($fp)	# spill _tmp0 from $t0 to $fp-24
	  sw $t1, -8($fp)	# spill i from $t1 to $fp-8
	  sw $t2, -28($fp)	# spill _tmp1 from $t2 to $fp-28
	  sw $t3, -12($fp)	# spill j from $t3 to $fp-12
  _L0:
	# _tmp2 = 0
	  li $t0, 0		# load constant value 0 into $t0
	# _tmp3 = j < _tmp2
	  lw $t1, -12($fp)	# load j from $fp-12 into $t1
	  slt $t2, $t1, $t0	
	# IfZ _tmp3 Goto _L1
	# (save modified registers before flow of control change)
	  sw $t0, -32($fp)	# spill _tmp2 from $t0 to $fp-32
	  sw $t2, -36($fp)	# spill _tmp3 from $t2 to $fp-36
	  beqz $t2, _L1	# branch if _tmp3 is zero 
	# _tmp4 = i * j
	  lw $t0, -8($fp)	# load i from $fp-8 into $t0
	  lw $t1, -12($fp)	# load j from $fp-12 into $t1
	  mul $t2, $t0, $t1	
	# i = _tmp4
	  move $t0, $t2		# copy value
	# _tmp5 = 1
	  li $t3, 1		# load constant value 1 into $t3
	# _tmp6 = j + _tmp5
	  add $t4, $t1, $t3	
	# j = _tmp6
	  move $t1, $t4		# copy value
	# j = j
	  move $t1, $t1		# copy value
	# Goto _L0
	# (save modified registers before flow of control change)
	  sw $t0, -8($fp)	# spill i from $t0 to $fp-8
	  sw $t1, -12($fp)	# spill j from $t1 to $fp-12
	  sw $t2, -40($fp)	# spill _tmp4 from $t2 to $fp-40
	  sw $t3, -44($fp)	# spill _tmp5 from $t3 to $fp-44
	  sw $t4, -48($fp)	# spill _tmp6 from $t4 to $fp-48
	  b _L0		# unconditional branch
  _L1:
	# _tmp7 = 0
	  li $t0, 0		# load constant value 0 into $t0
	# Return _tmp7
	  move $v0, $t0		# assign return value into $v0
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
