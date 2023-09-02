#ifndef MODELOS_H_INCLUDED
#define MODELOS_H_INCLUDED

//MEDIDAS CABEÇA
#define CABECA_H 2
#define CABECA_W 2
#define NARIZ_H 0.3
#define NARIZ_W 0.1
#define OLHO 0.2

//MEDIDAS TORSO
#define TORSO_H 8
#define TORSO_W 4

//MEDIDAS BRAÇO
#define CIMA_BRACO_H 3
#define BAIXO_BRACO_H 4
#define BRACO_W 1.5

//MEDIDAS CINTURA
#define BASE_H 1
#define BASE_W 4

//MEDIDAS PERNA
#define PERNA_H 6
#define PERNA_W 2

//MEDIADS JUNTAS
#define JUNTAS 1
#define JUNTA_MENOR 0.5

//TAMANHOS
#define TAM_PERNA 2*PERNA_H+2*JUNTAS

#endif // MODELOS_H_INCLUDED

#include "movimentos.h"
/*
**************************
*   ALGUMAS INFORMAÇÕES  *
**************************

              CABEÇA
                |
        _________________
        |       |       |
    BRAÇO     TORSO    BRAÇO
       |        |       |
  ANTEBRAÇO     |      ANTEBRAÇO
               BASE
                |
        ___________________
        |                  |
    PERNA_CIMA         PERNA_CIMA
        |                  |
    PERNA_BAIXO        PERNA_BAIXO
*/


/*
*****************************************************
*   FUNÇÕES PARA DESENHAR A PARTE DE BAIXO DO ROBO  *
*****************************************************
*/
//ESSA FUNÇÃO DESENHA A BASE(CINTURA) DO ROBO
void Desenha_Base(void)
{
    glPushMatrix();
        glScalef(BASE_W, BASE_H, BASE_W);
        /*
            |4  0   0   0|
        S = |0  1   0   0|
            |0  0   4   0|
            |0  0   0   1|
        */
        glColor3f(0.0, 0.0, 1.0); //AZUL
        glutSolidCube(1.0);
    glPopMatrix();
}

//DENHA A PARTE DE CIMA DA PERNA
void Desenha_Perna_Cima(const int d_lado)
{
    glPushMatrix();

        glScalef(JUNTAS, JUNTAS, JUNTAS);
        /*
            |1  0   0   0|
        S = |0  1   0   0|
            |0  0   1   0|
            |0  0   0   1|
        */
        glColor3f(0.0, 1.0, 0.0); //VERDE
        glutSolidSphere(1.0 , 8, 8);

        if(d_lado == ESQUERDO)
            glRotatef(e_rot_perna_cima, 1.0, 0.0, 0.0);
        else
            glRotatef(d_rot_perna_cima, 1.0, 0.0, 0.0);
        /*
            |1  0           0           0|
        R = |0  COS(ROT)   -SIN(ROT)    0|
            |0  SIN(ROT)    COS(ROT)    0|
            |0  0           0           1|
        */

        glTranslatef(0.0, -(PERNA_H * 0.65), 0.0);
        /*
            |1  0   0      0|
        T = |0  1   0   -3.9|
            |0  0   1      0|
            |0  0   0      1|
        */

        glScalef(PERNA_W, PERNA_H, PERNA_W);
        /*
            |2  0   0   0|
        S = |0  6   0   0|
            |0  0   2   0|
            |0  0   0   1|
        */
        glColor3f(0.0, 0.0, 1.0); //AZUL
        glutSolidCube(1.0);
    glPopMatrix();
}

