#! /bin/bash -

i=16
while [ $i != 128 ]
do
    j=200
    while [ $j != 1200 ]
    do
	k=1
	while [ $k != 11 ]
	do
	    ./policy $i $j ${i}-${j}-${k}
	    echo $((k+=1))
	    echo -e '\n'
	done
	echo $((j+=200))
	echo -e '\n'
    done
    echo $((i=i*2))
    echo -e '\n'
done
