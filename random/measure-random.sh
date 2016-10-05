#! /bin/bash -
# This shell is for class bench rulelist and header list
# 
i=32
#while [ $i != 128 ]
while [ $i != 128 ]
do
    j=200
    while [ $j != 1200 ]
    do
	k=1
	while [ $k != 11 ]
	do
	    ../main ${i}-${j}-${k} p_${i} | grep 'Search Time\|Total\|A number of' > tmp${k}
	    cat tmp${k} | awk 'NR==1' | awk '{ print $NF }' > nodes_rbt${k}  # a number of nodes on RBT
	    cat tmp${k} | awk 'NR==2' | awk '{ print $NF }' > runs_rbt${k}   # a number of runs on RBT
	    cat tmp${k} | awk 'NR==3' | awk '{ print $NF }' > nodes_prbt${k} # a number of nodes on PRBT
	    cat tmp${k} | awk 'NR==4' | awk '{ print $NF }' > runs_prbt${k}  # a number of runs on PRBT
	    cat tmp${k} | awk 'NR==5' | awk '{ print $NF }' > l_tmptime${k}  # for linear search
	    cat tmp${k} | awk 'NR==6' | awk '{ print $NF }' > l_tmpcomp${k}  
	    cat tmp${k} | awk 'NR==7' | awk '{ print $NF }' > s_tmptime${k}  # for simple search
	    cat tmp${k} | awk 'NR==8' | awk '{ print $NF }' > s_tmpcomp${k}
	    cat tmp${k} | awk 'NR==9' | awk '{ print $NF }' > p_tmptime${k}  # for pointer search
	    cat tmp${k} | awk 'NR==10' | awk '{ print $NF }' > p_tmpcomp${k}
	    echo $((k+=1))
	    echo -e '\n'
	done
	cat nodes_rbt* > random_nodes_rbt_${i}-${j}.txt   # a number of nodes on RBT
	cat runs_rbt* > random_runs_rbt_${i}-${j}.txt     # a number of runs on RBT
	cat nodes_prbt* > random_nodes_prbt_${i}-${j}.txt # a number of nodes on PRBT
	cat runs_prbt* > random_runs_prbt_${i}-${j}.txt   # a number of runs on PRBT
	cat l_tmptime* > random_time_${i}-${j}l.txt  # for linear search
	cat l_tmpcomp* > random_comp_${i}-${j}l.txt
	cat s_tmptime* > random_time_${i}-${j}s.txt  # for simple search
	cat s_tmpcomp* > random_comp_${i}-${j}s.txt
	cat p_tmptime* > random_time_${i}-${j}p.txt  # for pointer search
	cat p_tmpcomp* > random_comp_${i}-${j}p.txt
	rm l_tmp*
	rm s_tmp*
	rm p_tmp*
	rm tmp*
	rm runs_*
	echo $((j+=200))
	echo -e '\n'
    done
    echo $((i=i*2))
    echo -e '\n'
done
