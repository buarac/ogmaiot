#set(COMPONENT_SRCS "ogma_dev.cpp")
#set (COMPONENT_SRCS "ogma_espnow.c")
set (COMPONENT_SRCS "espnow.c")

register_component()

# Create a SPIFFS image from the contents of the 'spiffs_image' directory
# that fits the partition named 'storage'. FLASH_IN_PROJECT indicates that
# the generated image should be flashed when the entire project is flashed to
# the target with 'idf.py -p PORT flash'.
