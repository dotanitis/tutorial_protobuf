cmake_minimum_required(VERSION 3.28.3)

project(generate_protobuf)

#ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/src")
#ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/proto")

find_package(Protobuf REQUIRED)

add_library(proto-objects OBJECT "${CMAKE_CURRENT_LIST_DIR}/proto/addressbook.proto")

target_link_libraries(proto-objects PUBLIC protobuf::libprotobuf)

set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/src")

target_include_directories(proto-objects PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")

protobuf_generate(
        TARGET proto-objects
        IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/proto"
        PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")


