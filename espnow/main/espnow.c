#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_now.h"
#include "esp_crc.h"

#define ESPNOW_WIFI_MODE WIFI_MODE_AP
#define ESPNOW_WIFI_IF   ESP_IF_WIFI_AP
#define ESPNOW_QUEUE_SIZE   10

typedef struct {
    uint8_t     mac_addr[ESP_NOW_ETH_ALEN];
    uint8_t*    data;
    int         data_len;
} espnow_event_t;

static const char* TAG = "espnow";

static xQueueHandle s_espnow_queue;
static uint8_t  s_broadcast_mac[ESP_NOW_ETH_ALEN] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

#define IS_BROADCAST_ADDR(addr) (memcmp(addr, s_broadcast_mac, ESP_NOW_ETH_ALEN) == 0 )

//static void gtway_espnow_deinit();
static esp_err_t gtway_espnow_init(void);
static void gtway_wifi_init(void);
static void gtway_espnow_send_cb(const uint8_t *mac_addr, esp_now_send_status_t status);
static void gtway_espnow_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int len);
static void gtway_espnow_task(void *pvParameter);

//
static void gtway_wifi_init(void) {
    ESP_LOGD(TAG, "gtway_wifi_init");    

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(ESPNOW_WIFI_MODE) );
    ESP_ERROR_CHECK( esp_wifi_start());    
}
//
static esp_err_t gtway_espnow_init(void) {
    ESP_LOGD(TAG, "gtway_espnow_init");   

    s_espnow_queue = xQueueCreate(ESPNOW_QUEUE_SIZE, sizeof(espnow_event_t));
    if (s_espnow_queue == NULL) {
        ESP_LOGE(TAG, "Create mutex fail");
        return ESP_FAIL;
    }

    /* Initialize ESPNOW and register sending and receiving callback function. */
    ESP_ERROR_CHECK( esp_now_init() );
    ESP_ERROR_CHECK( esp_now_register_send_cb(gtway_espnow_send_cb) );
    ESP_ERROR_CHECK( esp_now_register_recv_cb(gtway_espnow_recv_cb) );

    /* Add broadcast peer information to peer list. */
    esp_now_peer_info_t *peer = malloc(sizeof(esp_now_peer_info_t));
    if (peer == NULL) {
        ESP_LOGE(TAG, "Malloc peer information fail");
        vSemaphoreDelete(s_espnow_queue);
        esp_now_deinit();
        return ESP_FAIL;
    }
    memset(peer, 0, sizeof(esp_now_peer_info_t));
    peer->channel = 11;
    peer->ifidx = ESPNOW_WIFI_IF;
    peer->encrypt = false;
    memcpy(peer->peer_addr, s_broadcast_mac, ESP_NOW_ETH_ALEN);
    ESP_ERROR_CHECK( esp_now_add_peer(peer) );
    free(peer);
    return ESP_OK;
}
//
/*
static void gtway_espnow_deinit() {
    ESP_LOGD(TAG, "gtway_espnow_deinit");    
}
*/
//
static void gtway_espnow_send_cb(const uint8_t *mac_addr, esp_now_send_status_t status) {
    ESP_LOGD(TAG, "gtway_espnow_send_cb");
    ESP_LOGI(TAG, "espnow data sent to "MACSTR" with status %d", MAC2STR(mac_addr), status);
}
//
static void gtway_espnow_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int len) {
    ESP_LOGD(TAG, "gtway_espnow_recv_cb");
    espnow_event_t evt;

    if ( data == NULL || len <= 0 ) {
        return;
    }

    evt.data = calloc(1, len);
    if ( evt.data == NULL ) {
        ESP_LOGW(TAG, "failed to calloc espnow event");
        return;
    }

    memcpy(evt.mac_addr, mac_addr, ESP_NOW_ETH_ALEN);
    memcpy(evt.data, data, len);
    evt.data_len = len;
    if (xQueueSend(s_espnow_queue, &evt, portMAX_DELAY) != pdTRUE) {
        ESP_LOGW(TAG, "Send receive queue fail");
        free(evt.data);
    }
}
// 
static void gtway_espnow_task(void *pvParameter) {
    ESP_LOGD(TAG, "gtway_espnow_task");

    espnow_event_t evt;

    while (xQueueReceive(s_espnow_queue, &evt, portMAX_DELAY) == pdTRUE) {
        ESP_LOG_BUFFER_HEXDUMP(TAG, &evt, sizeof(espnow_event_t), ESP_LOG_INFO);
        if ( evt.data != NULL ) {
            free(evt.data);
        }
    }
}

void app_main(void) {

    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK( nvs_flash_erase() );
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    gtway_wifi_init();
    ESP_ERROR_CHECK(gtway_espnow_init());
    xTaskCreate(gtway_espnow_task, "gtway_espnow_task", 2048, NULL, 4, NULL);
    while(1) {
        ESP_LOGD(TAG, "i'm alive.");
        vTaskDelay(30000/portTICK_RATE_MS);
    }
}
