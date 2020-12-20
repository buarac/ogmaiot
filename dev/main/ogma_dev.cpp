#include "node.h"
//#include "nodelist.h"

uint8_t mac1[6] = { 0x56, 0x67, 0x12, 0xAB, 0xFE, 0x01};
uint8_t mac2[6] = { 0xbc, 0xa1, 0x83, 0xcd, 0x10, 0x50};
uint8_t bcast[6]= { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

extern "C" {
    void app_main(void);
};



void app_main(void) {

    CNode node1;
    CNode node2(1973, "TEST", mac1);

    node1.Display();
    node2.Display();   

    printf("node1.id=%d\n", node1.GetId()); 
    printf("node1.name=%s\n", node1.GetName()); 
    printf("node1.id="MACSTR"\n", MAC2STR(node1.GetMac())); 
    printf("node1.status=%d\n", node1.GetStatus()); 

    node1.SetId(1050);
    node1.SetName("TESTAVECSETTER");
    node1.SetMac(mac1);
    node1.SetStatus(NODE_REGISTRED);
    node1.Display();

    node_handle_t node = node_create();

    node_set_id(node, 1051);
    node_set_name(node, "TESTAVECDEVENC");
    node_set_mac(node, mac2);
    node_set_status(node, NODE_REGISTRED);
    node_display(node);

    NODE_SET(node, 2020, "LESYSTEMLECHUZA", mac1, NODE_UNDEFINED);
    node_display(node);

    CNode node3(node);
    node3.Display();
}