//DESENHA A PARTE DE BAIXO DA PERNA
void Desenha_Perna_Baixo(const int d_lado)
{
    glPushMatrix();

        glScalef(JUNTAS, JUNTAS, JUNTAS);
        /*
            |1  0   0   0|
        S = |0  1   0   0|
            |0  0   1   0|
            |0  0   0   1|
        */
        glColor3f(0.0, 1.0, 0.0); //VERDE
        glutSolidSphere(1.0, 8, 8);

        if(d_lado == ESQUERDO)
            glRotatef(e_rot_perna_baixo, 1.0, 0.0, 0.0);
        else
            glRotatef(d_rot_perna_baixo, 1.0, 0.0, 0.0);
        /*
            |1  0           0           0|
        R = |0  COS(ROT)   -SIN(ROT)    0|
            |0  SIN(ROT)    COS(ROT)    0|
            |0  0           0           1|
        */

        glTranslatef(0.0, -(PERNA_H * 0.65), 0.0);
        /*
            |1  0   0      0|
        T = |0  1   0   -3.9|
            |0  0   1      0|
            |0  0   0      1|
        */

        glScalef(PERNA_W, PERNA_H, PERNA_W);
        /*
            |2  0   0   0|
        S = |0  6   0   0|
            |0  0   2   0|
            |0  0   0   1|
        */
        glColor3f(0.0, 0.0, 1.0); //AZUL
        glutSolidCube(1.0);
    glPopMatrix();
}

//DESENHA A PERNA INTEIRA
void Desenha_Perna(const int d_lado)
{
    glPushMatrix();
        Desenha_Perna_Cima(d_lado);

        if(d_lado == ESQUERDO)
            glRotatef(e_rot_perna_cima, 1.0, 0.0, 0.0);
        else
            glRotatef(d_rot_perna_cima, 1.0, 0.0, 0.0);
        /*
            |1  0           0           0|
        R = |0  COS(ROT)   -SIN(ROT)    0|
            |0  SIN(ROT)    COS(ROT)    0|
            |0  0           0           1|
        */

        glTranslatef(0.0, -(PERNA_H + JUNTAS), 0.0);
        /*
            |1  0   0    0|
        T = |0  1   0   -7|
            |0  0   1    0|
            |0  0   0    1|
        */

        Desenha_Perna_Baixo(d_lado);
    glPopMatrix();
}

//DESENHA TODA A PARTE DE BAIXO DO ROBO (CINTURA + PERNAS)
void Desenha_Inferior(void)
{
    glPushMatrix();
        Desenha_Base();
        glTranslatef(0.0, -BASE_H, 0.0);
        /*
            |1  0   0    0|
        T = |0  1   0   -1|
            |0  0   1    0|
            |0  0   0    1|
        */
        glPushMatrix();
            glTranslatef((BASE_W* 0.33), 0.0, 0.0);
            /*
                |1  0   0   1.32|
            T = |0  1   0      0|
                |0  0   1      0|
                |0  0   0      1|
            */
            Desenha_Perna(ESQUERDO);
        glPopMatrix();
            glTranslatef(-(BASE_W* 0.33), 0.0, 0.0);
            /*
                |1  0   0   -1.32|
            T = |0  1   0       0|
                |0  0   1       0|
                |0  0   0       1|
            */
            Desenha_Perna(DIREITO);
    glPopMatrix();
}

/*
*****************************************************
*   FUNÇÕES PARA DESENHAR A PARTE DE CIMA DO ROBO   *
*****************************************************
*/

//DESENHA O TORSO DO ROBO
void Desenha_Torso(void)
{
    glPushMatrix();
        glScalef(TORSO_W, TORSO_H, TORSO_W);
        /*
            |4  0   0   0|
        S = |0  8   0   0|
            |0  0   4   0|
            |0  0   0   1|
        */

        glColor3f(1.0, 0.0, 0.0); //VERMELHO
        glutSolidCube(1.0);
    glPopMatrix();
}

