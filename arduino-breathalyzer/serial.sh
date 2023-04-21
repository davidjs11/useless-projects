# check arguments
if [ $# -ne 1 ]
then
    echo "You must introduce baudrate as argument!";
    exit 0;
fi;

stty -F /dev/ttyACM0 $1 raw -clocal -echo
cat /dev/ttyACM0
