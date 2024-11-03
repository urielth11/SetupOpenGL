#include <GLFW/glfw3.h>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

//Función para configurar e inicializar el entorno de OpenGL
//para sólidos
bool inicializarOpenGL() {
    //prepara el entorno para el trazado y la visualización de un sólido
    glEnable(GL_DEPTH_TEST); //habilitar el test de profunidad
    //glEnable(GL_LIGHTING); //habilitar la iluminación
    //glEnable(GL_LIGHT0); //habilitar la luz 0
    glEnable(GL_COLOR_MATERIAL); //habilitar colores de materiales

    //Configurar la luz difusa
    GLfloat luzDifusa[] = { 1.0f,1.0f,1.0f,1.0f }; //luz blanca
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa); //aplicar luz de difusa

    //Posicionar la luz en el espacio
    GLfloat posicionLuz[] = { 1.0f,1.0f,1.0f,0.0f };
    //glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz); //Aplicar posición de la luz

    return true;
}

void dibujarCuadradoEnZ(int x0, int y0, int z0) {
    float x = (float)x0 / 10;
    float y = (float)y0 / 10;
    float z = (float)z0 / 10;

    glVertex3f(x, y+x, z);
    glVertex3f(-x, y+x, z);
    glVertex3f(-x, y-x, z);
    glVertex3f(x, y-x, z);
}

void dibujarCuadradoEnX(int x0, int y0, int z0) {
    float x = (float)x0 / 10;
    float y = (float)y0 / 10;
    float z = (float)z0 / 10;

    glVertex3f(x, y-x, z-x);
    glVertex3f(x, y-x, z+x);
    glVertex3f(x, y+x, z+x);
    glVertex3f(x, y+x, z-x);
}

void dibujarCuadradoEnY(int x0, int y0, int z0) {
    float x = (float)x0 / 10;
    float y = (float)y0 / 10;
    float z = (float)z0 / 10;

    glVertex3f(-x, y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, y, z);
    glVertex3f(-x, y, z);
}


void dibujarFalange1(int t) {

    glBegin(GL_QUADS); // Inicia la definición de un conjunto de polígonos de 4 vértices (cuadrados)
    // Definir cada cara del cubo con su color y vértices

    glColor3f(0.5f, 0.0f, 0.0f); //Color rojo 

    dibujarCuadradoEnZ(t, 0, t); //Cara frontal
    dibujarCuadradoEnZ(t, 0, -t);//Cara trasera
    dibujarCuadradoEnX(t, 0, 0);//Cara derecha
    dibujarCuadradoEnX(-t, 0, 0);//Cara izquierda
    dibujarCuadradoEnY(t, -t, t);//Cara inferior
    dibujarCuadradoEnY(t, t, t);//Cara superior

    glEnd(); // Termina la definición del cubo
}

void dibujarFalange2(int t) {

    glBegin(GL_QUADS); // Inicia la definición de un conjunto de polígonos de 4 vértices (cuadrados)
    // Definir cada cara del cubo con su color y vértices

    glColor3f(0.0f, 1.0f, 0.0f); // Color verde 

    dibujarCuadradoEnZ(t, t*2, t); //Cara frontal
    dibujarCuadradoEnZ(t, t * 2, -t);//Cara trasera
    dibujarCuadradoEnX(t, t * 2, 0);//Cara derecha
    dibujarCuadradoEnX(-t, t * 2, 0);//Cara izquierda
    dibujarCuadradoEnY(t, t * 2, t);//Cara inferior
    dibujarCuadradoEnY(t, t * 3, t);//Cara superior

    glEnd(); // Termina la definición del cubo
}

void dibujarFalange3(int t) {

    glBegin(GL_QUADS); // Inicia la definición de un conjunto de polígonos de 4 vértices (cuadrados)
    // Definir cada cara del cubo con su color y vértices

    glColor3f(0.0f, 0.0f, 1.0f); // Color azul Cara izquierda // Color verde Cara trasera
    
    dibujarCuadradoEnZ(t, t * 4, t); //Cara frontal
    dibujarCuadradoEnZ(t, t * 4, -t);//Cara trasera
    dibujarCuadradoEnX(t, t * 4, 0);//Cara derecha
    dibujarCuadradoEnX(-t, t * 4, 0);//Cara izquierda
    dibujarCuadradoEnY(t, t * 4, t);//Cara inferior
    dibujarCuadradoEnY(t, t * 5, t);//Cara superior

    glEnd(); // Termina la definición del cubo
}


int main() {
    if (!glfwInit()) {
        return -1;
    }

    // Crear la ventana GLFW
    GLFWwindow* window = glfwCreateWindow(640, 480, "Cubo 3D Estático", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Establecer el contexto OpenGL
    glfwMakeContextCurrent(window);

    //Inicializar OpenGL
    inicializarOpenGL();

    //Configurar su visualización, proyección en perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float fov = 45.0f;
    float aspect = 640.0f / 480.0f;
    float nearClip = 0.1f;
    float farClip = 10.0f;
    float top = tan(fov * 3.1416 / 360.0) * nearClip;
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    glFrustum(left, right, bottom, top, nearClip, farClip);

    float rotacion1 = 0.0f;
    float rotacion2 = 0.0f;
    float rotacion3 = 0.0f;

    //Bucle de renderizado
    while (!glfwWindowShouldClose(window)) {
        //Limpiar la pantalla y el buffer de profundidad
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //Aplicar las transformaciones de visualización al cubo
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();//Reseteamos la matriz de modelo-vista
        glTranslatef(0.0f, 0.0f, -3.0f); //Alejar la cámara

        glPushMatrix();// Guardar la matriz actual
        glRotatef(rotacion1, 1.0f, 0.0f, 0.0f); //rotar el cubo para una mejor visualizaciòn
        dibujarFalange1(2);//Dibujamos el cubo
        glPopMatrix();// Restaurar la matriz anterior para que otros objetos no se roten
        
        glPushMatrix();// Guardar la matriz actual
        glRotatef(rotacion2, 1.0f, 0.0f, 0.0f); //rotar el cubo para una mejor visualizaciòn
        dibujarFalange2(2);//Dibujamos el cubo
        glPopMatrix();// Restaurar la matriz anterior para que otros objetos no se roten

        glPushMatrix();// Guardar la matriz actual
        glRotatef(rotacion3, 1.0f, 0.0f, 0.0f); //rotar el cubo para una mejor visualizaciòn
        dibujarFalange3(2);//Dibujamos el cubo
        glPopMatrix();// Restaurar la matriz anterior para que otros objetos no se roten

        // Intercambiar buffers y actualizar eventos
        // Comprobar si la tecla espacio está presionada
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            rotacion1 += 0.005f;
            rotacion2 += 0.006f;
            rotacion3 += 0.007f;
            //anguloRotacion += 90.0f;  // Aumentar el ángulo de rotación
            if (rotacion1 >= 100.0f) {  // Resetear si supera 360 grados
                rotacion1 = 0;
                rotacion2 = 0;
                rotacion3 = 0;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            rotacion1 -= 0.005f;
            rotacion2 -= 0.006f;
            rotacion3 -= 0.007f;
            //anguloRotacion += 90.0f;  // Aumentar el ángulo de rotación
            if (rotacion1 <= 0.0f) {  // Resetear si supera 360 grados
                rotacion1 = 0;
                rotacion2 = 0;
                rotacion3 = 0;
            }
        }
        
        /*if (anguloRotacion >= 360.0f) {
            anguloRotacion = 0.0f;
        }*/

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // Terminar GLFW
    glfwTerminate();
    return 0;
}