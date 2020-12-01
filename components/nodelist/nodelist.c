#include "nodelist.h"

const static char* TAG = "NODELIST";

static nodelist_dev_t m_nList;

nodelist_handle_t nodelist_get_handle() {
    return (nodelist_handle_t)&m_nList;
}

nodelist_handle_t nodelist_init() {
    ESP_LOGD(TAG, "nodelist_init()");

    nodelist_dev_t* nl = (nodelist_dev_t*)nodelist_get_handle();
    if ( nl == NULL ) {
        ESP_LOGE(TAG, "nodelist object is null");
        return NULL;
    }
    for(int i=0; i < OGMA_NODE_MAX_NUMBER; i++) {
        node_dev_t* node = nl->data[i];
        if ( node != NULL ) {
            free(node);
            nl->data[i] = NULL;
        }
    }
    nl->count = 0;
    return ESP_OK;
}

esp_err_t nodelist_new_node(char* name, uint16_t id, uint8_t* mac) {
    ESP_LOGD(TAG, "nodelist_new_node()");

    nodelist_dev_t* nl = (nodelist_dev_t*)nodelist_get_handle();
    if ( nl == NULL ) {
        ESP_LOGE(TAG, "nodelist is null");
        return ESP_FAIL;
    }

    if ( nl->count >= OGMA_NODE_MAX_NUMBER ) {
        ESP_LOGW(TAG, "Max number of node reached, can't add new node");
        return ESP_FAIL;
    }

    node_handle_t handle = node_create();
    if ( handle == NULL ) {
        ESP_LOGW(TAG, "Creation of new node object failed");
        return ESP_FAIL;
    }

    node_dev_t* node = (node_dev_t*)handle;
    strncpy(node->name, name, OGMA_NODE_NAME_LEN);
    node->name[OGMA_NODE_NAME_LEN] = '\0';
    memcpy(node->mac_addr, mac, ESP_NOW_ETH_ALEN);
    node->id = id,
    node->status = NODE_UNREGISTRED;
    nl->data[nl->count++] = node;

    return ESP_OK;
}


void nodelist_display_all() {
    ESP_LOGD(TAG, "nodelist_display_all()");

    nodelist_dev_t* nl = (nodelist_dev_t*)nodelist_get_handle();
    if ( nl == NULL ) {
        ESP_LOGE(TAG, "nodelist is null");
        return ESP_FAIL;
    }
    for(int i=0; i < OGMA_NODE_MAX_NUMBER; i++) {
        node_dev_t* node = nl->data[i];
        if ( node != NULL ) {
            node_display(node);
        }
    }
}

/*

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

