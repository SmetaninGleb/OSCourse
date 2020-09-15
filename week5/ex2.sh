
# Before fixing the script the race condition was appearing. It appeared when both threads tried to work with the 
# ex2_file.txt file. Also then the file ex2_file.txt is the critical section (region).

echo "1" > ex2_file.txt
rm ex2_file.txt.lock;
for i in {1..5}
do
    if ln ex2_file.txt ex2_file.txt.lock
    then
        last=`cat ex2_file.txt | tail -n 1`;
        expr $last + 1 >> ex2_file.txt;
        rm ex2_file.txt.lock;
    else
        while ! ln ex2_file.txt ex2_file.txt.lock
        do
        :;
        done
        last=`cat ex2_file.txt | tail -n 1`;
        expr $last + 1 >> ex2_file.txt;
        rm ex2_file.txt.lock;
    fi
done