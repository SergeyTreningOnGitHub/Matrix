include_directories(${ROOT_DIR}/Inc)
                                   
add_executable(matrix.out main.cpp)

install(TARGETS matrix.out DESTINATION ${ROOT_DIR}/bin)