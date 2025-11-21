

file(GLOB SRCS *.c)
file(GLOB HEAD include)
set(GNL_SRCS ../get_next_line/get_next_line_bonus.c ../get_next_line/get_next_line_utils_bonus.c )

set(LIBFT "$ENV{PWD}/libft/libft.a")
add_executable(iagent ${SRCS} ${GNL_SRCS})
target_include_directories(iagent PRIVATE ${HEAD})

target_link_libraries(iagent PRIVATE ${LIBFT})