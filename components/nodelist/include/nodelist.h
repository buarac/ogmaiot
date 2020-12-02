#ifndef _OGMA_NODELIST_H_
#define _OGMA_NODELIST_H_

#include "node.h"

typedef struct {
    node_dev_t* data[OGMA_NODE_MAX_NUMBER];
    int count;
} nodelist_dev_t;
typedef void* nodelist_handle_t;

nodelist_handle_t nodelist_init();
esp_err_t nodelist_new_node(char* name, uint16_t id, uint8_t* mac);

void nodelist_display_all();


node_handle_t nodelist_get_by_index(int idx);
node_handle_t nodelist_get_by_id(uint16_t id);
node_handle_t nodelist_get_by_mac(uint8_t* mac);
node_handle_t nodelist_get_by_name(char* name);

/*
esp_err_t ogma_nodelist_init();
esp_err_t ogma_nodelist_new(char* name, uint16_t id, uint8_t* mac_addr);
ogma_node_handle_t ogma_nodelist_nodeByIndex(int idx);
ogma_node_handle_t ogma_nodelist_nodeById(uint16_t id);
ogma_node_handle_t ogma_nodelist_nodeByMacAddress(uint8_t* mac_addr);
*/

#endif // _OGMA_NODELIST_H_