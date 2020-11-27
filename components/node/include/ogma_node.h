#ifndef _OGMA_NODE_H_
#define _OGMA_NODE_H_

#include "ogma_common.h"

typedef void* ogma_node_handle_t;

typedef struct {
    char        name[OGMA_NODE_NAME_LEN];
    uint8_t     mac_addr[ESP_NOW_ETH_ALEN];
    uint16_t    id;
} ogma_node_t;

ogma_node_handle_t ogma_node_create();
esp_err_t ogma_node_delete(ogma_node_handle_t node);

esp_err_t ogma_nodelist_init();
esp_err_t ogma_nodelist_new(char* name, uint16_t id, uint8_t* mac_addr);
ogma_node_handle_t ogma_nodelist_nodeByIndex(int idx);
ogma_node_handle_t ogma_nodelist_nodeById(uint16_t id);
ogma_node_handle_t ogma_nodelist_nodeByMacAddress(uint8_t* mac_addr);

#endif // _OGMA_NODE_H_