#include "nodelist.h"

#define NODELIST_ASSERT_NOT_NULL  nodelist_dev_t* nl = (nodelist_dev_t*)nodelist_get_handle(); \
    if( nl == NULL ) { \
        ESP_LOGE(TAG,"nodelist is null -> %s:%d (%s)", __FILE__, __LINE__, __FUNCTION__); \
        return NULL; \
    } \

#define NODELIST_ASSERT_INDEX(a) if ( idx < 0 || idx >= OGMA_NODE_MAX_NUMBER ) { \
        ESP_LOGE(TAG, "Index out of bounds"); \
        return NULL; \
    } \


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
        return;
    }
    for(int i=0; i < OGMA_NODE_MAX_NUMBER; i++) {
        node_dev_t* node = nl->data[i];
        if ( node != NULL ) {
            node_display(node);
        }
    }
}

node_handle_t nodelist_get_by_index(int idx) {
    ESP_LOGD(TAG, "node_get_by_index(%d)", idx);

    NODELIST_ASSERT_NOT_NULL;
    NODELIST_ASSERT_INDEX(idx);

    return (node_handle_t)nl->data[idx];
}

node_handle_t nodelist_get_by_id(uint16_t id) {
    ESP_LOGD(TAG, "nodelist_get_by_id(%d)", id);

    NODELIST_ASSERT_NOT_NULL;

    for(int i=0; i < OGMA_NODE_MAX_NUMBER; i++) {
        node_dev_t* node = (node_dev_t*)nl->data[i];
        if ( node != NULL ) {
            if ( node->id == id ) {
                return (node_handle_t)node;
            }
        }
    }
    return NULL;
}

node_handle_t nodelist_get_by_mac(uint8_t* mac) {
    ESP_LOGD(TAG, "nodelist_get_by_mac("MACSTR")", MAC2STR(mac));

    NODELIST_ASSERT_NOT_NULL;

    for(int i=0; i < OGMA_NODE_MAX_NUMBER; i++) {
        node_dev_t* node = (node_dev_t*)nl->data[i];
        if ( node != NULL ) {
            if ( memcmp(node->mac_addr, mac, ESP_NOW_ETH_ALEN) == 0 ) {
                return (node_handle_t)node;
            }
        }
    }
    return NULL;
}

node_handle_t nodelist_get_by_name(char* name) {
    ESP_LOGD(TAG, "nodelist_get_by_name(%s)", name);

    NODELIST_ASSERT_NOT_NULL;

    for(int i=0; i < OGMA_NODE_MAX_NUMBER; i++) {
        node_dev_t* node = (node_dev_t*)nl->data[i];
        if ( node != NULL ) {
            if ( strcmp(node->name, name) == 0 ) {
                return (node_handle_t)node;
            }
        }
    }
    return NULL;
}
