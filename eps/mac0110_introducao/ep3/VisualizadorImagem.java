import java.awt.*;
import java.awt.image.BufferedImage;
import javax.swing.*;

public class VisualizadorImagem extends JFrame {

    private Image imagem;

    VisualizadorImagem() {
        super("VisualizadorImagem");
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
    }

    // Abre janela e desenha imagem
    void mostraImagem(Imagem imagem) {
        this.mostraImagem(imagem, "VisualizadorImagem");
    }

    // Abre janela com nome titulo e desenha imagem
    void mostraImagem(Imagem imagem, String titulo) {
        int altura = imagem.altura();
        int largura = imagem.largura();

        BufferedImage bufimagem = new BufferedImage(largura, altura,
                BufferedImage.TYPE_INT_RGB);

        // Confecciona array de pixels para desenho da imagem
        int indice = 0;
        int[] pixels = new int[largura * altura];
        for (int i = 0; i < altura; i++) {
            for (int j = 0; j < largura; j++) {
                int r = imagem.pixels[i][j] << 16;
                int g = imagem.pixels[i][j] << 8;
                int b = imagem.pixels[i][j];
                pixels[indice++] = 0xff000000 + r + g + b;
            }
        }

        // Copia pixels
        bufimagem.setRGB(0, 0, largura, altura, pixels, 0, largura);
        this.imagem = bufimagem;

        // Coloca título na janela
        setTitle(titulo);

        // Ajusta tamanho da janela de acordo com o tamanho da imagem
        setSize(imagem.largura(), imagem.altura());

        // Se a janela não está visível, mostre-a
        setVisible(true);

        // Redesenha janela se necessario
        repaint();
    }

    public void paint(Graphics graphics) {
        graphics.drawImage(imagem, 0, 0, null);
    }
}
