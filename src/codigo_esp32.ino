/*****************************************************************************************
* PROJETO: Roberto L. Stefan
* MÓDULO: Sistema de Triagem com Sensor Infravermelho MLX90614
*
* DESCRIÇÃO:
* Firmware responsável pela identificação de usuários, verificação de prioridade
* de atendimento e medição de temperatura corporal utilizando sensor infravermelho.
* O sistema realiza triagem automatizada e indica o nível de prioridade através
* de sinalização visual (LED RGB) e sonora (buzzer).
*
* FUNCIONALIDADES PRINCIPAIS:
* - Leitura de identificação do usuário via interface serial
* - Verificação de prioridade por idade ou condição especial
* - Aquisição de temperatura utilizando sensor MLX90614
* - Processamento e classificação da temperatura corporal
* - Indicação visual através de LED RGB
* - Alerta sonoro por buzzer
*
* HARDWARE UTILIZADO:
* - Microcontrolador: Arduino Uno
* - Sensor de Temperatura: MLX90614
* - LED RGB
* - Buzzer
*
* INTERFACES UTILIZADAS:
* - I2C (Comunicação com sensor MLX90614)
* - UART / Serial (Entrada de dados do usuário)
* - GPIO (Controle de LED e buzzer)
*
* AUTOR / RESPONSÁVEL: Roberto L. Stefan
* ORGANIZAÇÃO / EMPRESA: 
*
* VERSÃO DO SOFTWARE: __________
* DATA DE CRIAÇÃO: ____ / ____ / ______
* ÚLTIMA MODIFICAÇÃO: ____ / ____ / ______
*
* OBSERVAÇÕES:
******************************************************************************************/

// Biblioteca para comunicação com o sensor MLX90614
#include <Adafruit_MLX90614.h>

//////////////////////////////////////////////////////
// Variáveis globais
//////////////////////////////////////////////////////

int codigoSus;      // Armazena o código SUS digitado
int idade;          // Armazena a idade do paciente
float febre;        // Armazena a temperatura média medida
int Sim;            // Variável usada para resposta de prioridade
int Continuar;      // Controla repetição do atendimento

//////////////////////////////////////////////////////
// Definição dos pinos do LED RGB
//////////////////////////////////////////////////////

const int pinRed = 15;     // Pino do LED vermelho
const int pinGreen = 2;    // Pino do LED verde
const int pinBlue = 4;     // Pino do LED azul

//////////////////////////////////////////////////////
// Definição do pino do buzzer
//////////////////////////////////////////////////////

const int pinBuzzer = 5;   // Pino do buzzer

//////////////////////////////////////////////////////
// Inicialização do sensor MLX90614
//////////////////////////////////////////////////////

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//////////////////////////////////////////////////////
// Função SETUP
// Executada apenas uma vez ao iniciar o sistema
//////////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);  // Inicializa comunicação serial

  // Configuração dos pinos como saída
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  // Inicialização do sensor de temperatura
  if (!mlx.begin()) {

    // Caso o sensor não seja detectado
    Serial.println("Erro ao inicializar o sensor MLX-90614. Verifique as conexões.");

    while (true); // trava o sistema
  }

  // Inicia o programa principal
  iniciarPrograma();
}

//////////////////////////////////////////////////////
// Função principal do sistema
//////////////////////////////////////////////////////

void iniciarPrograma() {

  Serial.println("Digite (1) Para Iniciar o Programa");

  // Lê comando inicial
  Continuar = lerEntrada();

  // Loop principal do sistema
  while (Continuar == 1) {

    Serial.println("Insira a Sequência de Numeros da Carteira do SUS:");

    codigoSus = lerEntrada();

//////////////////////////////////////////////////////
// Paciente 1
//////////////////////////////////////////////////////

    if (codigoSus == 12345) {

      Serial.println("Roberto Leonel Stefan - CPF 12764950802");

      Serial.println("Insira a Sua Idade:");

      idade = lerEntrada();

      // Verifica se é idoso
      if (idade >= 60) {

        processarFebre("Sala 1 - Preferencial", "Fila 1 - Preferencial");

      } else {

        Serial.println("Pessoas Com Deficiência - Gestantes - Lactantes - Crianças de Colo - Pessoas Obesas");
        Serial.println("Sim - Digite 1");
        Serial.println("Não - Digite Qualquer Numero:");

        Sim = lerEntrada();

        if (Sim == 1) {

          processarFebre("Sala 2 - Preferencial", "Fila 2 - Preferencial");

        } else {

          processarFebre("Sala 3 - Normal", "Fila 3 - Normal");
        }
      }

      Serial.println("Deseja Realizar Outro Atendimento? (1 - Sim, 0 - Não):");

      Continuar = lerEntrada();

//////////////////////////////////////////////////////
// Paciente 2
//////////////////////////////////////////////////////

    } else if (codigoSus == 54321) {

      Serial.println("Maria Clara Silva - CPF 98765432101");

      Serial.println("Insira a Sua Idade:");

      idade = lerEntrada();

      if (idade >= 60) {

        processarFebre("Sala 1 - Preferencial", "Fila 1 - Preferencial");

      } else {

        Serial.println("Pessoas Com Deficiência - Gestantes - Lactantes - Crianças de Colo - Pessoas Obesas");

        Serial.println("Sim - Digite 1");
        Serial.println("Não - Digite Qualquer Numero:");

        Sim = lerEntrada();

        if (Sim == 1) {

          processarFebre("Sala 2 - Preferencial", "Fila 2 - Preferencial");

        } else {

          processarFebre("Sala 3 - Normal", "Fila 3 - Normal");
        }
      }

      Serial.println("Deseja Realizar Outro Atendimento? (1 - Sim, 0 - Não):");

      Continuar = lerEntrada();

//////////////////////////////////////////////////////
// Paciente 3
//////////////////////////////////////////////////////

    } else if (codigoSus == 67890) {

      Serial.println("Carlos Eduardo Gomes - CPF 12309845677");

      Serial.println("Insira a Sua Idade:");

      idade = lerEntrada();

      if (idade >= 60) {

        processarFebre("Sala 1 - Preferencial", "Fila 1 - Preferencial");

      } else {

        Serial.println("Pessoas Com Deficiência - Gestantes - Lactantes - Crianças de Colo - Pessoas Obesas");

        Serial.println("Sim - Digite 1");
        Serial.println("Não - Digite Qualquer Numero:");

        Sim = lerEntrada();

        if (Sim == 1) {

          processarFebre("Sala 2 - Preferencial", "Fila 2 - Preferencial");

        } else {

          processarFebre("Sala 3 - Normal", "Fila 3 - Normal");
        }
      }

      Serial.println("Deseja Realizar Outro Atendimento? (1 - Sim, 0 - Não):");

      Continuar = lerEntrada();

//////////////////////////////////////////////////////
// Código não encontrado
//////////////////////////////////////////////////////

    } else {

      Serial.println("Código Não Encontrado - Dirija-se ao setor de Cadastro");

      Serial.println("Deseja Realizar Outro Atendimento? (1 - Sim, 0 - Não):");

      Continuar = lerEntrada();
    }
  }

  Serial.println("Programa Encerrado - Favor Reiniciar");
}

