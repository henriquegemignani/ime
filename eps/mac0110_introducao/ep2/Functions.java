/*******************************************************************/
/**   MAC 110 - Introducao a Computacao                           **/
/**   IME-USP - Primeiro Semestre de 2009                         **/
/**   Turma 45 - Marcelo Finger                                   **/
/**                                                               **/
/**   Segundo Exercicio-Programa                                  **/
/**   Arquivo: Functions.java                                     **/
/**                                                               **/
/**   Diogo Haruki Kykuta                  ???????                **/
/**   Henrique Gemignani Passos Lima       ???????                **/
/**                                                               **/
/**   24/05/2009                                                  **/
/*******************************************************************/

/* Nas funções onde é necessário haver manipulação do resultado, 
devido à limitações nas séries de taylor, há também uma manipulação 
na precisão usada para que o resultado final tenha o número 
de casas decimais exigidas. */
class Functions {

    Helper h;
    /*
     * Método construtor. Exige um objeto da classe Helper para evitar instanciar
     * mais objetos.
     */

    Functions(Helper help) {
        h = help;
    }

    /*
     * Devolve o objeto Helper atribuido a este objeto.
     */
    Helper getHelper() {
        return h;
    }

    /*
     * Devolve o seno de x, usando float.
     */
    float floatSin(float x) {
        float term = x, result = term;
        int i = 1;
        while (h.abs(term) > h.precision) {
            result += term *= -x * x / (2 * i * (2 * i++ + 1));
        }
        return result;
    }
    /*
     * Devolve o seno de x, usando double.
     */

    double sin(double x) {
        double term = x, result = term;
        int i = 1;
        while (h.abs(term) > h.precision) {
            result += term *= -x * x / (2 * i * (2 * i++ + 1));
        }
        return result;
    }

    /*
     * Devolve o cosseno de x, usando double.
     */
    double cos(double x) {
        double term = 1, result = term;
        int i = 1;
        while (term * term > h.precision * h.precision) {
            result += term *= -x * x / (2 * i * (2 * i++ - 1));
        }
        return result;
    }

    /*
     * Se x < 0, devolve Double.NaN
     * Se x >= 0, devolve a raiz quadrada de x.
     */
    double sqrt(double x) {
        if (x < 0) {
            return Double.NaN;
        }
        if (x == 0) {
            return 0;
        }
        double result;
        int cont;
        if (x > 1.8) {
            for (cont = 0; x >= 1.8; cont++) {
                x /= 4;
            }
            result = sqrtAux(x, cont) * h.pow(2, cont);
        } else if (x < 0.5) {
            for (cont = 0; x < 0.5; cont++) {
                x *= 4;
            }
            result = sqrtAux(x, cont) / h.pow(2, cont);
        } else {
            result = sqrtAux(x);
        }
        return result;
    }

    /*
     * Chama sqrtAux com cont = 0
     */
    double sqrtAux(double xPlusOne) {
        return sqrtAux(xPlusOne, 0);
    }

    /*
     * Se xPlusOne < 0 ou xPlusOne > 2, devolve Double.NaN
     * Se 0 < xPlusOne < 2, devolve a raiz quadrada de x, modificando a precisao 
     * por 2 elevado a cont.
     */
    double sqrtAux(double xPlusOne, int cont) {
        if (xPlusOne < 0) {
            return Double.NaN;
        }
        if (xPlusOne > 2) {
            return Double.NaN;
        }
        double x = xPlusOne - 1, term = 1, result = term;
        int i = 1;
        while (h.abs(term) > h.precision / (h.pow(2, cont))) {
            result += term *=
                    -1 * x * (2 * i - 1) * (2 * i) * (1 - 2 * (i - 1)) /
                    ((1 - 2 * i) * i * i++ * 4);
        }
        return result;
    }
    /*
     * Se x < 0, devolve Double.NaN
     * Se x == 0, devolve Double.NEGATIVE_INFINITY
     * Se x > 0, devolve ln x.
     */

    double ln(double x) {
        if (x < 0) {
            return Double.NaN;
        }
        if (x == 0) {
            return Double.NEGATIVE_INFINITY;
        }
        double result = 0;
        int cont;
        for (cont = 0; x > 1.5; cont++) {
            result += 0.6931471805599453; //ln 2
            x = x / 2;
        }
        result += lnaux(x, cont);
        return result;
    }
    /*
     * Chama lnaux com cont = 0
     */

    double lnaux(double xPlusOne) {
        return lnaux(xPlusOne, 0);
    }
    /*
     * Se xPlusOne < 0 ou xPlusOne > 2, devolve Double.NaN
     * Se xPlusOne == 0, devolve Double.NEGATIVE_INFINITY
     * Se 0 < xPlusOne < 2, devolve ln x, modificando a precisao por 2 elevado a cont.
     */

    double lnaux(double xPlusOne, int cont) {
        if (xPlusOne < 0) {
            return Double.NaN;
        }
        if (xPlusOne == 0) {
            return Double.NEGATIVE_INFINITY;
        }
        if (xPlusOne > 2) {
            return Double.NaN;
        }

        double x = xPlusOne - 1, term = x, result = term;
        int i = 1;
        while (h.abs(term) > h.precision / (h.powDouble(2, cont))) {
            result += term *= -x * i / ++i;
        }
        return result;
    }
    /*
     * Devolve E elevado a x.
     */

    double eX(double x) {
        double term = 1, result = term;
        int i = 1;
        while (term * term > h.precision * h.precision) {
            result += term *= x / i++;
        }
        return result;
    }
}
