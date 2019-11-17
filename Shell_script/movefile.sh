#shell script two move a directory , ab is moved to cd, the first file is what we have, and second is what we wish
echo "please enter two file names"
read ab cd
if mv $ab $cd
then
    echo "the file is successfully moved."
else
    echo "the file can't be moved."

fi
