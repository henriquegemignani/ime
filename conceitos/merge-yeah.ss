;/**********************************************************************/
;/** IME-USP -- MAC0316-2011 - Conceitos de Linguagens de Programação **/
;/** Exercicios de Scheme                                             **/
;/** Henrique Gemignani Passos Lima      nUSP: 6879634                **/
;/**********************************************************************/

;Merge com recursão com cauda
(define mergetailaux
	(lambda (l1 l2 bw)
		(cond
			((and (null? l1) (null? l2)) (reverse bw))
			((null? l1) (mergetailaux l1 (cdr l2) (cons (car l2) bw)))
			((null? l2) (mergetailaux (cdr l1) l2 (cons (car l1) bw)))
			((< (car l1) (car l2)) (mergetailaux (cdr l1) l2 (cons (car l1) bw)))
			(else (mergetailaux l1 (cdr l2) (cons (car l2) bw))))))

(define mergetail
	(lambda (l1 l2)
		(mergetailaux l1 l2 '())))

;Merge com recursão básica
(define merge
	(lambda (l1 l2)
		(cond
			((null? l1) l2)
			((null? l2) l1)
			((< (car l1) (car l2))
				(cons (car l1) (merge (cdr l1) l2)))
			(else 
				(cons (car l2) (merge l1 (cdr l2)))))))

(define a (list 1 2 3 4 5 6 7 8))
(define b (list 4 7 9 12 20 22))

(begin
	(display a)
	(newline)
	(display b)
	(newline)
	(display (merge a b))
	(newline)
	(display (mergetail a b))
	(newline))

; Gunaxf, Jvy