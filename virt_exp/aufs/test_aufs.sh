DIR=$HOME/unifs
cd $DIR
mkdir b1 b2
echo "b1" > b1/file
echo "b2" > b2/file

mount -t unionfs -o dirs=$DIR/b1:$DIR/b2 none $DIR/u
