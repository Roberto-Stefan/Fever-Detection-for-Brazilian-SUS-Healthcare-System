#include <Adafruit_MLX90614.h>

int codigoSus;
int idade;
float febre;
int Sim;
int Continuar;

// Definição dos pinos do LED RGB
const int pinRed = 15;
const int pinGreen = 2;
const int pinBlue = 4;

// Definição do pino do buzzer
const int pinBuzzer = 5;

// Inicialização do sensor MLX-90614
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);

  // Configuração dos pinos como saída
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  // Inicialização do sensor
  if (!mlx.begin()) {
    Serial.println("Erro ao inicializar o sensor MLX-90614. Verifique as conexões.");
    while (true)
      ;
  }

  iniciarPrograma();
}

void iniciarPrograma() {
  Serial.println("Digite (1) Para Iniciar o Programa");
  Continuar = lerEntrada();

  while (Continuar == 1) {
    Serial.println("Insira a Sequência de Numeros da Carteira do SUS:");
    codigoSus = lerEntrada();

    if (codigoSus == 12345) {
      Serial.println("Roberto Leonel Stefan - CPF 12764950802");
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
    } else {
      Serial.println("Código Não Encontrado - Dirija-se ao setor de Cadastro");
      Serial.println("Deseja Realizar Outro Atendimento? (1 - Sim, 0 - Não):");
      Continuar = lerEntrada();
    }
  }
  Serial.println("Programa Encerrado - Favor Reiniciar");
}

void loop() {
  // O loop está vazio porque o programa principal está todo no setup.
}

float lerEntrada() {
  while (!Serial.available())
    ;                                             // Aguarda entrada
  String entrada = Serial.readStringUntil('\n');  // Lê até o final da linha
  entrada.trim();                                 // Remove espaços em branco extras
  if (entrada.length() > 0) {
    return entrada.toFloat();  // Converte para float
  } else {
    return -1;  // Retorna -1 se a entrada for inválida
  }
}

void processarFebre(String mensagemAlta, String mensagemNormal) {
  float somaTemperaturas = 0;
  int leiturasValidas = 0;

  for (int i = 0; i < 3; i++) {
    Serial.print("Por favor, coloque o dedo indicador no sensor para a leitura ");
    Serial.print(i + 1);
    Serial.println(" de 3.");
    emitirBip();  // Aviso sonoro para o usuário
    delay(5000);  // Tempo para posicionar o dedo

    Serial.println("Medindo a temperatura... Aguarde.");
    float leitura = mlx.readObjectTempC();  // Lê a temperatura do objeto em Celsius

    if (!isnan(leitura)) {
      somaTemperaturas += leitura;
      leiturasValidas++;
      Serial.print("Leitura ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(leitura);
      Serial.println(" °C");
    } else {
      Serial.println("Erro ao ler a temperatura. Verifique o sensor.");
    }
  }

  if (leiturasValidas > 0) {
    febre = somaTemperaturas / leiturasValidas;
    Serial.print("Temperatura média detectada: ");
    Serial.print(febre);
    Serial.println(" °C");

    if (febre >= 34.7 && febre <= 35.9) {
      Serial.println("Temperatura Normal - " + mensagemNormal);
      setColor(255, 0, 0);  // Verde para temperatura normal
    } else if (febre >= 36.0 && febre <= 37.1) {
      Serial.println("Febre Alta");
      Serial.println("Atenção! Prioridade " + mensagemAlta);
      setColor(255, 255, 0);  // Amarelo para febre alta
      emitirBip();            // Bip para febre alta
    } else if (febre >= 37.2) {
      Serial.println("Febre Muito Alta");
      Serial.println("Atenção! Prioridade " + mensagemAlta);
      setColor(0, 255, 0);  // Vermelho para febre muito alta
      emitirBip();          // Bip para febre muito alta
    } else {
      Serial.println("Erro: Valor de febre inválido");
      apagarLeds();  // Apaga os LEDs em caso de erro
    }
  } else {
    Serial.println("Nenhuma leitura válida foi realizada.");
    apagarLeds();
  }

  delay(3000);   // Segura a cor por 2 segundos
  apagarLeds();  // Apaga os LEDs após o delay
}

void setColor(int red, int green, int blue) {
  analogWrite(pinRed, red);
  analogWrite(pinGreen, green);
  analogWrite(pinBlue, blue);
}

void apagarLeds() {
  analogWrite(pinRed, 0);
  analogWrite(pinGreen, 0);
  analogWrite(pinBlue, 0);
  1
}

void emitirBip() {
  tone(pinBuzzer, 1000, 500);  // Emite um som de 1000 Hz por 500 ms
  delay(500);                  // Aguarda 500 ms antes de seguir
}
