#include "node.h"

CNode::CNode() {
    m_node_handle = node_create();
}

CNode::CNode(node_handle_t handle) {
    m_node_handle = handle;
}

CNode::CNode(uint16_t id, char* name, uint8_t* mac) {
    m_node_handle = node_create();
    SetId(id);
    SetName(name);
    SetMac(mac);
    SetStatus(NODE_UNREGISTRED);
}

CNode::~CNode() {
    node_delete(m_node_handle);
    m_node_handle=NULL;
}
    
void CNode::Display(void) {
    node_display(m_node_handle);
}

void CNode::SetId(uint16_t id) { node_set_id(m_node_handle, id); }
void CNode::SetName(char* name) { node_set_name(m_node_handle, name); }
void CNode::SetMac(uint8_t* mac) { node_set_mac(m_node_handle, mac); }
void CNode::SetStatus(node_status_t status) { node_set_status(m_node_handle, status); }

uint16_t CNode::GetId() { return node_get_id(m_node_handle); }
char* CNode::GetName() { return node_get_name(m_node_handle); }
uint8_t* CNode::GetMac() { return node_get_mac(m_node_handle); }
node_status_t CNode::GetStatus() { return node_get_status(m_node_handle); }

