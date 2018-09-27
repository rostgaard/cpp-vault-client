
add_executable(test_client client.cpp hashicorpvaultclient.cpp)

target_link_libraries(test_client curl)
