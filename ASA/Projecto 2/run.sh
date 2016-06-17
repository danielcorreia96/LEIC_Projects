for i in {1..6}
do
	./a.out < testes_p2/p2_Tstudents/T0$i/input > testes_p2/p2_Tstudents/T0$i/myoutput
	diff testes_p2/p2_Tstudents/T0$i/output  testes_p2/p2_Tstudents/T0$i/myoutput
done
for i in {1..4}
do
	./a.out < testes_p2/testes_enunciado/input$i.txt > testes_p2/testes_enunciado/myoutput
	diff testes_p2/testes_enunciado/myoutput testes_p2/testes_enunciado/output$i.txt
done
for i in {1..4}
do
	./a.out < testes_p2/testst2-students/in$i > testes_p2/testst2-students/myoutput
	diff testes_p2/testst2-students/myoutput testes_p2/testst2-students/out$i
done
