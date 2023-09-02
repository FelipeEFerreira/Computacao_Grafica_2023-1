#ifndef MOVIMENTOS_H_INCLUDED
#define MOVIMENTOS_H_INCLUDED

//TECLAS
#define ESC 27
#define TAB 9

//CONSTANTES DE MOVIMENTAÇÃO
#define X 0
#define Y 1
#define Z 2
#define ESQUERDO 0
#define DIREITO 1
#define FRENTE 1
#define TRAS 0

//SELEÇÃO DE MEMBROS E MODOS
#define ANDAR -1
#define  GESTICULAR 0
#define CABECA 1
#define BRACO 2
#define PERNA 3
#define CORPO 4

#endif // MOVIMENTOS_H_INCLUDED


//OS COMENTÁRIOS NA FRENTE INDICA O EIXO NO QUAL OCORRE A ROTAÇÃO
//ROTAÇÔES DOS MEMBROS
GLfloat rot_cabeca[3] = {0.0f, 0.0f, 0.0f}; //X e Y
GLfloat d_rot_brac_cima[3] = {0.0f, 0.0f, 0.0f}; //X e Z
GLfloat d_rot_brac_baixo[3] = {0.0f, 0.0f, 0.0f}; //X e Z
GLfloat e_rot_brac_cima[3] = {0.0f, 0.0f, 0.0f}; //X e Z
GLfloat e_rot_brac_baixo[3] = {0.0f, 0.0f, 0.0f}; //X e Z
GLfloat d_rot_perna_cima = 0.0f; //X
GLfloat d_rot_perna_baixo = 0.0f; //X
GLfloat e_rot_perna_cima = 0.0f; //X
GLfloat e_rot_perna_baixo = 0.0f; //X

//MOVIMENTAÇÂO DO CORPO
GLfloat base_rot = 0.0; //Y
GLfloat base_mov[3] = {0.0f, 0.0f, 0.0f}; //Y e Z

//MODO, LADOS e MEMBRO
int lado_mov = ESQUERDO;
int direcao_mov = FRENTE;
int lado_gest = ESQUERDO;
int membro = BRACO;
int modo = GESTICULAR;

//RESETA A POSIÇÃO DOS MEMBROS QUANDO ALTERAR ENTRE MODO ANDAR E GESTICULAR
void ResetaModelo(void)
{
    for(int i = 0; i < 3; i++)
    {
        rot_cabeca[i] = 0.0f;
        d_rot_brac_cima[i] = 0.0f;
        d_rot_brac_baixo[i] = 0.0f;
        e_rot_brac_cima[i] = 0.0f;
        e_rot_brac_baixo[i] = 0.0f;
        base_mov[i] = 0.0f;
    }
    base_rot = 0.0f;
    d_rot_perna_cima = 0.0f;
    d_rot_perna_baixo = 0.0f;
    e_rot_perna_cima = 0.0f;
    e_rot_perna_baixo = 0.0f;
    direcao_mov = FRENTE;
}

//O RESTANTE É BEM INTUITIVO, SENDO APENAS ALTERAÇÕES DE VARIAVEIS
//AS FUNÇÕES ABAIXO SÃO UTILIZADAS NA CALLBACK DE TECLADO

void moveCabeca(unsigned char key)
{
    switch(key)
    {
    //MOVE A CABEÇA
        case 'W': case 'w':
            if(rot_cabeca[X] >= -60.0f)
                rot_cabeca[X] -= 10.0f;
            break;
        case 'S': case 's':
            if(rot_cabeca[X] <= 60.0f)
                rot_cabeca[X] += 10.0f;
            break;
        case 'A': case 'a':
            if(rot_cabeca[Y] <= 90.0f)
                rot_cabeca[Y] += 10.0f;
            break;
        case 'D': case 'd':
            if(rot_cabeca[Y] >= -90.0f)
                rot_cabeca[Y] -=10.0f;
            break;
    }
}

