#lang racket
;; filter: (x -> bool) (listof x) -> (listof x)
(define (filter f l)
  (cond
    [(empty? l) empty]
    [else (cond
            [(f (first l)) (cons (first l)
                                 (filter f (rest l)))]
            [else (filter f (rest l))])]))

;; filter/k: (x receiver -> doesn't return) (listof x) receiver -> doesn't return	  
(define (filter/k f l k)
  (if (empty? l) (k empty)
	(f (first l) (lambda (c)
	  (if c (filter/k f (rest l) (lambda (r)
				(k (cons (first l) r))))
			(filter/k f (rest l) k))))))

(define (less-than-three x)
   (< x 3))
(filter less-than-three
        (cons 1 (cons 4 empty))) ;; this evaluates to (list 1)
	
(define (less-than-tree/k x k)
	(k (< x 3)))
	
(filter/k less-than-tree/k (list 1 2 3 4 5 6) values)