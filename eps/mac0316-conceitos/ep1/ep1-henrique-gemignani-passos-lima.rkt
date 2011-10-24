#lang plai
(define-type Binding
  [binding (name symbol?) (named-expr WAE?)])


;<WAE> ::= <num>
;    | {+ <WAE> <WAE>}
;    | {- <WAE> <WAE>}
;    | {* <WAE> <WAE>}
;    | {/ <WAE> <WAE>}
;    | {with {{<id> <WAE>} ...} <WAE>}
;    | <id>
(define-type WAE
  [num (n number?)]
  [binop (op procedure?) (lhs WAE?) (rhs WAE?)]
  [with (lob (listof Binding?)) (body WAE?)]
  [id (name symbol?)])

;; Funcao auxiliar que detecta divisao por zero
(define (div-aux a b)
  (if (equal? b 0)
      (error 'interp "division by zero")
      (/ a b)))

;; Tabela de operacoes validas
(define op-table 
  (list
   (list '+ +)
   (list '- -)
   (list '* *)
   (list '/ div-aux)))

;; lookup-opaux : symbol -> procedure
(define (lookup-opaux op list)
  (cond
    [(null? list) (error 'parse "unknown operator")]
    [(symbol=? op (car (first list))) (second (first list))]
    [else (lookup-opaux op (list-tail list 1))]))

;; Dado um simbolo, procura a procedure associada na tabela
(define (lookup-op op)
  (lookup-opaux op op-table))

(define-type DefrdSub
  [mtSub]
  [aSub (name symbol?) (value number?) (ds DefrdSub?)])

;; lookup-subst : id DefrdSub -> number
;; Consumes a WAE identifier a to eargerly calculate the it's value, using the DefrdSub
(define (lookup-subst name ds)
  (type-case DefrdSub ds
    [mtSub () (error 'interp "identifier not bound")]
    [aSub (bound-name bound-value rest-ds)
          (if (symbol=? bound-name name)
              bound-value
              (lookup-subst name rest-ds))]))


(define (look-for-identifier i arg)
  (cond 
    [(null? arg) #f]
    [(symbol=? i (binding-name (first arg))) #t]
    [else (look-for-identifier i (list-tail arg 1))]))
      

;; parse-with-aux : (listof s-exp) (listof Binding) -> (listof Binding)
(define (parse-with-aux arg aux)
  (if (null? arg) 
      aux
      (if (look-for-identifier (car (first arg)) aux)
          (error 'parse "identifier redefined")
          (parse-with-aux (list-tail arg 1) 
                          (cons (binding (car (first arg)) 
                                         (parse (second (first arg)))) 
                                aux)))))

;; parse-with : (listof s-exp) -> (listof Binding)
(define (parse-with arg)
  (if (null? arg)
      (list)
      (parse-with-aux arg (list))))
       

;; parse : s-exp -> WAE
;; Consumes an s-expression and generates the corresponding WAE
(define (parse sexp)
  (cond
    [(number? sexp) (num sexp)]
    [(symbol? sexp) (id sexp)]
    [(list? sexp)
     (case (first sexp)
       [(+ - * /) (binop (lookup-op (first sexp))
                         (parse (second sexp))
                         (parse (third  sexp)))]
       [(with) (with (parse-with (second sexp))
                     (parse (third sexp)))])]))


(define (merge-ds lob ds)
  (if (null? lob)
      ds
      (aSub (binding-name (first lob))
            (auxinterp (binding-named-expr (first lob)) ds)
            (merge-ds (list-tail lob 1) ds))))

;; auxinterp : WAE DefrdSub -> number
(define (auxinterp expr ds)
  (type-case WAE expr
    [num (n) n]
    [binop (op lhs rhs)
           (apply op (list 
                      (auxinterp lhs ds)     ; primeiro arg
                      (auxinterp rhs ds)))]  ; segundo  arg
    [with (lob bound-body)
          (auxinterp bound-body
                     (merge-ds lob ds))]
    [id (i) (lookup-subst i ds)]))
    


;; interp : WAE -> number
;; Consumes a WAE representation of an expression and computes
;;   the corresponding numerical result
(define (interp expr)
  (auxinterp expr (mtSub)))



; Tests
(test (interp (parse '5)) 5)
(test (interp (parse '{+ 5 5})) 10)
(test (interp (parse '{with {{x {+ 5 5}}} {+ x x}})) 20)
(test (interp (parse '{with {{x 5}} {+ x x}})) 10)
(test (interp (parse '{with {{x 5}} {/ x x}})) 1)
(test (interp (parse '{with {{x {+ 5 5}}} {with {{y {- x 3}}} {+ y y}}})) 14)
(test (interp (parse '{with {{x 5}} {with {{y {- x 3}}} {+ y y}}})) 4)
(test (interp (parse '{with {{x 5}} {+ x {with {{x 3}} 10}}})) 15)
(test (interp (parse '{with {{x 5}} {+ x {with {{x 3}} x}}})) 8)
(test (interp (parse '{with {{x 5}} {+ x {with {{y 3}} x}}})) 10)
(test (interp (parse '{with {{x 5}} {with {{y x}} y}})) 5)
(test (interp (parse '{with {{x 5}} {with {{x x}} x}})) 5)
(test (interp (parse '{with {} {* 15 10}})) 150)
(test/exn (interp (parse '{/ 1 0})) "division by zero")
(test/exn (interp (parse '{+ 5 x})) "identifier not bound")
(test/exn (lookup-op 'expt) "unknown operator")
(test/exn (interp (parse '{with {{x 5} {y x}} {+ x x}})) "identifier not bound")
(test/exn (interp (parse '{with {{x 5} {x 10}} {+ x 10}})) "identifier redefined")

;(interp (parse (read)))