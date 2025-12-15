# tutorial-projeto-mull
Um tutorial de como utilizar o Mull, com o uso do wsl.

Segue o video no youtube com o tutorial:
https://www.youtube.com/watch?v=9ReyQ9azE44

Neste video abordamos os seguintes passos:


> **Projeto** **Mull** **–** **passo** **a** **passo:**
>
> Mull -\> Link para o tutorial:
>
> [<u>https://github.com/mull-project/mull</u>](https://github.com/mull-project/mull)
>
> Mull -\> Instalação
>
> [<u>https://mull.readthedocs.io/en/latest/Installation.html</u>](https://mull.readthedocs.io/en/latest/Installation.html)
>
> **Instalar:**
>
> Abrir o CMD e inserir o seguinte comando:
>
> • wsl --install (após o download pede usuário e senha, depois procure
> nos seus arquivos e abra o seu wsl – Ubuntu on Windows)
>
> Ubuntu no Windows:
>
> Para update e upgrade da ferramenta:
>
> • sudo apt update
>
> • sudo apt upgrade -y
>
> Conferir a versão instalada:
>
> • lsb_release -a
>
> Curl:
>
> • curl -1sLf [<u>'https://dl.cloudsmith.io/public/mull-project/mull-stable/setup.deb.sh</u>'](https://dl.cloudsmith.io/public/mull-project/mull-stable/setup.deb.sh) | sudo -E bash
>
> Instalar pacotes:
>
> • sudo apt-get update
>
> • sudo apt-get install mull-19
> • sudo apt-get install clang-19
>
> Verificar se está tudo ok:
>
> • mull-runner-19 --version
>
> Inserindo o código no wsl, através do comando:
>
> • nano cruise_control.c
>
> Então, copie o código de onde o salvou e cole, dando um clique com o
> botão direito na janela do nano.
>
> Linhas comentadas nos ‘Teste de Limite’ e ‘Testes de Tolerância’, para
> observarmos os mutantes que sobreviveriam
>
> Conferir se está todo o código inserido corretamente e se sim, em
> seguida crtl+s e ctrl+x, para salvar e sair respectivamente do ‘nano’;
>
> Os seguintes comandos para compilar e rodar o código usando o Mull:
>
> • clang-19 -fpass-plugin=/usr/lib/mull-ir-frontend-19 -g -grecord-command-line cruise_control.c -o result
>
> • mull-runner-19 result
>
> Observaremos um resultado de ‘Mutation Score’ de 66%, ou seja,
> 04(quatro) deles sobrevivem.
>
> Então, entramos novamente com o comando:
>
> • nano cruise_control.c
>
> E, retiraremos as linhas com comentarios nos ‘Teste de Limite’ e
> ‘Testes de Tolerância’, para verificarmos que o resultado será de 100%
>
> Novamente, entraremos com os seguintes comandos:
>
> • clang-19 -fpass-plugin=/usr/lib/mull-ir-frontend-19 -g -grecord-command-line cruise_control.c -o result
>
> • mull-runner-19 result
>
> Checando a saída:
>
> Todos os Mutantes foram mortos;
>
> Por padrão o Mull traz todas as mutações. Vejamos alguns exemplos de
> operadores de mutação suportados:
>
> xx_adicionar_atribuição_à_sub_atribuiçãoSubstitui += por -=
>
> cxx_adicionar_ao_sub > Substitui + por -
>
> cxx_e_atribuir_a_ou_atribuir > Substitui &= por \|=
>
> cxx_e_para_ou > Substitui & por \|
>
> cxx_assign_const > Substitui 'a = b' por 'a = 42'
>
> cxx_bitwise_not_to_noop > Substitui ~x por x
>
> cxx_div_assign_to_mul_assign > Substitui /= por \*=
>
> cxx_div_para_mul > Substitui / por \*
>
> cxx_eq_para_ne > Substitui == por !=
>
> cxx_ge_para_gt > Substitui \>= por \>
>
> cxx_ge_para_lt > Substitui \>= por \<
>
> cxx_gt_para_ge > Substitui \> por \>=
>
> cxx_gt_para_le > Substitui \> por \<=
