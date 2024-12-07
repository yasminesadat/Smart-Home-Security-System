#include "shared.h"
#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "ssi.h"
#include "cgi.h"
#include "lwip/netif.h"
#include "ir_sensor.h"

// Wi-Fi Credentials
const char WIFI_SSID[] = "Youssef";
const char WIFI_PASSWORD[] = "youssef12345";


void print_ip_address() {
    struct netif *netif = netif_default;  // Get the default network interface
    if (netif != NULL) {
        printf("Device IP Address: %s\n", ip4addr_ntoa(&netif->ip_addr));
    } else {
        printf("Network interface not available\n");
    }
}
void init ()
{
    ir_sensor_init();
}

int main() {
    stdio_init_all();
 
    // Initialize the Wi-Fi module
    if (cyw43_arch_init() != 0) {
        printf("Failed to initialize CYW43.\n");
        return -1;
    }

    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000) != 0) {
        printf("Retrying Wi-Fi connection...\n");
        sleep_ms(1000);
    }


    
    printf("Connected to Wi-Fi!\n");

    print_ip_address();

    // Initialize HTTP server
    httpd_init();
    printf("HTTP server initialized.\n");

    // Configure CGI handlers
    ssi_init();
    
    cgi_init();
    printf("CGI handler initialized.\n");

    // Infinite loop to keep the server running
    init();

    while (1) {
        ir_reading =ir_sensor_read();
         sleep_ms(1000);
    }

    return 0;
}
