(load "SolF3.fas")

(defun states-to-list (stts)
    (let ((cost 0))
		(dolist (el stts)
			(setf cost (+ cost (state-cost el))))
		(print cost)
	)
  (loop for st in stts
	  collect (format nil "POS: ~a VEL: ~a ACT: ~a COST: ~a~&"
	  (state-pos st)  (state-vel st)  (state-action st)  (state-cost st)))

)

(defun initial-state (track)
  (make-state :pos (track-startpos track) :vel (make-vel 0 0) :action nil :cost 0 :track track)
)

;Para cada um dos tabuleiros junto foi feito o seguinte teste:
;(compute-heuristic (initial-state (loadtrack <track-file-name>)))
;O resultado esperado para cada teste é 4.
;
;(a* (make-problem 	:initial-state (initial-state (loadtrack <track-file-name>)) 
;					:fn-isGoal #'isGoalp 
;					:fn-nextstates #'nextStates 
;					:fn-h #'compute-heuristic))
;
;(best-search (make-problem :initial-state (initial-state (loadtrack <track-file-name>)) 
;							:fn-isGoal #'isGoalp 
;							:fn-nextstates #'nextStates 
;							:fn-h #'compute-heuristic))

(print "Testing 3.1-Heuristica")
(print "Testing trackheur1.txt to trackheur4.txt...")
(with-open-file (*standard-output* "output/trackheur.out" :direction :output)
	(format t "Testing 3.1-Heuristica - Output ~&")
	(format t "~% Result: ~a~&" (compute-heuristic (initial-state (loadtrack "trackheur1.txt"))))
	(format t "~% Result: ~a~&" (compute-heuristic (initial-state (loadtrack "trackheur2.txt"))))
	(format t "~% Result: ~a~&" (compute-heuristic (initial-state (loadtrack "trackheur3.txt"))))
	(format t "~% Result: ~a~&" (compute-heuristic (initial-state (loadtrack "trackheur4.txt"))))
)

(print "Testing 3.2-A-star")
(print "Testing trackstar1.txt to trackstar4.txt...")
(with-open-file (*standard-output* "output/trackstar.out" :direction :output)
	(format t "Testing 3.2-A-star - Output ~&")
	(format t "~% Result: ~a~&" (states-to-list (a* (make-problem 	
					:initial-state (initial-state (loadtrack "trackstar1.txt")) 
					:fn-isGoal #'isGoalp 
					:fn-nextstates #'nextStates 
					:fn-h #'compute-heuristic))))
	(format t "~% Result: ~a~&" (states-to-list (a* (make-problem 	
					:initial-state (initial-state (loadtrack "trackstar2.txt")) 
					:fn-isGoal #'isGoalp 
					:fn-nextstates #'nextStates 
					:fn-h #'compute-heuristic))))
	(format t "~% Result: ~a~&" (states-to-list (a* (make-problem 	
					:initial-state (initial-state (loadtrack "trackstar3.txt")) 
					:fn-isGoal #'isGoalp 
					:fn-nextstates #'nextStates 
					:fn-h #'compute-heuristic))))
	(format t "~% Result: ~a~&" (states-to-list (a* (make-problem 	
					:initial-state (initial-state (loadtrack "trackstar4.txt")) 
					:fn-isGoal #'isGoalp 
					:fn-nextstates #'nextStates 
					:fn-h #'compute-heuristic))))
)

(print "Testing 3.3-Best-search")
(print "Testing trackbest1.txt to trackbest4.txt...")
(with-open-file (*standard-output* "output/trackbest.out" :direction :output)
	(format t "Testing 3.2-A-star - Output ~&")
	(format t "~% Result: ~a~&" (states-to-list (a* (make-problem 	
					:initial-state (initial-state (loadtrack "trackbest1.txt")) 
					:fn-isGoal #'isGoalp 
					:fn-nextstates #'nextStates 
					:fn-h #'compute-heuristic))))
	(format t "~% Result: ~a~&" (states-to-list (a* (make-problem 	
					:initial-state (initial-state (loadtrack "trackbest2.txt")) 
					:fn-isGoal #'isGoalp 
					:fn-nextstates #'nextStates 
					:fn-h #'compute-heuristic))))
	(format t "~% Result: ~a~&" (states-to-list (a* (make-problem 	
					:initial-state (initial-state (loadtrack "trackbest3.txt")) 
					:fn-isGoal #'isGoalp 
					:fn-nextstates #'nextStates 
					:fn-h #'compute-heuristic))))
	(format t "~% Result: ~a~&" (states-to-list (a* (make-problem 	
					:initial-state (initial-state (loadtrack "trackbest4.txt")) 
					:fn-isGoal #'isGoalp 
					:fn-nextstates #'nextStates 
					:fn-h #'compute-heuristic))))
	(format t "~% Result: ~a~&" (states-to-list (a* (make-problem 	
					:initial-state (initial-state (loadtrack "trackbest5.txt")) 
					:fn-isGoal #'isGoalp 
					:fn-nextstates #'nextStates 
					:fn-h #'compute-heuristic))))
	(format t "~% Result: ~a~&" (states-to-list (a* (make-problem 	
					:initial-state (initial-state (loadtrack "trackbest6.txt")) 
					:fn-isGoal #'isGoalp 
					:fn-nextstates #'nextStates 
					:fn-h #'compute-heuristic))))
)