void moveBraco(unsigned char key)
{
    switch(key)
    {
    //MOVE OS BRAÇOS
        case 'W': case 'w':
            if(lado_gest == ESQUERDO){
                if(e_rot_brac_baixo[X] >= -120.0f)
                    e_rot_brac_baixo[X] -= 10.0f;
            }else
                if(d_rot_brac_baixo[X] >= -120.0f)
                    d_rot_brac_baixo[X] -= 10.0f;
            break;
        case 'S': case 's':
            if(lado_gest == ESQUERDO){
                if(e_rot_brac_baixo[X] < 0.0f)
                    e_rot_brac_baixo[X] += 10.0f;
            }else
                if(d_rot_brac_baixo[X] < 0.0f)
                    d_rot_brac_baixo[X] += 10.0f;
            break;
    }
}

void teclasEspeciaisBraco(int key)
{
    switch(key)
    {
    //MOVE BRACO CIMA
        case GLUT_KEY_UP:
            if(lado_gest == ESQUERDO){
                if(e_rot_brac_cima[Z] == 0){
                    if(e_rot_brac_cima[X] >= -180.0f)
                        e_rot_brac_cima[X] -= 10.0f;
                }else
                    if(e_rot_brac_cima[X] >= -90.0)
                        e_rot_brac_cima[X] -= 10.0f;
            }else
                if(d_rot_brac_cima[Z] == 0){
                    if(d_rot_brac_cima[X] >= -180.0f)
                        d_rot_brac_cima[X] -= 10.0f;
                }else{
                    if(d_rot_brac_cima[X] >= -90.0)
                        d_rot_brac_cima[X] -= 10.0f;
                }
            break;

        case GLUT_KEY_DOWN:
            if(lado_gest == ESQUERDO){
                if(e_rot_brac_cima[X] < 0.0f)
                    e_rot_brac_cima[X] += 10.0f;
            }else
                if(d_rot_brac_cima[X] < 0.0f)
                    d_rot_brac_cima[X] += 10.0f;
            break;

        case GLUT_KEY_LEFT:
            if(lado_gest == ESQUERDO){
                if(e_rot_brac_cima[Z] > 0)
                    e_rot_brac_cima[Z] -= 10.0f;
            }else{
                if(d_rot_brac_cima[X] < -90)
                    break;
                if(d_rot_brac_cima[Z] >= -90.0f)
                    d_rot_brac_cima[Z] -= 10.0f;
            }
            break;

        case GLUT_KEY_RIGHT:
            if(lado_gest == ESQUERDO){
                if(e_rot_brac_cima[X] < -90)
                    break;
                if(e_rot_brac_cima[Z] <= 90.0f)
                    e_rot_brac_cima[Z] += 10.0f;
            }else
                if(d_rot_brac_cima[Z] < 0)
                    d_rot_brac_cima[Z] += 10.0f;
            break;
    }
}

void movePerna(unsigned char key)
{
    switch(key)
    {
    //MOVE AS PERNAS
        case 'W': case 'w':
            if(lado_gest == ESQUERDO){
                if(e_rot_perna_baixo > 0.0f)
                    e_rot_perna_baixo -= 10.0f;
            }else
                if(d_rot_perna_baixo > 0.0f)
                    d_rot_perna_baixo -= 10.0f;
            break;
        case 'S': case 's':
            if(lado_gest == ESQUERDO){
                if(e_rot_perna_baixo <= 90.0f)
                    e_rot_perna_baixo += 10.0f;
            }else
                if(d_rot_perna_baixo <= 90.0f)
                    d_rot_perna_baixo += 10.0f;
            break;
    }
}

