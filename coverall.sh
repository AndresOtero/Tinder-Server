cd build/coverage-data
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/usr/include/*' --output-file coverage.info
lcov --remove coverage.info 'rocksdb/*' --output-file coverage.info
lcov --remove coverage.info 'gmock/*' --output-file coverage.info
lcov --remove coverage.info 'gtest/*' --output-file coverage.info
lcov --remove coverage.info 'test/*' --output-file coverage.info
lcov --remove coverage.info 'json/*' --output-file coverage.info
lcov --list coverage.info
coveralls-lcov --repo-token "${COVERALLS_TOKEN}" coverage.info
