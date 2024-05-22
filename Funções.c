// Posição inical do desenho da forca
void gotoxy(int x, int y)
{ // x é linha e y é coluna
    // Posiciona o curso em um lugar na tela
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x + 45, y});
}

// Função para desenhar forca a cada erro do usuario, recebe como paremetros os erros da sessão
void desenharForca(int erro)
{
    int col = 5, lin = 5;

    // desenha a forca
    gotoxy(lin, col);
    printf("______");
    gotoxy(lin, col + 1);
    printf("|");

    // A cada erro é desenhado na tela uma parte do copor do boneco de palitinho
    for (int i = 1; i <= 3; i++)
    {
        gotoxy(lin + 5, col + i);
        printf("|");
    }
    printf("\n");

    if (erro > 0)
    {
        gotoxy(lin, col + 2);
        printf("O");
        printf("\n");
    }
    if (erro > 1)
    {
        gotoxy(lin, col + 3);
        printf("|");
        printf("\n");
    }
    if (erro > 2)
    {
        gotoxy(lin + 1, col + 3);
        printf("\\");
        printf("\n");
    }
    if (erro > 3)
    {
        gotoxy(lin - 1, col + 3);
        printf("/");
        printf("\n");
    }
    if (erro > 4)
    {
        gotoxy(lin + 1, col + 4);
        printf("\\");
        printf("\n");
    }
    if (erro > 5)
    {
        gotoxy(lin - 1, col + 4);
        printf("/");
        printf("\n");
        gotoxy(lin + 5, col + 5);
        printf("MORTO!");
        printf("\n");
    }
}

// Quando o usuario escolhe sair do jogo essa função da seus scores finais
void calculoScoreFinal()
{
    // For para a soma de cada espaço do meu vetor de Score Parcial exemplo (100+234+123)
    for (int i = 0; i < numeroDeVezesJogadas; i++)
    {
        jogador.scoreFinal = jogador.scoreFinal + jogador.scoreParcial[i];
    }

    // Calculo do Score final que leva em consideração seu count de miss em todo o seu jogo (soma todos seus erros de suas sessões)
    // Soma de seus Scores Parcias - 2 vezes todos seus erros no jogo, tudo isso multiplicado por 10
    jogador.scoreFinal = ((jogador.scoreFinal) - (2 * countDeMissTotal)) * 10.0;

    if (jogador.scoreFinal < 0)
    {
        // Caso o jogador tiver uma pontuação ruim
        printf("Seu Score final foi menor que zero D:\nSeu Score final foi: %d\n",
               jogador.scoreFinal);
    }
    else
    {
        // Caso o jogador tiver uma pontuação Boa
        printf("\n");
        printf("[Jogador: %s]\nParabens pela pontuacao\n", jogador.nome);
        printf("Seu Score final foi: %d\n", jogador.scoreFinal);
        printf("\nObrigado por jogar!");
    }
}

// Função para cada final de sessão, perguntando se o usuario quer continuar ou não
void continuarOuNao()
{
    // Assergura que a cada nova sessão o valor escolhido na anterior seja re escolhido dando um inicio automatico forçado
    int continuar = 0;

    printf("\n");
    printf("Deseja jogar novamente?\n\n");
    printf("[1] - Voltar ao Menu\n[2] - Sair do Jogo\n");
    printf("\n");
    scanf(" %d", &continuar);
    fflush(stdin);
    printf("\n");
    system("cls");
    // system (cls) limpa o termianal!!!

    if (continuar == 2)
    {
        // acaba com o loop do jogo principal e da o Score ao usuario
        gameLoop = false;
        calculoScoreFinal();
    }
}