//DESENHA A CABEÇA DO ROBO (CABEÇA + OLHOS + NARIZ)
void Desenha_cabeca(void)
{
    glPushMatrix();
        glScalef(JUNTA_MENOR, JUNTA_MENOR, JUNTA_MENOR);
        /*
            |0.5   0      0   0|
        S = |0    0.5     0   0|
            |0     0     0.5  0|
            |0     0      0   1|
        */
        glColor3f(0.0, 1.0, 0.0); //VERDE
        glutSolidSphere(1.0, 8, 8);
    glPopMatrix();

    glPushMatrix();
        glRotatef(rot_cabeca[X], 1.0, 0.0, 0.0);
        glRotatef(rot_cabeca[Y], 0.0, 1.0, 0.0);

        /*
             |1  0           0           0|
        Rx = |0  COS(ROT)   -SIN(ROT)    0|
             |0  SIN(ROT)    COS(ROT)    0|
             |0  0           0           1|
        -----------------------------------
             |1  COS(ROT)     SIN(ROT)   0|
        Ry = |0     1           0        0|
             |0  -SIN(ROT)    COS(ROT)   0|
             |0     0           0        1|
        */

        glTranslatef(0.0, (CABECA_H*0.65), 0.0);
        /*
            |1  0   0     0|
        T = |0  1   0   1.3|
            |0  0   1     0|
            |0  0   0     1|
        */
        glScalef(CABECA_W, CABECA_H, CABECA_W);
        /*
            |2  0   0   0|
        S = |0  2   0   0|
            |0  0   2   0|
            |0  0   0   1|
        */
        glColor3f(1.0, 1.0, 0.0); //AMARELO
        glutSolidCube(1.0);

        glPushMatrix();
            glTranslatef(0.0, 0.0, 0.3*CABECA_W);
            /*
                |1  0   0      0|
            T = |0  1   0      0|
                |0  0   1    0.6|
                |0  0   0      1|
            */
            glScalef(NARIZ_W, NARIZ_H, NARIZ_W);
            /*
                |0.1   0      0   0|
            S = |0    0.3     0   0|
                |0     0     0.1  0|
                |0     0      0   1|
            */
            glColor3f(1.0, 0.0, 0.0); //VERMELHO
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.15*CABECA_W, 0.15* CABECA_H, 0.3*CABECA_W);
            /*
                |1  0   0   0.3|
            T = |0  1   0   0.3|
                |0  0   1   0.6|
                |0  0   0     1|
            */
            glScalef(OLHO, OLHO, 0.0);
            /*
                |0.2   0      0   0|
            S = |0    0.2     0   0|
                |0     0     0.2  0|
                |0     0      0   1|
            */
            glColor3f(0.0, 0.0, 0.0); //PRETO
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-(0.15*CABECA_W), 0.15* CABECA_H, 0.3*CABECA_W);
            /*
                |1  0   0   -0.3|
            T = |0  1   0    0.3|
                |0  0   1    0.6|
                |0  0   0      1|
            */
            glScalef(OLHO, OLHO, 0.0);
            /*
                |0.2   0      0   0|
            S = |0    0.2     0   0|
                |0     0     0.2  0|
                |0     0      0   1|
            */
            glColor3f(0.0, 0.0, 0.0); //PRETO
            glutSolidCube(1.0);
        glPopMatrix();

    glPopMatrix();
}

