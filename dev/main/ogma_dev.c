#include "node.h"
#include "nodelist.h"

uint8_t mac1[6] = { 0x56, 0x67, 0x12, 0xAB, 0xFE, 0x01};
uint8_t mac2[6] = { 0xbc, 0xa1, 0x83, 0xcd, 0x10, 0x50};
uint8_t bcast[6]= { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};



void app_main(void) {

    node_handle_t handle = node_create();
    node_display(handle);
    node_delete(handle);

    nodelist_init();
    nodelist_new_node("12345TESTNODEAJOUTER", 23, mac1);
    nodelist_new_node("67890TESTNODEAJOUTER", 25, mac2);
    nodelist_new_node("0123456789012345678901234567890123456789", 68, bcast);

    nodelist_display_all();

    /*
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
    */
}
