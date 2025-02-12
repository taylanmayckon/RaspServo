# RaspServo

### Link do vídeo 🎥
**[Link do Drive](https://drive.google.com/drive/folders/17F2SiuFKdQpai-zrvFgZ2ikyz1JJhM3m?usp=sharing)**

### Funcionamento do Projeto 📋
O projeto tem como objetivo configurar o PWM para a frequência de 50Hz, com o intuito de operar um servomotor através da GPIO 22.
O código inicia com uma rotina que movimenta o braço do servo para as posições de: 180º, 90º e 0º, respectivamente, com um intervalo de 5 segundos entre as movimentações.
Após isso, se inicia uma outra rotina, dessa vez com a interrupção do repeating timer, que a cada 10ms ajusta o movimento do braço com um incremento de período de duty cycle de aproximadamente +/- 5us (microssegundos), equivalente a 0,00025% do duty cycle. Essa rotina faz incremento/decremento da angulação do braço num intervalo de 180º a 0º, e depois de 0º a 180º enquanto a placa BitDogLab estiver ativa.
O projeto foi simulado no Wokwi integrado ao VS Code, entretanto devido à falta de um circuito de interface e servomotores para a execução do projeto na prática, configurou-se o mesmo PWM na GPIO 12, que na BitDogLab está conectado a um LED RGB, controlando a cor azul. Com isso, foi possível visualizar a alteração da luminosidade do LED na prática, permitindo a visualização do projeto na vida real e entendendo um pouco mais sobre o funcionamento prático do PWM e sua interação com dispositivos eletrônicos.
