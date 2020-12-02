#include "node.h"

CNode::CNode() {
    m_node_handle = node_create();
}

CNode::CNode(uint16_t id, char* name, uint8_t* mac) {
    m_node_handle = node_create();
    node_dev_t* node = (node_dev_t*)m_node_handle;
    if ( node != NULL ) {
        node->id = id;
        strncpy(node->name, name, OGMA_NODE_NAME_LEN);
        node->name[OGMA_NODE_NAME_LEN] = '\0';
        memcpy(node->mac_addr, mac, ESP_NOW_ETH_ALEN);
    }
}

CNode::~CNode() {
    node_delete(m_node_handle);
    m_node_handle=NULL;
}

void CNode::Display(void) {
    node_display(m_node_handle);
}

void CNode::SetId(uint16_t id) {
    node_set_id(m_node_handle, id);
}

uint16_t CNode::GetId() {
    return node_get_id(m_node_handle);
}