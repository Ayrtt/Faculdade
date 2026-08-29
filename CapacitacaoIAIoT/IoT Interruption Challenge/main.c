#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_0 GPIO_NUM_21
#define LED_1 GPIO_NUM_19
#define LED_2 GPIO_NUM_18
#define LED_3 GPIO_NUM_5
#define LED_4 GPIO_NUM_26
#define LED_5 GPIO_NUM_25
#define LED_6 GPIO_NUM_33
#define LED_7 GPIO_NUM_32

#define BUTTON_0 GPIO_NUM_15
#define BUTTON_1 GPIO_NUM_2

#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<LED_0) | (1ULL<<LED_1) | (1ULL<<LED_2) | (1ULL<<LED_3))
#define GPIO_OUTPUT_PIN_SEL2 ((1ULL<<LED_4) | (1ULL<<LED_5) | (1ULL<<LED_6) | (1ULL<<LED_7))
#define GPIO_INPUT_PIN_SEL ((1ULL<<BUTTON_0) | (1ULL<<BUTTON_1))

static void IRAM_ATTR gpio0_isr_handler(void* arg){
  uint8_t *v = (uint8_t*) arg;
  *v = 0;
}

static void IRAM_ATTR gpio1_isr_handler(void* arg){
  uint8_t *v = (uint8_t*) arg;
  *v = 1;
}

int limit(int count){
  if (count == 8) { return 0; }
  else if (count == -1) { return 7; }
  else { return count; }
}

void setup() {
  gpio_config_t led_conf = {};
  led_conf.intr_type = GPIO_INTR_DISABLE;
  led_conf.mode = GPIO_MODE_OUTPUT;
  led_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL | GPIO_OUTPUT_PIN_SEL2;
  led_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  led_conf.pull_up_en = GPIO_PULLUP_DISABLE;
  gpio_config(&led_conf);

  gpio_config_t button_conf = {};
  button_conf.intr_type = GPIO_INTR_LOW_LEVEL;
  button_conf.mode = GPIO_MODE_INPUT;
  button_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
  button_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  button_conf.pull_up_en = GPIO_PULLUP_DISABLE;
  gpio_config(&button_conf);
}

void app_main() {
  setup();

  unsigned lista_led[8] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7};
  unsigned int  lista_valor[] = {1, 2, 4, 8, 16, 32, 64, 128};
  uint8_t direcao = 0;
  int count = 0;

  gpio_install_isr_service(ESP_INTR_FLAG_LOWMED);
  gpio_isr_handler_add(BUTTON_0, gpio0_isr_handler, (void*) &direcao);
  gpio_isr_handler_add(BUTTON_1, gpio1_isr_handler, (void*) &direcao);
  
  while(true){
    gpio_set_level(lista_led[count], 1);
    printf("Valor: %d\n", lista_valor[count]);
    vTaskDelay(1000 / portTICK_RATE_MS);
    gpio_set_level(lista_led[count], 0);
    if (direcao == 0){ count++; }
    else{ count--; } 
    count = limit(count);  
  }
}
