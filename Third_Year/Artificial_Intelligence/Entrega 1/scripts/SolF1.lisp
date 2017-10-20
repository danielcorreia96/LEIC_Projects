; Grupo 77 - Pedro Caldeira (81888) e Daniel Correia (80967)
;;; These functions, and any other ones needed must be implemented

;;; Utilizar estes includes para os testes na versao local
;;; comentar antes de submeter
;(load "datastructures.lisp")
;(load "auxfuncs.lisp")

;;; Utilizar estes includes para a versao a submeter
; tirar o comentario antes de submeter
(load "datastructures.fas")
(load "auxfuncs.fas")

(defun isObstaclep (pos track)
  "check if there is an obstacle at position pos of the track"
  (let ( (linha (first pos)) (coluna (second pos)) )
    (if (and (< linha (first (track-size track)))
            (< coluna (second (track-size track)))
            (> coluna 0)
            (> linha 0))
        (not (nth coluna (nth linha (track-env track))))))
)

(defun isGoalp (st)
  "check if st is a goal state"
  (let*  (  (car_pos (state-pos st)) (track (state-track st))
            (goals (track-endpositions track))
         )

         (if (and  (< (first car_pos) (first (track-size track)))
                (< (second car_pos) (second (track-size track)))
                (> (second car_pos) 0)
                (> (first car_pos) 0))
          (dolist (goal_el goals nil) (when (equal car_pos goal_el) (return t)))
      )

  )
)

(defun nextState (st act)
  "generate the nextState after state st and action act"
  (let*((old_vel (state-vel st))
        (old_pos (state-pos st))

        (new_vel (list (+ (first old_vel) (first act)) (+ (second old_vel) (second act))))
        (new_pos (list (+ (first old_pos) (first new_vel)) (+ (second old_pos) (second new_vel))))
        (new_st (make-STATE :POS new_pos
                            :VEL new_vel
                            :ACTION act
                            :TRACK (state-track st)))
       )

       (cond
         ((isObstaclep (state-pos st) (state-track st))
           (progn
              (setf (state-pos new_st) (old_pos))
              (setf (state-cost new_st) 20)
              (setf (state-vel new_st) (list 0 0))
            )
         )
         ((isGoalp new_st)
           (setf (state-cost new_st) -100)
         )
         (t
             (setf (state-cost new_st) 1)
         )
        )
      (return-from nextState new_st)
    )
)
