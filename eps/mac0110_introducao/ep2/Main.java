/*******************************************************************/
/**   MAC 110 - Introducao à Computacao                           **/
/**   IME-USP - Primeiro Semestre de 2009                         **/
/**   Turma 45 - Marcelo Finger                                   **/
/**                                                               **/
/**   Segundo Exercicio-Programa                                  **/
/**   Arquivo: Main.java                                          **/
/**                                                               **/
/**   Diogo Haruki Kykuta                  ???????                **/
/**   Henrique Gemignani Passos Lima       ???????                **/
/**                                                               **/
/**   24/05/2009                                                  **/
/*******************************************************************/
/*
 * Inicializa um AutoTest
 */
class Main { 
    public static void main(String[] args) {
        Helper h = new Helper();
        if( args.length == 1 )
            h.setPrecision( Double.parseDouble( args[0] ) );
        AutoTest t = new AutoTest(h);
        t.fullTest();
    }
}
