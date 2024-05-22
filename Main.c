int main()

{
    // Tamanho máximo do nome escolhido pelo usuário
    char inicias[7];
    // opções do menu principal
    int optionsPrincipal = 0;
    // opções do menu categoria
    int optionsCategorias = 0;
    // opções do menu de scores
    int optionsScores = 0;

    // Variavel para guardar o tamanho do nome
    int tamanhoDasInicias;
    printf("\t**Jogo da Forca**");

    // gameLoop é um valor bool para fechar o jogo completamente em condicionais.
    while (gameLoop)
    {

        printf("\n");
        printf("\nDigite seu nome (maximo, 6 letras), EX: FELIPE\n");
        printf("\n");
        scanf(" %s", &inicias);
        // fflush(stdin) limpa o buffer do teclado para prevenir Bugs nas entradas do usuario
        fflush(stdin);
        printf("\n");
        // Limpa o terminal a cada scanf
        system("cls");

        // Tamanho do nome
        tamanhoDasInicias = strlen(inicias);

        // Se o nome for maior que o limite estabelecido, um alerta é imprimido no terminal
        // Senão, iteramos sobre o nome e deixamos cada letra escolhida maiuscula usando a função toupper()
        // imprime o nome escolhido e sai do loop
        if (tamanhoDasInicias > 6)
        {
            printf("Nome Muito grande, digite novamente\n");
        }
        else
        {
            for (int i = 0; i < tamanhoDasInicias; i++)
            {
                char letraDoNome = inicias[i];
                inicias[i] = toupper(letraDoNome);
            }
            printf("Nome escolhido: [%s]", inicias);
            break;
        }
    }

    // O nome sendo copiadas para a variavel string do struct
    strcpy(jogador.nome, inicias);

    // gameLoop é um valor bool para fechar o jogo completamente em condicionais.
    while (gameLoop)
    {
        // Menu Principal
        printf("\n\n\t**Jogo da Forca**\n");

        printf("\n\t --------------\n\t Menu Principal\n\t --------------\nDigite o numero da opcao desejada: \n\n");
        printf("[1] - Selecionar categorias \n[2] - Mostrar Scores De Minhas "
               "Jogatinas\n[3] - Sair\n");
        printf("\n");
        scanf(" %d", &optionsPrincipal);
        fflush(stdin);
        system("cls");

        if (optionsPrincipal == 3)
        {
            // Se a opção digitada for a 3, chamamos a função para o calculo do score final
            calculoScoreFinal();
            break;
        }

        switch (optionsPrincipal)
        {
        case 1:
            // Menu de Categorias
            while (optionsPrincipal)
            {
                printf("\n");
                printf("\t[Menu Categorias]\nDigite o numero da opcao desejada: \n\n");
                printf("[1] - Cores \n[2] - Frutas\n[3] - Paises\n[4] - Animais\n[5] - "
                       "Times da serie A\n[6] - Personagens de Naruto\n[7] - Atos Musicais Gringos\n[8] - Protagonistas de Anime\n[9] - Desenhos animados\n[10] - Voltar\n\n");
                scanf(" %d", &optionsCategorias);
                fflush(stdin);
                system("cls");
                // escolha por tip de jogo
                switch (optionsCategorias)
                {
                // Casos para entrada do usuario
                case 1:
                    jogo(1);
                    break;
                case 2:
                    jogo(2);
                    break;

                case 3:
                    jogo(3);
                    break;

                case 4:
                    jogo(4);
                    break;

                case 5:
                    jogo(5);
                    break;
                case 6:
                    jogo(6);
                    break;

                case 7:
                    jogo(7);
                    break;

                case 8:
                    jogo(8);
                    break;

                case 9:
                    jogo(9);
                    break;
                // Sai do menu de categorias e volta ao principal
                case 10:
                    break;

                // Caso nao for digitado casos do switch não sera considerado valido
                default:
                    printf("[%d] Nao e uma opcao valida digite outra\n\n",
                           optionsCategorias);
                    continue;
                }

                break;
            }
            break;

        case 2:
            // Menu de Scores

            // Reverte o Vetor de Scores Original e outro vetor recebe esses valores
            for (int i = 0; i < numeroDeVezesJogadas; i++)
            {
                reversoVetorScore[i] = jogador.scoreParcial[numeroDeVezesJogadas - i - 1];
            }

            // Caso o usuario não tiver jogado ainda não seram mostrado scores
            if (numeroDeVezesJogadas == 0)
            {
                printf("\t[Menu de Scores]\nDigite o numero da opcao desejada: \n\n");
                printf("Voce ainda nao possue Scores! Jogue para pontuar!\n\n");
            }

            // Usando o vetorJogatinas que contem o numero das jogatinas e imprime elas de forma ao contrario

            /*
            isso se da por conta de o numero de jogatinas ser contado de forma crescente mostrado de forma que sua ultima jogatina sera a primeira e buscando valores anteriores. no caso do vetorJogatinas a ultima jogatina fica armazenada no primeiro index, e a antipenultima no segundo, tornando assim necessario a inversao da ordem do vetor dos Scores.
            */
            for (int i = 0; i < numeroDeVezesJogadas; i++)
            {
                printf("Jogatina %d: %d\n\n", vetorJogatinas[i], reversoVetorScore[i]);
            }

            printf("[1] - Voltar \n");
            printf("\n");
            scanf(" %d", &optionsScores);
            fflush(stdin);
            system("cls");
            // Voltar ao menu anterior
            switch (optionsScores)
            {
            case 1:
                break;

            default:
                break;
            }

            break;

        default:
            printf("[%d] Nao e uma opcao valida digite outra\n\n", optionsPrincipal);
            break;
        }
    }
}