//DESENHA A PARTE DE CIMA DO BRAÇO
void Desenha_Braco_Cima(const int d_lado)
{
    glPushMatrix();
        glScalef(JUNTAS, JUNTAS, JUNTAS);
        /*
            |1  0   0   0|
        S = |0  1   0   0|
            |0  0   1   0|
            |0  0   0   1|
        */
        glColor3f(0.0, 1.0, 0.0); //VERDE
        glutSolidSphere(1.0, 8, 8);
    glPopMatrix();
    glPushMatrix();

        if(d_lado == ESQUERDO)
        {
            glRotatef(e_rot_brac_cima[X], 1.0, 0.0, 0.0);
            glRotatef(e_rot_brac_cima[Z], 0.0, 0.0, 1.0);
            glTranslatef(0.15, 0.0, 0.0);
        }
        else
        {
            glRotatef(d_rot_brac_cima[X], 1.0, 0.0, 0.0);
            glRotatef(d_rot_brac_cima[Z], 0.0, 0.0, 1.0);

            glTranslatef(-0.15, 0.0, 0.0);
        }
        /*
             |1  0           0           0|
        Rx = |0  COS(ROT)   -SIN(ROT)    0|
             |0  SIN(ROT)    COS(ROT)    0|
             |0  0           0           1|
        -----------------------------------
             |COS(ROT)  -SIN(ROT)   0    0|
        Rz = |SIN(ROT)   COS(ROT)   0    0|
             |0            0        1    0|
             |0            0        0    1|

            |1  0   0   0.15|              |1  0   0   -0.15|
        T = |0  1   0      0|          T = |0  1   0       0|
            |0  0   1      0|    OU        |0  0   1       0|
            |0  0   0      1|              |0  0   0       1|

        O TRANSLATE É PARA O BRAÇO NÃO FICAR COLADO NO TORSO
        */
        glTranslatef(0.0, -(CIMA_BRACO_H * 0.75), 0.0);
        /*
            |1  0   0        0|
        T = |0  1   0    -2.25|
            |0  0   1        0|
            |0  0   0        1|
        */
        glScalef(BRACO_W, CIMA_BRACO_H, BRACO_W);
        /*
            |1.5  0    0   0|
        S = |0    3    0   0|
            |0    0   1.5  0|
            |0    0    0   1|
        */
        glColor3f(0.0, 1.0, 1.0); //CIANO
        glutSolidCube(1.0);
    glPopMatrix();
}

//DESENHA A PARTE DE BAIXO DO BRAÇO
void Desenha_Braco_Baixo(const int d_lado)
{
    glPushMatrix();
        if(d_lado == ESQUERDO)
            glTranslatef(0.20, 0.0, 0.0);
        else
            glTranslatef(-0.20, 0.0, 0.0);
        /*
            |1  0   0    0.2|              |1  0   0   -0.2|
        T = |0  1   0      0|          T = |0  1   0      0|
            |0  0   1      0|    OU        |0  0   1      0|
            |0  0   0      1|              |0  0   0      1|
        */
        glScalef(JUNTAS, JUNTAS, JUNTAS);
        /*
            |1  0   0   0|
        S = |0  1   0   0|
            |0  0   1   0|
            |0  0   0   1|
        */
        glColor3f(0.0, 1.0, 0.0); //VERDE
        glutSolidSphere(1.0, 8, 8);
    glPopMatrix();

    glPushMatrix();

        if(d_lado == ESQUERDO)
        {
            glRotatef(e_rot_brac_baixo[X], 1.0, 0.0, 0.0);
            glTranslatef(0.15, 0.0, 0.0);
        }
        else
        {
            glRotatef(d_rot_brac_baixo[X], 1.0, 0.0, 0.0);
            glTranslatef(-0.15, 0.0, 0.0);
        }
        /*
             |1  0           0           0|
        Rx = |0  COS(ROT)   -SIN(ROT)    0|
             |0  SIN(ROT)    COS(ROT)    0|
             |0  0           0           1|

            |1  0   0   0.15|              |1  0   0   -0.15|
        T = |0  1   0      0|          T = |0  1   0       0|
            |0  0   1      0|    OU        |0  0   1       0|
            |0  0   0      1|              |0  0   0       1|

        O TRANSLATE É PARA O BRAÇO NÃO FICAR COLADO NO TORSO
        */

        glTranslatef(0.0, -(BAIXO_BRACO_H * 0.65), 0.0);
        /*
            |1  0   0       0|
        T = |0  1   0    -2.6|
            |0  0   1       0|
            |0  0   0       1|
        */

        glScalef(BRACO_W, BAIXO_BRACO_H, BRACO_W);
        /*
            |1.5  0    0   0|
        S = |0    4    0   0|
            |0    0   1.5  0|
            |0    0    0   1|
        */
        glColor3f(0.0, 1.0, 1.0); //CIANO
        glutSolidCube(1.0);
    glPopMatrix();

}

