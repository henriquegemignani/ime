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
class Imagem {

    int[][] pixels;
    // Inicializa matriz de pixels da classe

    Imagem(int[][] matriz) {
        pixels = matriz;
    }

    // Devolve largura em pixels da imagem
    int largura() {
        if (pixels != null) {
            return pixels[0].length;
        } else {
            return 0;
        }
    }

    // Devolve altura em pixels da imagem
    int altura() {
        if (pixels != null) {
            return pixels.length;
        } else {
            return 0;
        }
    }

    // Suaviza imagem com filtro m�dio
    void filtroMedio(int tamanho) {
        int altura = altura(), largura = largura();
        int[][] novo = new int[altura][largura];
        for (int y = 0; y < altura; y++) {
            for (int x = 0; x < largura; x++) {
                //novo[y][x] = Auxiliar.media( Auxiliar.matrizParaVetor( pixels, x, y, tamanho ) );
                novo[y][x] = Auxiliar.media(
                        Auxiliar.matrizParaVetor(
                        Auxiliar.recortaMatriz(pixels, x, y, tamanho)));
            }
        }
        pixels = novo;
    }

    // Suaviza imagem com filtro mediano
    void filtroMediano(int tamanho) {
        int altura = altura(), largura = largura();
        int[][] novo = new int[altura][largura];
        for (int y = 0; y < altura; y++) {
            for (int x = 0; x < largura; x++) {
                novo[y][x] = Auxiliar.mediana(
                        Auxiliar.matrizParaVetor(
                        Auxiliar.recortaMatriz(pixels, x, y, tamanho)));
            }
        }
        pixels = novo;
    }

    // Suaviza imagem com filtro gaussiano
    void filtroGaussiano(double sigma, int tamanho) {
        int altura = altura(), largura = largura();
        int[][] novo = new int[altura][largura];
        Auxiliar.gauss = new double[tamanho][tamanho];
        for (int y = 0; y < altura; y++) {
            for (int x = 0; x < largura; x++) {
                novo[y][x] = Auxiliar.matrizGauss(pixels, x, y, tamanho, sigma);
            }
        }
        pixels = novo;
    }

    void bordaHorizontal() {
        pixels = Auxiliar.diferencaHorizontal(Auxiliar.diferencaHorizontal(pixels));
        int altura = altura(), largura = largura();
        for (int y = 0; y < altura; y++) {
            for (int x = 0; x < largura; x++) {
                if (pixels[y][x] > Auxiliar.limiar) {
                    pixels[y][x] = 0;
                } else {
                    pixels[y][x] = 255;
                }
            }
        }
    }

    void bordaVertical() {
        pixels = Auxiliar.diferencaVertical(Auxiliar.diferencaVertical(pixels));
        int altura = altura(), largura = largura();
        for (int y = 0; y < altura; y++) {
            for (int x = 0; x < largura; x++) {
                if (pixels[y][x] > Auxiliar.limiar) {
                    pixels[y][x] = 0;
                } else {
                    pixels[y][x] = 255;
                }
            }
        }
    }

    void bordas() {
        int altura = altura(), largura = largura();
        int[][] h = new int[altura][largura], v = new int[altura][largura];
        v = Auxiliar.diferencaVertical(Auxiliar.diferencaVertical(pixels));
        h = Auxiliar.diferencaHorizontal(Auxiliar.diferencaHorizontal(pixels));
        for (int y = 0; y < altura; y++) {
            for (int x = 0; x < largura; x++) {
                if (v[y][x] > Auxiliar.limiar || h[y][x] > Auxiliar.limiar) {
                    pixels[y][x] = 0;
                } else {
                    pixels[y][x] = 255;
                }
            }
        }
    }
}
