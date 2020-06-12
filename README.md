# ForrestChat

Um chat multiusuários desenvolvido puramente em linguagem C. Foi o meu primeiro projeto desenvolvido sozinho após 3 meses estudando programação, quando comecei a questionar processos assincronos e conexão multiusuários em realtime.

Utilizei conceitos de Multithread e Socket para desenvolver esse projeto. Utilizar essas ferramentas dentro de um projeto em C se mostrou desafiante, visto que não haviam exemplos simples sobre como utiliza-las e por eu estar me aventurando até então por um mundo desconhecido, muitas coisas no início não faziam sentido, ou não funcionavam como o esperado... Quem já se aventurou pelas multithreads sem nenhuma ajuda deve saber do que eu estou falando rs.



## Modo de Uso

### Em rede
Utilize o código do Chat.cpp e do /server/network/Serve.cpp, verifique se ambos estão utilizando a mesma porta. Dentro do script do Chat.cpp, localize o IP dentro do código, e altere-o para ficar com o IP onde o servidor estará rodando.

Compile os dois códigos e execute-os dentro da mesma rede. O server.exe deve ser executado primeiro.

Cada pessoa que quiser se conectar no chat, deve utilizar o executável chat.exe que foi gerado.