//DESENHA TODO O BRAÇO
void Desenha_braco(const int d_lado)
{
    glPushMatrix();
        Desenha_Braco_Cima(d_lado);

        //Aplica rotação de cima do braço em baixo
        if(d_lado == ESQUERDO)
        {
            glRotatef(e_rot_brac_cima[X], 1.0, 0.0, 0.0);
            glRotatef(e_rot_brac_cima[Z], 0.0, 0.0, 1.0);
        }
        else
        {
            glRotatef(d_rot_brac_cima[X], 1.0, 0.0, 0.0);
            glRotatef(d_rot_brac_cima[Z], 0.0, 0.0, 1.0);
        }
        /*
             |1  0           0           0|
        Rx = |0  COS(ROT)   -SIN(ROT)    0|
             |0  SIN(ROT)    COS(ROT)    0|
             |0  0           0           1|
        -----------------------------------
             |COS(ROT)  -SIN(ROT)   0    0|
        Rz = |SIN(ROT)   COS(ROT)   0    0|
             |0            0        1    0|
             |0            0        0    1|
        */

        glTranslatef(0.0, -(CIMA_BRACO_H*1.5), 0.0);
        /*
            |1  0   0       0|
        T = |0  1   0    -4.5|
            |0  0   1       0|
            |0  0   0       1|
        */
        Desenha_Braco_Baixo(d_lado);
    glPopMatrix();
}

//DESENHA TODA A PARTE DE CIMA DO ROBO (TORSO + BRAÇOS + CABEÇA)
void Desenha_Superior(void)
{
    glPushMatrix();
        glTranslatef(0.0, TORSO_H * 0.50, 0.0);
        /*
            |1  0   0    0|
        T = |0  1   0    4|
            |0  0   1    0|
            |0  0   0    1|
        */
        Desenha_Torso();
        glTranslatef(0.0, TORSO_H * 0.55, 0.0);
        /*
            |1  0   0      0|
        T = |0  1   0    4.4|
            |0  0   1      0|
            |0  0   0      1|
        */
        Desenha_cabeca();
        glPushMatrix();
            glTranslatef((TORSO_W*0.75), -(TORSO_H * 0.1), 0.0);
            /*
                |1  0   0   3|
            T = |0  1   0   0|
                |0  0   1   0|
                |0  0   0   1|
            */
            Desenha_braco(ESQUERDO);
        glPopMatrix();
        glTranslatef(-(TORSO_W*0.75), -(TORSO_H * 0.1), 0.0);
        /*
            |1  0   0   -3|
        T = |0  1   0    0|
            |0  0   1    0|
            |0  0   0    1|
        */
        Desenha_braco(DIREITO);
    glPopMatrix();
}


/*
*****************************************
*   FUNÇÕES PARA DESENHAR TODA A CENA   *
*****************************************
*/

//DESENHA O ROBO COMPLETO
void Desenha_Modelo(void)
{
    glPushMatrix();
        glTranslatef(0.0, base_mov[Y], base_mov[Z]);
        /*
             |1  0   0        0     |
        T =  |0  1   0    BASE_MOVEy|
             |0  0   1    BASE_MOVEz|
             |0  0   0        1     |
        */
        glRotatef(base_rot, 0.0, 1.0, 0.0);
        /*
             |1  COS(ROT)     SIN(ROT)   0|
        Ry = |0     1           0        0|
             |0  -SIN(ROT)    COS(ROT)   0|
             |0     0           0        1|
        */
        Desenha_Inferior();
        glTranslatef(0.0, BASE_H*0.5, 0.0);
        /*
            |1  0   0      0|
        T = |0  1   0    0.5|
            |0  0   1      0|
            |0  0   0      1|
        */

        Desenha_Superior();
    glPopMatrix();
}

//DESENHA O CHÃO
void DesenhaChao(void)
{
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
		glVertex3f(-100.0, 0.0, -100.0);
		glVertex3f(-100.0, 0.0, 100.0);
		glVertex3f( 100.0, 0.0, 100.0);
		glVertex3f( 100.0, 0.0, -100.0);
	glEnd();
}