void teclasEspeciaisPernas(int key)
{
    switch(key)
    {
    //MOVE BRACO CIMA
        case GLUT_KEY_UP:
            if(lado_gest == ESQUERDO){
                if(e_rot_perna_cima >= -90.0)
                        e_rot_perna_cima -= 10.0f;
            }else
                if(d_rot_perna_cima >= -90.0)
                        d_rot_perna_cima -= 10.0f;
            break;

        case GLUT_KEY_DOWN:
            if(lado_gest == ESQUERDO){
                if(e_rot_perna_cima < 0.0f)
                    e_rot_perna_cima += 10.0f;
            }else
                if(d_rot_perna_cima < 0.0f)
                    d_rot_perna_cima += 10.0f;
            break;
    }
}

void giraRobo(unsigned char key)
{
    switch(key)
    {
       case 'A':case 'a':
           base_rot += 10.0f;
           break;
       case 'D':case 'd':
            base_rot -= 10.0f;
    }
}
void andar(unsigned char key)
{
    switch(key)
    {
    //MOVE O BONECO
        case 'W': case 'w':
            if(direcao_mov == TRAS)
            {
                base_rot -= 180;
                direcao_mov = FRENTE;
            }
            if(base_mov[Y] < 0.0f)
                base_mov[Y] += 0.1;
            else
                base_mov[Y] -= 0.1;
            if(base_mov[Z] < 60.0f)
                base_mov[Z] += 0.5; //VELOCIDADE DO ROBO
            if(lado_mov == ESQUERDO)
            {
                if(e_rot_perna_cima > -20.0f)
                {
                    e_rot_perna_cima -= 10.0f;
                    d_rot_perna_cima += 10.0f;
                    d_rot_brac_cima[X] -= 5.0f;
                    e_rot_brac_cima[X] += 5.0f;
                    if(d_rot_perna_baixo <= 0)
                    {
                        d_rot_perna_baixo += 10.0f;
                        e_rot_perna_baixo += 10.0f;
                    }
                }
                else
                    lado_mov = DIREITO;
            }
            else
            {
                if(d_rot_perna_cima > -20.0f)
                {
                    d_rot_perna_cima -= 10.0f;
                    e_rot_perna_cima += 10.0f;
                    d_rot_brac_cima[X] += 5.0f;
                    e_rot_brac_cima[X] -= 5.0f;
                    if(d_rot_perna_baixo > 0)
                    {
                        d_rot_perna_baixo -= 10.0f;
                        e_rot_perna_baixo -= 10.0f;
                    }
                }
                else
                    lado_mov = ESQUERDO;
            }
            break;

        case 'S':case 's':
            if(direcao_mov == FRENTE)
            {
                base_rot -= 180;
                direcao_mov = TRAS;
            }
            if(base_mov[Y] < 0.0f)
                base_mov[Y] += 0.1;
            else
                base_mov[Y] -= 0.1;
            if(base_mov[Z] > -30.0f)
                base_mov[Z] -= 0.5; //VELOCIDADE DO ROBO
            if(lado_mov == ESQUERDO)
            {
                if(e_rot_perna_cima > -20.0f)
                {
                    e_rot_perna_cima -= 10.0f;
                    d_rot_perna_cima += 10.0f;
                    d_rot_brac_cima[X] -= 5.0f;
                    e_rot_brac_cima[X] += 5.0f;
                    if(d_rot_perna_baixo <= 0)
                    {
                        d_rot_perna_baixo += 10.0f;
                        e_rot_perna_baixo += 10.0f;
                    }
                }
                else
                    lado_mov = DIREITO;
            }
            else
            {
                if(d_rot_perna_cima > -20.0f)
                {
                    d_rot_perna_cima -= 10.0f;
                    e_rot_perna_cima += 10.0f;
                    d_rot_brac_cima[X] += 5.0f;
                    e_rot_brac_cima[X] -= 5.0f;
                    if(d_rot_perna_baixo > 0)
                    {
                        d_rot_perna_baixo -= 10.0f;
                        e_rot_perna_baixo -= 10.0f;
                    }
                }
                else
                    lado_mov = ESQUERDO;
            }
            break;
    }
}
