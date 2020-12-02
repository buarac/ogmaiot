#ifndef _OGMA_NODE_H_
#define _OGMA_NODE_H_

#include "ogma_common.h"

#ifdef __cplusplus
extern "C"
{
#endif

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
void node_set_id(node_handle_t handle, uint16_t id);
uint16_t node_get_id(node_handle_t handle);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

class CNode {
    private:
        node_handle_t m_node_handle;

        CNode(const CNode&);
        CNode& operator =(const CNode&);
    public:
        CNode();
        CNode(uint16_t id, char* name, uint8_t* mac);
        ~CNode();

        void Display(void);
        uint16_t GetId();
        void SetId(uint16_t id);
};

#endif // __cplusplus

#endif // _OGMA_NODE_H_