/*******************************************************************/
/**   MAC 110 - Introducao a Computacao                           **/
/**   IME-USP - Primeiro Semestre de 2009                         **/
/**   Turma 45 - Marcelo Finger                                   **/
/**                                                               **/
/**   Segundo Exercicio-Programa                                  **/
/**   Arquivo: AutoTest.java                                      **/
/**                                                               **/
/**   Diogo Haruki Kykuta                  ???????                **/
/**   Henrique Gemignani Passos Lima       ???????                **/
/**                                                               **/
/**   24/05/2009                                                  **/
/*******************************************************************/
class AutoTest {

    Functions f;
    Helper h;
    /*
     * Método construtor. Exige um objeto da classe Helper para evitar instanciar
     * mais objetos.
     */

    AutoTest(Helper help) {
        h = help;
        f = new Functions(h);
    }
    /* Define a precisao do objeto Helper atribuido a este objeto. */

    void setPrecision(double p) {
        h.setPrecision(p);
    }
    /*
     * De i = 0 até i = toTest.length - 1, verifica se toTest[i] é igual a compareTo[i],
     * dentro da precisao. Imprime na tela uma mensagem de erro relacinado a funcName.
     * Devolve true se ocorreu algum erro, false se nao.
     */

    boolean test(double[] toTest, double[] compareTo, String funcName) {
        boolean error = false;
        for (int i = 0; i < toTest.length; i++) {
            if (h.equal(toTest[i], compareTo[i]) == false) {
                System.out.println("<ERRO> " + funcName + ": " + toTest[i] + " != " + compareTo[i]);
                error = true;
            }
        }
        return error;
    }
    /*
     * Para cada valor de toTest, calcula Functions.sin( toTest ).
     * Entao, roda AutoTest.test( toTest, compareTo, "sin" ) e se esse retorna false,
     * imprime avisando do sucesso dos testes.
     */

    void testSin(double[] toTest, double[] compareTo) {
        for (int i = 0; i < toTest.length; i++) {
            toTest[i] = f.sin(toTest[i]);
        }

        if (test(toTest, compareTo, "sin") == false) {
            System.out.println("Todos os testes de sin foram bem sucedidos.");
        }
    }
    /*
     * Para cada valor de toTest, calcula Functions.cos( toTest ).
     * Entao, roda AutoTest.test( toTest, compareTo, "cos" ) e se esse retorna false,
     * imprime avisando do sucesso dos testes.
     */

    void testCos(double[] toTest, double[] compareTo) {
        for (int i = 0; i < toTest.length; i++) {
            toTest[i] = f.cos(toTest[i]);
        }

        if (test(toTest, compareTo, "cos") == false) {
            System.out.println("Todos os testes de cos foram bem sucedidos.");
        }
    }
    /*
     * Para cada valor de toTest, calcula Functions.sqrt( toTest ).
     * Entao, roda AutoTest.test( toTest, compareTo, "sqrt" ) e se esse retorna false,
     * imprime avisando do sucesso dos testes.
     */

    void testSqrt(double[] toTest, double[] compareTo) {
        for (int i = 0; i < toTest.length; i++) {
            toTest[i] = f.sqrt(toTest[i]);
        }

        if (test(toTest, compareTo, "sqrt") == false) {
            System.out.println("Todos os testes de sqrt foram bem sucedidos.");
        }
    }
    /*
     * Para cada valor de toTest, calcula Functions.ln( toTest ).
     * Entao, roda AutoTest.test( toTest, compareTo, "ln" ) e se esse retorna false,
     * imprime avisando do sucesso dos testes.
     */

    void testLn(double[] toTest, double[] compareTo) {
        for (int i = 0; i < toTest.length; i++) {
            toTest[i] = f.ln(toTest[i]);
        }

        if (test(toTest, compareTo, "ln") == false) {
            System.out.println("Todos os testes de ln foram bem sucedidos.");
        }
    }
    /*
     * Para cada valor de toTest, calcula Functions.eX( toTest ).
     * Entao, roda AutoTest.test( toTest, compareTo, "eX" ) e se esse retorna false,
     * imprime avisando do sucesso dos testes.
     */

    void testEx(double[] toTest, double[] compareTo) {
        for (int i = 0; i < toTest.length; i++) {
            toTest[i] = f.eX(toTest[i]);
        }

        if (test(toTest, compareTo, "eX") == false) {
            System.out.println("Todos os testes de eX foram bem sucedidos.");
        }
    }
    /*
     * Utilizando-se de valores e propriedades conhecidas, verifica se as 
     * seguintes funcoes de Functions estao corretas: ln, eX, sin, cos, sqrt.
     * No fim, chama Performance.init().
     */

