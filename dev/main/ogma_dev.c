#include "ogma_node.h"

uint8_t mac1[6] = { 0x56, 0x67, 0x12, 0xAB, 0xFE, 0x01};
uint8_t mac2[6] = { 0xbc, 0xa1, 0x83, 0xcd, 0x10, 0x50};
uint8_t bcast[6]= { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

void display_node(ogma_node_handle_t node) {
    if ( node == NULL ) {
        printf("node is null\n");
    }
    else {
        ogma_node_t* n = (ogma_node_t*)node;
        printf("node name: %s\n", n->name);
        printf("node id  : %d\n", n->id);
        printf("node mac : "MACSTR"\n", MAC2STR(n->mac_addr));
    }
}

void app_main(void) {

    ogma_node_handle_t node = ogma_node_create();
    ogma_node_delete(node);

    ogma_nodelist_init();
    ogma_nodelist_new("12345TESTNODEAJOUTER", 23, mac1);
    ogma_nodelist_new("67890TESTNODEAJOUTER", 25, mac2);

    node = ogma_nodelist_nodeByIndex(0);
    display_node(node);
    node = ogma_nodelist_nodeByIndex(1);
    display_node(node);
    node = ogma_nodelist_nodeByIndex(2);
    display_node(node);
    node = ogma_nodelist_nodeByIndex(45);
    display_node(node);
    node = ogma_nodelist_nodeById(23);
    display_node(node);
    node = ogma_nodelist_nodeById(24);
    display_node(node);
    node = ogma_nodelist_nodeById(25);
    display_node(node);
    node = ogma_nodelist_nodeByMacAddress(mac1);
    display_node(node);
    node = ogma_nodelist_nodeByMacAddress(mac2);
    display_node(node);
    node = ogma_nodelist_nodeByMacAddress(bcast);
    display_node(node);
}
