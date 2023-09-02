/*
    ******************************************************************************************
    **  COMPUTAÇÃO GRÁFICA 2023 - 1                                                         **
    **  DOCENTE: ADAILTON JOSE ALVES DA CRUZ                                                **
    **  DISCENTE: FELIPE EMANUEL FERREIRA                           RGA: 20200712175441     **
    **  EMAIL: felipe.ferreira035@academico.ufgd.edu.br                                     **
    **                                                                                      **
    **  AVALIAÇÃO 2:                                                                        **
    **  O PROJETO CONSISTE NO USO DAS BIBLIOTECAS FREEGLUT E OPENGL PARA A MODELAGEM 3D     **
    **  DE UM ROBO HUMANOIDE, CAPAZ DE ANDAR E GESTICULAR UTILIZANDO EVENTOS DE TECLADO.    **
    **                                                                                      **
    **  O PROJETO É DIVIDIDO EM ARQUIVOS, A MAIN.CPP QUE CONTÉM AS CALLBACKS E A CRIAÇÃO    **
    **  O MODELOS.H CONTÉM AS FUNÇÕES DE MODELAGEM DO ROBO E MOVIMENTOS.H CONTÉM AS FUNÇÕES **
    **  RESPONSÁVEL POR MOVER CADA PARTE DO ROBO.                                           **
    ******************************************************************************************
*/
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "modelos.h"

void Resize(int w, int h)
{
	glMatrixMode(GL_PROJECTION); // SELECIONA MATRIZ DE PROJEÇÃO
	glLoadIdentity(); // CARREGA A MATRIZ IDENTIDADE (RESETA A MATRIZ)
	gluPerspective(45.0, (GLdouble) w/h, 1.0, 100.0); // TRANSFORMAÇÃO DA PERSPECTIVA (FOV, ASPECT, NEAR, FAR)

	/*
	MATRIZ DE PROJEÇÃO:

	| 1 / (aspect * tan(fov/2))   0                 0                              0                             |
    | 0                           1 / tan(fov/2)    0                              0                             |
    | 0                           0                -(Far + Near) / (Far - Near)  -(2 * Far * Near) / (Far - Near)|
    | 0                           0                -1                              0                             |


	       |1.81     0       0            0|
    PROJ = |0        0.41    0            0|
           |0        0      -1.02     -2.02|
           |0        0       -1           0|
	*/
	glMatrixMode(GL_MODELVIEW); // SELECIONA A MATRIZ MODELVIEW
	glViewport(0, 0, w, h); // DEFINE A VIEW PORT NA JANELA DE INTERAÇÃO COMO A TELA TODA
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //LIMPA A TELA
    glLoadIdentity(); //CARREGA IDENTIDADE DA MODELVIEW
    // Set camera position
    gluLookAt(  10.0, 20.0, 30 - base_mov[Z], //POSIÇÃO DA CAMERA (EYE)
                0.0, 0.0, base_mov[Z], //DIREÇÃO QUE ESTÁ OLHANDO (CENTER)
                0.0, 1.0, 0.0); //UP
    /*
    PARA O CASO INICIAL TEMOS QUE:

    Xe =  1/||up x Ze|| * (up x Ze) = [0.0, 1.0, 0.0]
    Ye =  Ze x Xe = [0.0, 0.5345, 0.0]
    Ze = 1/||eye - center|| * (eye - center) = [0.2672, 0.5345, 0.8017]

          |0        1       0       0|
    Rew = |0        0.53    0       0|
          |0.26     0.53    0.8     0|
          |0        0       0       1|

          |1    0   0   -10|
    Tew = |0    1   0   -20|
          |0    0   1   -30|
          |0    0   0     1|

                      |0        1       0         -20|
    Lat = Rew x Tew = |0        0.53    0       -10.6|
                      |0.26     0.53    0.8     -37.2|
                      |0        0       0           1|


    A MATRIZ MODELVIEW É UTILIZADA PARA MAPEAR OS OBJETOS DA CENA
    COM AS COORDENADAS DA CAMERA, ELA É DADA POR:

    Mview = Lat x Mobj

    ONDE Mobj É A MATRIZ RESULTANTE DE TODAS AS TRANSFORMAÇÕES NO SRU

             |-0.95    0      -0.32         0|
    Mview =  |-0.17    0.85    0.51         0|
             |0.27     0.53   -0.8     -37.42|
             |0        0       0            1|
    */

    glPushMatrix();
    //UM TRANSLATE PARA DESENHAR O CHÃO
    //O CHÃO DEVE FICAR ABAIXO DO ROBO
        glTranslatef(0.0, -1.42*TAM_PERNA, 0.0);
        /*
            |1  0   0        0|
        T = |0  1   0   -19.88|
            |0  0   1        0|
            |0  0   0        1|
        */
        DesenhaChao(); //DESENHA O CHÃO
    glPopMatrix();

    Desenha_Modelo(); //DESENHA O ROBO
    glutSwapBuffers(); //TROCA O BUFFER
}