    void fullTest() {
        final double E = 2.7182818282861687,  PI = 3.14159265358979323846;
        // parte 1: valores "conhecidos"
        double[] testsLn = {1, E}, valueLn = {0, 1};
        testLn(testsLn, valueLn);

        double[] testsEX = {0, 1}, valueEX = {1, E};
        testEx(testsEX, valueEX);

        double[] testsSin = {0, PI / 6, PI / 2, PI},
                valueSin = {0, 1.0 / 2, 1, 0};
        testSin(testsSin, valueSin);

        double[] testsCos = {0, PI / 3, PI / 2, PI},
                valueCos = {1, 1.0 / 2, 0, -1};
        testCos(testsCos, valueCos);

        double[] testsSqrt = {0, 1, 4, 9, 0.01, 0.0016},
                valueSqrt = {0, 1, 2, 3, 0.1, 0.04};
        testSqrt(testsSqrt, valueSqrt);

        // parte 2: funções conhecidas
        int errors = 6; //n
        if (testTrig(PI / 2)) {
            errors--;
        }
        if (testTrig(PI / 4)) {
            errors--;
        }
        if (testTrig(PI / 6)) {
            errors--;
        }
        if (testTrig(PI / 2)) {
            errors--;
        }
        if (testTrig(PI / 4)) {
            errors--;
        }
        if (testTrig(PI)) {
            errors--;
        }
        if (errors == 0) {
            System.out.println(
                    "Todos os testes da relacao trigonométrica foram bem sucedidos.");
        }

        errors = 10;
        for (int i = 0; i < 10; i++) {
            if (testEpowLnX((double) (E * (i + 1)))) {
                errors--;
            }
        }
        if (errors == 0) {
            System.out.println(
                    "Todos os testes de e elevado a lnx foram bem sucedidos.");
        }

        errors = 10;
        for (int i = 0; i < 10; i++) {
            if (testLnEpowX((double) (E * (i + 1)))) {
                errors--;
            }
        }
        if (errors == 0) {
            System.out.println(
                    "Todos os testes de ln de e elevado a x foram bem sucedidos.");
        }

        errors = 10;
        for (int i = 0; i < 10; i++) {
            if (testSqrtPow2((double) (0.10 + i * 0.15))) {
                errors--;
            }
        }
        if (errors == 0) {
            System.out.println(
                    "Todos os testes de sqrt(x)^2 foram bem sucedidos.");
        }

        errors = 10;
        for (int i = 0; i < 10; i++) {
            if (testPowSqrt2((double) (0.10 + i * 0.15))) {
                errors--;
            }
        }
        if (errors == 0) {
            System.out.println(
                    "Todos os testes de sqrt(x^2) foram bem sucedidos.");
        }


        Performance p = new Performance(f);
        p.init();

    }
    /*
     * Utilizando-se de um x passado, verifica se a relacao trigonometrica I
     * é valida para Functions.sin e Functions.cos.
     */

    boolean testTrig(double x) {
        double a = f.sin(x), b = f.cos(x), result = a * a + b * b;
        if (!h.equal(result, 1.0)) {
            System.out.println("<ERRO> Para x = " + x + ", sen(x)^2 + cos(x)^2 = " + result);
            return false;
        }
        return true;
    }
    /*
     * Verifica, usando um x passado, se Functions.eX( Functions.ln( x )  ) é igual a x, 
     * dentro da precisao.
     */

    boolean testEpowLnX(double x) {
        double a = f.ln(x), b = f.eX(a);
        if (!h.equal(b, x)) {
            System.out.println("<ERRO> Para x = " + x + ", e elevado a ln x = " + b);
            return false;
        }
        return true;
    }
    /*
     * Verifica, usando um x passado, se Functions.ln( Functions.eX( x )  ) é igual a x, 
     * dentro da precisao.
     */

    boolean testLnEpowX(double x) {
        double a = f.eX(x), b = f.ln(a);
        if (!h.equal(b, x)) {
            System.out.println("<ERRO> Para x = " + x + ", ln de e elevado a x = " + b);
            return false;
        }
        return true;
    }

    /* 
     * Sobre testSqrtPow2:
     * Para c² manter-se com a precisão pedida pelo usuário, é necessário que aumentemos
     * a precisao durante a iteração da raiz quadrada, para que o primeiro algarismo
     * errado não interfira no último algarismo pedido corretamente pelo usuário. 
     */
    /*
     * Verifica, usando um x passado, se Functions.sqrt( x )² é igual a x, 
     * dentro da precisao.
     */
    boolean testSqrtPow2(double x) {
        setPrecision(h.precision / 10);
        double c = f.sqrt(x), b = c * c;
        setPrecision(h.precision * 10);
        if (!h.equal(b, x)) {
            System.out.println("<ERRO> Para x = " + x + ", sqrt(x)^2 = " + b);
            return false;
        }
        return true;
    }
    /*
     * Verifica, usando um x passado, se Functions.sqrt( x² ) é igual a x, 
     * dentro da precisao.
     */

    boolean testPowSqrt2(double x) {
        setPrecision(h.precision);
        double a = x * x, b = f.sqrt(a);
        setPrecision(h.precision);
        if (!h.equal(b, x)) {
            System.out.println("<ERRO> Para x = " + x + ", sqrt(x^2) = " + b);
            return false;
        }
        return true;
    }
}
