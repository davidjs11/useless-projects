# check argument number
if [ $# -ne 1 ]
then
    echo "Argument number is incorrect. You must load one file only";
    exit 0;
fi;

# check if file exists
if ! [ -f $1 ]
then
    echo "File doesn't exist or is not a file";
    exit 0;
fi;

# load the program to the board
echo "Loading" $1 "...";
arduino --upload $1 --port /dev/ttyACM0;
echo "Done!";
