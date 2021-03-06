(load "SolF3.lisp")

(defun states-to-list (stts)
  (loop for st in stts
	  collect (format nil "POS: ~a VEL: ~a ACT: ~a COST: ~a~&"
	  (state-pos st)  (state-vel st)  (state-action st)  (state-cost st)))
)

(defun initial-state (track)
  (make-state :pos (track-startpos track) :vel (make-vel 0 0) :action nil :cost 0 :track track)
)

(print "Testing track0.txt...")
(with-open-file (*standard-output* "generatedoutput/track0.out" :direction :output)
	(defvar *t1* nil)
	(defvar *p1* nil)
	(print "----------------------------------")
	(setf *t1* (loadtrack "track0.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p1*)))
	(print "----------------------------------")
)


(print "Testing track1.txt...")
(with-open-file (*standard-output* "generatedoutput/track1.out" :direction :output)
	(defvar *t3* nil)
	(defvar *p3* nil)
	(print "----------------------------------")
	(setf *t3* (loadtrack "track1.txt"))
	(setf *p3* (make-problem :initial-state (initial-state *t3*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p3*)))
	(print "----------------------------------")
)

(print "Testing track9.txt...")
(with-open-file (*standard-output* "generatedoutput/track9.out" :direction :output)
	(defvar *t4* nil)
	(defvar *p4* nil)
	(print "----------------------------------")
	(setf *t4* (loadtrack "track9.txt"))
	(setf *p4* (make-problem :initial-state (initial-state *t4*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p4*)))
	(print "----------------------------------")
)

(print "Testing trackCIA.txt...")
(with-open-file (*standard-output* "generatedoutput/trackCIA.out" :direction :output)
	(defvar *t5* nil)
	(defvar *p5* nil)
	(print "----------------------------------")
	(setf *t5* (loadtrack "trackCIA.txt"))
	(setf *p5* (make-problem :initial-state (initial-state *t5*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p5*)))
	(print "----------------------------------")
)


(print "Testing track007.txt...")
(with-open-file (*standard-output* "generatedoutput/track007.out" :direction :output)
	(defvar *t2* nil)
	(defvar *p2* nil)
	(print "----------------------------------")
	(setf *t2* (loadtrack "track007.txt"))
	(setf *p2* (make-problem :initial-state (initial-state *t2*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p2*)))
	(print "----------------------------------")
)

(print "Testing trackInterpol.txt...")
(with-open-file (*standard-output* "generatedoutput/trackInterpol.out" :direction :output)
	(defvar *t6* nil)
	(defvar *p6* nil)
	(print "----------------------------------")
	(setf *t6* (loadtrack "trackInterpol.txt"))
	(setf *p6* (make-problem :initial-state (initial-state *t6*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p6*)))
	(print "----------------------------------")
)

(print "Testing trackMI5.txt...")
(with-open-file (*standard-output* "generatedoutput/trackMI5.out" :direction :output)
	(defvar *t7* nil)
	(defvar *p7* nil)
	(print "----------------------------------")
	(setf *t7* (loadtrack "trackMI5.txt"))
	(setf *p7* (make-problem :initial-state (initial-state *t7*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p7*)))
	(print "----------------------------------")
)

(print "Testing trackMossad.txt...")
(with-open-file (*standard-output* "generatedoutput/trackMossad.out" :direction :output)
	(defvar *t8* nil)
	(defvar *p8* nil)
	(print "----------------------------------")
	(setf *t8* (loadtrack "trackMossad.txt"))
	(setf *p8* (make-problem :initial-state (initial-state *t8*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p8*)))
	(print "----------------------------------")
)