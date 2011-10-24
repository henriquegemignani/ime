;Recursão com cauda
(define mergetailaux
  (lambda (l1 l2 bw)
    (cond
      [(and (null? l1) (null? l2)) (reverse bw)]
      [(null? l1) (mergetailaux l1 (cdr l2) (cons (car l2) bw))]
      [(null? l2) (mergetailaux (cdr l1) l2 (cons (car l1) bw))]
      [(< (car l1) (car l2)) (mergetailaux (cdr l1) l2 (cons (car l1) bw))]
      [else (mergetailaux l1 (cdr l2) (cons (car l2) bw))])))

;Interface
(define mergetail
  (lambda (l1 l2)
    (mergetailaux l1 l2 '())))

;Recursão 'normal'
(define merge
  (lambda (l1 l2)
    (cond
      [(null? l1) l2]
      [(null? l2) l1]
      [(< (car l1) (car l2))
        (cons (car l1) (merge (cdr l1) l2))]
      [else (cons (car l2) (merge l1 (cdr l2)))])))

;Compara listas
(define list=
  (lambda (l1 l2)
    (cond
      [(null? l1) (if (null? l2) "Ok" "Horror!")]
      [(null? l2) (if (null? l1) "Ok" "Horror!")]
      [(if (= (car l1) (car l2)) (list= (cdr l1) (cdr l2)) "Horror!")])))


(define l (list 1 2 3 4))
(define k (list 2 3 4 5))

;(list= (list 1 2 3 3 4 4 5) (mergetailaux k l '()))
(list= (mergetail k l) (merge k l))
