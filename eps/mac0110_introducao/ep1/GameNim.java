/*******************************************************************/
/** MAC 110 - Introdução à Computação                             **/
/** IME-USP - Primeiro Semestre de 2009                           **/
/** <turma> - Marcelo Finger                                      **/
/**                                                               **/
/** Primeiro Exercício-Programa -- jogo do NIM                    **/
/** Arquivo: GameNim.java                                         **/                                             
/** Classes: GameNim, GameNimTourney                              **/
/**                                                               **/
/** Métodos para Uso:                                             **/
/**    startGame( int num, int max ) - Inicia um novo jogo.       **/
/**    turnPlayer( int num )         - Indica a sua rodada.       **/
/**    startTourney()                - Inicia novo torneio.       **/
/**    endTourney()                  - Termina um torneio.        **/
/**                                                               **/
/** Henrique Gemignani Passos Lima    nº USP: ???????             **/
/**                                                               **/
/** 12/04/2009                                                    **/
/*******************************************************************/


class GameNim {
    boolean playerTurn;
    int curPiece, maxMove;    
    /*
     * Inicia uma nova partida com num peças e valor máximo de uma jogada igual a max.
     */
    void startGame( int num, int max ) {
        if( num * max <= 0 ) {
            System.out.println( "Erro: Valores devem ser obrigatóriamente positivos e não-nulos." );
            return;
        }
        curPiece = num;
        maxMove = max;
        System.out.println( "Iniciando novo jogo. Movimento máximo: " + maxMove );
        printStatus();
        
        if( curPiece % ( maxMove + 1 ) == 0 ) {
            playerTurn = true;
            System.out.println( "Você começa." );
        } else {
            playerTurn = false;
            System.out.println( "Computador começa." );
            turnComputer();
        }
    }
    /*
     * Termina um jogo. 
     * Se playerTurn == true, considera-se o jogador como vitorioso, caso contrário o computador.
     */
    void endGame( ) {
        curPiece = 0;
        maxMove = 0;
        System.out.print( "Fim de jogo. ");
        if( playerTurn ) {
            System.out.println( "Parabéns! Você venceu! Impressionante!");
        } else {
            System.out.println( "Venci! Foi um bom jogo, tente novamente!");
        }
    }
    /*
     * Retorna true se existe um jogo em atividade, false se não existe.
     * Caso printError == true, exibe uma mensagem de erro somente se não existe um jogo em atividade.
     */
    boolean checkGameExists() {
        if( curPiece * maxMove <= 0 ) {
            System.out.println( "Erro: Inicie um jogo antes." );
            return false;
        } else {
            return true;
        }
    }
    /*
     * Exibe na tela quantas peças restam no jogo atual.
     */
    void printStatus() {
        System.out.println( curPiece + " peças sobrando." );
    }
    
    /*
     * Controla os turnos.
     * Decrementa a quantidade de peças sobrando, verifica se é fim de jogo e exibe na tela a quantidade de peças restantes e removidas.
     * playerTurn == true para turno do jogador, false para turno do computador.
     * Se for turno do jogador, inicializa o turno do computador
     */
    void runTurn( int num ) {
        if( num <= 0 || num > maxMove ) {
            System.out.println( "Erro Interno: playTurn foi chamado com um número inválido de movimentos." );
            return;
        }
        curPiece -= num;
        if( playerTurn )
            System.out.print( "Você" );
        else
            System.out.print( "Computador" );
        System.out.println( " remove " + num + " peças." );
        if( curPiece <= 0 ) {
            endGame();
            return;
        }
        printStatus();
        playerTurn = !playerTurn;
        if( !playerTurn )
            turnComputer();
    }
    
    /*
     * Cálcula quantas peças o computador vai retirar na ação dele.
     * runTurn controla todas as ações do turno em si.
     */
    void turnComputer() {
        if( !checkGameExists() ) return;
        if( playerTurn ) {
            System.out.println( "Erro: Computador não pode jogar na vez do jogador." );
            return;
        }
        
        int nextAct;
        if( curPiece <= maxMove )
            nextAct = curPiece; // Computador ganhou, pegar todas as peças restantes.
        else {
            nextAct = curPiece - (curPiece / (maxMove + 1)) * (maxMove + 1);
            // lógica para sempre restar múltiplo de maxMove + 1 peças
            if( nextAct == 0 )
              nextAct = maxMove;
        }
        
        if( nextAct > maxMove )
            nextAct = maxMove;
        else if( nextAct <= 0 )
            nextAct = 1;
        runTurn( nextAct );
    }
    
    /*
     * Verifica se o num é uma ação válida.
     * runTurn controla todas as ações do turno em si.
     */
    void turnPlayer( int num ) {
        if( !checkGameExists() ) return;
        if( num <= 0 || num > maxMove ) {
            System.out.println( "Erro: Jogadas devem ser entre 1 e " + maxMove );
            return;
        }
        runTurn( num );
    }
    
}

class GameNimTourney {
    boolean playerTurn;
    int curPiece, maxMove;
    boolean tourOn = false;
    int tourNum, tourPlay, tourCom;
    
    /*
     * Inicia um novo torneio.
     */
    void startTourney() {
        if( checkGameExists( false ) ) {
            System.out.println( "Erro: Termine a partida atual antes de iniciar um torneio." );
            return;
        } else if( !tourOn ){
            tourNum = 0;
            tourPlay = 0;
            tourCom = 0;
            tourOn = true;
            System.out.println( "Iniciado um torneio! Agora é para valer!" );
        } else {
            System.out.println( "Erro: Já existe um torneio em andamento." );
        }
    }
    
