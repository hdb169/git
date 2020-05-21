#do test.sh runNum

#!/usr/bin/bash
runs=$1
echo
echo
echo $runs

eval "echo $ROOTSYS"


source /site/12gev_phys/softenv.sh 2.3
eval "echo $ROOTSYS"


home_dir=/u/group/c-csv/hdbhatt/my_analysis/livetime/job

echo "$home_dir"
echo
echo

#eval "ls"


root -l -q -b "$home_dir/job_sub_test.C(${runs})"


eval "mv test_job_${runs}.root $home_dir/root"
eval "mv test_job_${runs}.pdf $home_dir/pdf"
echo
echo


#eval "ls $home_dir/pdf/"
#echo
#echo

#eval "ls $home_dir/root/"
#echo
#echo

echo "job success"
