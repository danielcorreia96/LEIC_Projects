;(load "SolF3.lisp")
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
(print "Testing track3.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/track3.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "track3.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing track4.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/track4.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "track4.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing etrack3.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/etrack3.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "etrack3.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing track0.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/track0.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "track0.txt"))
	(print (track-endpositions *t1*))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing track1.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/track1.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "track1.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing track2.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/track2.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "track2.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)


(print "Testing track9.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/track9.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "track9.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 6.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/6.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "6.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 7.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/7.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "7.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 8.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/8.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "8.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 9.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/9.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "9.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 10.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/10.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "10.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)


(print "Testing 11.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/11.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "11.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 12.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/12.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "12.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 13.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/13.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "13.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 14.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/14.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "14.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 15.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/15.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "15.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 16.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/16.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "16.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 17.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/17.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "17.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 18.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/18.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "18.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 19.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/19.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "19.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)


(print "Testing 20.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/20.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "20.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing 21.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/21.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "21.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (best-search *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing trackCIA.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/trackCIA.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "trackCIA.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)


(print "Testing track007.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/track007.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "track007.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing trackInterpol.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/trackInterpol.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "trackInterpol.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing trackMI5.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/trackMI5.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "trackMI5.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)

(print "Testing trackMossad.txt...")
(with-open-file (*standard-output* "bestgeneratedoutput/trackMossad.out" :direction :output)
	(setf real1 (get-internal-real-time))
	(print "----------------------------------")
	(setf *t1* (loadtrack "trackMossad.txt"))
	(setf *p1* (make-problem :initial-state (initial-state *t1*)  :fn-isGoal #'isGoalp	  :fn-nextstates #'nextStates	  :fn-h #'compute-heuristic))
	(print (states-to-list (a* *p1*)))
	(setf real2 (get-internal-real-time))
	(format t "~%Computation took: ~f seconds of real time~%" (/ (- real2 real1) internal-time-units-per-second))
	(print "----------------------------------")
)


