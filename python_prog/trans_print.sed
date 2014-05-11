# trans 'print xxx' to 'print(xxx)'
sed "s/\(\W*\)print \(.*\)$/\1print(\2)/" -i 
