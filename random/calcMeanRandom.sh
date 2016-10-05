#! /bin/bash -

i=16
while [ $i != 128 ]
do
    j=200
    while [ $j != 1200 ]
    do
	cat random_nodes_rbt_${i}-${j}.txt  | awk '{m+=$1} END{print m/NR;}' > tmp_random_nodes_rbt${i}
	cat random_runs_rbt_${i}-${j}.txt   | awk '{m+=$1} END{print m/NR;}' > tmp_random_runs_rbt${i}
	cat random_nodes_prbt_${i}-${j}.txt | awk '{m+=$1} END{print m/NR;}' > tmp_random_nodes_prbt${i}
	cat random_runs_prbt_${i}-${j}.txt  | awk '{m+=$1} END{print m/NR;}' > tmp_random_runs_prbt${i}
	cat random_time_${i}-${j}l.txt      | awk '{m+=$1} END{print m/NR;}' > tmp_random_time_l${i}
	cat random_comp_${i}-${j}l.txt      | awk '{m+=$1} END{print m/NR;}' > tmp_random_comp_l${i}
	cat random_time_${i}-${j}s.txt      | awk '{m+=$1} END{print m/NR;}' > tmp_random_time_s${i}
	cat random_comp_${i}-${j}s.txt      | awk '{m+=$1} END{print m/NR;}' > tmp_random_comp_s${i}
	cat random_time_${i}-${j}p.txt      | awk '{m+=$1} END{print m/NR;}' > tmp_random_time_p${i}
	cat random_comp_${i}-${j}p.txt      | awk '{m+=$1} END{print m/NR;}' > tmp_random_comp_p${i}
	rm tmp*
	echo $((j+=200))
	echo -e '\n'
    done
    echo $((i=i*2))
    echo -e '\n'
done

cat tmp_random_comp_p* > tmp-random-comp-p
sed -e '1d' tmp-random-comp-p > tmp-random-comp-p1
sed -e '2,$d' tmp-random-comp-p > tmp-random-comp-p2
cat tmp-random-comp-p1 tmp-random-comp-p2 > random-comp-p

cat tmp_random_time_p* > tmp-random-time-p
sed -e '1d' tmp-random-time-p > tmp-random-time-p1
sed -e '2,$d' tmp-random-time-p > tmp-random-time-p2
cat tmp-random-time-p1 tmp-random-time-p2 > random-time-p

cat tmp_random_comp_s* > tmp-random-comp-s
sed -e '1d' tmp-random-comp-s > tmp-random-comp-s1
sed -e '2,$d' tmp-random-comp-s > tmp-random-comp-s2
cat tmp-random-comp-s1 tmp-random-comp-s2 > random-comp-s

cat tmp_random_time_s* > tmp-random-time-s
sed -e '1d' tmp-random-time-s > tmp-random-time-s1
sed -e '2,$d' tmp-random-time-s > tmp-random-time-s2
cat tmp-random-time-s1 tmp-random-time-s2 > random-time-s

cat tmp_random_comp_l* > tmp-random-comp-l
sed -e '1d' tmp-random-comp-l > tmp-random-comp-l1
sed -e '2,$d' tmp-random-comp-l > tmp-random-comp-l2
cat tmp-random-comp-l1 tmp-random-comp-l2 > random-comp-l

cat tmp_random_time_l* > tmp-random-time-l
sed -e '1d' tmp-random-time-l > tmp-random-time-l1
sed -e '2,$d' tmp-random-time-l > tmp-random-time-l2
cat tmp-random-time-l1 tmp-random-time-l2 > random-time-l

cat tmp_random_runs_prbt* > tmp-random-runs-prbt
sed -e '1d' tmp-random-runs-prbt > tmp-random-runs-prbt1
sed -e '2,$d' tmp-random-runs-prbt > tmp-random-runs-prbt2
cat tmp-random-runs-prbt1 tmp-random-runs-prbt2 > random-runs-prbt

cat tmp_random_nodes_prbt* > tmp-random-nodes-prbt
sed -e '1d' tmp-random-nodes-prbt > tmp-random-nodes-prbt1
sed -e '2,$d' tmp-random-nodes-prbt > tmp-random-nodes-prbt2
cat tmp-random-nodes-prbt1 tmp-random-nodes-prbt2 > random-nodes-prbt

cat tmp_random_runs_rbt* > tmp-random-runs-rbt
sed -e '1d' tmp-random-runs-rbt > tmp-random-runs-rbt1
sed -e '2,$d' tmp-random-runs-rbt > tmp-random-runs-rbt2
cat tmp-random-runs-rbt1 tmp-random-runs-rbt2 > random-runs-rbt

cat tmp_random_nodes_rbt* > tmp-random-nodes-rbt
sed -e '1d' tmp-random-nodes-rbt > tmp-random-nodes-rbt1
sed -e '2,$d' tmp-random-nodes-rbt > tmp-random-nodes-rbt2
cat tmp-random-nodes-rbt1 tmp-random-nodes-rbt2 > random-nodes-rbt

rm tmp*

# cat tmp_time_acl* > tmpat
# sed -e '1d' tmpat > tmpat1
# sed -e '2,$d' tmpat > tmpat2
# cat tmpat1 tmpat2 > acl_time_l

# cat tmp_comp_fw* > tmpfc
# sed -e '1d' tmpfc > tmpfc1
# sed -e '2,$d' tmpfc > tmpfc2
# cat tmpfc1 tmpfc2 > fw_comp_l

# cat tmp_time_fw* > tmpft
# sed -e '1d' tmpft > tmpft1
# sed -e '2,$d' tmpft > tmpft2
# cat tmpft1 tmpft2 > fw_time_l

# cat tmp_comp_ipc* > tmpic
# sed -e '1d' tmpic > tmpic1
# sed -e '2,$d' tmpic > tmpic2
# cat tmpic1 tmpic2 > ipc_comp_l

# cat tmp_time_ipc* > tmpit
# sed -e '1d' tmpit > tmpit1
# sed -e '2,$d' tmpit > tmpit2
# cat tmpit1 tmpit2 > ipc_time_l

# rm tmp*
