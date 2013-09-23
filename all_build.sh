#!/bin/bash
WF="simple_chinese"
VM=2
VS=0
EXT='.pbw'
GEO='src/geometry.h'
MAIN="src/$WF.c"
BLDCMD='./waf build'
BLDDIR='build'
STDBLD=$BLDDIR/$WF$EXT
RDIR='releases'
line=(4 6 8)
symb=("n" "s" "w")
tt=(true false)

set -x
cp $MAIN $MAIN.sav
sed -i -e "s/1\,\ 0\,/$VM\,\ $VS\,/" $MAIN

mv $GEO $GEO.sav

for t0 in ${tt[@]}
do
   for t1 in ${tt[@]}
   do
	for t2 in ${tt[@]}
	do
	   cp $GEO.sav $GEO
	   suf=""
	   for(( i=0; i<3; i++))
	   do
		var="t$i"
		[ ${!var} = true ] && suf=$suf${symb[$i]}
		sed -i -e "${line[$i]}s/false/${!var}/" $GEO
	   done
	   $BLDCMD
	   cp $STDBLD $RDIR/$WF.v$VM.$VS$suf$EXT
	done
   done
done

mv $GEO.sav $GEO
mv $MAIN.sav $MAIN