//CALLBACK DOS EVENTOS DE TECLADO
//AS FUNÇÕES ESTÃO DETALHADAS NO ARQUIVO MOVIMENTOS.H
void teclado(unsigned char key, int x, int y)
{

    switch(key)
    {
        case TAB: //ALTERA ENTRE MODO ANDAR E GESTICULAR E RESETA O MODELO
            if(modo == GESTICULAR)
            {
                ResetaModelo();
                modo = ANDAR;
            }

            else
            {
                ResetaModelo();
                modo = GESTICULAR;
            }
            break;
        case ESC: //SAI DO PROGRAMA
            exit(0);
            break;
        case 'Q': case 'q': //SELECIONA MEMBRO ESQUERDO
            lado_gest = ESQUERDO;
            break;
        case 'E': case 'e': //SELECIONA MEMBRO DIREITO
            lado_gest = DIREITO;
            break;
        case 'C': case 'c': //SELECIONA A CABEÇA
            membro = CABECA;
            break;
        case 'B': case 'b': //SELECIONA O BRAÇO
            membro = BRACO;
            break;
        case 'P': case 'p': //SELECIONA A PERNA
            membro = PERNA;
            break;
        case 'R': case 'r':
            membro = CORPO;
            break;
        default: //CHAMA AS FUNÇÕES PARA MOVIMENTAR OS MEMBROS OU O ROBO
            if(modo == GESTICULAR)
                switch(membro)
                {
                    case CABECA:
                        moveCabeca(key);
                        break;
                    case BRACO:
                        moveBraco(key);
                        break;
                    case PERNA:
                        movePerna(key);
                        break;
                    case CORPO:
                        giraRobo(key);
                        break;
                }
            else
                andar(key);
    }
}

//FUNÇÃO PARA UTILIZAR AS SETAS
//FUNÇÕES DETALHADAS NO ARQUIVO MOVIMENTOS.H
//AS SETAS SÃO UTILIZADS PARA MOVER A PARTE DE CIMA DOS BRAÇOS E PERNAS
void teclasEspeciais(int key, int x, int y)
{
    if(modo == GESTICULAR)
        switch(membro)
        {
            case BRACO:
                teclasEspeciaisBraco(key);
                break;
            case PERNA:
                teclasEspeciaisPernas(key);
                break;
        }
}

//MANTÉM A CENA ATUALIZADA
void update(void)
{
    glutPostRedisplay();
}

//MENU DAS TECLAS
void imprimeMenu(void)
{
    printf("MAPEAMENTO DE TECLAS:\n\n");

    printf("ESC - SAIR\nTAB - GESTICULAR/ANDAR/RESETAR\nQ - MOVE MEMBRO ESQUERDO\nE - MOVE MEMBRO DIREITO\n\n");

    printf("MODO GESTICULAR:\n\n");
    printf("R - GIRAR ROBO:\n");
    printf("A - GIRAR P/ ESQUERDA\tD - GIRAR P/ DIREITA\n\n");

    printf("C - MOVER CABECA:\n");
    printf("W - OLHAR CIMA\t\tA - OLHAR ESQUERDA\nS - OLHAR BAIXO\t\tD - OLHAR DIREITA\n\n");

    printf("B - MOVER BRACO:\n");
    printf("W - ERGUER ANTEBRACO\tS - ABAIXAR ANTEBRACO\n");
    printf("CIMA - ERGUER BRACO\tESQUERDA - ABRIR/FECHAR BRACO\nBAIXO - ABAIXAR BRACO\tDIREITA - ABRIR/FECHAR BRACO\n\n");

    printf("P - MOVER PERNAS:\n");
    printf("W - ESTICAR JOELHO\tS - DOBRAR JOELHO\n");
    printf("CIMA - ERGUER PERNA\tBAIXO - ABAIXAR PERNA\n\n");

    printf("MODO ANDAR:\n\n");
    printf("W(SEGURAR) - ANDAR P/ FRENTE\n");
    printf("S(SEGURAR) - ANDAR P/ TRAS");
}

//FUNÇÃO MAIN
int main(int argc, char** argv)
{
    imprimeMenu();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Robo humanoide");

    //CONFIGURANDO CALLBACKS
    glutReshapeFunc(Resize);
    glutIdleFunc(update);
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclasEspeciais);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
