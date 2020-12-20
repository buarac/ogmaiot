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

void node_set_id(node_handle_t handle, uint16_t id) {
    ESP_LOGD(TAG, "node_set_id(%d)", id);
    ((node_dev_t*)handle)->id = id; 
}

void node_set_name(node_handle_t handle, char* name) {
    ESP_LOGD(TAG, "node_set_name(%s)", name);
    node_dev_t* node = (node_dev_t*)handle;
    strncpy(node->name, name, OGMA_NODE_NAME_LEN);
    node->name[OGMA_NODE_NAME_LEN] = '\0';
}

void node_set_mac(node_handle_t handle, uint8_t* mac) {
    ESP_LOGD(TAG, "node_set_mac("MACSTR")", MAC2STR(mac));
    memcpy(((node_dev_t*)handle)->mac_addr, mac, ESP_NOW_ETH_ALEN);
}

void node_set_status(node_handle_t handle, node_status_t status) {
    ESP_LOGD(TAG, "node_set_status(%d)", status);
    ((node_dev_t*)handle)->status = status;
}

uint16_t node_get_id(node_handle_t handle) {
    return ((node_dev_t*)handle)->id;
}

char* node_get_name(node_handle_t handle) {
    return ((node_dev_t*)handle)->name;
}

uint8_t* node_get_mac(node_handle_t handle) {
    return ((node_dev_t*)handle)->mac_addr;
}

node_status_t node_get_status(node_handle_t handle) {
    return ((node_dev_t*)handle)->status;
}

void node_display(node_handle_t handle) {
    ESP_LOGD(TAG, "node_display");
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
