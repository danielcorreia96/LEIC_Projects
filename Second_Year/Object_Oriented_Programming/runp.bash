JAVADIR=/usr/share/java
PROJDIR=/home/oops/Desktop/share/Projecto/12_11/project
CLASSPATH=$JAVADIR/po-uilib.jar:$JAVADIR/edt-support.jar:$PROJDIR/edt-textui/edt-textui.jar:$PROJDIR/edt-core/edt-core.jar
echo $CLASSPATH
java -Dimport=project/edt-textui/test.import -cp $CLASSPATH edt.textui.TextEditor