    /*
     * Inicia uma nova partida com num peças e valor máximo de uma jogada igual a max.
     */
    void startGame( int num, int max ) {
        if( num * max <= 0 ) {
            System.out.println( "Erro: Valores devem ser obrigatóriamente positivos e não-nulos." );
            return;
        }
        curPiece = num;
        maxMove = max;
        System.out.println( "Iniciando novo jogo. Movimento máximo: " + maxMove );
        printStatus();
        if( curPiece % ( maxMove + 1 ) == 0 ) {
            System.out.println( "Você começa." );
        } else {
            System.out.println( "Computador começa." );
            turnComputer();
        }
        
    }
    
    /*
     * Termina um jogo. 
     * Se playerTurn == true, considera-se o jogador como vitorioso, caso contrário o computador.
     */
    void endGame( ) {
        curPiece = 0;
        maxMove = 0;
        System.out.print( "Fim de jogo. ");
        if( tourOn ) tourNum++;
        if( playerTurn ) {
            if( tourOn ) tourPlay++;
            System.out.println( "Parabéns! Você venceu! Impressionante!");
        } else {
            if( tourOn ) tourCom++;
            System.out.println( "Venci! Foi um bom jogo, tente novamente!");
        }
    }
    
    /*
     * Retorna true se existe um jogo em atividade, false se não existe.
     * Caso printError == true, exibe uma mensagem de erro somente se não existe um jogo em atividade.
     */
    boolean checkGameExists( boolean printError ) {
        if( curPiece * maxMove <= 0 ) {
            if( printError ) System.out.println( "Erro: Inicie um jogo antes." );
            return false;
        } else {
            return true;
        }
    }
    
    /*
     * Exibe na tela quantas peças restam no jogo atual.
     */
    void printStatus() {
        System.out.println( curPiece + " peças sobrando." );
    }
    
    /*
     * Controla os turnos.
     * Decrementa a quantidade de peças sobrando, verifica se é fim de jogo e exibe na tela a quantidade de peças restantes e removidas.
     * playerTurn == true para turno do jogador, false para turno do computador.
     * Se for turno do jogador, inicializa o turno do computador
     */
    void runTurn( int num ) {
        if( num <= 0 || num > maxMove ) {
            System.out.println( "Erro Interno: playTurn foi chamado com um número inválido de movimentos." );
            return;
        }
        curPiece -= num;
        if( playerTurn )
            System.out.print( "Você" );
        else
            System.out.print( "Computador" );
        System.out.println( " remove " + num + " peças." );
        if( curPiece <= 0 ) {
            endGame( );
            return;
        }
        printStatus();
        playerTurn = !playerTurn;
        if( !playerTurn )
            turnComputer();
    }
    
    /*
     * Cálcula quantas peças o computador vai retirar na ação dele.
     * runTurn controla todas as ações do turno em si.
     */
    void turnComputer() {
        if( !checkGameExists( true ) ) return;
        if( playerTurn ) {
            System.out.println( "Erro: Computador não pode jogar na vez do jogador." );
            return;
        }
        
        int nextAct;
        if( curPiece <= maxMove )
            nextAct = curPiece; // Computador ganhou, pegar todas as peças restantes.
        else {
            nextAct = curPiece - (curPiece / (maxMove + 1)) * (maxMove + 1); 
            // lógica para sempre restar múltiplo de maxMove + 1 peças
            if( nextAct == 0 )
              nextAct = maxMove;
        }
        if( nextAct > maxMove )
            nextAct = maxMove;
        else if( nextAct <= 0 )
            nextAct = 1;
        runTurn( nextAct );
    }
    
    /*
     * Verifica se o num é uma ação válida.
     * runTurn controla todas as ações do turno em si.
     */
    void turnPlayer( int num ) {
        if( !checkGameExists( true ) ) return;
        if( num <= 0 || num > maxMove ) {
            System.out.println( "Erro: Jogadas devem ser entre 1 e " + maxMove );
            return;
        }
        runTurn( num );
    }
    
    /*
     * Imprime na tela o estado atual do torneio em andamento.
     */
    void printTourneyStatus() {
        if( !tourOn ) {
            System.out.println( "Erro: Não existe um torneio em andamento." );
            return;
        }
        System.out.println( "Status do torneio:\n" 
                + tourCom + " vitórias do computador\n"
                + tourPlay + " vitórias do jogador\n"
                + tourNum + " partidas totais" );
    }
    
    /*
     * Finaliza um torneio e exibe na tela o estado final e o vitorioso.
     */
    void endTourney() {
        if( !tourOn ) {
            System.out.println( "Erro: Não existe um torneio em andamento." );
            return;
        }
        if( tourNum == 0 ) {
            System.out.println( "Torneio cancelado por motivos técnicos." );
            return;
        }
        System.out.println( "Fim do torneio!" );
        printTourneyStatus();
        System.out.print( "\n" );
        if( tourPlay > tourCom ) {
            System.out.println( "Vitória do jogador! Meus parabéns!" );
        } else if( tourPlay == tourCom ) {
            System.out.println( "Um impressionante empate!" );
        } else {
            System.out.println( "Mais uma vitória do computador!" );
        }
        tourNum = 0;
        tourPlay = 0;
        tourCom = 0;
        tourOn = false;
    }
}
