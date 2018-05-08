#!/bin/bash

# Mudar o caminho da variavel DIR para o directorio onde estao os testes
DIR="testing/tests-xpl-daily-201701121739/"
# DIR="testing/double_basic_tests/"

COUNTER=1

for file in ${DIR}*.xpl
do
  # detecta numero do teste
  FILENAME=$(basename $file)
  NUM=`echo "$FILENAME" | cut -d'-' -f3`
  
  # comando a ser executado
  NAME=`echo "$file" | cut -d'.' -f1`
  TEST=`echo "$FILENAME" | cut -d'.' -f1`
  echo $TEST
  # { ./xpl "$file" --target xml; } >& /dev/null
  { "./xpl/xpl" "$file" --target xml; } >& $DIR/$TEST".xml" # se este nao estiver usa o de cima
  
  # cenas pra converter pra dot e depois pra imagem (neste caso, .ps porque a maquina virtual nao tem nada melhor...)
  { "./xml2dot.py" $DIR/$TEST".xml";   } &> $DIR/"dotfiles"/$TEST".dot"
  { "dot" "-Tps" $DIR/"dotfiles"/$TEST".dot"; } &> $DIR/"images"/$TEST".ps"
  echo $FILENAME" : xml done"
  
  let COUNTER=COUNTER+1
done
#--------------------------------------------------------------------------------------#

echo
echo $(($COUNTER - 1)) " ficheiros xmlizados."
echo

cd $DIR
echo "Verificar error"
grep -nHr --include="*.xml" "error"
echo "Verificar unknown"
grep -nHr --include="*.xml" "unknown"
echo "Verificar undeclared"
grep -nHr --include="*.xml" "undeclared"
cd ../../