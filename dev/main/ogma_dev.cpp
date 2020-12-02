#include "node.h"
#include "nodelist.h"

uint8_t mac1[6] = { 0x56, 0x67, 0x12, 0xAB, 0xFE, 0x01};
uint8_t mac2[6] = { 0xbc, 0xa1, 0x83, 0xcd, 0x10, 0x50};
uint8_t bcast[6]= { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

extern "C" {
    void app_main(void);
};



void app_main(void) {

    /*
    node_handle_t handle = node_create();
    node_display(handle);
    node_delete(handle);

    node_dev_t* node = NULL;

    nodelist_init();
    nodelist_new_node("12345TESTNODEAJOUTER", 23, mac1);
    nodelist_new_node("0123456789012345678901234567890123456789", 25, mac2);
    //nodelist_new_node("0123456789012345678901234567890123456789", 68, bcast);

    nodelist_display_all();

    node = nodelist_get_by_index(0);
    node_display(node);
    node = nodelist_get_by_index(1);
    node_display(node);
    node = nodelist_get_by_index(2);
    node_display(node);
    node = nodelist_get_by_index(3);
    node_display(node);
    node = nodelist_get_by_index(4);
    node_display(node);
    node = nodelist_get_by_index(400);
    node_display(node);


    node = nodelist_get_by_id(23);
    node_display(node);
    node = nodelist_get_by_id(24);
    node_display(node);
    node = nodelist_get_by_id(25);
    node_display(node);
    node = nodelist_get_by_mac(mac1);
    node_display(node);
    node = nodelist_get_by_mac(mac2);
    node_display(node);
    node = nodelist_get_by_mac(bcast);
    node_display(node);
    node = nodelist_get_by_name("12345TESTNODEAJOUTER");
    node_display(node);
    node = nodelist_get_by_name("01234567890123456789012345678901");
    node_display(node);
    node = nodelist_get_by_name("TEST");
    node_display(node);
    */

    CNode node1;
    CNode node2(1973, "TEST", mac1);

    node1.Display();
    node2.Display();   
    printf("node1.id=%d\n", node1.GetId()); 
    printf("node2.id=%d\n", node2.GetId()); 
    node2.SetId(1389);
    printf("node2.id=%d\n", node2.GetId()); 
}
