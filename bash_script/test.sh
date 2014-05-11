#!/usr/bin/bash
set -o errexit
set -o noclobber
set -o nounset
set -o pipefail
set -o errtrace

function traperr
{
    echo "ERROR: ${BASH_SOURCE[0]} ${LINENO}"
    exit 1   # does not seem to affect the program.
    # return 1 # does not seem to affect the program.
}
trap traperr ERR

# run while in a subshell
echo "ONE:"
set +o pipefail
head -1 /etc/passwd |while read aLine
do
    test=$(true | false | true);
    # if as below, same as case FOUR
    # test=$(true | false);
done
echo -e "pass ONE\n"

# not run while in a subshell
echo "TWO:"
set +o pipefail
while read aLine
do
    test=$(true | false | true);
    # if as below, same as case FIVE
    # test=$(true | false);
    break
done </etc/passwd
echo -e "pass TWO\n"

## will block here because errexit
# echo "THREE:"
# set +o pipefail
# test=$(true | false | true |false);
# echo -e "pass THREE\n"

## will block here because 'while' is in a subprocess
## output:
##      ERROR: ./test.sh 10
##      ERROR: ./test.sh 10
##
# echo "FOUR:"
# set -o pipefail
# head -1 /etc/passwd |while read aLine
# do
#     test=$(true | false | true);
# done
# echo -e "pass FOUR\n"


## will block here because because 'while' not in a subprocess
## output:
##      ERROR: ./test.sh 10
# echo "FIVE:"
# set -o pipefail
# while read aLine
# do
#     test=$(true | false | true);
#     break
# done </etc/passwd
# echo -e "pass FIVE\n"

echo "END"