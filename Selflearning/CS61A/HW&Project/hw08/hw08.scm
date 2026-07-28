(define (ascending? s) (cond
                            ((null? s) #t)
                            ((null? (cdr s)) #t)
                            ((> (car s) (car (cdr s))) #f)
                            (else (ascending? (cdr s)))
                        ))

(define (my-filter pred s) (cond
                                ((null? s) nil)
                                ((pred (car s)) (cons (car s) (my-filter pred (cdr s))))
                                (else (my-filter pred (cdr s)))
                            ))

(define (interleave lst1 lst2) (cond
                                    ((and (null? lst1) (null? lst2)) nil)
                                    ((null? lst1) (cons (car lst2) (interleave (cdr lst2) lst1)))
                                    ((null? lst2) (cons (car lst1) (interleave (cdr lst1) lst2)))
                                    (else (cons (car lst1) (interleave lst2 (cdr lst1))))
                                ))

(define (no-repeats s)
    (define (not_equal_filter s_num)
        (define (not_equal x)
            (not (= s_num x))
        )
        not_equal
    )
    (if (null? s)
        nil
        (cons (car s) (filter (not_equal_filter (car s)) (no-repeats (cdr s))))
    )
)
