

file(GLOB SRCS ../srcs/inotify.c ../srcs/thread_monitor.c ../srcs/socket.c ../get_next_line/*.c)
file(GLOB TEST_UNIT *.c)
file(GLOB HEAD ../include)

add_compile_options(-Wall -Wextra -Werror)

set(LIBFT /home/cc/gpu_lab/log_agent/bash_agent_ia/libft/libft.a)


add_executable(test_1  ${TEST_UNIT} ${SRCS})

target_link_libraries(test_1 PRIVATE ${LIBFT})
target_include_directories(test_1 PRIVATE ${HEAD})

add_test(NAME test_1 COMMAND test_1)