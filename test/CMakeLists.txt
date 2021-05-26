add_executable(encrypt_tests encrypt_tests.c)
target_link_libraries(encrypt_tests PUBLIC libblowfish)

add_test(NAME test_encrypt COMMAND encrypt_tests)

add_executable(decrypt_tests decrypt_tests.c)
target_link_libraries(decrypt_tests PUBLIC libblowfish)

add_test(NAME test_decrypt COMMAND decrypt_tests)
