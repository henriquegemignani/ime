(define what-kind
	(lambda (a b c)
		(define delta (- (* b b) (* 4 a c)) )
		(cond
			((= a 0) 'degenerate)
			((< delta 0) 'none)
			((= delta 0) 'one)
			(else 'two)
		)
	)
)