void logicaForca(char palavraEscolhida[], int categoria)
{
    // Apenas usado para mostrar com quantos erros voce pode perder
    tentativas = 6;
    int i = 0;
    int j = 0;
    // Miss na string (Usado para medir se a letra digitada não está na palavra)
    int countDeMiss = 0;

    // Tamanho da palavra escolhida
    int tamanhoDaString = strlen(palavraEscolhida);

    // Nova variavel para a String que ficara ocultada
    char stringDoUsuario[tamanhoDaString];

    // Letra digitada pelo usuario
    char letra = 'a';

    // Usado para ter o codigo ASCII da letra digitada pelo usuario
    int asciiLetra = 0;

    // Vetor para guardar valores que se relacionam com as letras do alfabeto (Usado no sistema de impedimento de erros continuos pela mesma letra)
    int alfabeto[27];

    // String para controle de acertos na String ocultada e não permitindo que o jogador pontue infinitamente usando a mesma letra
    char strControleAcertos[100];

    // Usado para contar os erros de letras digitadas
    /*
    Exmplo: O usario digitou A e náo esta na palavra, isto ira adicionar ao vetor alfabeto no indice 0 que é o indice do A
    que ela foi digitada uma vez
    */

    // Usado para tomar conta de qual indice a letra do usuario digitada pertence
    int indexAlfabeto;

    // string para printar a categoria selecionada na sessão
    char strCategoria[20];

    // Fazemos uma copia da string original para a nossa string nova
    strcpy(stringDoUsuario, palavraEscolhida);

    // Esconde a string nova, se tiver travessao ou espaço ira mostrar
    for (i = 0; i < tamanhoDaString; i++)
    {
        if (palavraEscolhida[i] != '-')
        {
            stringDoUsuario[i] = '*';
        }
        if (palavraEscolhida[i] == ' ')
        {
            stringDoUsuario[i] = ' ';
        }
    }

    // Coloca todos os valores de letras do alfabeto digitados para zero
    for (int i = 0; i <= 27; i++)
    {
        alfabeto[i] = 0;
    }

    switch (categoria)
    {
    case 1:
        strcpy(strCategoria, "Cores");
        break;
    case 2:
        strcpy(strCategoria, "Frutas");
        break;
    case 3:
        strcpy(strCategoria, "Paises");
        break;
    case 4:
        strcpy(strCategoria, "Animais");
        break;
    case 5:
        strcpy(strCategoria, "Times da Serie A");
        break;
    case 6:
        strcpy(strCategoria, "Personagens de Naruto");
        break;
    case 7:
        strcpy(strCategoria, "Atos Musicais Gringos");
        break;
    case 8:
        strcpy(strCategoria, "Protagonistas de Anime");
        break;

    case 9:
        strcpy(strCategoria, "Desenhos animados");
        break;

    default:
        break;
    }

    // Comapra as duas strings, caso elas forem iguais o valor da variavel será 0, qualquer outro valor se elas forem diferentes
    int comparandoStrings = strcmp(palavraEscolhida, stringDoUsuario);

    printf("Se digitado mais de uma letra, apenas a primeira letra sera considerada\n\n");

    // Enquanto as strings forem diferentes faça as instruções
    while (comparandoStrings != 0)
    {
        // Cada iteração o valor de count de miss é resetado
        // O sistema de erros tem um loop que deixa essa variavel com o tamanho da palavra caso sua letra não estiver na palavra
        // Logo a cada passada essa variavel tem que ser resetada
        countDeMiss = 0;

        // Comparação dentro do loop para cada iteração
        int comparandoStrings = strcmp(palavraEscolhida, stringDoUsuario);

        // Checagem se o Jogo acabou por acertar a palavra
        if (comparandoStrings == 0)
        {
            printf("Voce acertou a palavra!\n\nA palavra era: %s\n", palavraEscolhida);
            desenharForca(countDeMissDaSessao);
            numeroDeVezesJogadas++;
            auxiliarNumeroDeJogadas = numeroDeVezesJogadas;

            // Deixa um vetor separado para mostrar quais jogatinas de forma
            // descrescente
            for (int i = 0; i <= numeroDeVezesJogadas; i++)
            {
                vetorJogatinas[i] = auxiliarNumeroDeJogadas;
                auxiliarNumeroDeJogadas--;
            }
            // Reseta o contador de erros da sessão para o eventual jogo seguinte
            countDeMissDaSessao = 0;
            continuarOuNao();
            break;
        }

        // Checagem se o Jogo acabou por esgotar o numero de tentativas
        if (tentativas <= 0)
        {
            printf("Voce perdeu por falta de tentivas! A palavra era: %s\n", palavraEscolhida);
            desenharForca(countDeMissDaSessao);
            numeroDeVezesJogadas++;
            auxiliarNumeroDeJogadas = numeroDeVezesJogadas;

            // Deixa um vetor separado para mostrar quais jogatinas de forma
            // descrescente
            for (int i = 0; i <= numeroDeVezesJogadas; i++)
            {
                vetorJogatinas[i] = auxiliarNumeroDeJogadas;
                auxiliarNumeroDeJogadas--;
            }
            // Reseta o contador de erros da sessão para o eventual jogo seguinte
            countDeMissDaSessao = 0;
            continuarOuNao();
            break;
        }

        // Logica Principal
        desenharForca(countDeMissDaSessao);
        printf("Categoria: %s\n\n", strCategoria);
        printf("Essa Palavra tem %d letras \n\n", tamanhoDaString);
        printf("Numero de tentativas: %d\n", tentativas);
        printf("Digite apenas uma letra\n\n");
        printf("%s\n\n", stringDoUsuario);
        // Tipo s permite que o caractere digitado seja considerado apenas a
        // primeira letra, pois o conteudo da suposta string ira ser armazenado em uma variavel tipo char
        // Nesse caso sera considerada apenas a primeira letra do que foi digitado

        scanf(" %s", &letra);
        fflush(stdin);
        printf("\n");
        system("cls");
        //  toupper Deixa a letra digitada em maiusculo
        letra = toupper(letra);

        // variavel int recebe varivael char, esse valor sera a equivalencia do valor char na tabela ASCII
        asciiLetra = letra;

        // Indice da string alfabeto determinado pelo ASCII da palavra menos 65 pois 65 é o codigo da letra A e subtraindo isso teremos os indices do alfabeto em nossa string
        // EX: A = 65 indice = 65-65 = 0, B = 66 indide = 66-65 = 1
        indexAlfabeto = asciiLetra - 65;

        // verfica se a letra digitada ja esta na palavra ate então não descoberta, senão, ele
        // atribuie ha uma string de letras ja digitadas
        for (i = 0; i < tamanhoDaString; i++)
        {
            if (letra == stringDoUsuario[i])
            {
                letra = toupper(letra);
                strControleAcertos[i] = letra;
            }
        }

        // Itera sobre a palavra e ve se a letra escolhida pelo usuario esta nela
        for (j = 0; j <= tamanhoDaString; j++)
        {
            // Se estiver a string oculta no indice j revelara a letra que foi corretamente adivinhada
            if (letra == palavraEscolhida[j])
            {
                stringDoUsuario[j] = palavraEscolhida[j];

                // Impede que as letras ja digitadas pontuem
                if (letra == strControleAcertos[j])
                {
                    printf("Letra %c ja foi escolhida escolhida!\n\n", letra);
                    printf("SCORE: %d\n", jogador.scoreParcial[numeroDeVezesJogadas]);
                    break;
                }
                else
                {
                    // Caso acerte
                    // Calculo do score parcial que leva em consideração os erros da sessão
                    // quanto mais erros menos se pontuara por letra acertada
                    printf("A letra %c esta na palavra :)\n\n", letra);
                    jogador.scoreParcial[numeroDeVezesJogadas] =
                        jogador.scoreParcial[numeroDeVezesJogadas] + 100 -
                        (2 * countDeMissDaSessao);
                    printf("SCORE: %d\n\n", jogador.scoreParcial[numeroDeVezesJogadas]);
                }
            }
        }

        // Usamos o vetor alfabeto para verificar se a letra não esta na palavra e se ela não estiver
        // Sera feito um incremento nos erros da palavra que no final tera o mesmo valor da string se a letra não estiver na palavra
        // a letra escolhida tera seu indice no vetor de letras adicionado +1 a a cada iteração
        for (int j = 0; j < tamanhoDaString; j++)
        {
            if (letra != palavraEscolhida[j])
            {

                alfabeto[indexAlfabeto] = ((alfabeto[indexAlfabeto] + 1));
            }
        }

        // Subtraimos a quantidade de somas por conta da iteração para nos resultar em um valor de o ou mais
        // que ira corresponder ao numero de vezes que a letra escolhida pelo usuario foi digitada
        alfabeto[indexAlfabeto] = alfabeto[indexAlfabeto] - (tamanhoDaString - 1);

        // De novo iteramos sobre a palavra e se a palavra tiver sido digitada pela primeira vez e não pertecer a palavra
        // o contador de miss de cada letra da string sera incrementado
        // Senão o numero de erros não incrementara e o usuario não perde tentativas
        for (int i = 0; i < tamanhoDaString; i++)
        {
            if (alfabeto[indexAlfabeto] == 1 && letra != palavraEscolhida[j])
            {
                countDeMiss++;
            }
            else
            {
                if (alfabeto[indexAlfabeto] > 1 && letra != palavraEscolhida[j])
                {
                    printf("Letra %c ja foi escolhida escolhida!\n\n", letra);
                    printf("SCORE: %d\n", jogador.scoreParcial[numeroDeVezesJogadas]);
                    break;
                }
            }
        }

        // Se houver uma letra digitada que não esta em nenhuma das letras da
        // palavra(Isso sendo determinado pelo countMiss), decrementamos as tentativa por 1
        if (countDeMiss == tamanhoDaString)
        {
            printf("A letra %c nao esta na palavra :(\n", letra);
            printf("SCORE: %d\n", jogador.scoreParcial[numeroDeVezesJogadas]);
            tentativas--;
            countDeMissTotal++;
            countDeMissDaSessao++;
            // Reassegurando que o valor dos erros das letras do usuario sera resetado a cada iteração
            // Impedindo que resulte em uma constante falha por falta de tentativas
            countDeMiss = 0;
        }
    }
}

