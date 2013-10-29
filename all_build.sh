#!/bin/bash
WF="simple_chinese"
VM=3
VS=2
EXT='.pbw'
CFG='src/config.h'
MAIN="src/$WF.c"
BLDCMD='./waf build'
BLDDIR='build'
STDBLD=$BLDDIR/$WF$EXT
RDIR="releases/v$VM.$VS"
Ncfg=4
line=(4 6 8 10)
symb=(n s w f)
tt=(true false)
uuid0=0x99
uuid=$uuid0

set -x
mkdir -p $RDIR
cp $MAIN $MAIN.sav
sed -i -e "s/1\,\ 0\,/$VM\,\ $VS\,/" $MAIN
cp $MAIN $MAIN.tmp


mv $CFG $CFG.sav
for l in ${line[@]}
do
   sed -i -e "${l}s/true/false/" $CFG.sav
done

function func() {
   if [ $1 -lt $Ncfg ]; then
	for t in ${tt[@]}
	do
	   func `expr $1 + 1` $t ${*:2}
	done
   else
	declare -a T=(${*:2})
	echo;echo "---------------------------------------------------------"
	cp $CFG.sav $CFG
	cp $MAIN.tmp $MAIN 
	uuid=`printf "0x%x\n" $(($uuid + 1))`
	sed -i -e "s/$uuid0/$uuid/" $MAIN
	suf=
	for(( i=0; i<$Ncfg; i++))
	do
	   [ ${T[$i]} = true ] && suf=$suf${symb[$i]}
	   sed -i -e "${line[$i]}s/false/${T[$i]}/" $CFG
	done
	if [ ! -z $suf ];then
	   sed -i -e "s/Chinese\",/Chinese $suf\",/" $MAIN
	fi
	$BLDCMD
	mv $STDBLD $RDIR/$WF.v$VM.$VS$suf$EXT
   fi
}

func 0

mv $CFG.sav $CFG
mv $MAIN.sav $MAIN
rm $MAIN.tmp
