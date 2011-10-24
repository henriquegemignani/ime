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
import java.util.*;
public class Main {
    public static MenuAtual estado = MenuAtual.semImagem;
    public static void imprimeMenu() {
        System.out.println("MENU");
        System.out.println("============");
        switch (estado) {
            case semImagem:
                System.out.println("1) Carregar Imagem");
                break;
            case comImagem:
                System.out.println("1) Carregar Nova Imagem");
                System.out.println("2) Suavizar Imagem");
                System.out.println("3) Bordas");
                System.out.println("4) Gravar Imagem");
                break;
            case filtro:
                System.out.println("1) Suavizar Imagem Com Filtro Médio");
                System.out.println("2) Suavizar Imagem Com Filtro Mediano");
                System.out.println("3) Suavizar Imagem Com Filtro Gaussiano");
                System.out.println("4) Menu Anterior");
                break;
            case borda:
                System.out.println("1) Bordas Verticais");
                System.out.println("2) Bordas Horizontais");
                System.out.println("3) Bordas Horizontais e Verticais");
                System.out.println("4) Menu Anterior");
                break;
            default:
                estado = MenuAtual.semImagem;
            // deu merda
        }
        System.out.println("0) Sair");
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Imagem minhaImagem = null;
        int input;
        String nomeFile = new String();
        VisualizadorImagem vis = new VisualizadorImagem();
        while (true) {
            imprimeMenu();
            input = sc.nextInt();
            if (input == 0) {
                vis.dispose();
                return;
            }
            switch (estado) {
                case semImagem:
                     {
                        if (input == 1) {
                            System.out.println("Digite o nome do arquivo sem a extensão:");
                            nomeFile = sc.next() + ".pgm";
                            minhaImagem = LeituraEscritaImagem.leImagem(nomeFile);
                            if (minhaImagem == null) {
                                System.out.println("Arquivo não existente ou problemas na leitura");
                            } else {
                                vis.mostraImagem(minhaImagem, nomeFile);
                                estado = MenuAtual.comImagem;
                            }
                        }
                    }// SemImg
                    break;
                case comImagem:
                     {
                        if (input == 1) {
                            System.out.println("Digite o nome do arquivo sem a extensão:");
                            nomeFile = sc.next() + ".pgm";
                            minhaImagem = LeituraEscritaImagem.leImagem(nomeFile);
                            if (minhaImagem == null) {
                                System.out.println("Arquivo n~ao existente ou problemas na leitura");
                            }
                            vis.mostraImagem(minhaImagem, nomeFile);
                            estado = MenuAtual.comImagem;
                        } else if (input == 2) {
                            estado = MenuAtual.filtro;
                        } else if (input == 3) {
                            estado = MenuAtual.borda;
                        } else if (input == 4) {
                            System.out.println("Digite o nome da nova imagem:");
                            String salvarComo = sc.next() + ".pgm";
                            LeituraEscritaImagem.escreveImagem(salvarComo, minhaImagem);
                            estado = MenuAtual.comImagem;
                        }
                    }// comImg
                    break;
                case filtro:
                     {
                        if (input == 1) {
                            System.out.println("Digite o tamanho desejado:");
                            int tamanho = sc.nextInt();
                            minhaImagem.filtroMedio(tamanho);
                            vis.mostraImagem(minhaImagem, nomeFile);
                            estado = MenuAtual.comImagem;
                        } else if (input == 2) {
                            System.out.println("Digite o tamanho desejado:");
                            int tamanho = sc.nextInt();
                            minhaImagem.filtroMediano(tamanho);
                            vis.mostraImagem(minhaImagem, nomeFile);
                            estado = MenuAtual.comImagem;
                        } else if (input == 3) {
                            System.out.println("Digite o tamanho desejado:");
                            int tamanho = sc.nextInt();
                            System.out.println("Digite o valor de Sigma desejado:");
                            double sig = sc.nextDouble();
                            minhaImagem.filtroGaussiano(sig, tamanho);
                            vis.mostraImagem(minhaImagem, nomeFile);
                            estado = MenuAtual.comImagem;
                        } else if (input == 4) {
                            estado = MenuAtual.comImagem;
                        }
                    }// Filtro
                    break;
                case borda:
                     {
                        if (input == 1) {
                            minhaImagem.bordaHorizontal();
                            vis.mostraImagem(minhaImagem, nomeFile);
                            estado = MenuAtual.comImagem;
                        } else if (input == 2) {
                            minhaImagem.bordaVertical();
                            vis.mostraImagem(minhaImagem, nomeFile);
                            estado = MenuAtual.comImagem;
                        } else if (input == 3) {
                            minhaImagem.bordas();
                            vis.mostraImagem(minhaImagem, nomeFile);
                            estado = MenuAtual.comImagem;
                        } else if (input == 4) {
                            estado = MenuAtual.comImagem;
                        }
                    }// Borda
                    break;
                default:
                    estado = MenuAtual.semImagem;
                // deu merda
            }
        }
    }
}
