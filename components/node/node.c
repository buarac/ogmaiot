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

    if ( handle == NULL ) {
        ESP_LOGD(TAG, "node to display is null");
        return;
    }
    ((node_dev_t*)handle)->id = id;
}

uint16_t node_get_id(node_handle_t handle) {
    ESP_LOGD(TAG, "node_get_id");

    if ( handle == NULL ) {
        ESP_LOGD(TAG, "node to display is null");
        return 0;
    }
    return ((node_dev_t*)handle)->id;
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
