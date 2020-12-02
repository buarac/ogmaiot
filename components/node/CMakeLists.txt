
idf_component_register(
    SRCS "node.c" "node_obj.cpp"
    INCLUDE_DIRS include
    PRIV_INCLUDE_DIRS "include"
    REQUIRES common
)
