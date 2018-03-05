JAVADIR=/usr/share/java
PROJDIR=/home/oops/Desktop/share/Projecto/12_11/project
CLASSPATH=$JAVADIR/po-uilib.jar:$JAVADIR/edt-support.jar:$PROJDIR/edt-textui/edt-textui.jar:$PROJDIR/edt-core/edt-core.jar
echo $CLASSPATH

java -Din=testes_in/test1.in  -Dout=testes_out/test1.tout -cp $CLASSPATH edt.textui.TextEditor
java -Din=testes_in/test2.in  -Dout=testes_out/test2.tout -cp $CLASSPATH edt.textui.TextEditor
java -Dimport=testes_in/test3.import -Din=testes_in/test3.in  -Dout=testes_out/test3.tout -cp $CLASSPATH edt.textui.TextEditor
java -Dimport=testes_in/test4.import -Din=testes_in/test4.in  -Dout=testes_out/test4.tout -cp $CLASSPATH edt.textui.TextEditor
java -Din=testes_in/test5.in  -Dout=testes_out/test5.tout -cp $CLASSPATH edt.textui.TextEditor
java -Din=testes_in/test6.in  -Dout=testes_out/test6.tout -cp $CLASSPATH edt.textui.TextEditor
java -Dimport=testes_in/test7.import -Din=testes_in/test7.in  -Dout=testes_out/test7.tout -cp $CLASSPATH edt.textui.TextEditor

diff testes_out/test1.tout testes_ex/test1.out
diff testes_out/test2.tout testes_ex/test2.out
diff testes_out/test3.tout testes_ex/test3.out
diff testes_out/test4.tout testes_ex/test4.out
diff testes_out/test5.tout testes_ex/test5.out
diff testes_out/test6.tout testes_ex/test6.out
diff testes_out/test7.tout testes_ex/test7.out

rm doc1
