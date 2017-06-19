#!/bin/bash

maplen=50
mapcol=10
numberoftests=100
resolutor="../bin/inunda"
concorrentes=("../exemplo/floodit_h1" "../exemplo/floodit_h2" "../exemplo/floodit_h4" "../exemplo/floodit_h6")
geradormapa=../utils/geramapa
validasol=../utils/verifica

printf "%-10s\t" ${resolutor##*/}

for i in ${concorrentes[@]}
do
	printf "%-10s\t" ${i##*/}
done
echo

bestCase=0
worstCase=0

for ((i=1; i<=$numberoftests; i++ ))
do
	winning=true
	losing=true
	$geradormapa $maplen $maplen $mapcol $RANDOM > tmp.map
	$resolutor < tmp.map > out.sol
	cat tmp.map out.sol | $validasol
	if [ $? -eq 0 ];
	then
		lensolres=$(head -1 out.sol)
		printf "%-10s\t" ${lensolres}
	else
		printf "%-10s\t" "XXXXX"
		winning=false
	fi
	for res in ${concorrentes[@]}
	do
		$res < tmp.map > out.sol
		cat tmp.map out.sol | $validasol
		if [ $? -eq 0 ];
		then
			lensol=$(head -1 out.sol)
			printf "%-10s\t" ${lensol}
			if [ $lensol -le $lensolres ];
			then
				winning=false
			elif [ $lensol -gt $lensolres ];
			then
				losing=false
			fi
		else
			printf "%-10s\t" "XXXXX"
		fi
	done
	if [ $winning = true ];
	then
		bestCase=$((bestCase+1))
	elif [ $losing = true ];
	then
		worstCase=$((worstCase+1))
	fi
	echo
done

echo "Vitórias: ${bestCase}"
echo "Derrotas: ${worstCase}"
