#!/bin/bash
set -x
WF="simple_chinese"
VM=1
VS=1
EXT='.pbw'
GEO='src/geometry.h'
MAIN="src/$WF.c"
BLDCMD='./waf build'
BLDDIR='build'
STDBLD=$BLDDIR/$WF$EXT
RDIR='releases'
SUF=('n' 'w' 'nw')
B0=('false' 'true' 'false')
B1=('true' 'false' 'false')
LINES=(4 6)

cp $MAIN $MAIN.sav
sed -i -e "s/1\,\ 0\,/$VM\,\ $VS\,/" $MAIN

$BLDCMD
cp $STDBLD $RDIR/$WF.v$VM.$VS$EXT

mv $GEO $GEO.sav
i=0  #0 1 2
for suf in ${SUF[@]}
do
    j=0 # 0 1
    cp $GEO.sav $GEO
    for line in ${LINES[@]}
    do
	var="B$j[$i]"
	sed -i -e "${line}s/true/${!var}/" $GEO
	$BLDCMD
	cp $STDBLD $RDIR/$WF.v$VM.$VS$suf$EXT
	j=`expr $j + 1`
    done
    i=`expr $i + 1`
    echo
done

mv $GEO.sav $GEO
mv $MAIN.sav $MAIN
