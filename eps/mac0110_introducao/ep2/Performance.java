/*******************************************************************/
/**   MAC 110 - Introducao a Computacao                           **/
/**   IME-USP - Primeiro Semestre de 2009                         **/
/**   Turma 45 - Marcelo Finger                                   **/
/**                                                               **/
/**   Segundo Exercicio-Programa                                  **/
/**   Arquivo: Performance.java                                   **/
/**                                                               **/
/**   Diogo Haruki Kykuta                  ???????                **/
/**   Henrique Gemignani Passos Lima       ???????                **/
/**                                                               **/
/**   24/05/2009                                                  **/
/*******************************************************************/
class Performance {

    Helper h;
    Functions f;
    /*
     * Método construtor. Exige um objeto da classe Functions para evitar instanciar
     * mais objetos.
     */

    Performance(Functions func) {
        f = func;
        h = f.getHelper();
    }

    /*
     * Imprime na tela, usando Helper.printTableRow com nome = func, o ganho
     * relativo da média e mediana do vetor values em relacao ao vetor original.
     */
    void printGainAgainst(long[] values, long[] original, String func) {
        h.bubbleSort(values);
        h.bubbleSort(original);
        double average = h.relativeGain(h.average(values), h.average(original)),
                median = h.relativeGain(h.median(values), h.median(original));
        String[] t = {func, h.truncateDouble(average) + "%",
            "Desnecessario",
            h.truncateDouble(median) + "%"
        };
        h.printTableRow(t);
    }
    /*
     * Imprime na tela, usando Helper.printTableRow com nome = func, a media,
     * desvio padrao e mediana do vetor values.
     */

    void printResults(long[] values, String func) {
        h.bubbleSort(values);
        double average = h.average(values),
                deviation = h.standardDeviation(values, f),
                median = h.median(values);
        String[] t = {func, h.truncateDouble(average / 1000000),
            h.truncateDouble(deviation / 1000000),
            h.truncateDouble(median / 1000000)
        };
        h.printTableRow(t);
    }
    /*
     * Devolve um vetor desordenado com o tempo de execucao de 100 testes
     * da funcao Functions.sin.
     */

    long[] testSin() {
        long[] results = new long[100];
        long time;
        double d;
        for (int i = 0; i < results.length; i++) {
            d = (i + 1) * 0.1;
            time = System.nanoTime();
            d = f.sin(d);
            results[i] = System.nanoTime() - time;
        }
        return results;
    }
    /*
     * Devolve um vetor desordenado com o tempo de execucao de 100 testes
     * da funcao Functions.floatSin.
     */
    long[] testFloatSin() {
        long[] results = new long[100];
        long time;
        float d;
        for (int i = 0; i < results.length; i++) {
            d = (float) ((i + 1) * 0.1);
            time = System.nanoTime();
            d = f.floatSin(d);
            results[i] = System.nanoTime() - time;
        }
        return results;
    }
    /*
     * Devolve um vetor desordenado com o tempo de execucao de 100 testes
     * da funcao Functions.cos.
     */

    long[] testCos() {
        long[] results = new long[100];
        long time;
        double d;
        for (int i = 0; i < results.length; i++) {
            d = (i + 1) * 0.1;
            time = System.nanoTime();
            d = f.cos(d);
            results[i] = System.nanoTime() - time;
        }
        return results;
    }
    /*
     * Devolve um vetor desordenado com o tempo de execucao de 100 testes
     * da funcao Functions.ln.
     */

    long[] testLn() {
        long[] results = new long[100];
        long time;
        double d;
        for (int i = 0; i < results.length; i++) {
            d = (i + 1) * 0.1;
            time = System.nanoTime();
            d = f.ln(d);
            results[i] = System.nanoTime() - time;
        }
        return results;
    }
    /*
     * Devolve um vetor desordenado com o tempo de execucao de 100 testes
     * da funcao Functions.eX.
     */

    long[] testEX() {
        long[] results = new long[100];
        long time;
        double d;
        for (int i = 0; i < results.length; i++) {
            d = (i + 1) * 0.1;
            time = System.nanoTime();
            d = f.eX(d);
            results[i] = System.nanoTime() - time;
        }
        return results;
    }
    /*
     * Devolve um vetor desordenado com o tempo de execucao de 100 testes
     * da funcao Functions.sqrt.
     */

    long[] testSqrt() {
        long[] results = new long[100];
        long time;
        double d;
        for (int i = 0; i < results.length; i++) {
            d = (i + 1) * 0.1;
            time = System.nanoTime();
            d = f.sqrt(d);
            results[i] = System.nanoTime() - time;
        }
        return results;
    }
    /*
     * Testa a performance dos metodos sin, cos, ln, eX, sqrt alem de comparar
     * floatsin com sin. Imprime todos os resultados na tela.
     */

    void init() {
        System.out.println();
        String[] t = {"Funcao", "Media", "Desvio Padrao", "Mediana"};
        h.printTableRow(t);
        long[] doublesin = testSin();
        printResults(doublesin, "sin");
        printResults(testCos(), "cos");
        printResults(testLn(), "ln");
        printResults(testEX(), "eX");
        printResults(testSqrt(), "sqrt");
        System.out.println();
        long[] floatsin = testFloatSin();
        printGainAgainst(floatsin, doublesin, "floatsin");
    }
}
