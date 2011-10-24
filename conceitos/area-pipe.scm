(define circle-area
	(lambda (radius)
		(* pi radius radius)
	)
)

(define cylinder-surface
	(lambda (radius height)
		(* 2 pi radius height)
	)
)

(define area-pipe
	(lambda (radius height thickness)
		(+
			(cylinder-surface radius height)
			(cylinder-surface (+ radius thickness) height)
			
			(* 2 
				(- 	(circle-area (+ radius thickness)) 
					(circle-area radius))
			)
		)
	)
)