#include "node.h"

const static char* TAG = "NODE";

/*
static node_handle_t node_list[OGMA_NODE_MAX_NUMBER];
static int node_list_count;

typedef struct {
    uint16_t    count;
    ogma_node_t list[OGMA_NODE_MAX_NUMBER];
} ogma_nodelist_t;
*/

node_handle_t node_create() {
    ESP_LOGD(TAG, "node_create");

    node_dev_t* node = calloc(1, sizeof(node_dev_t));
    if ( node == NULL ) {
        ESP_LOGE(TAG, "calloc failed");
        return NULL;
    }
    node->status = NODE_UNREGISTRED;
    return (node_handle_t)node;
}

esp_err_t node_delete(node_handle_t handle) {
    ESP_LOGD(TAG, "node_delete");
    if ( handle == NULL ) {
        ESP_LOGI(TAG, "node handle is null");
        return ESP_FAIL;
    }
    node_dev_t* node = (node_dev_t*)handle;
    free(node);
    return ESP_OK;
}

void node_display(node_handle_t handle) {
    if ( handle == NULL ) {
        ESP_LOGD(TAG, "node to display is null");
        return;
    }
    node_dev_t* node = (node_dev_t*)handle;
    ESP_LOGI(TAG, "node name  : %s", node->name);
    ESP_LOGI(TAG, "node id    : %d", node->id);
    ESP_LOGI(TAG, "node mac   : "MACSTR"", MAC2STR(node->mac_addr));
    ESP_LOGI(TAG, "node status: %d", node->status);
}



/*
esp_err_t ogma_nodelist_init() {
    ESP_LOGD(TAG, "ogma_nodelist_init()");
    for(int i=0; i < OGMA_NODE_MAX_NUMBER; i++) {
        ogma_node_handle_t node = node_list[i];
        if ( node != NULL ) {
            free(node);
            node_list[i] = NULL;
        }
    }
    node_list_count = 0;
    ESP_LOGI(TAG, "sizeof(node_list) = %d", sizeof(node_list));
    return ESP_OK;     
}

esp_err_t ogma_nodelist_new(char* name, uint16_t id, uint8_t* mac_addr) {
    ESP_LOGD(TAG, "ogma_nodelist_new(%s, %d)", name, id);

    if ( node_list_count >= OGMA_NODE_MAX_NUMBER ) {
        ESP_LOGE(TAG, "max number of node");
        return ESP_FAIL;
    }

    ogma_node_handle_t node = ogma_node_create();
    if ( node != NULL ) {
        ogma_node_t* n = (ogma_node_t*)node;
        strncpy(n->name, name, OGMA_NODE_NAME_LEN);
        memcpy(n->mac_addr, mac_addr, ESP_NOW_ETH_ALEN);
        n->id = id;
        node_list[node_list_count++] = n;
        return ESP_OK;
    }
    else {
        return ESP_FAIL;
    }
}

ogma_node_handle_t ogma_nodelist_nodeByIndex(int idx) {
    ESP_LOGD(TAG, "ogma_nodelist_nodeByIndex(%d)", idx);

    if ( idx < 0 || ( idx >= node_list_count )) {
        ESP_LOGE(TAG, "index out of bounds");
        return NULL;
    }
    return node_list[idx];
}

ogma_node_handle_t ogma_nodelist_nodeById(uint16_t id) {
    ESP_LOGD(TAG, "ogma_nodelist_nodeById(%d)", id);
    for(int i=0; i < node_list_count; i++) {
        ogma_node_t* n = (ogma_node_t*)node_list[i];
        if ( n->id == id ) {
            return node_list[i];
        }
    }
    return NULL;
}

ogma_node_handle_t ogma_nodelist_nodeByMacAddress(uint8_t* mac_addr) {
    ESP_LOGD(TAG, "ogma_nodelist_nodeByMacAddress("MACSTR")", MAC2STR(mac_addr));
    for(int i=0; i < node_list_count; i++) {
        ogma_node_t* n = (ogma_node_t*)node_list[i];
        if ( memcmp(n->mac_addr, mac_addr, ESP_NOW_ETH_ALEN) == 0 ) {
            return node_list[i];            
        }
    }
    return NULL;
}
*/