// Função  Jogo tem como parametro os numeros associados as categorias
int jogo(int categoria)
{
    // srand serve para randomizar o valor randomico gerado por rand() a cada execução do programa
    srand(time(0));
    // Categoria cores
    if (categoria == 1)
    {
        printf("\n");
        printf("Categoria Selecionada: Cores!\n\n");
        // Lista de Strings, o primeiro colchetes eh o numero de elementos reservados para a lista e o segundo
        // é para o tamanho maximo de cada caractere em cada string individual
        char listaCores[14][9] = {
      "VERMELHO",
      "AZUL",
      "AMARELO",
      "MARROM",
      "VERDE",
      "LARANJA",
      "VIOLETA",
      "ROSA",
      "CINZA",
      "PRETO",
      "BRANCO",
      "DOURADO",
      "PRATA"};
      
      // Escolhe um numero aleatorio de 1 ao numero de elementos na lista
        // Sempre adiconando mais 1 por que o index começa do 0 :p
        int indiceAleatorio = rand() % 14;
        // Tamanho da string escolhida pelo indice aleatorio
        int tamanhoDaPalavra = strlen(listaCores[indiceAleatorio]);
        // Cria-se uma string com a palavra aleatoriamente escolhida
        char palavra[tamanhoDaPalavra];
        // Copiamos o conteudo Original para a recentemente criada string
        strcpy(palavra, listaCores[indiceAleatorio]);
        // Passamos a string recentemente criada como argumento para a fução logicaForca()
        logicaForca(palavra, 1);
    }

    // categoria frutas

    if (categoria == 2)
    {
        printf("\n");
        printf("Categoria Selecionada: Frutas!\n\n");
        char listaFrutas[87][16] = {
      "ABACATE",
      "ABACAXI",
      "ABIU",
      "ACKEE",
      "ACEROLA",
      "AMEIXA",
      "AMENDOA",
      "AMORA",
      "ARATICUM",
      "BABACO",
      "BACABA",
      "BACUPARI",
      "BACURI",
      "BANANA",
      "BIRIBA",
      "BURITI",
      "CACAU",
      "CAJA",
      "CAJU",
      "CAMBUCI",
      "CAQUI",
      "CARAMBOLA",
      "CEREJA",
      "CHERIMOIA",
      "CIDRA",
      "COCO",
      "DAMASCO",
      "FIGO",
      "FIGO-DA-INDIA",
      "FRAMBOESA",
      "FRUTA-DO-CONDE",
      "FRUTA-PAO",
      "GABIROBA",
      "GOIABA",
      "GRANADILLA",
      "GRAVATA",
      "GRAVIOLA",
      "GROSELHA",
      "GRUMIXAMA",
      "GUARANA",
      "INGA",
      "JABUTICABA",
      "JACA",
      "JAMBO",
      "JAMELAO",
      "JATOBA",
      "JENIPAPO",
      "JUA",
      "KINO",
      "KIWI",
      "LARANJA",
      "LICHIA",
      "LIMA",
      "LIMAO",
      "LONGAN",
      "MAMAO",
      "MANGA",
      "MANGABA",
      "MARACUJA",
      "MARMELO",
      "MELANCIA",
      "MELAO",
      "MEXERICA",
      "MIRTILO",
      "MORANGO",
      "MURICI",
      "NECTARINA",
      "PERA",
      "PESSEGO",
      "PITANGA",
      "PITAYA",
      "PITOMBA",
      "POMELO",
      "PUPUNHA",
      "RAMBUTAO",
      "ROMA",
      "SAPOTI",
      "SAPUCAIA",
      "SERIGUELA",
      "TAMARA",
      "TAMARINDO",
      "TORANJA",
      "TOMATE",
      "TUCUMA",
      "UMBU",
      "UVA"};
        int indiceAleatorio = rand() % 88;
        int tamanhoDaPalavra = strlen(listaFrutas[indiceAleatorio]);
        char palavra[tamanhoDaPalavra];
        strcpy(palavra, listaFrutas[indiceAleatorio]);
        logicaForca(palavra, 2);
    }
    if (categoria == 3)
    {
        printf("\n");
        printf("Categoria Selecionada: Paises!\n\n");
        char listaPaises[192][31] = {
                                    "AFRICA DO SUL",
                                     "EGITO",
                                     "MALI",
                                     "SERRA LEOA",
                                     "ANGOLA",
                                     "ERITREIA",
                                     "MARROCOS",
                                     "SEICHELES",
                                     "ARGELIA",
                                     "ETIOPIA",
                                     "MAURICIO",
                                     "TUNISIA",
                                     "BENIN",
                                     "GABAO",
                                     "MAURITANIA",
                                     "SOMALIA",
                                     "BOTSUANA",
                                     "GAMBIA",
                                     "SUAZILANDIA",
                                     "BURKINA FASSO",
                                     "GANA",
                                     "NAMIBIA",
                                     "SUDAO",
                                     "BURUNDI",
                                     "GUINE",
                                     "NIGER",
                                     "SUDAO DO SUL",
                                     "CABO VERDE",
                                     "GUINE-BISSAU",
                                     "NIGERIA",
                                     "UGANDA",
                                     "CAMAROES",
                                     "GUINE-EQUATORIAL",
                                     "QUENIA",
                                     "TANZANIA",
                                     "CHADE",
                                     "LESOTO",
                                     "REPUBLICA CENTRO-AFRICANA",
                                     "TOGO",
                                     "COMORES",
                                     "LIBERIA",
                                     "REPUBLICA DEMOCRATICA DO CONGO",
                                     "ZAMBIA",
                                     "CONGO",
                                     "LIBIA",
                                     "RUANDA",
                                     "ZIMBABUE",
                                     "COSTA DO MARFIM",
                                     "MADAGASCAR",
                                     "SAO TOME E PRINCIPE",
                                     "ANTIGUA E BARBUDA",
                                     "COLOMBIA",
                                     "GUIANA",
                                     "REPUBLICA DOMINICANA",
                                     "ARGENTINA",
                                     "COSTA RICA",
                                     "HAITI",
                                     "SANTA LUCIA",
                                     "BAHAMAS",
                                     "CUBA",
                                     "HONDURAS",
                                     "SAO CRISTOVAO E NEVIS",
                                     "BARBADOS",
                                     "DOMINICA",
                                     "JAMAICA",
                                     "SAO VICENTE E GRANADINAS",
                                     "BELIZE",
                                     "EL SALVADOR",
                                     "MEXICO",
                                     "SURINAME",
                                     "BOLIVIA",
                                     "EQUADOR",
                                     "NICARAGUA",
                                     "TRINIDAD E TOBAGO",
                                     "BRASIL",
                                     "ESTADOS UNIDOS",
                                     "PANAMA",
                                     "URUGUAI",
                                     "CANADA",
                                     "GRANADA",
                                     "PARAGUAI",
                                     "VENEZUELA",
                                     "CHILE",
                                     "GUATEMALA",
                                     "PERU",
                                     "AFEGANISTAO",
                                     "COREIA DO NORTE",
                                     "JORDANIA",
                                     "QUIRGUISTAO",
                                     "ARABIA SAUDITA",
                                     "COREIA DO SUL",
                                     "KUWAIT",
                                     "SIRIA",
                                     "BANGLADESH",
                                     "EMIRADOS ARABES UNIDOS",
                                     "LAOS",
                                     "SRI LANKA",
                                     "BAREIN",
                                     "FILIPINAS",
                                     "LIBANO",
                                     "TADJIQUISTAO",
                                     "BRUNEI",
                                     "IEMEN",
                                     "MALASIA",
                                     "TAILANDIA",
                                     "BUTAO",
                                     "INDIA",
                                     "MALDIVAS",
                                     "TIMOR-LESTE",
                                     "CAMBOJA",
                                     "INDONESIA",
                                     "MYANMAR",
                                     "TURQUIA",
                                     "CATAR",
                                     "IRA",
                                     "MONGOLIA",
                                     "TURCOMENISTAO",
                                     "CAZAQUISTAO",
                                     "IRAQUE",
                                     "NEPAL",
                                     "UZBEQUISTAO",
                                     "CHINA",
                                     "ISRAEL",
                                     "OMA",
                                     "VIETNA",
                                     "CINGAPURA",
                                     "JAPAO",
                                     "PAQUISTAO",
                                     "QUIRGUISTAO",
                                     "ALBANIA",
                                     "DINAMARCA",
                                     "ITALIA",
                                     "POLONIA",
                                     "ALEMANHA",
                                     "ESLOVAQUIA",
                                     "LETANIA",
                                     "PORTUGAL",
                                     "ANDORRA",
                                     "ESLOVENIA",
                                     "LIECHTENSTEIN",
                                     "REINO UNIDO",
                                     "ARMENIA",
                                     "ESPANHA",
                                     "LITUANIA",
                                     "REPUBLICA TCHECA",
                                     "AUSTRIA",
                                     "ESTONIA",
                                     "LUXEMBURGO",
                                     "ROMENIA",
                                     "AZERBAIJAO",
                                     "FINLANDIA",
                                     "MACEDONIA",
                                     "RUSSIA",
                                     "BELARUS",
                                     "FRANCA",
                                     "MALTA",
                                     "SAN MARINO",
                                     "BELGICA",
                                     "GEORGIA",
                                     "MOLDAVIA",
                                     "SERVIA",
                                     "BOSNIA-HERZEGOVINA",
                                     "GRECIA",
                                     "MONACO",
                                     "SUECIA",
                                     "BULGARIA",
                                     "HUNGRIA",
                                     "MONTENEGRO",
                                     "CHIPRE",
                                     "IRLANDA",
                                     "NORUEGA",
                                     "UCRANIA",
                                     "CROACIA",
                                     "ISLANDIA",
                                     "PAISES BAIXOS",
                                     "AUSTRALIA",
                                     "KIRIBATI",
                                     "PALAU",
                                     "TUVALU",
                                     "FIJI",
                                     "MICRONESIA",
                                     "PAPUA NOVA GUINE",
                                     "VANUATU",
                                     "ILHAS MARSHALL",
                                     "NAURU",
                                     "SAMOA",
                                     "ILHAS SALOMAO",
                                     "NOVA ZELANDIA",
                                     "TONGA",
                                     "DJIBUTI",
                                     "MALAWI",
                                     "SENEGAL"};

        int indiceAleatorio = rand() % 193;
        int tamanhoDaPalavra = strlen(listaPaises[indiceAleatorio]);
        char palavra[tamanhoDaPalavra];
        strcpy(palavra, listaPaises[indiceAleatorio]);
        logicaForca(palavra, 3);
    }

    if (categoria == 4)
    {
        printf("\n");
        printf("Categoria Selecionada: Animais!\n\n");

        char listaAnimais[45][16] = {
      "ABELHA",
      "ANDORINHA",
      "BABUINO",
      "BALEIA",
      "CACHORRO",
      "CAMELO",
      "CAMALEAO",
      "DRAGAO-DE-KOMODO",
      "DROMEDARIO",
      "EMA",
      "ELEFANTE",
      "FOCA",
      "FLAMINGO",
      "GOLFINHO",
      "GATO",
      "GUAXINIM",
      "HIPOPOTAMO",
      "HIENA",
      "IGUANA",
      "IMPALA",
      "JAGUAR",
      "JACARE",
      "JABUTI"
      "KIWI",
      "LEAO",
      "LAGARTO",
      "MACACO",
      "MICO",
      "NAJA",
      "OVELHA",
      "ORANGOTANGO",
      "ORNITORRINCO",
      "PAPAGAIO",
      "PATO",
      "RAPOSA",
      "RATO",
      "SAPO",
      "TARTARUGA",
      "TAMANDUA",
      "URSO",
      "URUBU",
      "VEADO",
      "VACA",
      "ZEBRA"};
        int indiceAleatorio = rand() % 45;
        int tamanhoDaPalavra = strlen(listaAnimais[indiceAleatorio]);
        char palavra[tamanhoDaPalavra];
        strcpy(palavra, listaAnimais[indiceAleatorio]);
        logicaForca(palavra, 4);
    }

    if (categoria == 5)
    {
        printf("\n");
        printf("Categoria Selecionada: Times da serie A!\n\n");

        char listatimes[21][14] = {
      "AMERICA-MG",
      "ATHLETICO-PR", "ATLETICO-MG",
      "BAHIA",
      "BOTAFOGO",
      "CORINTHIANS",
      "CORITIBA",
      "CRUZEIRO",
      "CUIABA",
      "FLAMENGO",
      "FLUMINENSE",
      "FORTALEZA",
      "GOIAS",
      "GREMIO",
      "INTERNACIONAL",
      "PALMEIRAS",
      "BRAGANTINO",
      "SANTOS",
      "SAO PAULO",
      "VASCO DA GAMA"
    };
        int indiceAleatorio = rand() % 21;
        int tamanhoDaPalavra = strlen(listatimes[indiceAleatorio]);
        char palavra[tamanhoDaPalavra];
        strcpy(palavra, listatimes[indiceAleatorio]);
        logicaForca(palavra, 5);
    }

    if (categoria == 6)
    {
        printf("\n");
        printf("Categoria Selecionada: Personagens de Naruto\n\n");

        char listanaruto[74][14] = {"NARUTO",
      "SASUKE",
      "KAKASHI",
      "SAKURA",
      "SAI",
      "INO",
      "CHOJI",
      "SHIKAMARU",
      "ASUMA",
      "GUY",
      "LEE",
      "NEJI",
      "TENTEN",
      "HINATA",
      "SHINO",
      "KIBA",
      "KURENAI",
      "MADARA",
      "OBITO",
      "ZETSU",
      "ITACHI",
      "KISAME",
      "KAKUZU",
      "HIDAN",
      "DEIDARA",
      "SASORI",
      "GAARA",
      "TEMARI",
      "KANKURO",
      "OROCHIMARU",
      "KABUTO",
      "YAMATO",
      "TSUNADE",
      "JIRAYA",
      "TOBIRAMA",
      "HASHIRAMA",
      "HIRUZEN",
      "DANZOU",
      "SHISUI",
      "KONOMARU",
      "KURAMA",
      "BORUTO",
      "SARADA",
      "MITSUKI",
      "KAWAKI",
      "AKAMARU",
      "KARIN",
      "SUIGETSU",
      "JUUGO",
      "KIMIMARO",
      "TAYUYA",
      "KIDOMARU",
      "SAKON",
      "UKON",
      "KIDOMARU",
      "PAIN",
      "NAGATO",
      "NAGATO",
      "IRUKA",
      "SHIZUNE",
      "RIN",
      "MINATO",
      "KUSHINA",
      "HAKU",
      "ZABUZA",
      "HAMURA",
      "KAGUYA",
      "HAGOROMO",
      "INDRA",
      "ASHURA",
      "SHUKAKU",
      "TOBI",
      "IRUKA"};
        int indiceAleatorio = rand() % 74;
        int tamanhoDaPalavra = strlen(listanaruto[indiceAleatorio]);
        char palavra[tamanhoDaPalavra];
        strcpy(palavra, listanaruto[indiceAleatorio]);
        logicaForca(palavra, 6);
    }

    if (categoria == 7)
    {
        printf("\n");
        printf("Categoria Selecionada: Atos Musicais Gringos\n\n");

        char listamusica[72][22] = {"KESHA",
      "ED SHERRAN",
      "BRUNO MARS",
      "SHAWN MENDES",
      "CAMILA CABELLO",
      "NORMANI",
      "CHLOE E HALLE",
      "AVRIL LAVIGNE",
      "CARDI B",
      "CARLY RAE JEPSEN",
      "DOJA CAT",
      "MEGAN THEE STALLION",
      "LANA DEL REY",
      "ZAYN",
      "HARRY STYLES",
      "TYLER THE CREATOR",
      "ROSALIA",
      "KALI UCHIS",
      "HALSEY",
      "BEBE REXHA",
      "SZA",
      "SNOOP DOG",
      "SIA",
      "SHAKIRA",
      "DUA LIPA",
      "MADONNA",
      "SAM SMITH",
      "SABRINA CARPENTER",
      "BLACKPINK",
      "BTS",
      "RINA SAWAYAMA",
      "RITA ORA",
      "POST MALONE",
      "JENNIFER LOPEZ",
      "BEYONCE",
      "BRITNEY SPEARS",
      "PHOEBE BRIDGERS",
      "PHARREL",
      "PARAMORE",
      "EVANESCENCE",
      "PINK",
      "MALUMA",
      "KHALID",
      "LIZZO",
      "LADY GAGA",
      "KENDRICK LAMAR",
      "J BALVIN",
      "COLDPLAY",
      "IMAGINE DRAGONS",
      "FRANK OCEAN",
      "ELTON JOHN",
      "TAYLOR SWIFT",
      "ARIANA GRANDE",
      "KATY PERRY",
      "ICE SPICE",
      "NICKI MINAJ",
      "BEYONCE",
      "RIHANNA",
      "THE WEEKND",
      "JUSTIN BIEBER",
      "SELENA GOMEZ",
      "JAY-Z",
      "DEMI LOVATO",
      "MILEY CYRUS",
      "OLIVIA RODRIGO",
      "BRITNEY SPEARS",
      "LIL NAS X",
      "DRAKE",
      "KANYE WEST",
      "MELANIE MARTINEZ",
      "LORDE"
    };
        int indiceAleatorio = rand() % 72;
        int tamanhoDaPalavra = strlen(listamusica[indiceAleatorio]);
        char palavra[tamanhoDaPalavra];
        strcpy(palavra, listamusica[indiceAleatorio]);
        logicaForca(palavra, 7);
    }

    if (categoria == 8)
    {
        printf("\n");
        printf("Categoria Selecionada: Protagonistas de Anime\n\n");

      char listaprotagonistas[23][15] = {"EREN",
      "GOKU",
      "LUFFY",
      "NARUTO"
      "GON",
      "KANEKI"
      "EDWARD",
      "LIGHT",
      "DEKU",
      "YUSUKE",
      "SAITAMA",
      "KORO-SENSEI",
      "ICHIGO",
      "BORUTO",
      "TANJIRO",
      "YUJI ITADORI",
      "NATSU",
      "JOTARO",
      "HINATA",
      "YUKITERU",
      "SHINJI",
      "TORIKO" };
      
        int indiceAleatorio = rand() % 23;
        int tamanhoDaPalavra = strlen(listaprotagonistas[indiceAleatorio]);
        char palavra[tamanhoDaPalavra];
        strcpy(palavra, listaprotagonistas[indiceAleatorio]);
        logicaForca(palavra, 8);
    }

    if (categoria == 9)
    {
        printf("\n");
        printf("Categoria Selecionada: Desenhos animados!\n\n");

        char listadesenhos[55][42] = {
            "FLINTSTONES",
            "LULUZINHA",
            "GASPARZINHO",
            "POPEYE",
            "CAVERNA DO DRAGAO",
            "BOB ESPONJA",
            "TOM E JERRY",
            "TURMA DA MONICA",
            "SOUTH PARK",
            "SIMPSONS",
            "MORANGUINHO",
            "JIMMY NEUTRON",
            "GRAVITY FALLS",
            "URSINHO POOH",
            "DEXTER",
            "CORAGEM",
            "CHARLIE E LOLA",
            "BACKYARDIGANS"
            "PHINEAS E FERB",
            "JOVENS TITANS",
            "MAX STEEL",
            "BARBIE",
            "STEVEN UNIVERSO",
            "AVATAR",
            "HORA DE AVENTURA",
            "AS TRAPALHADAS DE FLAPJACK",
            "APENAS UM SHOW",
            "O INCRIVEL MUNDO DE GUMBALL",
            "IRMAO DO JOREL",
            "CHOWDER",
            "ILHA DOS DESAFIOS",
            "ESPETACULAR HOMEM ARANHA",
            "SCOOBY-DOO",
            "BAKUGAN",
            "SUPER CHOQUE",
            "KND",
            "JOHNNY TEST",
            "A MANSAO FOSTER PARA AMIGOS IMAGINARIOS",
            "AS TERRIVEIS AVENTURAS DE BILLY E MANDY",
            "LOOONEY TUNES",
            "PADRINHOS MAGICOS",
            "X-MEN EVOLUTION",
            "CLUBE DAS WINX",
            "CHAVES",
            "TRES ESPIAS DEMAIS",
            "SNOOPY",
            "AS MENINAS SUPER PODEROSAS",
            "JOHNNY BRAVO",
            "DIGIMON",
            "BEYBLADE",
            "PICA PAU",
            "DORA AVENTUREIRA"
            "GARFIELD",
            "MUTANTE REX",

        };
        int indiceAleatorio = rand() % 58;
        int tamanhoDaPalavra = strlen(listadesenhos[indiceAleatorio]);
        char palavra[tamanhoDaPalavra];
        strcpy(palavra, listadesenhos[indiceAleatorio]);
        logicaForca(palavra, 9);
    }
}
