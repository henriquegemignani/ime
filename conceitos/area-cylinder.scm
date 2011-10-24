(define area-cylinder
	(lambda (radius height)
		(*
			2
			pi
			radius
			(+ radius height)
		)
	)
)