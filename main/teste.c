#include "driver/mcpwm.h"

// Define a callback function
bool on_compare_event(mcpwm_cmpr_handle_t cmpr, void *user_data) {
    // Your event handling code here
    printf("Comparator event triggered!\n");
    return true;  // Return true to clear the event, false otherwise
}

void app_main(void) {
    // 1. Create a comparator
    mcpwm_cmpr_handle_t comparator;
    mcpwm_comparator_config_t comparator_config = {
        .duty_cycle = 50.0  // Example duty cycle value
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(&comparator_config, &comparator));

    // 2. Define and fill the event callbacks structure
    mcpwm_comparator_event_callbacks_t cbs = {
        .on_compare = on_compare_event,  // Assign your callback function
    };

    // 3. Register the callbacks
    ESP_ERROR_CHECK(mcpwm_comparator_register_event_callbacks(comparator, &cbs, NULL));
    
    // The MCPWM comparator will now trigger the `on_compare_event` callback when the specified event occurs.
}

/**
 * @brief Explicação:
Configuração do Timer MCPWM: Configuramos um timer MCPWM para operar com uma frequência específica (1 kHz neste caso).

Operador e Gerador de PWM: Criamos um operador MCPWM e associamos um gerador de PWM ao operador. Esse gerador será responsável por produzir o sinal PWM.

Comparador: Um comparador é configurado para definir a ação do PWM na borda de descida (quando o valor de comparação é atingido). Configuramos o valor de comparação para 500, o que representa metade do período do PWM, fazendo com que o sinal mude para LOW nesse ponto.

Callback na Borda de Descida: Registramos uma callback que será chamada sempre que o comparador detectar que o PWM está na borda de descida. Isso é feito configurando o evento de comparação no mcpwm_comparator_event_callbacks_t.

Início do Timer: Finalmente, o timer MCPWM é habilitado e iniciado.

Resultado:
Sempre que o PWM estiver na borda de descida, a função on_pwm_falling_edge será chamada, e você verá a mensagem "Borda de descida detectada!" no log.

Considerações:
Retorno da Callback: A callback retorna true para indicar que o evento foi tratado e pode ser limpo. Se retornar false, o evento permanecerá pendente.

Flexibilidade: Esse exemplo é apenas um ponto de partida; você pode ajustar o período do PWM, a comparação, e outros parâmetros conforme necessário para sua aplicação específica.
 * 
 */
#include "driver/mcpwm.h"
#include "esp_log.h"

static const char *TAG = "MCPWM";

// Callback function that will be called on the falling edge
void on_pwm_falling_edge(mcpwm_cmpr_handle_t cmpr, void *user_data) {
    // Código para ser executado na borda de descida do PWM
    printf("Borda de descida detectada\n");
    //ESP_LOGI(TAG, "Borda de descida detectada!");
    //return true;  // Retorne true para limpar o evento, ou false para mantê-lo
}

void app_main(void) {
    // 1. Inicializar o MCPWM e configurar o gerador de PWM
    mcpwm_timer_handle_t pwm_timer;
    mcpwm_gen_handle_t pwm_gen;
    mcpwm_comparator_handle_t comparator;

    mcpwm_timer_config_t timer_config = {
        .group_id = 0,   // Grupo 0
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = 1000000, // 1 MHz resolution
        .period_ticks = 1000,  // Periodo do PWM (1 kHz)
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };

    ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &pwm_timer));

    mcpwm_operator_config_t operator_config = {
        .group_id = 0,  // Grupo 0
    };

    mcpwm_oper_handle_t oper;
    ESP_ERROR_CHECK(mcpwm_new_operator(&operator_config, &oper));
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(oper, pwm_timer));

    mcpwm_generator_config_t gen_config = {
        .gen_id = MCPWM_GEN_ID_0,
        .config = MCPWM_GEN_CFG_DEFAULT,
    };

    ESP_ERROR_CHECK(mcpwm_new_generator(oper, &gen_config, &pwm_gen));

    mcpwm_comparator_config_t comparator_config = {
        .flags.update_cmp_on_tez = true, // Atualiza a comparação na borda de subida do contador
    };

    ESP_ERROR_CHECK(mcpwm_new_comparator(oper, &comparator_config, &comparator));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, 500));  // Ajuste para metade do período

    mcpwm_generator_action_t action_on_cmp = {
        .direction = MCPWM_TIMER_DIRECTION_UP,  // Ação quando o timer está contando para cima
        .comparator = comparator,
        .action = MCPWM_GEN_ACTION_LOW,  // Coloque o sinal em LOW na borda de descida
    };

    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_comparator_event(pwm_gen, &action_on_cmp));

    mcpwm_comparator_event_callbacks_t cmp_callbacks = {
        .on_compare = on_pwm_falling_edge,  // Callback na borda de descida
    };

    // 2. Registrar a callback para a borda de descida
    ESP_ERROR_CHECK(mcpwm_comparator_register_event_callbacks(comparator, &cmp_callbacks, NULL));

    // 3. Iniciar o timer MCPWM
    ESP_ERROR_CHECK(mcpwm_timer_enable(pwm_timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(pwm_timer, MCPWM_TIMER_START_NO_STOP));
}

