/*******************************************************************/
/** MAC 110 - Introducao a Computacao                             **/
/** IME-USP - Primeiro Semestre de 2009                           **/
/** BCC - prof.Marcelo Finger                                     **/
/**                                                               **/
/** Terceiro Exercicio-Programa                                   **/
/** Arquivo: SuavizacaoDeImagens.java                             **/
/**                                                               **/
/** Gabriel Torres Gomes Pato      nUSP ???????                   **/
/** Henrique Gemignani Passos Lima nUSP ???????                   **/
/**                                                               **/
/** 23/06/2009                                                    **/
/*******************************************************************/
public class Auxiliar {
    public static double[][] gauss;
    public static final int limiar = 11;
    public static void sort( int[] vetor ) { //ordena ate a metade, usando bolha
        if( vetor.length <= 1 )
            return;
        int aux;
        boolean b = true;
        for( int i = vetor.length - 2; (i >= vetor.length / 2 - 1 && b); i-- ) {
            b = false;
            for( int j = 0; j < i; j++ ) {
                if( vetor[j] > vetor[j+1] ) {
                    aux = vetor[j+1];
                    vetor[j+1] = vetor[j];
                    vetor[j] = aux;
                    b = true;
                }
            }
        }
    }
    public static int media( int[] vetor ) {
        int result = 0;
        for( int i = 0; i < vetor.length; i++ )
            result += vetor[i];
        return Math.min( Math.max( 0, (int)( (double) result / vetor.length + 0.5) ), 255 );
    }
    public static int mediana( int[] vetor ) {
        sort( vetor );
        if( vetor.length % 2 == 0 )
            return ( vetor[ vetor.length / 2 - 1 ] + vetor[ vetor.length / 2 ] ) / 2;
        return vetor[ vetor.length / 2 ];
    }
    public static int[][] recortaMatriz( int[][] matriz, int x, int y, int tamanho ) {
        int ESQUERDA = x - tamanho/2, TOPO = y - tamanho/2, DIREITA = x + tamanho/2, BAIXO = y + tamanho/2;
        if( ESQUERDA < 0 ) ESQUERDA = 0;
        if( TOPO < 0 ) TOPO = 0;
        if ( DIREITA > matriz[0].length - 1 ) DIREITA = matriz[0].length - 1;
        if ( BAIXO > matriz.length - 1 ) BAIXO = matriz.length - 1;
        
        int[][] mini = new int[ (BAIXO - TOPO) ][ (DIREITA - ESQUERDA) ];
        for( int j = TOPO; j < BAIXO; j++ ) {
            for( int i = ESQUERDA; i < DIREITA; i++ ) {
                mini[ j - TOPO ][ i - ESQUERDA ] = matriz[j][i];
            }
        }
        return mini;
    }
    public static int[] matrizParaVetor( int[][] matriz ) {
        int[] vetor = new int[ matriz.length * matriz[0].length ];
        for( int j = 0; j < matriz.length; j++ ) {
            for( int i = 0; i < matriz[0].length; i++ ) {
                vetor[ i*matriz.length + j] = matriz[j][i];
            }
        }
        return vetor;
    }
    
    public static int matrizGauss( int[][] matriz, int x, int y, int tamanho, double sigma ) {
        int ESQUERDA = x - tamanho/2, TOPO = y - tamanho/2, DIREITA = x + tamanho/2, BAIXO = y + tamanho/2;
        if( ESQUERDA < 0 ) ESQUERDA = 0;
        if( TOPO < 0 ) TOPO = 0;
        if ( DIREITA > matriz[0].length - 1 ) DIREITA = matriz[0].length - 1;
        if ( BAIXO > matriz.length - 1 ) BAIXO = matriz.length - 1;
        
        double d = 0, t;
        for( int j = TOPO; j < BAIXO; j++ ) {
            for( int i = ESQUERDA; i < DIREITA; i++ ) {
                d += funcaoGaussiana( sigma, x - i, y - j, tamanho) * matriz[j][i];
            }
        }
        return Math.min( Math.max( 0, (int)( (double) d + 0.5) ), 255 );
    }
    public static double funcaoGaussiana( double sigma, int x, int y, int tamanho ) {
        if( gauss[y + tamanho/2][x + tamanho/2] == 0 )
            gauss[y + tamanho/2][x + tamanho/2] = Math.exp( - (x*x + y*y) / ( 2 * sigma * sigma ) ) / ( 2 * Math.PI * sigma * sigma );
        return gauss[y + tamanho/2][x + tamanho/2];
    }

    public static int[][] diferencaHorizontal( int[][] a ) {
        int[][] d = new int[a.length][a[0].length];
        for( int i = 0; i < a.length; i++ ) {
            for( int j = 0; j < a[0].length - 1; j++ ) {
                d[i][j] = Math.abs( a[i][j+1] - a[i][j] );
            }
        }
        return d;
    }
    public static int[][] diferencaVertical( int[][] a ) {
        int[][] d = new int[a.length][a[0].length];
        for( int i = 0; i < a.length - 1; i++ ) {
            for( int j = 0; j < a[0].length; j++ ) {
                d[i][j] = Math.abs( a[i+1][j] - a[i][j] );
            }
        }
        return d;
    }
}












