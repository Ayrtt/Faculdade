#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "nvs_flash.h"
#include "ultrasonic.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"

#define SSID "Wokwi-GUEST"
#define PASSPHARSE ""
#define TCPServerIP "159.203.79.141"
#define PORT 50000

#define ECHO_GPIO 12
#define TRIGGER_GPIO 13
#define MAX_DISTANCE_CM 500

static const char *id = "201921250007";

static EventGroupHandle_t wifi_event_group;
const int CONNECTED_BIT = BIT0;
static const char *TAG="tcp_client";

char rx_buffer[128];
char tx_buffer[128];
int sock;
float distance;

SemaphoreHandle_t mutex;
SemaphoreHandle_t binary;

//simple_app.py -a playback.laced.com.br -p 50000 -d 201921250007

void wifi_connect() {
    wifi_config_t cfg = {
        .sta = {
            .ssid = SSID,
            .password = PASSPHARSE,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_disconnect());
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &cfg));
    ESP_ERROR_CHECK(esp_wifi_connect());
}

static esp_err_t event_handler(void *ctx, system_event_t *event) {
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}

static void initialise_wifi(void) {
    esp_log_level_set("wifi", ESP_LOG_NONE); // disable wifi driver logging
    tcpip_adapter_init();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

bool check_error(int err){
  if (err < 0) {
    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
    return 0;
  }
  else {
    int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
    if (len < 0) {
      ESP_LOGE(TAG, "recv failed: errno %d", errno);
      return 0;
    }
    rx_buffer[len] = 0;
    if(strcmp(rx_buffer,"ok") != 0){
      return 0;
    }
  }
  return 1;
}

void start_socket(){
  char host_ip[] = TCPServerIP;
  int addr_family = 0;
  int ip_protocol = 0;
  struct sockaddr_in tcpServerAddr;
  tcpServerAddr.sin_addr.s_addr = inet_addr(TCPServerIP);
  tcpServerAddr.sin_family = AF_INET;
  tcpServerAddr.sin_port = htons(PORT);
  int s, r;
    
  xEventGroupWaitBits(wifi_event_group,CONNECTED_BIT,false,true,portMAX_DELAY);

  sock =  socket(AF_INET, SOCK_STREAM, 0);

  if (sock < 0) {
    ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
    return;
  }
  ESP_LOGI(TAG, "Socket created, connecting to %s:%d", host_ip, PORT);

  int err = connect(sock, (struct sockaddr *)&tcpServerAddr, sizeof(tcpServerAddr));
  if (err != 0) {
    ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
    return;
  }
    
  ESP_LOGI(TAG, "Successfully connected");

  err = send(sock, id, strlen(id), 0);
  if (!check_error(err)){
    printf("Falha no login.\n");
  }
  else{
    printf("Login realizado com sucesso\n");
  }
}

void ultrasonic_test() {
  ultrasonic_sensor_t sensor = {
    .trigger_pin = TRIGGER_GPIO,
    .echo_pin = ECHO_GPIO
  };

  ultrasonic_init(&sensor);
  
  while (true) {
    esp_err_t res = ultrasonic_measure(&sensor, MAX_DISTANCE_CM, &distance);

    if (res == ESP_OK) {
      printf("Distance: %0.04f m\n", distance);
    }
    else {
      printf("Error %d: ", res);
      switch (res) {
        case ESP_ERR_ULTRASONIC_PING:
          printf("Cannot ping (device is in invalid state)\n");
          break;
        case ESP_ERR_ULTRASONIC_PING_TIMEOUT:
          printf("Ping timeout (no device found)\n");
          break;
        case ESP_ERR_ULTRASONIC_ECHO_TIMEOUT:
          printf("Echo timeout (i.e. distance too big)\n");
          break;
        default:
          printf("%s\n", esp_err_to_name(res));
      }
    }

    xSemaphoreGive(binary);
    vTaskDelay(pdMS_TO_TICKS(30000));
  }
}

void tcp_client(){
  while(true){
    xSemaphoreTake(binary, portMAX_DELAY);
    xSemaphoreTake(mutex, portMAX_DELAY);
    printf("distancia tcp: %f m\n", distance);
    sprintf(tx_buffer,"%f", distance);
    int err = send(sock, tx_buffer, strlen(tx_buffer), 0);
    if (err < 0) {
      ESP_LOGE(TAG, "TCP Error occurred during sending: errno %d", errno);
    }
    else{
      printf("dado enviado\n");
    }

    //xSemaphoreGive(binary);
    xSemaphoreGive(mutex);
  }
}

void status_update(){ //task do alive
  while(true){
    xSemaphoreTake(mutex, portMAX_DELAY);
    int err = send(sock, "alive", 5, 0);
    if (!check_error(err)){
      printf("Erro ao enviar 'alive'.\n");
    }
    else{
      printf("'Alive' enviado.\n");
    }
    xSemaphoreGive(mutex);
    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}

void setup() {
  ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
  wifi_event_group = xEventGroupCreate();
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK( ret );
  initialise_wifi();
}

void app_main() {	
  setup();
  start_socket();
  binary = xSemaphoreCreateBinary();
  mutex = xSemaphoreCreateMutex();
  xTaskCreate(ultrasonic_test, "ultrasonic_test", configMINIMAL_STACK_SIZE * 3, NULL, 6, NULL);
  xTaskCreate(&tcp_client,"tcp_client",4096,NULL,5,NULL);
  xTaskCreate(&status_update, "status_update",1024,NULL,5,NULL);
}
