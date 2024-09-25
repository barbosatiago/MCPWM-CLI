#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulações de funções de hardware

void read_temperature_sensor() {
    printf("Temperature Sensor: 25.3°C\n");
}

void read_humidity_sensor() {
    printf("Humidity Sensor: 40%%\n");
}

void wifi_connect(const char *ssid) {
    printf("Connecting to Wi-Fi network '%s'...\n", ssid);
    // Simulação de tempo de conexão
    printf("Connected to '%s' successfully.\n", ssid);
}

void wifi_status() {
    printf("Wi-Fi Status: Connected to 'MyWiFi'\n");
}

void wifi_disconnect() {
    printf("Disconnecting from Wi-Fi...\n");
    printf("Wi-Fi disconnected.\n");
}

// Funções para cada comando
int cmd_temperature(char **args) {
    read_temperature_sensor();
    return 1;
}

int cmd_humidity(char **args) {
    read_humidity_sensor();
    return 1;
}

int cmd_wifi_connect(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "Error: Expected SSID after 'wifi_connect'\n");
    } else {
        wifi_connect(args[1]);
    }
    return 1;
}

int cmd_wifi_status(char **args) {
    wifi_status();
    return 1;
}

int cmd_wifi_disconnect(char **args) {
    wifi_disconnect();
    return 1;
}

int cmd_exit(char **args) {
    return 0;
}

// Lista de comandos embutidos
char *builtin_str[] = {
    "temperature",
    "humidity",
    "wifi_connect",
    "wifi_status",
    "wifi_disconnect",
    "exit"
};

// Funções correspondentes para os comandos embutidos
int (*builtin_func[])(char **) = {
    &cmd_temperature,
    &cmd_humidity,
    &cmd_wifi_connect,
    &cmd_wifi_status,
    &cmd_wifi_disconnect,
    &cmd_exit
};

// Leitura de linha de entrada
char *read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

// Dividir a linha em tokens (argumentos)
char **split_line(char *line) {
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

// Execução de comandos embutidos
int execute_command(char **args) {
    if (args[0] == NULL) {
        // Comando vazio
        return 1;
    }

    for (int i = 0; i < sizeof(builtin_str) / sizeof(char *); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    printf("Unknown command: %s\n", args[0]);
    return 1;
}

// Loop principal do shell
void shell_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("embedded-shell> ");
        line = read_line();
        printf("linha chegou\n");
        args = split_line(line);
        printf("parser realizado\n");
        status = execute_command(args);

        free(line);
        free(args);
    } while (status);
}

int main(int argc, char **argv) {
    // Executa o loop principal do shell
    shell_loop();

    return EXIT_SUCCESS;
}