//////////////////////////////////////////////////////
// Loop vazio (programa roda no setup)
//////////////////////////////////////////////////////

void loop() {

  // O programa principal está no setup
}

//////////////////////////////////////////////////////
// Função para ler dados da serial
//////////////////////////////////////////////////////

float lerEntrada() {

  while (!Serial.available());  // Aguarda entrada

  String entrada = Serial.readStringUntil('\n');  // Lê até ENTER

  entrada.trim();  // remove espaços

  if (entrada.length() > 0) {

    return entrada.toFloat();  // converte para número

  } else {

    return -1; // valor inválido
  }
}

//////////////////////////////////////////////////////
// Função responsável por medir temperatura
//////////////////////////////////////////////////////

void processarFebre(String mensagemAlta, String mensagemNormal) {

  float somaTemperaturas = 0;  // soma das leituras
  int leiturasValidas = 0;     // contador de leituras válidas

  // Realiza 3 medições
  for (int i = 0; i < 3; i++) {

    Serial.print("Por favor, coloque o dedo indicador no sensor para a leitura ");

    Serial.print(i + 1);

    Serial.println(" de 3.");

    emitirBip();  // alerta sonoro

    delay(5000);  // tempo para posicionar dedo

    Serial.println("Medindo a temperatura... Aguarde.");

    float leitura = mlx.readObjectTempC();  // leitura do sensor

    if (!isnan(leitura)) {

      somaTemperaturas += leitura;

      leiturasValidas++;

      Serial.print("Leitura ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(leitura);
      Serial.println(" °C");

    } else {

      Serial.println("Erro ao ler a temperatura.");
    }
  }

//////////////////////////////////////////////////////
// Cálculo da média
//////////////////////////////////////////////////////

  if (leiturasValidas > 0) {

    febre = somaTemperaturas / leiturasValidas;

    Serial.print("Temperatura média detectada: ");
    Serial.print(febre);
    Serial.println(" °C");

//////////////////////////////////////////////////////
// Classificação da temperatura
//////////////////////////////////////////////////////

    if (febre >= 34.7 && febre <= 35.9) {

      Serial.println("Temperatura Normal - " + mensagemNormal);

      setColor(255, 0, 0);  // LED verde

    }

    else if (febre >= 36.0 && febre <= 37.1) {

      Serial.println("Febre Alta");

      Serial.println("Atenção! Prioridade " + mensagemAlta);

      setColor(255, 255, 0); // LED amarelo

      emitirBip();

    }

    else if (febre >= 37.2) {

      Serial.println("Febre Muito Alta");

      Serial.println("Atenção! Prioridade " + mensagemAlta);

      setColor(0, 255, 0); // LED vermelho

      emitirBip();
    }

    else {

      Serial.println("Erro: Valor de febre inválido");

      apagarLeds();
    }

  } else {

    Serial.println("Nenhuma leitura válida foi realizada.");

    apagarLeds();
  }

  delay(3000);   // mantém LED aceso

  apagarLeds();  // apaga LED
}

//////////////////////////////////////////////////////
// Função para controlar LED RGB
//////////////////////////////////////////////////////

void setColor(int red, int green, int blue) {

  analogWrite(pinRed, red);
  analogWrite(pinGreen, green);
  analogWrite(pinBlue, blue);
}

//////////////////////////////////////////////////////
// Função para apagar LEDs
//////////////////////////////////////////////////////

void apagarLeds() {

  analogWrite(pinRed, 0);
  analogWrite(pinGreen, 0);
  analogWrite(pinBlue, 0);
}

//////////////////////////////////////////////////////
// Função para emitir som no buzzer
//////////////////////////////////////////////////////

void emitirBip() {

  tone(pinBuzzer, 1000, 500); // frequência 1000Hz por 500ms

  delay(500);
}
