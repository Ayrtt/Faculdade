#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_system.h"
#include <esp_err.h>
#include "ultrasonic.h"
#include "driver/gpio.h"

#define ECHO_GPIO 12
#define TRIGGER_GPIO 13
#define MAX_DISTANCE_CM 500 // Maximum of 5 meters
#define LED_RED GPIO_NUM_21
#define LED_YEL GPIO_NUM_19
#define LED_GRE GPIO_NUM_18
#define GPIO_OUTPUT_PIN_SEL ((1ULL<<LED_RED) | (1ULL<<LED_YEL) | (1ULL<<LED_GRE))

enum trafficLight_states {RED, YELLOW, GREEN};

static TaskHandle_t xtask_handle_leds = NULL;
enum trafficLight_states state = RED;

void start_leds() {
  gpio_config_t led_config =  {};
  led_config.intr_type = GPIO_INTR_DISABLE;
  led_config.mode = GPIO_MODE_OUTPUT;
  led_config.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
  led_config.pull_down_en = GPIO_PULLDOWN_ENABLE;
  led_config.pull_up_en = GPIO_PULLDOWN_DISABLE;
  gpio_config(&led_config);
}

void setRED(){
  gpio_set_level(LED_RED, 1);
  gpio_set_level(LED_YEL, 0);
  gpio_set_level(LED_GRE, 0);
}

void setYELLOW(){
  gpio_set_level(LED_RED, 0);
  gpio_set_level(LED_YEL, 1);
  gpio_set_level(LED_GRE, 0);
}

void setGREEN(){
  gpio_set_level(LED_RED, 0);
  gpio_set_level(LED_YEL, 0);
  gpio_set_level(LED_GRE, 1);
}

int led_update (int *state){
  if (*state == RED){
    setRED();
    *state = GREEN;
    return 2;
  }
  
  else if (*state == GREEN){
    setGREEN();
    *state = YELLOW;
    return 3;
  }

  else{
    setYELLOW();
    *state = RED;
    return 1;
  }
}

void led_control (void *pvParameters){
  while(true){
    printf("Current state: %d\n", state);
    int time = led_update(&state);
    vTaskDelay((1000*time) / portTICK_RATE_MS);
  }
}

void ultrasonic_test(void *pvParameters)
{
  float distance;

  ultrasonic_sensor_t sensor = {
    .trigger_pin = TRIGGER_GPIO,
    .echo_pin = ECHO_GPIO
  };

  ultrasonic_init(&sensor);
  int pause = 0;
  while (true) {
    esp_err_t res = ultrasonic_measure(&sensor, MAX_DISTANCE_CM, &distance);

    if (res == ESP_OK) {
      printf("Distance: %0.04f m\n", distance);
      if(distance <= 1 && pause == 0){
        vTaskSuspend(xtask_handle_leds);
        setRED();
        state = RED;
        pause = 1;
      }
      else if(distance > 1 && pause == 1){
        vTaskResume(xtask_handle_leds);
        pause = 0;
      }
    } // Print error
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
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

void app_main()
{
  start_leds();
  xTaskCreate(ultrasonic_test, "ultrasonic_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
  xTaskCreate(led_control, "LEDs", 2048, NULL, 5, &xtask_handle_leds);
}
