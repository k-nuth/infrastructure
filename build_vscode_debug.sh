cd build

# rm -rf *

conan install .. -o with_tests=True -s build_type=Debug 

conan build ..