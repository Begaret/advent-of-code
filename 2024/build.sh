cc $1/$1.c -o $1/$1

echo "******* input ******"
cat $1/$1.input | ./$1/$1

echo "******* test *******"
cat $1/$1.test | ./$1/$1

