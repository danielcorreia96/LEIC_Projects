; IA - Entrega 3
; Grupo 77
; Pedro Caldeira 81888
; Daniel Correia 80967

(load "datastructures.fas")
(load "auxfuncs.fas")

;(load "datastructures.lisp")
;(load "auxfuncs.lisp")

;;; TAI positions
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
  (let ((successors nil))
    (dolist (act (possible-actions) successors)
      (let ((new-state (nextState st act)))
  (if (not (member new-state successors :test #'equalp))
      (push new-state successors))))))

;;; Solucao e uma seq ordenada de estados
(defun solution (node)
  (let ((seq-states nil))
    (loop
      (when (null node)
  (return))
      (push (node-state node) seq-states)
      (setf node (node-parent node)))
    (values seq-states)))


;;; limdepthfirstsearch
(defun limdepthfirstsearch (problem lim &key cutoff?)
  "limited depth first search
     st - initial state
     problem - problem information
     lim - depth limit"
  (labels ((limdepthfirstsearch-aux (node problem lim)
       (if (isGoalp (node-state node))
     (solution node)
     (if (zerop lim)
         :cutoff
         (let ((cutoff? nil))
           (dolist (new-state (nextStates (node-state node)))
       (let* ((new-node (make-node :parent node :state new-state))
        (res (limdepthfirstsearch-aux new-node problem (1- lim))))
         (if (eq res :cutoff)
             (setf cutoff? :cutoff)
             (if (not (null res))
           (return-from limdepthfirstsearch-aux res)))))
           (values cutoff?))))))
    (let ((res (limdepthfirstsearch-aux (make-node :parent nil :state (problem-initial-state problem))
          problem
          lim)))
      (if (eq res :cutoff)
    (if cutoff?
        :cutoff
        nil)
    res))))


;iterlimdepthfirstsearch
(defun iterlimdepthfirstsearch (problem &key (lim most-positive-fixnum))
  "limited depth first search
     st - initial state
     problem - problem information
     lim - limit of depth iterations"
  (let ((i 0))
    (loop
      (let ((res (limdepthfirstsearch problem i :cutoff? T)))
  (when (and res (not (eq res :cutoff)))
    (return res))
  (incf i)
  (if (> i lim)
      (return nil))))))

;; Solution of phase 3

(defstruct h_position
  pos
  value
)

(defun adjacentPositions (pos)
  "generate all possible next states"
  (let ( (nextStatesResult '()) (all-actions (possible-actions)) )
    (dolist (action all-actions)
	   (let ((newPosition (make-pos
              (+ (first pos) (first action))
              (+ (second pos) (second action))
            ))
          )
          (push newPosition nextStatesResult)
     )
    )
  (values nextStatesResult)
  )
)


(defun memberFrontier (pos frontier)
  (dolist (el frontier)
    (if (equal pos (h_position-pos el))
      (return-from memberFrontier T)
    )
  )
  (return-from memberFrontier nil)
)
;; Heuristica BFS - not working
(defun compute-heuristic (st)
  (if (isGoalp st)
    (return-from compute-heuristic 0)
  )
  (let* ( (initialPosition (make-h_position
            :pos (state-pos st)
            :value 0
          ))
          (endpositions (track-endpositions (state-track st)))
          (frontier (list initialPosition))

          (explored (list))
        )
    (loop
      (if (eq frontier nil)
        (return-from compute-heuristic nil)
      )
      (let ( (newPosition (first (last frontier))) )
        (setf frontier (butlast frontier))
        (push (h_position-pos newPosition) explored)
        (dolist (childPosition (adjacentPositions (h_position-pos newPosition)))
          (if (and (equal (member childPosition explored :test 'equal) nil)
                   (not(memberFrontier childPosition frontier)))
            (if (and (not(isObstaclep childPosition (state-track st)))
                     (not(equal childPosition (h_position-pos newPosition)))
                )
              (if (member childPosition endpositions :test 'equal)
                  (return-from compute-heuristic (+ (h_position-value newPosition) 1))
                  (push (make-h_position
                          :pos childPosition
                          :value (+ (h_position-value newPosition) 1)
                        )
                    frontier)
              )
            )
          )
        )
      )
    )
  )
)



(defun insertInPlace (child_node myList)
   (if (null myList)
       (cons child_node '())
       (if (<= (node-f child_node) (node-f (car myList)) )
           (cons child_node myList)
           (cons (car myList) (insertInPlace child_node (cdr myList)))))
)

(defun nodeSolution (node)
  (if (eq (node-parent node) nil)
    (return-from nodeSolution (list (node-state node)))
  )
    (return-from nodeSolution (append (nodeSolution (node-parent node)) (list (node-state node))))
)

;;; A*
(defun a* (problem)
  (let ( (h_value (compute-heuristic (problem-initial-state problem))) )
    (if (equal h_value nil)
      (return-from a* nil)
    )
    (let* ( (initial_node (make-node
              :state (problem-initial-state problem)
              :g 0
              :h h_value
              :f (+ 0 h_value)
            ))
            (frontier (make-heap :nodes (list initial_node) :size 1))
          )

      (loop
        (if (eq frontier nil)
            (return-from a* nil)
        )
        (let ( (node (extractMin frontier)) )
          (if (eq (funcall (problem-fn-isGoal problem) (node-state node)) t)
            (return-from a* (nodeSolution node))
          )
          (dolist (child_state (funcall (problem-fn-nextStates problem) (node-state node)) nil)
            (let* ( (h_child (compute-heuristic child_state))
                    (g_child (+ (state-cost child_state) (node-g node)))
                   (child_node (make-node
                    :state child_state
                     :parent node
                      :g g_child
                      :h h_child
                      :f (+ g_child h_child)
                    ))
                  )
                (heapInsert child_node frontier)
            )
          )
        )
      )
    )
  )
)


(defun key (node)
  (return-from key (node-f node))
)
(defun findMin (heap)
  (return-from findMin (car heap))
)
(defun extractMin (heap)
  (if (not (eq (heap-nodes heap ) nil))
    (progn

      (let ( (min (first (heap-nodes heap))) )
      (setf (heap-size heap) (1-(heap-size heap)))

      (setf  (heap-nodes heap) (append (last (heap-nodes heap)) (cdr ( butlast (heap-nodes heap))) ))
      (heapSiftDown heap )
      (return-from extractMin min))
    )
  )
)


(defun heapSiftDown (heap)
    (let ((root 0)
          (end  ( heap-size heap))
         )
      (loop while (<= (heapLeftChild root) end)
         do
         (let ( (child (heapLeftChild root)) )
            (if (and (<= (1+ child) (1- end)) (> (key (nth child (heap-nodes heap))) (key (nth (1+ child) (heap-nodes heap)))))
              (setf child (1+ child))
            )

            (if (and (<= child (1- end))(> (key (nth root (heap-nodes heap))) (key (nth child (heap-nodes heap)))))
              (progn
                  (heapSwap root child heap)
                  (setf root child)
              )
              (return-from heapSiftDown heap)
            )
          )
      )
    )
     (return-from heapSiftDown heap)
)

(defun heapInsert (node heap)
  (let (
        (index (heap-size heap))
        )

      (setf (heap-nodes heap) (append (heap-nodes heap) (list node )))
      (setf (heap-size heap) (1+ index))
      (loop while (and (> index  0 ) (<= (key (nth index (heap-nodes heap)) ) (key (nth (heapParent index) (heap-nodes heap) ) ))  )
        do
          (heapSwap index (heapParent index) heap)
          (setf index (heapParent index))

          )
      (return-from heapInsert t)
    )
)

(defun heapSwap (i j heap)
  (psetf (nth i (heap-nodes heap)) (nth j (heap-nodes heap))
         (nth j (heap-nodes heap)) (nth i (heap-nodes heap)))
)
(defun heapParent (i)
  (floor (/ (1- i ) 2))
)

(defun heapRightChild (i)
  ( + (* i 2) 2)
)

(defun heapLeftChild (i)
   (+ (* i 2) 1))

(defstruct heap
  nodes
  size
)

(defun best-search (problem)
      (let* ((initialState (problem-initial-state problem))
             (heuristicMap (createNewHeuristicMatrix initialState) )
            )
        (if (eq (nth (pos-c (state-pos initialState)) (nth (pos-l (state-pos initialState)) heuristicMap)) nil)
          (return-from best-search nil)
        )
        (return-from best-search (best-a* problem heuristicMap))
      )
)

(defun memberExplored (st explored)
  (dolist (el explored)
    (if (and (equal (state-pos st) (state-pos el))
             (equal (state-vel st) (state-vel el))
      )
        (return-from memberExplored "A")
    )
  )
  (return-from memberExplored "B")
)
(defun best-a* (problem matrix)
  (let* ( (initial_state (problem-initial-state problem))
          (h_value (best-compute-heuristic initial_state matrix)) 
          (initial_node (make-node
              :state (problem-initial-state problem)
              :g 0
              :h h_value
              :f (+ 0 h_value)
            ))
          ; (list initial_node) -> passar pra array
          (frontier (make-heap :nodes (list initial_node) :size 1))
          (explored (list))
        )
      (setf (state-action initial_state) (make-acce 0 0))
      (loop
        (if (eq (heap-size frontier) -1)
            (return-from best-a* nil)
        )
        (let ( (node (extractMin frontier)) )
          (if (eq (funcall (problem-fn-isGoal problem) (node-state node)) t)
            (return-from best-a* (nodeSolution node))
          )
          (push (node-state node) explored)
          
          (dolist (child_state (funcall (problem-fn-nextStates problem) (node-state node)) nil)
            (let* ( (h_child (best-compute-heuristic child_state matrix))
                    (g_child (+ (state-cost child_state) (node-g node)))
                   (child_node (make-node
                    :state child_state
                     :parent node
                      :g g_child
                      :h h_child
                      :f (+ g_child h_child)
                    ))
                  )
              (if (not(equal (memberExplored child_state explored) "A"))
                  (heapInsert child_node frontier)
              )
            )
          )
        )
      )
    )
  )

(defun best-compute-heuristic (st matrix) 
  (let* ( 
          (st_vel (state-vel st))
          (st_pos (state-pos st))
          (v_max (max (abs(vel-l st_vel)) (abs(vel-c st_vel))))
          (distance (nth (pos-c st_pos) (nth (pos-l st_pos) matrix)))
          (somatory 0)
          (h_value 0)
          (loop_vel v_max)
        )
    (loop while (< somatory distance) do
      (setf loop_vel (1+ loop_vel))
      (setf somatory (+ somatory loop_vel))
      (setf h_value (1+ h_value))
    )
    (return-from best-compute-heuristic h_value)
  )
)

(defun createNewHeuristicMatrix (state)
  (let* ( (size (track-size ( state-track state ) ) )
         (newMatrix (make-list (car size) ))

        )
        (dotimes (x (pos-l size))
            (setf (nth x newMatrix) (make-list (pos-c size) :initial-element most-positive-fixnum))
        )
        (fillMatrixWithDistances state newMatrix)
        (return-from createNewHeuristicMatrix newMatrix)
  )
)

(defun fillMatrixWithDistances (st matrix)
  (let* ( (goals (track-endpositions (state-track st)))
          (frontier goals)
      )
    (loop 
      for x from 0 to most-positive-fixnum 
      while (not(equal frontier nil))  
      do
      (dolist (el frontier) 
        (setf (nth (pos-c el) (nth (pos-l el) matrix) ) x)
      )
      (let ( (new_frontier (list)) )
        (dolist (el frontier)
          (dolist (adj_pos (adjacentPositions el)) 
            (if (and(not(isObstaclep adj_pos (state-track st))) 
                    (eq (nth (pos-c adj_pos) (nth (pos-l adj_pos) matrix)) most-positive-fixnum)
                    (not(member adj_pos new_frontier :test 'equal))
                )
              (push adj_pos new_frontier)
            )
          )
        )
        (setf frontier new_frontier)
      )
    )
  )
)
