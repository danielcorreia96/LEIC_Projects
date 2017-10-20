; IA - Entrega 2
; Grupo 77
; Pedro Caldeira 81888
; Daniel Correia 80967
;;; Utilizar estes includes para os testes na versao local
;;; comentar antes de submeter
(load "datastructures.lisp")
(load "auxfuncs.lisp")

;;; Utilizar estes includes para a versao a submeter
; tirar o comentario antes de submeter
;(load "datastructures.fas")
;(load "auxfuncs.fas")


;;; TAI position
(defun make-pos (c l)
  (list c l))
(defun pos-l (pos)
  (first pos))
(defun pos-c (pos)
  (second pos))

;;; TAI acceleration
(defun make-acce (c l)
  (list c l))
(defun acce-l (pos)
  (first pos))
(defun acce-c (pos)
  (second pos))

;;; TAI velocity
(defun make-vel (c l)
  (list c l))
(defun vel-l (pos)
  (first pos))
(defun vel-c (pos)
  (second pos))


;; Solution of phase 1

(defun getTrackContent (pos track)
  (nth (pos-c pos) (nth (pos-l pos) (track-env track))))

;; Pedir 0,4
(defun isObstaclep (pos track)
  "check if the position pos is an obstacle"
  (or (< (pos-l pos) 0) (< (pos-c pos) 0)
      (>= (pos-l pos) (pos-l (track-size track)))
      (>= (pos-c pos) (pos-c (track-size track)))
      (null (getTrackContent pos track))))

;; Pedir 0,4
(defun isGoalp (st)
  "check if st is a solution of the problem"
  (let ((current-position (state-pos st))
	(track (state-track st)))
    (and (member current-position (track-endpositions track) :test #'equalp)
	 T)))

;; Pedir 1,2
(defun nextState (st act)
  "generate the nextState after state st and action act from prolem"
  (let ((new-state (make-state :action act :track (state-track st))))
    (setf (state-vel new-state)
	  (make-vel (+ (vel-l (state-vel st)) (acce-l act))
		    (+ (vel-c (state-vel st)) (acce-c act))))
    (setf (state-pos new-state)
	  (make-pos (+ (pos-l (state-pos st)) (vel-l (state-vel new-state)))
		    (+ (pos-c (state-pos st)) (vel-c (state-vel new-state)))))
    (setf (state-cost new-state)
	  (cond ((isGoalp new-state) -100)
		((isObstaclep (state-pos new-state) (state-track new-state)) 20)
		(T 1)))
    (when (= (state-cost new-state) 20)
      (setf (state-vel new-state) (make-vel 0 0))
      (setf (state-pos new-state) (make-pos (pos-l (state-pos st))
					    (pos-c (state-pos st)))))
    (values new-state)))



;; Solution of phase 2

;;; Pedir
(defun nextStates (st)
  "generate all possible next states"
  (let ((nextStatesResult '()) (all-actions (possible-actions)))
    (dolist (action all-actions)
	  (let (newState (nextState st action))
		(setf (state-vel newState) (make-vel 0 0))
		(push (nextState st action) nextStatesResult)
	  )
      
    )
  (values nextStatesResult))
)


(defun recursiveDLS (node problem limit)
	(if (funcall (problem-fn-isGoal problem) (node-state node))
    (return-from recursiveDLS node)
  )
	(if (= limit 0)
		(return-from recursiveDLS ':corte)
  )
	(let ( (cutoff_occurred nil) )
		(dolist (child_state (funcall (problem-fn-nextStates problem) (node-state node)))
	    (let* ( (child_node (make-node :state child_state :parent node))
	            (result (recursiveDLS child_node problem (- limit 1) )))
        (cond ((eq result ':corte) (setf cutoff_occurred t))
              ((not (eq result nil)) (return-from recursiveDLS result))
        )
	    )
	  )
    (if (eq cutoff_occurred t)
  		(return-from recursiveDLS ':corte)
  		(return-from recursiveDLS nil)
  	)
	)
)

(defun nodeSolution (node)
  (if (eq (node-parent node) nil)
    (return-from nodeSolution (list (node-state node)))
  )
    (return-from nodeSolution (append (nodeSolution (node-parent node)) (list (node-state node))))
)

;;; limdepthfirstsearch
(defun limdepthfirstsearch (problem lim)
  "limited depth first search
     st - initial state
     problem - problem information
     lim - depth limit"
  (let* ( (initial_node (make-node :state (problem-initial-state problem)))
          (result (recursiveDLS initial_node problem lim))
        )
    ;(print result)
    ;(print lim)
    (cond ((eq result nil) (return-from limdepthfirstsearch nil))
          ((eq result ':corte) (return-from limdepthfirstsearch ':corte))
          (t (return-from limdepthfirstsearch (nodeSolution result)))
    )
  )
)

;iterlimdepthfirstsearch
(defun iterlimdepthfirstsearch (problem)
  "limited depth first search
     st - initial state
     problem - problem information
     lim - limit of depth iterations"
  (let ((limit 0) )
    (loop
      (let ( (result (limdepthfirstsearch problem limit)) )
        (if (not (eq result ':corte))
          (return-from iterlimdepthfirstsearch result)
        )
        (setf limit (+ limit 1))
      )
    )
  )
)
