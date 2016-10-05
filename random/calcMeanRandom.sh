#! /bin/bash -

i=16
while [ $i != 128 ]
do
    j=200
    while [ $j != 1200 ]
    do
	cat random_nodes_rbt_${i}-${j}.txt  | awk '{m+=$1} END{print m/NR;}' > tmp_random_nodes_rbt${j}
	cat random_runs_rbt_${i}-${j}.txt   | awk '{m+=$1} END{print m/NR;}' > tmp_random_runs_rbt${j}
	cat random_nodes_prbt_${i}-${j}.txt | awk '{m+=$1} END{print m/NR;}' > tmp_random_nodes_prbt${j}
	cat random_runs_prbt_${i}-${j}.txt  | awk '{m+=$1} END{print m/NR;}' > tmp_random_runs_prbt${j}
	cat random_time_${i}-${j}l.txt      | awk '{m+=$1} END{print m/NR;}' > tmp_random_time_l${j}
	cat random_comp_${i}-${j}l.txt      | awk '{m+=$1} END{print m/NR;}' > tmp_random_comp_l${j}
	cat random_time_${i}-${j}s.txt      | awk '{m+=$1} END{print m/NR;}' > tmp_random_time_s${j}
	cat random_comp_${i}-${j}s.txt      | awk '{m+=$1} END{print m/NR;}' > tmp_random_comp_s${j}
	cat random_time_${i}-${j}p.txt      | awk '{m+=$1} END{print m/NR;}' > tmp_random_time_p${j}
	cat random_comp_${i}-${j}p.txt      | awk '{m+=$1} END{print m/NR;}' > tmp_random_comp_p${j}
	echo $((j+=200))
	echo -e '\n'
    done

    cat tmp_random_comp_p* > tmp-random-comp-p
    sed -e '1d' tmp-random-comp-p > tmp-random-comp-p1
    sed -e '2,$d' tmp-random-comp-p > tmp-random-comp-p2
    cat tmp-random-comp-p1 tmp-random-comp-p2 > random-comp-${i}p

    cat tmp_random_time_p* > tmp-random-time-p
    sed -e '1d' tmp-random-time-p > tmp-random-time-p1
    sed -e '2,$d' tmp-random-time-p > tmp-random-time-p2
    cat tmp-random-time-p1 tmp-random-time-p2 > random-time-${i}p

    cat tmp_random_comp_s* > tmp-random-comp-s
    sed -e '1d' tmp-random-comp-s > tmp-random-comp-s1
    sed -e '2,$d' tmp-random-comp-s > tmp-random-comp-s2
    cat tmp-random-comp-s1 tmp-random-comp-s2 > random-comp-${i}s

    cat tmp_random_time_s* > tmp-random-time-s
    sed -e '1d' tmp-random-time-s > tmp-random-time-s1
    sed -e '2,$d' tmp-random-time-s > tmp-random-time-s2
    cat tmp-random-time-s1 tmp-random-time-s2 > random-time-${i}s

    cat tmp_random_comp_l* > tmp-random-comp-l
    sed -e '1d' tmp-random-comp-l > tmp-random-comp-l1
    sed -e '2,$d' tmp-random-comp-l > tmp-random-comp-l2
    cat tmp-random-comp-l1 tmp-random-comp-l2 > random-comp-${i}l

    cat tmp_random_time_l* > tmp-random-time-l
    sed -e '1d' tmp-random-time-l > tmp-random-time-l1
    sed -e '2,$d' tmp-random-time-l > tmp-random-time-l2
    cat tmp-random-time-l1 tmp-random-time-l2 > random-time-${i}l

    cat tmp_random_runs_prbt* > tmp-random-runs-prbt
    sed -e '1d' tmp-random-runs-prbt > tmp-random-runs-prbt1
    sed -e '2,$d' tmp-random-runs-prbt > tmp-random-runs-prbt2
    cat tmp-random-runs-prbt1 tmp-random-runs-prbt2 > random-runs-prbt${i}

    cat tmp_random_nodes_prbt* > tmp-random-nodes-prbt
    sed -e '1d' tmp-random-nodes-prbt > tmp-random-nodes-prbt1
    sed -e '2,$d' tmp-random-nodes-prbt > tmp-random-nodes-prbt2
    cat tmp-random-nodes-prbt1 tmp-random-nodes-prbt2 > random-nodes-prbt${i}

    cat tmp_random_runs_rbt* > tmp-random-runs-rbt
    sed -e '1d' tmp-random-runs-rbt > tmp-random-runs-rbt1
    sed -e '2,$d' tmp-random-runs-rbt > tmp-random-runs-rbt2
    cat tmp-random-runs-rbt1 tmp-random-runs-rbt2 > random-runs-rbt${i}

    cat tmp_random_nodes_rbt* > tmp-random-nodes-rbt
    sed -e '1d' tmp-random-nodes-rbt > tmp-random-nodes-rbt1
    sed -e '2,$d' tmp-random-nodes-rbt > tmp-random-nodes-rbt2
    cat tmp-random-nodes-rbt1 tmp-random-nodes-rbt2 > random-nodes-rbt${i}

    rm tmp*

    echo $((i=i*2))
    echo -e '\n'
done
