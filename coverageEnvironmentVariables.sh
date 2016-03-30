MYPWD=${PWD}
echo "export GCOV_PREFIX="$MYPWD/build/coverage-data""
echo "export GCOV_PREFIX_STRIP=`echo $GCOV_PREFIX | tr -d -c '/\n' | awk '{ print length; }'`"
