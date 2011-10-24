import java.io.*;
import java.io.ByteArrayInputStream;
import java.util.*;

class LeituraEscritaImagem {
    // Lê valor inteiro de arquivo
    // Não muito eficiente, porém funcional para pgms
    static private int leProximoInt(FileInputStream fis) {
        try {
            int valor = 0;
            String token = "";
            while (valor <= ' ') {
                valor = fis.read();
            }
            while (valor > ' ') {
                token = token + (char) valor;
                valor = (char) fis.read();
            }
            Scanner sc1 = new Scanner(token);
            return sc1.nextInt();
        } catch (IOException e) {
            e.printStackTrace();
            return -1;
        }
    }

    // Lê uma imagem no format pgm
    public static Imagem leImagem(String nome) {
        try {
            FileInputStream pgm = new FileInputStream(nome);

            // Abre arquivo com o nome especificado para leitura
            byte[] magic_array = new byte[2];
            magic_array[0] = (byte) pgm.read();
            magic_array[1] = (byte) pgm.read();

            // Lê número mágico que identifica formato do arquivo.
            // Um arquivo pgm possui a string "P5" como número mágico
            String magic = new String(magic_array);
            if (!magic.equals("P5")) {
                System.err.println(nome + " não está no formato pgm.");
                return null;
            }

            // Lê largura da imagem em pixels 
            int largura = leProximoInt(pgm);

            // Lê altura da imagem em pixels
            int altura = leProximoInt(pgm);

            // Lê valor máximo para os pixels deste arquivo
            int valmax = leProximoInt(pgm);

            // Caso intensidade máxima seja maior que 255,
            // pixels são compostos de 2 bytes e não
            // daremos suporte a esta variação.
            if (valmax > 255) {
                System.err.println(nome + " está em um formato pgm não suportado.");
                return null;
            }

            // Lê matriz de pixels
            int[][] pixels = new int[altura][largura];
            for (int i = 0; i < altura; i++) {
                for (int j = 0; j < largura; j++) {
                    pixels[i][j] = pgm.read();
                }
            }

            // Fecha arquivo
            pgm.close();

            // Devolve um objeto imagem
            return new Imagem(pixels);

        } catch (FileNotFoundException e) {
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }

    public static void escreveImagem(String nome, Imagem imagem) {
        if (imagem.pixels == null) {
            System.err.println("Imagem não contém pixels para escrever.");
            return;
        }

        try {

            // Abre arquivo para grava��o
            FileOutputStream pgm = new FileOutputStream(nome);

            // Escreve n�mero m�gico
            pgm.write('P');
            pgm.write('5');
            pgm.write(10);

            // Escreve largura e altura da imagem    
            int largura = imagem.pixels[0].length;
            int altura = imagem.pixels.length;

            String tamanho = Integer.toString(largura) + " " + Integer.toString(altura);
            byte[] array = tamanho.getBytes();
            for (int i = 0; i < array.length; i++) {
                pgm.write(array[i]);
            }
            pgm.write(10);

            // Escreve valor maximo para pixels
            pgm.write('2');
            pgm.write('5');
            pgm.write('5');
            pgm.write(10);

            // Escreve pixels
            for (int i = 0; i < altura; i++) {
                for (int j = 0; j < largura; j++) {
                    pgm.write(imagem.pixels[i][j]);
                }
            }

            // Fecha arquivo
            pgm.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
