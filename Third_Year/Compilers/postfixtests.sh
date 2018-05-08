#!/bin/bash

DIR="testing/tests-xpl-daily-201701121739/"
EXPECTED="testing/tests-xpl-daily-201701121739/expected/"

# DIR="testing/double_basic_tests/"
# EXPECTED="testing/double_basic_tests/expected/"

# DIR="testing/read_tests/"
# EXPECTED="testing/read_tests/expected/"


COUNTER=1
FAILED=0
COMPILERFAIL=()
YASMFAIL=()
LDFAIL=()
DIFFFAIL=()

for file in ${DIR}*.xpl
do
  # detecta numero do teste
  FILENAME=$(basename $file)
  NUM=`echo "$FILENAME" | cut -d'-' -f3`
  
  # comando a ser executado
  NAME=`echo "$file" | cut -d'.' -f1`
  N=`echo "$FILENAME" | cut -d'.' -f1`
  
  if [[ "$COUNTER" -eq "1" ]]; then
    echo "-----------------------------------------------------"
  fi
  
  # executar o compilador
  printf "%s : %s " "$COUNTER" "$N"
  { ./xpl/xpl "$file" --target asm; } >& "$NAME.output";
  if [[ "$?" -eq "0" ]]; then
    printf "..... Compiler: OK, " 
  else 
    printf "..... Compiler: Failed, ";
    COMPILERFAIL+=("$N")
    let FAILED=FAILED+1
  fi
  
  # produzir o ficheiro binario
  cd $DIR;
  { yasm -felf32 "$N.asm"; } >> /dev/null
  if [[ "$?" -eq "0" ]]; then
    printf "YASM: OK, " 
  else 
    printf "YASM: Failed, ";
      YASMFAIL+=("$N")
  fi
  
  # gerar o executavel linkando a biblioteca RTS
  { ld -m elf_i386 -o "$N"exec "$N.o" -lrts; } >> /dev/null
  if [[ "$?" -eq "0" ]]; then
    echo "LD: OK." 
  else 
    echo "LD: Failed.";
  fi
  { ./"$N"exec > "$N.out"; } >> /dev/null
  { cd ../..; } >& /dev/null
  
  echo
  echo "<<<<< Esperado: >>>>>"
  echo "$(cat $EXPECTED$N.out)"
  echo
  echo "«««««  Obtido:  »»»»»"
  echo "$(cat $NAME.out)"
  echo
  DIFF=$(diff -w -E -B "$NAME.out" "$EXPECTED$N.out") 
  if [ "$DIFF" != "" ];
  then
      let FAILEDTESTS=FAILEDTESTS+1
      echo "#ERRODIFF"
      DIFFFAIL+=("$N")
  fi
  echo "-----------------------------------------------------"
  
  let COUNTER=COUNTER+1
done
#--------------------------------------------------------------------------------------#

echo
echo
echo $(($COUNTER - 1)) " testes efectuados, falhas abaixo:"
echo
echo "COMPILADOR xpl:"
for i in "${COMPILERFAIL[@]}"
do
   echo "    !falha : " $i
done

echo "YASM:"
for i in "${YASMFAIL[@]}"
do
   echo "    !falha : " $i
done

echo "LD:"
for i in "${LDFAIL[@]}"
do
   echo "    !falha : " $i
done

echo "DIFF:"
for i in "${DIFFFAIL[@]}"
do
   echo "    !falha : " $i
done

echo
echo "Passam " $(($(($COUNTER - 1)) - $FAILEDTESTS)) "/" $(($COUNTER - 1))
echo
