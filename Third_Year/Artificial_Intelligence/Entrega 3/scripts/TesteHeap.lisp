(setf *queue* (make-heap :nodes (list  (make-node :f 5)) :size 1))
(heapInsert (make-node :f 7) *queue*)
(print "heapInsert 7")
(heapInsert (make-node :f 6) *queue*)
(print "heapInsert 6")
(heapInsert (make-node :f 10) *queue*)
(print "heapInsert 10")
(heapInsert (make-node :f 15) *queue*)
(print "heapInsert 15")
(heapInsert (make-node :f 17) *queue*)
(print "heapInsert 17")
(heapInsert (make-node :f 2) *queue*)
(print "heapInsert 2")
(heapInsert (make-node :f 6) *queue*)
(print "heapInsert 6")
(heapInsert (make-node :f 30) *queue*)
(print "heapInsert 30")
(heapInsert (make-node :f 21) *queue*)
(print "heapInsert 21")