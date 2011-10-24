/*******************************************************************/
/**   MAC 110 - Introducao a Computacao                           **/
/**   IME-USP - Primeiro Semestre de 2009                         **/
/**   Turma 45 - Marcelo Finger                                   **/
/**                                                               **/
/**   Segundo Exercicio-Programa                                  **/
/**   Arquivo: Helper.java                                        **/
/**                                                               **/
/**   Diogo Haruki Kykuta                  ???????                **/
/**   Henrique Gemignani Passos Lima       ???????                **/
/**                                                               **/
/**   24/05/2009                                                  **/
/*******************************************************************/
class Helper {

    double precision = 1.0e-8;

    /*
     * Define a precisaMatho como = a p.
     */
    void setPrecision(double p) {
        precision = p;
    }

    /*
     * Se a < 0, devolve -a
     * Se a >= 0, devolve a
     */
    double abs(double a) {
        if (a < 0) {
            return -a;
        }
        return a;
    }

    /*
     * True se a e b sao iguais dentre a precisao definida, false caso contrario.
     */
    boolean equal(double a, double b) {
        return (abs(a - b) <= precision);
    }

    /*
     * Dados um double base e um int pow:
     * Se pow < 0, devolve um double igual a 1 sobre base elevado a -pow.
     * Se pow == 0, devolve 1.
     * Se pow > 0, devolve um double igual a base elevado a pow.
     */
    double powDouble(double base, int pow) {
        if (pow < 0) {
            return 1 / powDouble(base, -pow);
        }
        int result = 1;
        for (int i = 1; i <= pow; i++) {
            result *= base;
        }
        return result;
    }

    /*
     * Dados um int base e um int pow:
     * Se pow < 0, devolve -1
     * Se pow == 0, devolve 1.
     * Se pow > 0, devolve um int igual a base elevado a pow.
     */
    int pow(int base, int pow) {
        if (pow < 0) {
            return -1;
        }
        int result = 1;
        for (int i = 1; i <= pow; i++) {
            result *= base;
        }
        return result;
    }
    /*
     * Dados dois double a e b:
     * Se a >= b, devolve a
     * Se b > a, devolve b
     */

    double max(double a, double b) {
        if (a > b) {
            return a;
        }
        return b;
    }

    /*
     * Dados um double cur e um double old, devolve (1 - cur / old) * 100
     */
    double relativeGain(double cur, double old) {
        return (1 - cur / old) * 100;
    }

    /*
     * Dado um vetor values, devolve o desvio padrao dos valores deste vetor.
     */
    double standardDeviation(long[] values, Functions f) { //desvio padrão
        long average = 0, quadratic = 0;
        for (int i = 0; i < values.length; i++) {
            average += values[i];
            quadratic += (values[i] * values[i]);
        }
        average /= values.length;
        quadratic /= values.length;
        return Math.sqrt((double) (quadratic - average * average));
    }

    /*
     * Dado um vetor ordenado array, devolve a mediana destes valores.
     */
    long median(long[] array) {
        if (array.length % 2 == 0) {
            return (array[array.length / 2 - 1] + array[array.length / 2]) / 2;
        } else {
            return array[array.length / 2];
        }
    }

    /*
     * Ordena um vetor array usando o algoritimo de bolhas.
     */
    void bubbleSort(long[] array) {
        int fim = array.length;
        long aux;
        boolean cont = true;
        for (int i = 0; i < fim - 1 && cont; i++) {
            cont = false;
            for (int j = 0; j < fim - 1 - i; j++) {
                if (array[j] > array[j + 1]) {
                    aux = array[j + 1];
                    array[j + 1] = array[j];
                    array[j] = aux;
                    cont = true;
                }
            }
        }
    }

    /*
     * Dado um vetor values, calcula a media dos valores deste.
     */
    double average(long[] values) {
        double average = 0;
        for (int i = 0; i < values.length; i++) {
            average += values[i];
        }
        return average / values.length;
    }

    /*
     * Trunca um double d para ter um numero de casas igual a precisao.
     */
    String truncateDouble(double d) {
        long p = (long) (d / precision);
        return Double.toString((double) p * precision);
    }

    /*
     * Imprime cada valor de vetor row com exatos 15 caracteres, truncando se necessario.
     */
    void printTableRow(String[] row) {
        for (int i = 0; i < row.length; i++) {
            if (row[i].length() < 15) {
                System.out.print(row[i]);
                for (int j = row[i].length(); j <= 15; j++) {
                    System.out.print(" ");
                }
            } else {
                System.out.print(row[i].substring(0, 15) + " ");
            }
        }
        System.out.println();
    }
}
