#ifndef _OGMA_NODE_H_
#define _OGMA_NODE_H_

#include "ogma_common.h"

typedef enum {
    NODE_UNREGISTRED = -1
} node_status_t;

typedef struct {
    char            name[OGMA_NODE_NAME_LEN+1];
    uint8_t         mac_addr[ESP_NOW_ETH_ALEN];
    uint16_t        id;
    node_status_t   status;
} node_dev_t;

typedef void* node_handle_t;


node_handle_t node_create();
esp_err_t node_delete(node_handle_t handle);
void node_display(node_handle_t handle);

/*
esp_err_t ogma_nodelist_init();
esp_err_t ogma_nodelist_new(char* name, uint16_t id, uint8_t* mac_addr);
ogma_node_handle_t ogma_nodelist_nodeByIndex(int idx);
ogma_node_handle_t ogma_nodelist_nodeById(uint16_t id);
ogma_node_handle_t ogma_nodelist_nodeByMacAddress(uint8_t* mac_addr);
*/

#endif // _OGMA_NODE_H_