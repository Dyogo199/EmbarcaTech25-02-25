# Projeto Embarcatech - Executando no Proteus e VSCode

## Descrição do Projeto

Bem-vindo ao projeto *Embarcatech*! Este repositório contém todas as informações necessárias para integrar sua biblioteca ao **Proteus** e usar o **CMake** no **VSCode** para compilar e executar seu projeto. Se você chegou até aqui, é porque está pronto para embarcar nesse mundo de desenvolvimento de sistemas embarcados com uma ferramenta poderosa. Vamos lá!

## Requisitos

Antes de iniciar, tenha certeza de que você possui o seguinte em seu ambiente de desenvolvimento:

- **Proteus** instalado (versão compatível com seu projeto)
- **VSCode** instalado
- **CMake** instalado no VSCode
- Bibliotecas necessárias para o projeto

## Passos para Adicionar a Biblioteca no Proteus

Adicionar a biblioteca no **Proteus** é fácil e rápido! Siga os passos abaixo:

1. **Baixe a Biblioteca**:
   - Acesse a pasta proteus e baixe o arquivo da biblioteca para o Proteus:  
   

2. **Instalar no Proteus**:
   - Extraia o arquivo da biblioteca para uma pasta local no seu computador.
   - No **Proteus**, vá para o menu **Library** → **Library Manager**.
   - Clique em **Browse** e selecione a pasta onde você extraiu os arquivos da biblioteca.
   - Clique em **Install** para adicionar a biblioteca ao Proteus.

3. **Confirmar Instalação**:
   - Após a instalação, você pode verificar se a biblioteca foi adicionada corretamente acessando o menu **Components** e pesquisando pelo nome da biblioteca que acabou de adicionar.

Agora, você pode começar a usar a biblioteca diretamente em seus esquemáticos no **Proteus**.

## Configurando o CMake no VSCode

Com o **CMake** configurado no **VSCode**, você poderá compilar e testar seu código diretamente do editor. Vamos configurar:

1. **Instalar Extensões no VSCode**:
   - Abra o VSCode e vá para a seção de **Extensões**.
   - Pesquise por **CMake Tools** e **C** e instale ambas.
   
2. **Configuração do CMake**:
   - No VSCode, crie um novo projeto ou abra o projeto existente.
   - Selecione **View** → **Terminal** para abrir o terminal integrado no VSCode.
   - Crie um arquivo `CMakeLists.txt` no diretório raiz do seu projeto com o seguinte conteúdo básico:
   
     ```cmake
     cmake_minimum_required(VERSION 3.0)
     project(Embarcatech)

     set(CMAKE_CXX_STANDARD 11)
     add_executable(embarcatech main.cpp)
     ```

3. **Configuração do Ambiente de Compilação**:
   - No terminal, digite o comando abaixo para configurar seu ambiente:
     ```bash
     cmake .
     ```
   - Após a configuração, para compilar, execute:
     ```bash
     make
     ```

## Executando o Projeto no Proteus

Agora que você configurou tanto o **Proteus** quanto o **VSCode** para compilar seu código, vamos executar o projeto:

1. **Importar o Arquivo do Projeto para o Proteus**:
   - No **Proteus**, clique em **File** → **Open** e selecione o arquivo de esquema do seu projeto (geralmente com a extensão `.PDS`).
   - O Proteus vai carregar o projeto e mostrar os componentes.

2. **Configurar o Microcontrolador**:
   - Se você estiver utilizando um microcontrolador como o **Arduino**, **PIC**, ou **AVR**, adicione o modelo correspondente ao seu projeto no **Proteus**.

3. **Configurar o Circuito no Proteus**:
   - Conecte todos os componentes, sensores e atuadores que fazem parte do seu projeto.

4. **Carregar o Código Compilado**:
   - Vá até a **IDE** ou a ferramenta que você usa para compilar o código para o seu microcontrolador.
   - Gere o arquivo `.hex` ou `.elf` que foi compilado pelo **CMake**.
   - No **Proteus**, clique duas vezes no microcontrolador para abrir as propriedades.
   - Em **Program File**, adicione o arquivo `.hex` gerado.

5. **Executar o Projeto**:
   - No **Proteus**, clique no botão **Play** para iniciar a simulação.
   - Você verá o comportamento do seu circuito em tempo real.

## Link do Projeto Explicativo

Para mais detalhes sobre como o projeto funciona, siga este [link explicativo](https://drive.google.com/file/d/1ryX_7qHBybcNYVtc1yT0CqlKfgzru8nS/view?usp=sharing), que traz um passo a passo detalhado de como o sistema foi desenvolvido e como você pode replicar a solução.

---

Se você seguiu esses passos, agora você está pronto para executar o projeto e explorar tudo o que a integração entre o **Proteus**, **VSCode**, e o **CMake** tem a oferecer. Boa sorte e divirta-se no processo de desenvolvimento de sistemas embarcados! 🚀

Se tiver dúvidas, não hesite em nos contatar!
