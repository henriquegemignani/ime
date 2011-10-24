#lang plai
;<CFWAE> ::= <num>
;    | {+ <CFWAE> <CFWAE>}
;    | {- <CFWAE> <CFWAE>}
;    | {* <CFWAE> <CFWAE>}
;    | {/ <CFWAE> <CFWAE>}
;    | <id>
;    | {if0 <CFWAE> <CFWAE> <CFWAE>}
;    | {with {{<id> <CFWAE>} ...} <CFWAE>}
;    | {fun {<id> ...} <CFWAE>}
;    | {<CFWAE> <CFWAE> ...}
(define-type CFAE
  [num (n number?)]
  [binop (op procedure?) (lhs CFAE?) (rhs CFAE?)]
  [id (name symbol?)]
  [if0 (c CFAE?) (t CFAE?) (e CFAE?)]
  [fun (args (listof symbol?)) (body CFAE?)]
  [app (f CFAE?) (args (listof CFAE?))])

(define-type Env
  [mtEnv]
  [anEnv (name symbol?) (value CFAE-Value?) (env Env?)])

(define-type CFAE-Value
  [numV (n number?)]
  [closureV (params (listof symbol?))
            (body CFAE?)
            (env Env?)])

;; lookup-subst : id Env -> CFAE-Value
(define (lookup-subst name ds)
  (type-case Env ds
    [mtEnv () (error 'interp "identifier not bound")]
    [anEnv (bound-name bound-value rest-env)
          (if (symbol=? bound-name name)
              bound-value
              (lookup-subst name rest-env))]))

;; insert-list : listof(symbol . CFAE-Value) Env -> Env
(define (insert-list list env)
  (if (empty? list)
      env
      (insert-list (rest list)
                   (anEnv (car (first list))
                          (cdr (first list))
                          env))))


(define (add-aux a b) (numV (+ (numV-n a) (numV-n b))))
(define (sub-aux a b) (numV (- (numV-n a) (numV-n b))))
(define (mul-aux a b) (numV (* (numV-n a) (numV-n b))))
(define (div-aux a b) (if (equal? b (numV 0))
                          (error 'interp "division by zero")
                          (numV (/ (numV-n a) (numV-n b)))))

;; Tabela de operacoes validas
(define op-table 
  (list (list '+ add-aux)
        (list '- sub-aux)
        (list '* mul-aux)
        (list '/ div-aux)))

;; lookup-opaux : symbol -> procedure
(define (lookup-opaux op list)
  (cond
    [(null? list) (error 'parse "unknown operator")]
    [(symbol=? op (car (first list))) (second (first list))]
    [else (lookup-opaux op (rest list))]))

;; Dado um simbolo, procura a procedure associada na tabela
(define (lookup-op op) (lookup-opaux op op-table))

;; verify-args : list -> boolean
;; Consumes a list and returns #t if it only contains symbols, #f otherwise 
(define (verify-args list)
  (if (empty? list) 
      #t
      (and (verify-args (rest list))
           (symbol? (first list)))))


;; parse : s-exp -> CFAE
;; Consumes an s-expression and generates the corresponding WAE
(define (parse sexp)
  (cond
    [(number? sexp) (num sexp)]
    [(symbol? sexp) (id sexp)]
    [(list? sexp)
     (if (empty? sexp) (error 'parse "empty expression")
     (case (first sexp)
       [(+ - * /) (binop (lookup-op (first sexp))
                         (parse (second sexp))
                         (parse (third  sexp)))]
       [(if0) (if0 (parse (second sexp))
                   (parse (third  sexp))
                   (parse (fourth  sexp)))]
       [(fun) (if (verify-args (second sexp))
                  (fun (second sexp) (parse (third sexp)))
                  (error 'parse "non-symbol in fun arg list"))]
       [(with) (app (fun (map first (second sexp))
                         (parse (third sexp)))
                    (map parse (map second (second sexp))))]
       [else (app (parse (first sexp)) (map parse (rest sexp)))]))]))


;; merge-list : list list -> listof dotted pair
(define (merge-list a b)
  (cond
    [(empty? a) '()]
    [(empty? b) '()]
    [else (cons (cons (first a) (first b)) (merge-list (rest a) (rest b)))]))
    

;; interp-list : (listof CFAE) Env -> (listof CFAE-Value)
(define (interp-list arg env)
  (if (null? arg)
      (list)
      (cons (auxinterp (first arg) env) 
            (interp-list (rest arg) env))))

;; auxinterp : CFAE Env -> CFAE-Value
(define (auxinterp expr ds)
  (type-case CFAE expr
    [num (n) (numV n)]
    [binop (op lhs rhs) (apply op (list 
                                   (auxinterp lhs ds)     ; primeiro arg
                                   (auxinterp rhs ds)))]  ; segundo  arg
    [if0 (c t e) (if (equal? (auxinterp c ds) (numV 0))
                     (auxinterp t ds)
                     (auxinterp e ds))]
    [fun (args body) 
         (closureV args body ds)]
    [app (fun-expr args) 
         (local ([define fun-val (auxinterp fun-expr ds)])
           (auxinterp (closureV-body fun-val)
                      (insert-list (merge-list (closureV-params fun-val)
                                               (interp-list args ds))
                                   ds)))]
    [id (i) (lookup-subst i ds)]))
    
 

;; interp : CFAE -> CFAE
;; Consumes a CFAE representation of an expression and computes
;;   the corresponding numerical result
(define (interp expr)
  (auxinterp expr (mtEnv)))


(define (ct symbol result)
  (test (interp (parse symbol)) (numV result)))

; Tests
(ct '5 5)
(ct '{+ 5 5} 10)
(ct '{with {{x {+ 5 5}}} {+ x x}} 20)
(ct '{with {{x 5}} {+ x x}} 10)
(ct '{with {{x 5}} {/ x x}} 1)
(ct '{with {{x {+ 5 5}}} {with {{y {- x 3}}} {+ y y}}} 14)
(ct '{with {{x 5}} {with {{y {- x 3}}} {+ y y}}} 4)
(ct '{with {{x 5}} {+ x {with {{x 3}} 10}}} 15)
(ct '{with {{x 5}} {+ x {with {{x 3}} x}}} 8)
(ct '{with {{x 5}} {+ x {with {{y 3}} x}}} 10)
(ct '{with {{x 5}} {with {{y x}} y}} 5)
(ct '{with {{x 5}} {with {{x x}} x}} 5)
(ct '{with {{x 5} {y 4}} {with {{x y}} {+ x x}}} 8)
(ct '{if0 {- 5 5} 10 {* 2 3}} 10)
(ct '{if0 {- 5 6} 10 {* 2 3}} 6)
(ct '{if0 {{fun {x} {- x x}} 42} 1337 51966} 1337)
(ct '{{fun {x} 1} 2} 1)
(ct '{{fun {x} x} 5} 5)
(ct '{{fun {a b} {+ a b}} 1 2} 3)
(ct '{{fun {a} {* a {{fun {b} {+ b b}} a}}} 3} 18)
(ct '{with {{fat {fun {a} {if0 a 1 {* a {fat {- a 1}}}}}}} {fat 5}} 120)
(ct '{with {{cake {fun {a b} {if0 {- a b} {+ a b} {- a b}}}}} {if0 {- {cake 2 4} 2} {cake 8 4} {cake 4 8}}} -4)
(ct '{with {{cake {fun {x} {if0 x 1 {/ {+ x 1} x}}}} 
          {pie {fun {x} {* x x}}}
          {a 8}} {* {pie a} {cake a}}} 72)
(test/exn (interp (parse '{/ 1 0})) "division by zero")
(test/exn (interp (parse '{+ 5 x})) "identifier not bound")
(test/exn (lookup-op 'expt) "unknown operator")
(test/exn (interp (parse '{{fun {x} {}} 5})) "empty expression")
(test/exn (interp (parse '{{fun {1} {+ 2 3}} 5})) "non-symbol in fun arg list")
(test (merge-list '(a b c) '(1)) (list (cons 'a 1)))

;(interp (parse (read)))