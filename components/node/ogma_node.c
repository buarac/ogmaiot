#include "ogma_node.h"

const char* TAG = "OGMA_NODE";

static ogma_node_handle_t node_list[OGMA_NODE_MAX_NUMBER];
static int node_list_count;

typedef struct {
    uint16_t    count;
    ogma_node_t list[OGMA_NODE_MAX_NUMBER];
} ogma_nodelist_t;

ogma_node_handle_t ogma_node_create() {
    ESP_LOGD(TAG, "ogma_node_create");

    ogma_node_t* node = calloc(1, sizeof(ogma_node_t));
    if ( node == NULL ) {
        return NULL;
    }

    return (ogma_node_handle_t)node;
}

esp_err_t ogma_node_delete(ogma_node_handle_t node) {
    ESP_LOGD(TAG, "ogma_node_delete");
    if ( node == NULL ) {
        ESP_LOGI(TAG, "node is null");
        return ESP_FAIL;
    }
    free(node);
    return ESP_OK;
}

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


