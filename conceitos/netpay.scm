(define tax
	(lambda (pay)
		(if (<= pay 240)
			0
			(if (<= pay 480)
				(* pay 0.15)
				(* pay 0.28)
			)
		)
	)
)

(define hourly-pay-rate 12)

(define netpay
	(lambda (hours)
		(define pay (* hours hourly-pay-rate))
		(- pay (tax pay))
	)
)