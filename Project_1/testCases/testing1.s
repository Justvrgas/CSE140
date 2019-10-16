Loop:
		beq	$a0,$0,Done
		addu	$v0,$v0,$a1
		addiu	$a0,$a0,-1
		j Loop
Done:	
		jr		$ra